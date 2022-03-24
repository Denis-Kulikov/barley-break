#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
//#include <Windows.h>
#include "inside.c"

int main() {
    int size = 4;
    int Dice[4][4];
    printf("Управление WASD\n\n");

    Randon(size, Dice);
    Play(size, Dice);
    
    return 0;
}