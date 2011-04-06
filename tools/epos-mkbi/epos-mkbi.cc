/*=======================================================================*/
/* MKBI.C                                                                */
// This work is licensed under the Creative Commons 
// Attribution-NonCommercial-NoDerivs License. To view a copy of this license, 
// visit http://creativecommons.org/licenses/by-nc-nd/2.0/ or send a letter to 
// Creative Commons, 559 Nathan Abbott Way, Stanford, California 94305, USA.

/*                                                                       */
/* Desc: Tool to generate an EPOS bootable image.			 */
/*                                                                       */
/* Parm: <boot image> <os image> <app1> <app2> ...	                 */
/*                                                                       */
/* Auth: Guto - Changed By Fauze                                         */
/*=======================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>

#include <system/config.h>

//GENERAL DEFINES
#define MAX_SI_LEN   512
#define MAX_BOOT_LEN 512
#define MIN_BOOT_LEN 128

typedef struct Target {
    char	  mode[16];
    char          mach[16];
    char 	  arch[16];
    unsigned int  clock;
    unsigned char word_size;
    bool 	  endianess; /* little = true - big=false */
    unsigned int  mem_base;
    unsigned int  mem_size;
    unsigned int  cpu_type;
    unsigned int  threads;
    unsigned int  tasks;
};


//FUNCTIONS PROTOTYPES
bool parse_target (char *tgt_file);
void strtolower (char *dst,const char* src);
bool add_machine_secrets(int  fd_out,unsigned int i_size );

int put_buf(int fd_out, void *buf, int size);
int put_file(int fd_out, char *file);
int pad(int fd_out, int size);
bool lil_endian();

template<typename T> void invert(T &n);
template<typename T> int put_number(int fd_out, T num);
template<typename T> bool add_boot_map (T t, int  fd_out,void * _si);

//TARGET DATA
Target TARGET;

//To access System_Info
typedef __SYS(System_Info) System_Info;
	
