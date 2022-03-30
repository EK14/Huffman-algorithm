#include <stdio.h>

int main() {
    int freq[256]={0};
    FILE* fr = fopen("hello.txt", "rb");
    if (!fr)
        return 1;
    fseek(fr, 0L, SEEK_END);
    long length = ftell(fr);
    fseek(fr, 0, SEEK_SET);
    for (int i = 0; i < length; ++i)
    {
        freq[(unsigned char)fgetc(fr)] ++;
    }
    printf("Hello");
    fclose(fr);
    return 0;
}
