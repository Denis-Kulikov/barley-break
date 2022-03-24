#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <Windows.h>
#include "inside.c"

#define FALSE 0
#define TRUE 1
#define SWAP(Arg1, Arg2)\
    {\
        int temp = Arg1;\
        Arg1 = Arg2;\
        Arg2 = temp;\
    }

enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

enum {
    QUIT,
    WIN
};

void Randon(int size, int Dice[size][size])
{
    int value, count = 0, j = 1;
    int *CheckMas = calloc(size * size, sizeof(int));
    while (j < size * size ) {
        value = (rand() % 15) + 1;
        for (int i = 1; i < size * size - 1; i++) {
            if(CheckMas[value] != 0)
                count = 0;
        }
        if (count == 1) {
            Dice[(j - 1) / size][(j - 1) % size] = value;
            CheckMas[value]++;
            j++;
        }   
        count = 1; 
    }

    Dice[3][3] = 0;
}

int Resolt(int size, int Dice[size][size]) {
    for (int i = 1; i < size * size - 1; i++) {
        if (!(Dice[(i - 1) / size][(i - 1) % size] == i)) {
            return FALSE;
        } 
    }

    return TRUE;
}

int Moving(int size, int Dice[size][size], int Direction, int Position[]) {
    //printf("Direction: %d\nPosition: %d %d\n", Direction, Position[0], Position[1]);
    switch (Direction) {
        case UP:
            if (Position[0] == 0)
                return FALSE;
            SWAP(Dice[Position[0] - 1][Position[1]], Dice[Position[0]][Position[1]]);
            Position[0]--;
            break;
        case DOWN:
            if (Position[0] == size - 1)
                return FALSE;
            SWAP(Dice[Position[0] + 1][Position[1]], Dice[Position[0]][Position[1]]);
            Position[0]++;
            break;
        case LEFT:
            if (Position[1] == 0)
                return FALSE;
            SWAP(Dice[Position[0]][Position[1] - 1], Dice[Position[0]][Position[1]]);
            Position[1]--;
            break;
        case RIGHT:
            if (Position[1] == size - 1)
                return FALSE;
            SWAP(Dice[Position[0]][Position[1] + 1], Dice[Position[0]][Position[1]]);
            Position[1]++;
            break;
    }
    return TRUE;
}

int GetDirection() {
    char Direction = getchar();
    while (getchar() != '\n')
    Direction = tolower(Direction);
    switch(Direction) {
        case 'w':
            return UP;
            break;
        case 's':
            return DOWN;
            break;
        case 'a':
            return LEFT;
            break;
        case 'd':
            return RIGHT;
            break;
        default:
            return FALSE;
            break;
    }

    return -1;
}

void PrintDice(int size , int Dice[size][size]) {
    for (int i = 0; i < size; i++)
        printf("+-----");
    printf("+\n");
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            if (Dice[y][x] < 10) {
                printf("|  %d  ", Dice[y][x]);
            } else {
                printf("|  %d ", Dice[y][x]);
            }
        }
        printf("|\n");
        for (int i = 0; i < size; i++)
            printf("+-----");
        printf("+\n");
    }
    printf("\n");
}

void Play(int size, int Dice[size][size]) {
    int Direction, Exit = FALSE, Position[2] = {size - 1, size - 1};
    PrintDice(size, Dice);

    while (!Exit) {
        Direction = GetDirection();
        //PlayUpdate(size, Dice, Direction);
        Moving(size, Dice, Direction, Position);
        Exit = Resolt(size, Dice);
        PrintDice(size, Dice);
    }
    
    switch(Exit) {
        case WIN:
            printf("You Win!\n");
            break;
        case QUIT:
            printf("Exit from the game.\n");
            break;
        default:
            break;
    }
}

int main() {
    int size = 4;
    int Dice[4][4];
    printf("Управление WASD\n\n");

    Randon(size, Dice);
    Play(size, Dice);
    
    return 0;
}