//MAIN
int main(int argc, char **argv)
{
    int i, fd_out;
    unsigned int  image_size,si_size;
    unsigned int  boot_size = 0;
    char          *epos_home;
    char          file[256];
    char          _si[MAX_SI_LEN];
    struct stat   file_stat;    
    bool need_SI  = true;
    System_Info   *si = (System_Info *) _si;

    //Parse ARGS
    if(argc < 2) {
	fprintf(stderr, "Usage: %s <options> <boot image> <app1> <app2> ...\n", argv[0]);
	return 1;
    }
    

    /* Say hello */
    printf("\nEPOS bootable image tool\n\n");
    
    
    /* Get EPOS environment variable */
    epos_home = getenv("EPOS");
    if(epos_home == NULL) {
	fprintf(stderr, "Error: environment variable EPOS not set!\n");
	return 1;
    }

    
    //Get the target features
    sprintf(file,"%s/tools/epos-mkbi/target.conf",epos_home);
    if(!(parse_target(file))) { 
   	fprintf(stderr, "Error: Target features file not found in <%s>\n",file);
        return(1);    
    } 

    
    /* Open destination file (rewrite) */
    fd_out = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 00644);
    if(fd_out < 0) {
	fprintf(stderr, "Error: can't create boot image file \"%s\"!\n",
		argv[1]);
	return 1;
    }

    
    /* Show Target features */
    printf("  EPOS Architecture: %s\n",TARGET.mode);
    printf("  Machine Target: %s\n",   TARGET.mach);
    printf("  Processor: %s\n",        TARGET.arch);       
    printf("  Memory Amount: %d KBytes\n", TARGET.mem_size/1024);
    printf("  Word Size: %d bits\n",   TARGET.word_size);
    printf("  Endianess: %s endian\n", TARGET.endianess ? "little" : "big");


    /* Add EPOS */
    image_size = 0; 
    printf("\n  Adding EPOS to => \"%s\".\n\n", argv[1]); 
 
    
    /* Add the boot strap */
    sprintf(file, "%s/img/%s_boot",epos_home,TARGET.mach);
    printf("  Boot strap \"%s\" ...", file);
    image_size += put_file(fd_out, file);
    if(image_size > MAX_BOOT_LEN) {
	printf(" failed!\n");
	fprintf(stderr, "Boot strap \"%s\" is too large! (%d bytes)\n", 
		file, image_size);
	return 1;
    }
    else {
	while((image_size % MIN_BOOT_LEN != 0))
	    image_size += pad(fd_out,1);
	boot_size = image_size;
	printf(" done. (%d bytes)\n",image_size);
    }

    
    /* Reserve space for Boot_Info if necessary*/
    if (image_size == 0) {
	need_SI = false;
    }
    else{
	si_size = sizeof(System_Info);
	if (si_size > MAX_SI_LEN) {
	    printf(" failed!\n");
	    fprintf(stderr, "System Info structure is too large (%d)!\n",si_size);
	    return 1;
	}
	else {	
	    image_size += pad(fd_out, MAX_SI_LEN);
	}
    }

    
    /* Add the setup */
    si->bm.setup_off = image_size - boot_size;
    sprintf(file, "%s/img/%s_setup",epos_home,TARGET.mach);
    printf("  Setup \"%s\" ...", file);
    image_size += put_file(fd_out, file);
    printf(" done.\n");

    
    if (!strcmp("library",TARGET.mode)) {
	si->bm.system_off = -1;
	image_size += 0;
    }	  
    else {
        /* Add the system */
        si->bm.system_off = image_size - boot_size;
        sprintf(file, "%s/img/%s_system",epos_home,TARGET.mach);
        printf("  System \"%s\" ...", file);
        image_size += put_file(fd_out, file);
        printf(" done.\n");
    }

    
    /* Add the loader */
    si->bm.loader_off = image_size - boot_size;
    if(argc == 3) { /* Single app */
	printf("  Single application \"%s\" ...", argv[2]);
	image_size += put_file(fd_out, argv[2]);
    } else {
	sprintf(file, "%s/img/%s_loader",epos_home,TARGET.mach);
	printf("  Loader \"%s\" ...", file);
	image_size += put_file(fd_out, file);
    }
    printf(" done.\n");

    
    /* Add applications */
    if (!strcmp("library",TARGET.mode)) {
        si->bm.app_off = -1;
        image_size += 0;
	if (argc > 3) 
	    printf("\n  Warning: --library mode just supports one application or remote loading\n");	
    }
    else {
	si->bm.app_off = image_size - boot_size;
	if(argc > 3) {
	    printf("Adding applications =>");
	    for(i = 2; i < argc; i++) {
		printf("  %s ...", argv[i]);
		stat(argv[i], &file_stat);
		image_size += put_number(fd_out, file_stat.st_size);
		image_size += put_file(fd_out, argv[i]);
		printf (" done.\n");
	    }
	    /* Signalize last application by writing 0 to the size of netx app */
	    image_size += put_number(fd_out, 0);
	}
    }


    /* Prepare the Boot Map */
    si->bm.mem_base  = TARGET.mem_base;
    si->bm.mem_size  = TARGET.mem_size;
    si->bm.cpu_type  = TARGET.cpu_type;; 
    si->bm.cpu_clock = TARGET.clock;
    si->bm.host_id   = (unsigned short)-1; /* get from net */
    si->bm.n_threads = TARGET.threads;
    si->bm.n_tasks   = TARGET.tasks;
    si->bm.img_size  = image_size - boot_size; /* Boot not included */


    if (need_SI) {
        //Add System Info
        if(lseek(fd_out, boot_size, SEEK_SET) < 0) {
	    fprintf(stderr, "Error: can not seek the boot image!\n");
	    return 1;
        }
        switch (TARGET.word_size) {
     
	case (8):	if(!add_boot_map((char)  NULL,fd_out,si)) return(1);
	    break;			
	case (16):	if(!add_boot_map((short) NULL,fd_out,si)) return(1);
	    break;					
	case (32):	if(!add_boot_map((long)  NULL,fd_out,si)) return(1);
	    break;
	case (64):	if(!add_boot_map((long long) NULL,fd_out,si)) return(1);
	    break;
	default:	return 1;
	}
    }
     
    
 
    //Adding ARCH particularities
    printf("\n  Adding specific boot features of %s!\n",TARGET.mach);
    if(!(add_machine_secrets(fd_out,image_size))) {
	fprintf(stderr, "Error: specific features error!\n");
	return 1;
    }    
    
    //Finish   
    close(fd_out);       
    printf("\n  Image size: %d bytes.\n\n",image_size);
    
    return 0;
}


