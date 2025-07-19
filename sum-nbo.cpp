#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define FILE1 "thousand.bin"
#define FILE2 "five-hundred.bin"
#define FILE3 "two-hundred.bin"

int main(void) {
    const char *files[] = { FILE1, FILE2, FILE3 };
    const int n_files = sizeof(files) / sizeof(files[0]);
    uint32_t values[n_files];
    uint32_t sum = 0;

    for (int i = 0; i < n_files; i++) {
        FILE *fp = fopen(files[i], "rb");
        if (!fp) {
            perror(files[i]);
            return 1;
        }

        unsigned char buf[4];
        size_t nread = fread(buf, 1, sizeof(buf), fp);
        fclose(fp);

        if (nread != sizeof(buf)) {
            fprintf(stderr, "Error: %s Not Read (Only Read: %zu)\n", files[i], nread);
            return 1;
        }

        // BE 4byte uint32_t
        uint32_t val = ((uint32_t)buf[0] << 24) |
        ((uint32_t)buf[1] << 16) |
        ((uint32_t)buf[2] <<  8) |
        ((uint32_t)buf[3]      );
        values[i] = val;
        sum += val;
    }

    // print set
    for (int i = 0; i < n_files; i++) {
        printf("%u(0x%08x)", values[i], values[i]);
        if (i < n_files - 1)
            printf(" + ");
        else
            printf(" = ");
    }
    printf("%u(0x%08x)\n", sum, sum);

    return 0;
}
