# 1 "ia32_crtn.S"
# 1 "<built-in>"
# 1 "<command line>"
# 1 "ia32_crtn.S"
        .file "crtn.s"

        .section .init
        .globl _init
        .type _init,@function
 leave
 ret

        .section .fini
        .globl _fini
        .type _fini,@function
 leave
 ret
