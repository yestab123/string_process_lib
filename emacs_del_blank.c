/* Delete unnecessary blank from one file to another file.
 * If using spacemacs/emacs, the blank at the last of one line will be highlight, so using this program to delete the blank.
 * 2016. Ziv Chow
 */
 #include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int
main(int argc, char **argv) {
    if (argc < 3) {
        printf("usage:%s [input_file] [output_file]\n", argv[0]);
        exit(0);
    }

    FILE *fp, *wp;

    fp = fopen(argv[1], "r");
    wp = fopen(argv[2], "w");

    char buf[1024];
    char sbuf[1024];
    int  flag = 0, idx, len, i, t;
    while(fgets(buf, 1024, fp) != NULL) {
        flag = 0;
        idx = 0;
        len = 0;
        for (i = 0; i < strlen(buf); i++) {
            if (buf[i] == ' ') {
                if (flag == 1) {
                    continue;
                }
                idx = i;
                flag = 1;
            } else if (buf[i] == '\r'||buf[i] == '\n') {
                sbuf[len] = buf[i];
                flag = 0;
                len++;
            } else {
                if (flag == 1) {
                    flag = 0;
                    for (t = idx; t <= i; t++) {
                        sbuf[len] = buf[t];
                        len++;
                    }
                } else {
                    sbuf[len] = buf[i];
                    len++;
                }
            }
        }

        sbuf[len] = '\0';
        fputs(sbuf, wp);
    }

    fclose(fp);
    fclose(wp);
}