/*=======================================================================*/
/* PARSE_TARGET                                                          */
/*                                                                       */
/* Desc:                                                                 */
/*                                                                       */
/* Parm:                                                                 */
/*                                                                       */
/* Rtrn:                                                                 */
/*                                                                       */
/* Creation date: 15/07/03                                               */
/* Last Updated : 15/07/03     Author: Fauze                             */
/*=======================================================================*/
bool parse_target(char* tgt_file) {
	
    char  line[256];
    char* token;
    FILE * f = NULL;			
    if (!(f=fopen(tgt_file,"rb"))) goto err;

    //Getting EPOS Mode
    fgets(line,255,f);
    token=strtok(line,"=");
    if (strcmp(token,"MODE") != 0) goto err;
    token=strtok(NULL,"\n");
    strtolower(TARGET.mode,token);						
	
    //Getting Machine
    fgets(line,255,f); 
    token=strtok(line,"=");
    if (strcmp(token,"MACH") != 0) goto err;
    token=strtok(NULL,"\n");		
    strtolower(TARGET.mach,token);	

    //Getting Arch
    fgets(line,255,f);
    token=strtok(line,"=");
    if (strcmp(token,"ARCH") != 0) goto err;
    token=strtok(NULL,"\n");
    strtolower(TARGET.arch,token);

    //Getting Clock
    fgets(line,255,f);
    token=strtok(line,"=");
    if (strcmp(token,"CLOCK") != 0) goto err;
    token=strtok(NULL,"\n");
    TARGET.clock=atoi(token);	
		
    //Word Size
    fgets(line,255,f);
    token=strtok(line,"=");
    if (strcmp(token,"WORD_SIZE") != 0) goto err;
    token=strtok(NULL,"\n");
    TARGET.word_size=atoi(token);

    //Endianess
    fgets(line,255,f);
    token=strtok(line,"=");
    if (strcmp(token,"ENDIANESS") != 0) goto err;
    token=strtok(NULL,"\n");
    if (strcmp(token,"little") == 0) TARGET.endianess = true;
    else TARGET.endianess = false;

    //Memory Base
    fgets(line,255,f);
    token=strtok(line,"=");
    if (strcmp(token,"MEM_BASE") != 0) goto err;
    token=strtok(NULL,"\n");
    TARGET.mem_base=atoi(token);	

    //Memory Size
    fgets(line,255,f);
    token=strtok(line,"=");
    if (strcmp(token,"MEM_SIZE") != 0) goto err;
    token=strtok(NULL,"\n");
    TARGET.mem_size=atoi(token);	

    TARGET.cpu_type = 0; //To use in the future
    TARGET.threads  = 8;
    TARGET.tasks    = 1;

    fclose(f);
    return(true);
	
  err:	
    if (f) fclose(f);
    return(false);
}


void strtolower(char* dst, const char* src) {
    int i = 0;
    strcpy(dst,src);
    while(src[i] != '\0') {
	dst[i] = tolower(dst[i]);		
	i++;
    }
}


