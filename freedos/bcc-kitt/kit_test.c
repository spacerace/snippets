/* DOS MOTD 
 * 
 *  (c) 2018 <stecdose@gmail.com>
 *  license: GPLv2
 */

#include <stdio.h>
#include "kitten.h"

int main(int argc, char *argv[]) {
    char *s;

    printf("kitten test with dev86/bcc\r\n\r\n");

    kittenopen("KIT_TEST.DE");
    s = kittengets(1, 1, "Hello World!");

    printf("opening KIT_TEST.DE, message 1.1: '%s'\r\n", s);

    kittenclose();

    return 0;
}
