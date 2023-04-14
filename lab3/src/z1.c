#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define N 1000000

uint32_t generate_number()
{
    const int r = rand();
    const int p = r % 100;
    if (p < 90) {
        return r % 128;
    }
    if (p < 95) {
        return r % 16384;
    }
    if (p < 99) {
        return r % 2097152;
    }
    return r % 268435455;
}

size_t encode_varint(uint32_t value, uint8_t* buf)
{
    assert(buf != NULL);
    uint8_t* cur = buf;
    while (value >= 0x80) {
        const uint8_t byte = (value & 0x7f) | 0x80;
        *cur = byte;
        value >>= 7;
        ++cur;
    }
    *cur = value;
    ++cur;
    return cur - buf;
}

uint32_t decode_varint(const uint8_t** bufp)
{
    const uint8_t* cur = *bufp;
    uint8_t byte = *cur++;
    uint32_t value = byte & 0x7f;
    size_t shift = 7;
    while (byte >= 0x80) {
        byte = *cur++;
        value += (byte & 0x7f) << shift;
        shift += 7;
    }
    *bufp = cur;
    return value;
}

int check_sequence(FILE* uc, FILE* c, size_t size)
{
    assert(uc != NULL);
    assert(c != NULL);

    fseek(uc, 0, SEEK_SET);
    fseek(c, 0, SEEK_SET);
    uint32_t dec, ndec;
    uint8_t* buf = malloc(sizeof(uint8_t) * size);
    const uint8_t* cur = buf;
    fread(buf, sizeof(uint8_t), size, c);

    for (int i = 0; i < N; i++) {
        dec = decode_varint(&cur);
        fread(&ndec, sizeof(uint32_t), 1, uc);
        if (ndec != dec) {
            free(buf);
            return -1;
        }
    }
    free(buf);
    return 0;
}

size_t writeAndTakeSize(FILE* uc, FILE* c)
{
    assert(uc != NULL);
    assert(c != NULL);
    uint8_t buf[4] = {};
    size_t size = 0;
    size_t finalsize = 0;
    for (int i = 0; i < N; i++) {
        uint32_t num = generate_number();
        fwrite(&num, sizeof(num), 1, uc);
        size = encode_varint(num, buf);
        finalsize += size;
        fwrite(&num, size, 1, c);
    }
    return finalsize;
}
int main()
{
    srand(time(NULL));

    FILE* ucfile;
    FILE* cfile;

    if ((ucfile = fopen("uncompressed.dat", "wb+")) == NULL) {
        printf("Не удалось открыть uncompressed.dat\n");
        exit(1);
    }

    if ((cfile = fopen("compressed.dat", "wb+")) == NULL) {
        printf("Не удалось открыть compressed.dat\n");
        exit(1);
    }

    size_t size = writeAndTakeSize(ucfile, cfile);

    printf("Size file without encoding: %d\nSize file with encoding: %ld\n",
           N * 4,
           size);

    size_t fsize = ftell(cfile);

    if (check_sequence(ucfile, cfile, fsize) == -1)
        printf("Последовательность неверна");
    else
        printf("Последовательность верна");
    return 0;
}
