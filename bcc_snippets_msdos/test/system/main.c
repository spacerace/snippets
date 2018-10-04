#include <stdio.h>
#include <string.h>
#include <dos.h>

int system(char *string);

int main(int argc, char *argv[]) {
    system("dir z:");

    return 0;
}

int system(char *string) {
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

    char cmd[129];
    char args[129];

    memset(cmd, '\0', sizeof(cmd));
    memset(args, '\0', sizeof(args));

    strcpy(cmd, "COMMAND.COM");

    args[0] = ' ';          /* WARNING dirty hack, first char of args is always
                             * lost. We place a dummy to get lost. */
    strcat(args, "/C ");
    strcat(args, string);

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

    int86x(0x21, &inregs, &outregs, &sregs);

    return 0;
}
