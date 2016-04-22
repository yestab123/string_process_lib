/* Delete blank and Enter(\r or \n) from input file to output file */
/* 20160422 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>

int
main(int argc, char **argv) {
    int input, output, i;
    char byte;

    if (argc < 3) {
        printf("error input arg. use ./program [input_file] [output_file]\n");
        exit(0);
    }

    input = open(argv[1], O_RDONLY);
    if (input < 0) {
        printf("open input file %s error\n", argv[1]);
        exit(0);
    }
    output = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC);
    if (output < 0) {
        printf("open output file %s error\n", argv[2]);
    }

    for (;;) {
        i = read(input, &byte, 1);
        if (i == 0) {
            break;
        }
        if (byte == ' ' || byte == '\r' || byte == '\n') {
            continue;
        }
        write(output, &byte, 1);
    }
    close(input);
    close(output);
}
