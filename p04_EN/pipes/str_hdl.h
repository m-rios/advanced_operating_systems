#ifndef STR_HDL_H
#define STR_HDL_H
#define SIZE 100
#define SIZE_HALF ((SIZE)/2 +1)

void concatenate(char all[SIZE], char half1[SIZE_HALF], char half2[SIZE_HALF]);
void split(char all[SIZE], char half1[SIZE_HALF], char half2[SIZE_HALF]);

#endif