/*=======================================================================*/
/* ADD_BOOT_MAP                                                          */
/*                                                                       */
/* Desc:      								 */
/*                                                                       */
/* Parm:                                                                 */
/*                                                                       */
/* Rtrn:                                                                 */
/*                                                                       */
/* Creation date: 15/07/03                                               */
/* Last Updated : 15/07/03     Author: Fauze                             */
/*=======================================================================*/
template<typename T> bool add_boot_map (T t, int fd_out, void * _si) {
	
    System_Info * si = (System_Info *) _si;
	
    pad(fd_out, (3*sizeof(T))); //Pading for the mem_size, mem_free, iomm_size
	
    if(!put_number(fd_out,(T) si->bm.mem_base))     return(false);
    if(!put_number(fd_out,(T) si->bm.mem_size))     return(false);
    if(!put_number(fd_out,(T) si->bm.cpu_type))     return(false);
    if(!put_number(fd_out,(T) si->bm.cpu_clock))    return(false);
    if(!put_number(fd_out,(T) si->bm.n_threads))    return(false);
    if(!put_number(fd_out,(T) si->bm.n_tasks))      return(false);
	
    if(!put_number(fd_out,si->bm.host_id))          return(false);
    if(!put_number(fd_out,si->bm.n_nodes))          return(false);
	
    if(!put_number(fd_out,(T) si->bm.img_size))     return(false);
    if(!put_number(fd_out,(T) si->bm.setup_off))    return(false);
    if(!put_number(fd_out,(T) si->bm.system_off))   return(false);
    if(!put_number(fd_out,(T) si->bm.loader_off))   return(false);
    if(!put_number(fd_out,(T) si->bm.app_off))      return(false);
	
    return(true);
}

/*=======================================================================*/
/* ADD_MACHINE_SCRETS                                                    */
/*                                                                       */
/* Desc:                                                                 */
/*                                                                       */
/* Parm:                                                                 */
/*                                                                       */
/* Rtrn:                                                                 */
/*                                                                       */
/* Creation date: 15/07/03                                               */
/* Last Updated : 15/07/03     Author: Fauze                             */
/*=======================================================================*/
bool add_machine_secrets(int fd_out, unsigned int i_size) {
	
    //PC 
    if (strcmp("pc",TARGET.mach)  == 0) {
	const unsigned int   floppy_size   = 1474560;
	const unsigned short count_offset  = 508;
	const unsigned short master_offset = 510;		
	unsigned short 	     boot_id	   = 0xaa55;
	unsigned short       num_sect	   = ((i_size + 511) / 512);

	/* Pad the image to the size of a standard floppy */
	if(lseek(fd_out, 0, SEEK_END) < 0) {
	    fprintf(stderr, "Error: can not seek the boot image!\n");
	    return false;
	}				
	pad(fd_out, (floppy_size  - i_size));		
			
	/* write the number of sectors to be read */
	if(lseek(fd_out, count_offset, SEEK_SET) < 0) {
	    fprintf(stderr, "Error: can not seek the boot image!\n");
	    return false;
	}
	put_number(fd_out,num_sect);
		
	//write master boot id
	if(lseek(fd_out, master_offset, SEEK_SET) < 0) {
	    fprintf(stderr, "Error: can not seek the boot image!\n");
	    return false;
	}
	put_number(fd_out, boot_id);    					
		
	return(true);
    }

    //RCX	
    else if (strcmp("rcx",TARGET.mach) == 0) {	
	char* key_string = "Do you byte, when I knock?";
	const unsigned short key_offset = 128 - (strlen(key_string) + 1);
		
	//write key string to unlock epos
	if(lseek(fd_out,key_offset,SEEK_SET) < 0) {
	    fprintf(stderr, "Error: can not seek the boot image!\n");
	    return false;
	}		
	put_buf(fd_out, key_string, (strlen(key_string)+1));		
	return(true);		
    }

    return(true);
}


