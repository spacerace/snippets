/* simple generator for sine tables to include in c code
 *
 * (c) 2012 nils stec
 *
 * license: GPL
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <sys/types.h>
#include <math.h>

#define DT_8            1
#define DT_16           2
#define DT_32           4
#define DT_DOUBLE       16
#define DT_SIGNED       0
#define DT_UNSIGNED     1

void help();
void gen_table(unsigned int len, unsigned int amplitude, int offset, int sign, int datatype, int comment);

int main(int argc, char **argv) {
        int i;

        unsigned int len = 32;
        unsigned int amp = 0;
        int off = 0;
        int sign = DT_SIGNED;
        int datatype = DT_8;
        int comment = 0;

        int itemp;
        unsigned long int ultemp;
        long int ltemp;
        unsigned int calc_temp;

        for(i = 0; i < argc; i++) {
                if(!(strcmp(argv[i], "-u"))) {          // only unsigned values
                        sign = DT_UNSIGNED;
                } else if( (!(strcmp(argv[i], "-h"))) || (!(strcmp(argv[i], "--help"))) ) {
                        help();
                        exit(0);
                } else if(!(strcmp(argv[i], "-c"))) {   // add comment
                        comment = 1;
                } else if(!(strcmp(argv[i], "-o"))) {   // offset DEC
                        if(argv[i+1] == NULL) {
                                printf("\nyou'll need to give me an offset!\n\n");
                                exit(1);
                        }
                        ltemp = strtol(argv[i+1], NULL, 10);
                        if(ltemp == 0) {
                                printf("\nzero-offset not allowed!\n\n");
                                exit(1);
                        }
                        off = (int)ltemp;
                } else if(!(strcmp(argv[i], "-a"))) {   // amplitude DEC
                        if(argv[i+1] == NULL) {
                                printf("\nyou'll need to give me max. amplitude!\n\n");
                                exit(1);
                        }
                        ltemp = strtol(argv[i+1], NULL, 10);
                        if(ltemp < 2) { 
                                printf("\namplitude negative or too small!\n\n");
                                exit(1);
                        }
                        amp = (unsigned int)ltemp;
                } else if(!(strcmp(argv[i], "-O"))) {   // offset HEX
                        if(argv[i+1] == NULL) {
                                printf("\nyou'll need to give me an offset in hex!\n\n");
                                exit(1);
                        }
                        ltemp = strtol(argv[i+1], NULL, 16);
                        if(ltemp == 0) {
                                printf("\nzero-offset not allowed!\n\n");
                                exit(1);
                        }
                        off = (int)ltemp;
                } else if(!(strcmp(argv[i], "-A"))) {   // amplitude HEX
                        if(argv[i+1] == NULL) {
                                printf("\nyou'll need to give me max. amplitude in hex!\n\n");
                                exit(1);
                        }
                        ltemp = strtol(argv[i+1], NULL, 16);
                        if(ltemp < 2) {   
                                printf("\namplitude negative or too small!\n\n");
                                exit(1);
                        }
                        amp = (unsigned int)ltemp;
                } else if(!(strcmp(argv[i], "-l"))) {   // length
                        if(argv[i+1] == NULL) {
                                printf("\nyou'll need to give me the length!\n\n");
                                exit(1);
                        }
                        ltemp = strtol(argv[i+1], NULL, 10);
                        if(ltemp < 2) {   
                                printf("\ntoo short!\n\n");
                                exit(1);
                        }
                        if((ltemp%2) != 0) {
                                printf("\nlen has to be a power of 2!\n\n");
                                exit(1);
                        }
                        len = (unsigned int)ltemp;
                } else if(!(strcmp(argv[i], "-d"))) {   // datatype
                        if(argv[i+1] == NULL) {
                                printf("\nyou'll need to give me a datatype!\n\n");
                                exit(1);
                        }
                        ultemp = strtoul(argv[i+1], NULL, 10);
                        itemp = (int)ultemp;
                        switch(itemp) {
                                case 8:
                                        datatype = DT_8;
                                        break;
                                case 16:
                                        datatype = DT_16;
                                        break;
                                case 32:
                                        datatype = DT_32;
                                        break;
                                default:
                                        if(strcmp(argv[i+1], "double") == 0) {
                                                datatype = DT_DOUBLE;
                                        } else {
                                                printf("\nwrong datatype!\n\n");
                                                help();
                                                exit(1);
                                        }
                                        break;
                        }
                }

        }

        printf("\n");

        switch(datatype) {
                case DT_8:
                        ultemp = 0xff;
                        ltemp = 0xff;
                        break;
                case DT_16:
                        ultemp = 0xffff;
                        ltemp = 0xffff;
                        break;
                case DT_32:
                        ultemp = 0xffffffff;
                        ltemp = 0xffffffff;
                        break;
                case DT_DOUBLE:
                        break;
        }

        if(datatype != DT_DOUBLE) {
                if(off < 0) calc_temp = (unsigned int)off * -1;
                else calc_temp = (unsigned int)off;

                if((calc_temp+amp) > ultemp) {
                        printf("\ndatatype too small to hold your sine!\n\n");
                        exit(-1);
                }
        }
        gen_table(len, amp, off, sign, datatype, comment);
        return 0;
}

void help() {
        printf("c sine table generator 0.01 [(c) 2012, nils stec]\n\n");
        printf("  -d 8/16/32/double      datatypes: int8_t,int16_t,int32_t,double\n");
        printf("  -u                     force unsigned values (signal zero is at max_amplitude/2)\n");
        printf("  -o offset              offset DECIMAL\n");
        printf("  -O offset              offset HEX\n");
        printf("  -a max_amplitude       max amplitude DECIMAL\n");
        printf("  -A max_amplitude       max amplitude HEX\n");
        printf("  -l len                 length\n");
        printf("  -c                     add comment\n");
        return;
}

void gen_table(unsigned int len, unsigned int amplitude, int offset, int sign, int datatype, int comment) {
        double sine;
        int n, i;
        uint32_t table_entry;

        if(sign == DT_UNSIGNED) {                               // if we want unsigned data, we have to pull our sine higher than zero
                while((int)(offset-amplitude)<0) offset++;
        }

        if(comment) {
                printf("/* sine table, ");

                if(datatype != DT_DOUBLE) { 
                        printf("max amplitude %d, ", amplitude);
                        printf("offset %d, ", offset);
                }
                printf("%d entries, size in memory: %dbytes */\n", len, datatype*len);

        }

        if(datatype != DT_DOUBLE) {
                if(sign==DT_UNSIGNED) printf("u");
                switch(datatype) {
                        case DT_8:
                                printf("int8_t sine_table[%d] = {\n", len);
                                break;
                        case DT_16:
                                printf("int16_t sine_table[%d] = {\n", len);
                                break;
                        case DT_32:
                                printf("int32_t sine_table[%d] = {\n", len);
                                break;
                }

        } else printf("double sine_table[%d] = {\n", len);

        n = 0;
        while(n < len) {
                printf("");
                for(i = 0; i < 8; i++) {
                        sine = sin(2.0*M_PI*n/len);
                        switch(datatype) {
                                case DT_DOUBLE:
                                        printf("%f", sine);
                                        break;
                                default:
                                        table_entry = (sine*(double)amplitude)+offset;
                                        printf("%d", table_entry);
                                        break;
                        }
                        n++;
                        if(n < len) printf(", ");
                }
                printf("\n");
        }
        printf("};\n\n");
}

