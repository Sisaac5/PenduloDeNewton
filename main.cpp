#include <GL/glut.h>
#include <stdio.h>

GLint LARGURA = 1200,
      ALTURA = 1200;

GLfloat LARGURA_BASE = 7.5,
        ALTURA_BASE = 0.8,
        PROFUNDIDADE_BASE = 5.5;

GLfloat LARGURA_HASTE = 0.5,
        ALTURA_HASTE = 5,
        PROFUNDIDADE_HASTE = 0.5;


void initGlut(int *argc, char **argv) {
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // Habilita o teste de profundidade
    glutInitWindowSize(LARGURA, ALTURA);
    int largura_tela = glutGet(GLUT_SCREEN_WIDTH);
    int altura_tela = glutGet(GLUT_SCREEN_HEIGHT);
    glutInitWindowPosition((largura_tela - LARGURA) / 2, (altura_tela - ALTURA) / 2);
    glutCreateWindow("Pendulo De Newton");
    //glutSetCursor(GLUT_CURSOR_NONE); 
}

void inicializacao() {
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST); // Habilita o teste de profundidade

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)LARGURA / (GLfloat)ALTURA, 1.0, 100.0); // Define a perspectiva

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f); // Afasta a câmera do cubo
}

void drawCube(GLfloat hight, GLfloat width, GLfloat depth,
              float x, float y, float z, float R, float G, float B) {

    glColor3f(R, G, B);

    glBegin(GL_QUADS);  // Inicia o desenho dos quadrados

    // Frente 
    glVertex3f(x, y, z);
    glVertex3f(x, y + hight, z);
    glVertex3f(x, y + hight, z + depth);
    glVertex3f(x, y, z + depth);

    // Traseira 
    glVertex3f(x + width, y, z);
    glVertex3f(x + width, y + hight, z);
    glVertex3f(x + width, y + hight, z + depth);
    glVertex3f(x + width, y, z + depth);

    // Superior 
    glVertex3f(x, y + hight, z);
    glVertex3f(x, y + hight, z + depth);
    glVertex3f(x + width, y + hight, z + depth);
    glVertex3f(x + width, y + hight, z);

    // Inferior 
    glVertex3f(x, y, z);
    glVertex3f(x, y, z + depth);
    glVertex3f(x + width, y, z + depth);
    glVertex3f(x + width, y, z);

    // Lateral direita 
    glVertex3f(x, y, z);
    glVertex3f(x, y + hight, z);
    glVertex3f(x + width, y + hight, z);
    glVertex3f(x + width, y, z);

    // Lateral esquerda 
    glVertex3f(x, y, z + depth);
    glVertex3f(x, y + hight, z + depth);
    glVertex3f(x + width, y + hight, z + depth);
    glVertex3f(x + width, y, z + depth);


    glEnd();  // Fim do desenho dos quadrados
}

void desenha() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    gluLookAt(0, 10, 10, //lookfrom 
    5, 0, 0, //lookat 
    0, 1, 0); //vetor normal

    glColor3f(1.0f, 1.0f, 1.0f);

    drawCube(ALTURA_BASE, LARGURA_BASE, PROFUNDIDADE_BASE, 
            0,0,0, 1, 1, 1); // base do pendulo

    glColor3f(0.5f, 0.5f, 0.5f); // Cor ciano
    
    //haste 1
    drawCube(ALTURA_HASTE, LARGURA_HASTE, PROFUNDIDADE_HASTE, 
            1,ALTURA_BASE,0.5, 1, 0, 0); // vermelha

    //haste 2
    drawCube(ALTURA_HASTE, LARGURA_HASTE, PROFUNDIDADE_HASTE, 
            LARGURA_BASE - 1 ,ALTURA_BASE, 0.5, 0, 1, 0); //verde

    //haste 3
    drawCube(ALTURA_HASTE, LARGURA_HASTE, PROFUNDIDADE_HASTE, 
            LARGURA_BASE - 1 ,ALTURA_BASE, PROFUNDIDADE_BASE - 1, 1, 1, 0); //amarelo
    
    //haste 4
    drawCube(ALTURA_HASTE, LARGURA_HASTE, PROFUNDIDADE_HASTE, 
            1,ALTURA_BASE,PROFUNDIDADE_BASE - 1, 0, 0, 1); //azul
 
    //suportes das cordas
//     drawCube(ALTURA_HASTE, LARGURA_HASTE, PROFUNDIDADE_HASTE, 
//             1,ALTURA_BASE,PROFUNDIDADE_BASE - 1);

//     drawCube(ALTURA_HASTE, LARGURA_HASTE, PROFUNDIDADE_HASTE, 
//             1,ALTURA_BASE,PROFUNDIDADE_BASE - 1);

    glFlush();
}

int main(int argc, char *argv[]) {
    initGlut(&argc, argv);
    inicializacao();
    glutDisplayFunc(desenha);
    //glutWarpPointer(LARGURA / 2, ALTURA / 2);
    glutMainLoop();
    return 0;
}