/*=======================================================================*/
/* LIL_ENDIAN                                                      	 */
/*                                                                       */
/* Desc:                                                                 */
/*                                                                       */
/* Parm:                                                                 */
/*                                                                       */
/* Rtrn:                                                                 */
/*                                                                       */
/* Creation date: 15/07/03                                               */
/* Last Updated : 15/07/03     Author: Fauze                             */
/*=======================================================================*/
bool lil_endian() {
    int test = 1;
    return (*((char*)&test)) ? true : false;
}

template<typename T> void invert(T &n) { 	
    for (int i=0,j=(sizeof(T) - 1); i<((int)(sizeof(T)/2));i++,j--) {
	char *h = &(((char *)&n)[i]);
	char *l = &(((char *)&n)[j]);
	*h ^= *l;
	*l ^= *h;
	*h ^= *l;
    }
}


/*=======================================================================*/
/* PUT_FILE                                                              */
/*                                                                       */
/* Desc: Copy a file to fd0.                                             */
/*                                                                       */
/* Parm: file                                                            */
/*                                                                       */
/* Rtrn: number of bytes written.                                        */
/*                                                                       */
/* Creation date: 10/14/96                                               */
/* Last Updated : 10/14/96     Authors: Aboelha Development Team         */
/*=======================================================================*/
int put_file(int fd_out, char * file)
{
    int fd_in;
    struct stat stat;
    char * buffer;

    fd_in = open(file, O_RDONLY);
    if(fd_in < 0) {
	fprintf(stderr, "Error: can not open %s!\n", file);
	return 0;
    }

    if(fstat(fd_in, &stat) < 0)  {
	fprintf(stderr, "Error: can not stat %s!\n", file);
	return 0;
    }

    buffer = (char *) malloc(stat.st_size);
    if(buffer == NULL) {
	fprintf(stderr, "Error: not enough memory!\n");
	return 0;
    }
    memset(buffer, '\1', stat.st_size);

    if(read(fd_in, buffer, stat.st_size) < 0) {
	fprintf(stderr, "Error: can not read from %s!\n", file);
	return 0;
    }

    if(write(fd_out, buffer, stat.st_size) < 0) {
	fprintf(stderr, "Error: can not write to the boot image!\n");
	return 0;
    }

    free(buffer);    
    close(fd_in);  

    return(stat.st_size);
}

/*=======================================================================*/
/* WRITE_NUMBER                                                          */
/*                                                                       */
/* Desc: Write a number at a position in fd0.                            */
/*                                                                       */
/* Parm: num     -> number to write                                      */
/*       offset  -> offset in fd0                                        */
/*                                                                       */
/* Rtrn: nothing.                                                        */
/*                                                                       */
/* Creation date: 10/14/96                                               */
/* Last Updated : 10/14/96     Authors: Aboelha Development Team         */
/*=======================================================================*/
template<typename T> int put_number(int fd_out, T num)
{
    if ((lil_endian() != TARGET.endianess) && (sizeof(T) > 1))
    	invert(num);
    if(write(fd_out, &num, sizeof(T)) < 0) {
	fprintf(stderr, "Error: can not wirte to file!\n");
	return 0;
    }
    return sizeof(T);
}


int put_buf(int fd_out, void * buf, int size)
{
    int written;
    if (size == 0) return(0);
    if((written = write(fd_out, buf, size)) < 0) {
	fprintf(stderr, "Error: can not wirte to file!\n");
	return 0;
    }
    return written;
}


int pad(int fd_out, int size)
{
    char * buffer;
    if (size == 0) return(0);

    buffer = (char *) malloc(size);
    if(buffer == NULL) {
	fprintf(stderr, "Error: not enough memory!\n");
	return 0;
    }

    memset(buffer,'\1', size);
    if(write(fd_out, buffer, size) < 0) {
	fprintf(stderr, "Error: can not write to the boot image!\n");
	return 0;
    }
    if(buffer != NULL) free(buffer);    
    return size;
}
