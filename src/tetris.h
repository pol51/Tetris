#ifndef __TETRIS_H__
#define __TETRIS_H__

class Tetris
{
public:
    unsigned char tet[4][4];
    unsigned char tt[4][4];
    unsigned char field[10][20];
    unsigned char next[4][4];
    unsigned char tets[32][4];
    float speed;

    int score;
    int col;
    int row;

    long Time_Elapsed;
    long Last_Time;
    long Current_Time;

    Tetris(float Speed=0.5);

    void Rotate();
    void MoveLeft();
    void MoveRight();
    void MoveDown(float sp);
    void Draw();
    void SetTetris();
    void Reset();
    void Next();
};

#endif
