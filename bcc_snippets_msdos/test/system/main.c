#include <stdio.h>
#include <string.h>
#include <dos.h>

int main(int argc, char *argv[]) {
    char cmd[129];
    char args[129];

    struct SREGS sregs;
    union REGS inregs, outregs;

    struct exec_params {
        unsigned int env_seg;
        unsigned int cmd_off;
        unsigned int cmd_seg;
        unsigned int fcb1_off;
        unsigned int fcb1_seg;
        unsigned int fcb2_off;
        unsigned int fcb2_seg;
    } param_block;

    sprintf(cmd, "argtest.com");
    sprintf(args, "1234567890 ABCDEF GHI jklmn 123");

    segread(&sregs);
    sregs.es = sregs.ss;

    param_block.env_seg = 0;
    param_block.cmd_off = (unsigned int)args;
    param_block.cmd_seg = __get_ds();
    param_block.fcb1_off = 0x5c;
    param_block.fcb2_off = 0x6c;
    param_block.fcb1_seg = __psp;
    param_block.fcb2_seg = __psp;

    inregs.h.ah = 0x4b;
    inregs.h.al = 0x00;
    inregs.x.dx = (unsigned int)cmd;
    inregs.x.bx = (unsigned int)&param_block;

    printf("executing '%s' wit args '%s':\r\n\r\n", cmd, args);

    int86x(0x21, &inregs, &outregs, &sregs);

    printf("\r\nint21 returned AX=0x%04x BX=0x%04x CX=0x%04x DX=0x%04x\r\n", outregs.x.ax, outregs.x.bx, outregs.x.cx, outregs.x.dx); 

    return 0;
}

