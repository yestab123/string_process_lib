/* Change escape(\") to unescape(") */
/* 20160422 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdint.h>
#include <malloc.h>
#include <string.h>

char *
change_escape(char *input_buff, int input_size, int *output_size) {
    int   i, t;
    char *output_buff;

    if (input_size <= 0 || output_size == NULL) {
        return NULL;
    }

    output_buff = malloc(input_size);
    if (output_buff == NULL) {
        return NULL;
    }

    memset(output_buff, '\0', input_size);

    for (i = 0, t = 0; i < input_size; i++) {
        if (i <= input_size - 2) {
            if (input_buff[i] == '\\' && input_buff[i+1] == '"') {
                output_buff[t] = input_buff[i + 1];
                t++;
                i++;
                continue;
            }
        }
        output_buff[t] = input_buff[i];
        t++;
    }

    *output_size = t;
    return output_buff;
}


int
main(int argc, char **argv) {
    int input, output, i, size, nsize;
    char buff[1024];
    char *p;

    if (argc < 2) {
        printf("error input arg. use ./program [input_file] \n");
        exit(0);
    }

    input = open(argv[1], O_RDONLY);
    if (input < 0) {
        printf("open input file %s error\n", argv[1]);
        exit(0);
    }
    /* output = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC); */
    /* if (output < 0) { */
    /*     printf("open output file %s error\n", argv[2]); */
    /* } */

    size = 0;
    for (;;) {
        i = read(input, buff + size, 1);
        if (i == 0) {
            break;
        }
        if (i > 0) {
            size += i;
        }
    }

    p = change_escape(buff, size, &nsize);
    if (p != NULL) {
        printf("%s\n", p);
        free(p);
    }
    close(input);

    return 0;
}
