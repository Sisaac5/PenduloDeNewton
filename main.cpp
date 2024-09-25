#include <GL/glut.h>
#include <stdio.h>

GLint LARGURA = 600,
      ALTURA = 600;

void initGlut(int *argc, char **argv) {
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // Habilita o teste de profundidade
    glutInitWindowSize(LARGURA, ALTURA);
    int largura_tela = glutGet(GLUT_SCREEN_WIDTH);
    int altura_tela = glutGet(GLUT_SCREEN_HEIGHT);
    glutInitWindowPosition((largura_tela - LARGURA) / 2, (altura_tela - ALTURA) / 2);
    glutCreateWindow("Pêdulo de newton");
    glutSetCursor(GLUT_CURSOR_NONE); 
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

void drawCube() {

    gluLookAt(-1.0f, 3.0f, 3.0f, //lookfrom 
    0, 0, 0, //lookat 
    0, 1, 0); //vetor normal


    glBegin(GL_QUADS);  // Inicia o desenho dos quadrados

    // Frente (Z positivo)
    glColor3f(1.0f, 0.0f, 0.0f); // Cor vermelha
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);

    // Traseira (Z negativo)
    glColor3f(0.0f, 1.0f, 0.0f); // Cor verde
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);

    // Superior (Y positivo)
    glColor3f(0.0f, 0.0f, 1.0f); // Cor azul
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);

    // Inferior (Y negativo)
    glColor3f(1.0f, 1.0f, 0.0f); // Cor amarela
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);

    // Lateral direita (X positivo)
    glColor3f(1.0f, 0.0f, 1.0f); // Cor rosa
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f,  1.0f);
    glVertex3f( 1.0f, -1.0f,  1.0f);

    // Lateral esquerda (X negativo)
    glColor3f(0.0f, 1.0f, 1.0f); // Cor ciano
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f,  1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);

    glEnd();  // Fim do desenho dos quadrados
}

void desenha() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawCube();
    glFlush();
}

int main(int argc, char *argv[]) {
    initGlut(&argc, argv);
    inicializacao();
    glutDisplayFunc(desenha);
    glutWarpPointer(LARGURA / 2, ALTURA / 2);
    glutMainLoop();
    return 0;
}
