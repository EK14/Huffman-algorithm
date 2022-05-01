#include "progressbar.h"

void progressbar(float i, int readsnumb){
    float x = ((float)(i+1)/readsnumb);
    printf("In progress: %d %c \r", (int)(x*100), '%');
    fflush(stdout);
}