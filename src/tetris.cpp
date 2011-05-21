#include <tetris.h>

#include <GL/glut.h>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>

Tetris::Tetris(float Speed): speed(Speed)
{
    unsigned char tmp[24][4] =
    {
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},

        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},

        {0, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0},

        {0, 0, 1, 0},
        {0, 1, 1, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0},

        {0, 1, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0},

        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    };

    memcpy(tets, tmp, 24 * 4 * sizeof(unsigned char));

    Reset();
    Next();
}

void Tetris::Rotate()
{
    unsigned char temp[4][4];

    memcpy(temp, tet, 4 * 4 * sizeof(unsigned char));
    memcpy(tt, tet, 4 * 4 * sizeof(unsigned char));

    for (int i = 4; --i >= 0;)
        for (int j = 4; --j >= 0;)
            tet[i][j] = tt[j][3 - i];

    // can rotate? ... pull back if over side!
    int tcol = col;

    for (int i = 4; --i >= 0;)
        for (int j = 4; --j >= 0;)
        {
            int x = i + col;
            int y = j + row;

            if (tet[j][i])
            {
                if (x > 9)
                {
                    col -= x - 9;
                    return;
                }

                if (x < 0)
                {
                    col += -x;
                    return;
                }

                if ((y > 19) || (field[x][y] == 2))
                {
                    memcpy(tet, temp, 4 * 4 * sizeof(unsigned char));
                    col = tcol;
                    return;
                }
            }
        }
}

void Tetris::MoveLeft()
{
    col--;

    for (int i = 4; --i >= 0;)
        for (int j = 4; --j >= 0;)
        {
            int x = i + col;
            int y = j + row;

            // test colision

            if ((tet[j][i] && x < 0) || (tet[j][i] && field[x][y] == 2))
            {
                col++;
                return;
            }
        }
}

void Tetris::MoveRight()
{
    col++;

    for (int i = 4; --i >= 0;)
        for (int j = 4; --j >= 0;)
        {
            int x = i + col;
            int y = j + row;

            // test colision

            if ((tet[j][i] && x > 9) || (tet[j][i] && field[x][y] == 2))
            {
                col--;
                return;
            }
        }
}

void Tetris::MoveDown(float sp)
{
    if (Time_Elapsed > sp)
    {
        row++;
        Last_Time = Current_Time;
    }

    for (int i = 4; --i >= 0;)
    {
        int x = i + col;

        if (x < 0 || x > 9) continue;

        for (int j = 4; --j >= 0;)
        {
            int y = j + row;

            if (y > 19) y = 19;

            // merge layers
            if (tet[j][i])
                field[x][y] = tet[j][i];

            // on bottom?
            if ((tet[j][i] && y > 18) || (tet[j][i] && field[x][y+1] == 2))
            {
                SetTetris();
                return;
            }
        }
    }
}

void Tetris::Draw()
{
    float sz = 0.05f;

    // draw game

    for (int x = 10; --x >= 0;)
    {
        for (int y = 20; --y >= 0;)
        {
            float r1, r2, g1, g2, b1, b2;

            if (!field[x][y])
            {
                r1 = .2;
                r2 = .0;
                g1 = .2;
                g2 = .0;
                b1 = .6;
                b2 = .4;
            }

            else
            {
                if (field[x][y] != 2)
                {
                    r1 = 1.;
                    r2 = .6;
                    g1 = 1.;
                    g2 = .6;
                    b1 = .0;
                    b2 = .0;
                }

                else
                {
                    r1 = .5;
                    r2 = .3;
                    g1 = 1.;
                    g2 = .3;
                    b1 = .0;
                    b2 = .0;
                }
            }

            glBegin(GL_QUADS);

            glColor3f(r1, g1, b1);
            glVertex2f(x * sz           , y * sz);
            glVertex2f(x * sz + sz * 0.9, y * sz);
            glVertex2f(x * sz + sz * 0.9, y * sz + sz * 0.9);
            glColor3f(r2, g2, b2);
            glVertex2f(x * sz           , y * sz + sz * 0.9);
            glEnd();


            if (field[x][y] != 2)
                field[x][y] = 0;
        }
    }

    // show next
    sz = 0.05f;

    for (int x = 4; --x >= 0;)
        for (int y = 4; --y >= 0;)
        {
            if (!next[y][x])
                continue;

            glColor3f(0.8, 0.8, 0.8);

            glBegin(GL_QUADS);

            glVertex2f(x * sz            + 0.7, y * sz);

            glVertex2f(x * sz + sz * 0.9 + 0.7, y * sz);

            glVertex2f(x * sz + sz * 0.9 + 0.7, y * sz + sz * 0.9);

            glColor3f(0.5, 0.5, 0.5);

            glVertex2f(x * sz            + 0.7, y * sz + sz * 0.9);

            glEnd();
        }
}

void Tetris::SetTetris()
{
    int nblines = 0;

    for (int i = 4; --i >= 0;)
        for (int j = 4; --j >= 0;)
        {
            int x = i + col;
            int y = j + row;

            if (x < 0 || x > 9)
                continue;

            if (y > 19)
                y = 19;

            // current item became a bloc
            if (tet[j][i])
                field[x][y] = 2;
        }

    // end of game

    if (row < 1)
        Reset();

    Next();

    // some lines?
    int cr = 20;

    while (cr)
    {
        bool dr = true;

        for (int i = 10; --i >= 0;)
            if (field[i][cr-1] < 2)
            {
                dr = false;
                break;
            }

        if (!dr)
            cr--;
        else
        {
            for (int tcr = cr; --tcr > 0;)
                for (int i = 10; --i >= 0;)
                    field[i][tcr] = field[i][tcr-1];

            nblines++;
        }
    }

    if (nblines)
    {
        score += nblines;
        printf("[score] %.6d\n", score);
    }
}

void Tetris::Reset()
{
    Time_Elapsed = 0;
    Last_Time = 0;
    Current_Time = 0;

    memset(field, 0, 10 * 20 * sizeof(unsigned char));
    speed = (speed > 0.4) ? 0.1f : 0.5f;

    score = 0;

    Next();
}

void Tetris::Next()
{
    row = 0;
    col = 3;

    memcpy(tet, next, 4 * 4 * sizeof(unsigned char));

    int it = (rand() % 5) * 4;

    for (int i = 4; --i >= 0;)
        for (int j = 4; --j >= 0;)
            next[i][j] = tets[j+it][i];
}
