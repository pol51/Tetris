#include <game.h>

#include <cmath>
#include <ctime>
#include <cstdlib>
#include <GL/glut.h>

Game *Game::inst = NULL;

int Game::run()
{
    inst = this;

    //initialisation window
    win_main = 0;

    //initialisation des nombres alleatoires
    srand(time(NULL));

    int a = 0;

    //initialisation de glut et creation de la fenetre principale
    glutInit(&a, NULL);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(scrW, scrH);
    win_main = glutCreateWindow("Tetris");
    glOrtho(-0.001, 1.001, 1.001, -0.001, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    //win_main = glutEnterGameMode();
    glutSetCursor(GLUT_CURSOR_NONE);

    //initialisation d'OpenGL
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    glShadeModel(GL_SMOOTH);

    //mise en place des fonctions de rappel
    glutDisplayFunc(affichage);
    glutKeyboardFunc(clavier);
    glutSpecialFunc(special);
    glutIdleFunc(idle);

    //entree dans la boucle principale
    glutMainLoop();

    timer.reset();

    return 0;
}

void Game::affichage()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    inst->tet.Draw();

    glFlush();
    glutSwapBuffers();
}

void Game::clavier(unsigned char touche, int x, int y)
{
    switch (touche)
    {
    case 27:
        exit(EXIT_SUCCESS);
    }
}

void Game::special(int touche, int x, int y)
{
    switch (touche)
    {
    case GLUT_KEY_LEFT:
        inst->tet.MoveLeft();
        break;
    case GLUT_KEY_DOWN:
        inst->tet.MoveDown(inst->speed / 200);
        break;
    case GLUT_KEY_RIGHT:
        inst->tet.MoveRight();
        break;
    case GLUT_KEY_UP:
        inst->tet.Rotate();
        break;
    default:
        break;
    }
}

void Game::idle()
{
    inst->tet.Current_Time = (long)(inst->timer.time());
    inst->tet.Time_Elapsed = (inst->tet.Current_Time - inst->tet.Last_Time) * inst->Time_Scale;

    inst->tet.MoveDown(inst->speed);
    glutPostRedisplay();
}
