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