#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define REGISTER1_MASK 0b00111000
#define REGISTER2_MASK 0b00000111

enum op_codes {
    mov = 0xE2,
};

char w1_registers_table[8][8] = {
    "ax",
    "cx",
    "dx",
    "bx",
    "sp",
    "bp",
    "si",
    "di"
};

char memory_modes_table[4][4] = {
    "mm00",
    "mm08",
    "mm16",
    "rm00"
};

char* get_register(bool wFlag, int code);
void print_binary(char x);


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

    char firstChar = buffer[0];

    bool wFlag = firstChar & 1;
    bool dFlag = firstChar & 2;

    char opCode = firstChar >> 2;

    char* operation;

    if (opCode == (char)mov) {
        operation = "mov";
    } else {
        printf("not a recognised opCode\n");
    }

    char secondChar = buffer[1];

    char mod = (secondChar >> 6);

    int modBit1 = mod & 1;
    int modBit2 = mod & 2;


    int modBit = 0;
    modBit |= modBit1;
    modBit |= modBit2;

    char* modCode = memory_modes_table[modBit];

    int register1 = (secondChar & REGISTER1_MASK) >> 3;
    int register2 = secondChar & REGISTER2_MASK;

    char* reg1 = get_register(wFlag, register1);
    char* reg2 = get_register(wFlag, register2);

    printf("bits 16\n");
    printf("\n");
    printf("%s %s, %s", operation, reg2, reg1);

    free(buffer);
    return 0;
}

char* get_register(bool wFlag, int code ) {
    if (wFlag) {

        return w1_registers_table[code];
    }

    return "implement w0 registers table";
}

void print_binary(char x) {
    
    for(int i = 7; i >= 0; i--) {
        putchar((x & (1 << i)) ? '1' : '0');
    }
    putchar('\n');
}
