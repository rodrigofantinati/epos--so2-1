// EPOS-- PC Display Mediator Declarations

#ifndef __pc_display_h
#define __pc_display_h

#include <display.h>
#include "uart.h"

__BEGIN_SYS

// Colour Graphics Adapter based on MC6845
class MC6845
{
public:
    // MC6845 I/O ports
    typedef CPU::IO_Port IO_Port;
    enum {
	ADDR_REG  = 0x03d4, // Address 
	DATA_REG  = 0x03d5, // Data 
	CTRL_REG  = 0x03d8, // Control [0,0,BLK,GR_HR,VOUT,B/W,GR,TX_HR]
	COLOR_REG = 0x03d9, // Color [0,0,PLT,BR,B-BG-FG]
	STAT_REG  = 0x03da  // Status [0,0,0,0,VR,LPS,LPT,EN]
    };

    // MC6845 Internal Addresses
    typedef CPU::Reg8 Address;
    enum {
	ADDR_CUR_START	= 0x0a,	// cursor mask
	ADDR_CUR_END	= 0x0b,
	ADDR_PAGE_HI	= 0x0c,	// current frame buffer page
	ADDR_PAGE_LO	= 0x0d,
	ADDR_CUR_POS_HI	= 0x0e,	// current curor position
	ADDR_CUR_POS_LO	= 0x0f
    };

public:
    MC6845() {}

    volatile int position() {
	CPU::out8(ADDR_REG, ADDR_CUR_POS_LO);
	int pos = CPU::in8(DATA_REG);
	CPU::out8(ADDR_REG, ADDR_CUR_POS_HI);
	pos |= CPU::in8(DATA_REG) << 8;
	return pos;
    }
    void position(int pos) {
	CPU::out8(ADDR_REG, ADDR_CUR_POS_LO);
	CPU::out8(DATA_REG, pos & 0xff);
	CPU::out8(ADDR_REG, ADDR_CUR_POS_HI);
	CPU::out8(DATA_REG, pos >> 8);
    }
};

class PC_Display: protected Display_Common, public MC6845
{
private:
    typedef Traits<PC_Display> Traits;
    static const Type_Id TYPE = Type<PC_Display>::TYPE;

    static const int FBA = Traits::FRAME_BUFFER_ADDRESS;
    static const int LINES = Traits::LINES;
    static const int COLUMNS = Traits::COLUMNS;
    static const int TAB_SIZE = Traits::TAB_SIZE;

public:
    // Frame Buffer
    typedef unsigned short Cell;
    typedef Cell * Frame_Buffer;

    // Cell Attributes
    typedef Cell Attribute;
    enum {
	NORMAL = 0x0700
    };

public:
    PC_Display(Frame_Buffer fb = reinterpret_cast<Frame_Buffer>(FBA))
	: _frame_buffer(fb) {}

    void clear() { 
	for(unsigned int i = 0; i < LINES * COLUMNS; i++)
	    _frame_buffer[i] = NORMAL | ' ';
	MC6845::position(0);
    }

    void putc(char c){
	unsigned int pos = MC6845::position();

	switch(c) {
	case '\n':
	    pos = (pos + COLUMNS) / COLUMNS * COLUMNS;
	    break;
	case '\t':
	    pos = (pos + TAB_SIZE) / TAB_SIZE * TAB_SIZE;
	    break;
	default:
	    _frame_buffer[pos++] = NORMAL | c;
	}
	if(pos >= LINES * COLUMNS) {
	    scroll();
	    pos-= COLUMNS;
	}
	MC6845::position(pos);
    }

    void puts(const char * s) {
	while(*s != '\0')
	    putc(*s++);
    }

    void position(int * line, int * column) {
	unsigned int pos = MC6845::position();
	*column = pos % COLUMNS;
	*line = pos / COLUMNS;
    }

    void position(int line, int column) {
	if(line > LINES)
	    line = LINES;
	if(column > COLUMNS)
	    column = COLUMNS;
	if((line < 0) || (column < 0)) {
	    int old_line, old_column;
	    position(&old_line, &old_column);
	    if(column < 0)
		column = old_column;
	    if(line < 0)
		line = old_line;
	}
	MC6845::position(line * COLUMNS + column);
    }

    void size(int * lines, int * columns) {
	*lines = LINES;
	*columns = COLUMNS;
    }

    static int init(System_Info * si);

private:
    void scroll() {
	for(unsigned int i = 0; i < (LINES - 1) * COLUMNS; i++)
	    _frame_buffer[i] = _frame_buffer[i + COLUMNS];
	for(unsigned int i = (LINES - 1) * COLUMNS; i < LINES * COLUMNS; i++)
	    _frame_buffer[i] = NORMAL | ' ';
    }

private:
    Frame_Buffer _frame_buffer;
};

class PC_Serial_Display: protected Display_Common
{
private:
    typedef Traits<PC_Display> Traits;
    static const Type_Id TYPE = Type<PC_Display>::TYPE;

public:
    PC_Serial_Display() {}

    void clear() {}

    void putc(char c){ _uart.put(c); }

    void puts(const char * s) {
	while(*s != '\0')
	    putc(*s++);
    }

    void size(int * lines, int * columns) {
	*lines = Traits::LINES;
	*columns = Traits::COLUMNS;
    }

    void position(int * line, int * column) {}
    void position(int line, int column) {}

    static int init(System_Info * si);

private:
    PC_UART _uart;
};

template <bool serial>
class PC_Select_Display: public PC_Display {};

template <>
class PC_Select_Display<true>: public PC_Serial_Display {};

typedef PC_Select_Display<Traits<PC_Display>::on_serial> Display;

__END_SYS

#endif

