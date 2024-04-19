#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum op_codes {
    mov = 0b100010,
    add = 0b100101
};

enum registers {
    ax = '0',
};

void print_binary(char x) {
    
    for(int i = 7; i >= 0; i--) {
        putchar((x & (1 << i)) ? '1' : '0');
    }
    putchar('\n');
}

int main(int argc, char* argv[]) {

    if (argc < 2) {
        printf("You must provide a file");
        return 1;
    }

    FILE* file = fopen(argv[1], "rb");

    if (file == NULL) {
        printf("Couldn't open file");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    char* buffer = (char*)malloc(sizeof(char) * file_size);

    if (buffer == NULL) {
        printf("Could not allocate buffer");
        fclose(file);
        return 1;
    }

    size_t read_size = fread(buffer, sizeof(char), file_size, file);
    fclose(file);

    for (int i = 0; i < file_size; i++) {
        printf("%d\n", (int)file_size);

        print_binary(buffer[i]);
    }

    // get first byte
    char firstChar = buffer[0];

    // check for flags
    bool wFlag = firstChar & 1;
    bool dFlag = firstChar & 2;

    // check opCode
    char opCode = firstChar >> 2;
    char hexMovCode = 0xE2;

    if (opCode == hexMovCode) {
        printf("mov");
    } else {
        printf("not a recognised opCode");
    }

    printf("%d, %d", wFlag, dFlag);

    free(buffer);
    return 0;
}

