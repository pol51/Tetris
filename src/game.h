#include <tetris.h>
#include <tempo.h>


class Game
{
protected:
    double Time_Scale;

    int scrW;
    int scrH;
    float speed;
    Tetris tet;
    int win_main;

    Tempo timer;
    static Game *inst;

protected:
    static void affichage();
    static void clavier(unsigned char touche, int x, int y);
    static void special(int touche, int x, int y);
    static void idle();

public:
    Game(): Time_Scale(0.005), scrW(600), scrH(600), speed(.5) {}
    int run();
};
