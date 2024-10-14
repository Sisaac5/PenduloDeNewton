#include <GL/glut.h>
#include <stdio.h>
#include <cmath>

GLint LARGURA = 600,
      ALTURA = 600;

GLfloat LARGURA_BASE = 7.5,
        ALTURA_BASE = 0.8,
        PROFUNDIDADE_BASE = 5.5;

GLfloat LARGURA_HASTE = 0.5,
        ALTURA_HASTE = 5,
        PROFUNDIDADE_HASTE = 0.5;

int qtd_esferas = 5;
float diametro_esfera = 1;
float x_lim = 4;

float camposx = 0;
float camposy = 10;
float camposz = 10.0;
float camrotx = 0;
float camroty = 0;

bool control_flag = true;
float raio;
float angulo = 0;
float incremento = -0.1;
float rotate_axis_x = LARGURA_BASE/2 - diametro_esfera*((qtd_esferas-1) / 2);
float rotate_axis_y;
float rotate_axis_z;

void initGlut(int *argc, char **argv) {
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // Habilita o teste de profundidade
    glutInitWindowSize(LARGURA, ALTURA);
    int largura_tela = glutGet(GLUT_SCREEN_WIDTH);
    int altura_tela = glutGet(GLUT_SCREEN_HEIGHT);
    glutInitWindowPosition((largura_tela - LARGURA) / 2, (altura_tela - ALTURA) / 2);
    glutCreateWindow("Pendulo De Newton");
}

void inicializacao() {
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST); // Habilita o teste de profundidade

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)LARGURA / (GLfloat)ALTURA, 1.0, 100.0); // Define a perspectiva

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2.5, 10, 20, //lookfrom 
              LARGURA_BASE/2, ALTURA_HASTE/2, 0, //lookat 
              0, 1, 0); //vetor normal
}

void drawCube(GLfloat hight, GLfloat width, GLfloat depth,
              float x, float y, float z, float R, float G, float B) {

    GLfloat vertex1[3] = {x - width/2, y, z - depth/2}; 
    GLfloat vertex2[3] = {x - width/2, y + hight, z - depth/2}; 
    GLfloat vertex3[3] = {x - width/2, y + hight, z + depth/2}; 
    GLfloat vertex4[3] = {x - width/2, y, z + depth/2}; 

    GLfloat vertex5[3] = {x + width/2, y, z - depth/2}; 
    GLfloat vertex6[3] = {x + width/2, y + hight, z - depth/2}; 
    GLfloat vertex7[3] = {x + width/2, y + hight, z + depth/2}; 
    GLfloat vertex8[3] = {x + width/2, y, z + depth/2}; 

    glColor3f(R, G, B);

    glBegin(GL_QUADS);  // Inicia o desenho dos quadrados

    // Frente 
    glVertex3fv(vertex1);
    glVertex3fv(vertex2);
    glVertex3fv(vertex3);
    glVertex3fv(vertex4);

    // Traseira 
    glVertex3fv(vertex5);
    glVertex3fv(vertex6);
    glVertex3fv(vertex7);
    glVertex3fv(vertex8);

    // Superior 
    glVertex3fv(vertex2);
    glVertex3fv(vertex3);
    glVertex3fv(vertex7);
    glVertex3fv(vertex6);

    // Inferior 
    glVertex3fv(vertex1);
    glVertex3fv(vertex4);
    glVertex3fv(vertex8);
    glVertex3fv(vertex5);

    // Lateral direita 
    glVertex3fv(vertex3);
    glVertex3fv(vertex4);
    glVertex3fv(vertex8);
    glVertex3fv(vertex7);

    // Lateral esquerda 
    glVertex3fv(vertex1);
    glVertex3fv(vertex2);
    glVertex3fv(vertex6);
    glVertex3fv(vertex5);

    glEnd();  // Fim do desenho dos quadrados
}

double menorRaiz(double a, double b, double c) {
    if (a == 0) {
       printf("Não é uma equação do segundo grau.\n");
        return NAN;  
    }

    double delta = b*b - 4*a*c;

    if (delta > 0) {
        double x1 = (-b + sqrt(delta)) / (2*a);
        double x2 = (-b - sqrt(delta)) / (2*a);
        return (x1 < x2) ? x1 : x2;  
    } else if (delta == 0) {
        return -b / (2*a);  
    } else {
        printf("A equação não possui raízes reais.\n");
        return NAN;  
    }
}

void desenha_esfera(float diametro, float x_c, float y_c, float z_c){
    glPushMatrix();  // Salva a matriz de transformação atual
    glTranslatef(x_c, y_c, z_c);
    glColor3f(1.0f, 0.0f, 0.0f);  // Define a cor da esfera (vermelha)
    glutSolidSphere(diametro/2, 20, 20);  // Desenha uma esfera de raio 1.0 na origem
    glPopMatrix();
}

void desenha_fio(float x_1, float y_1, float z_1,
                 float x_2, float y_2, float z_2){

    glColor3f(0, 0, 1.0f);
    glBegin(GL_LINES);
        glVertex3f(x_1, y_1, z_1);
        glVertex3f(x_2, y_2, z_2);
    glEnd();

}

void posicionarCamara() {
    glTranslatef(LARGURA_BASE/2, ALTURA_BASE + ALTURA_HASTE/2, PROFUNDIDADE_BASE/2);
    glRotatef(camrotx, 1.0, 0.0, 0.0);
    glRotatef(camroty, 0.0, 1.0, 0.0);
    glTranslatef(-LARGURA_BASE/2, -(ALTURA_BASE + ALTURA_HASTE/2), -PROFUNDIDADE_BASE/2);
    camrotx = 0;
    camroty = 0;
}

void esferaAmarrada(float diametro, float angulo,
                    float x_c, float y_c, float z_c){

    glPushMatrix();  // Salva a matriz de transformação atual
    glTranslatef(x_c, y_c, z_c);
    glRotatef(angulo,0,0,1);
    glColor3f(1.0f, 0.0f, 0.0f);  // Define a cor da esfera (vermelha)
    glutSolidSphere(diametro/2, 20, 20);  // Desenha uma esfera de raio 1.0 na origem
    glPopMatrix();

}

void desenha() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    posicionarCamara();

    glColor3f(1.0f, 1.0f, 1.0f);

    drawCube(ALTURA_BASE, LARGURA_BASE, PROFUNDIDADE_BASE, 
            LARGURA_BASE/2 ,0, PROFUNDIDADE_BASE /2, 
            1, 1, 1); // base do pendulo

    //haste 1
    drawCube(ALTURA_HASTE, LARGURA_HASTE, PROFUNDIDADE_HASTE, 
            1,ALTURA_BASE,1,
            0.5, 0.5, 0.5); // vermelha

    //haste 2
    drawCube(ALTURA_HASTE, LARGURA_HASTE, PROFUNDIDADE_HASTE, 
            LARGURA_BASE - 1,ALTURA_BASE, 1,
            0.5, 0.5, 0.5); //verde

    //haste 3
    drawCube(ALTURA_HASTE, LARGURA_HASTE, PROFUNDIDADE_HASTE, 
            LARGURA_BASE - 1 ,ALTURA_BASE, PROFUNDIDADE_BASE - 1,
            0.5, 0.5, 0.5); //amarelo
    
    //haste 4
    drawCube(ALTURA_HASTE, LARGURA_HASTE, PROFUNDIDADE_HASTE, 
            1, ALTURA_BASE, PROFUNDIDADE_BASE - 1,
            0.5, 0.5, 0.5); //azul
 
    //suportes das cordas
    drawCube(PROFUNDIDADE_HASTE, LARGURA_BASE - 1.5, PROFUNDIDADE_HASTE,
            LARGURA_BASE/2, ALTURA_BASE + ALTURA_HASTE, PROFUNDIDADE_BASE - 1,
            0.5, 0.5, 0.5);

    drawCube(PROFUNDIDADE_HASTE, LARGURA_BASE - 1.5, PROFUNDIDADE_HASTE, 
            LARGURA_BASE/2, ALTURA_BASE + ALTURA_HASTE, 1,
            0.5, 0.5, 0.5);

    //desenhado as esferas

    float initial_position_x = LARGURA_BASE/2 - diametro_esfera*((qtd_esferas-1) / 2);

    double y_o = ALTURA_BASE + ALTURA_HASTE + PROFUNDIDADE_HASTE/2;
    double x_o = initial_position_x;

    raio = 2.75;

    double a = 1;
    double b = -2*y_o;
    double c;
    for(int i = 0; i < qtd_esferas; i++){

        if(i == 0 && control_flag){
            c = pow(y_o, 2) + pow(rotate_axis_x - x_o,2) - pow(raio,2);
            desenha_esfera(diametro_esfera,
            rotate_axis_x, menorRaiz(a,b,c), PROFUNDIDADE_BASE/2);

            c = pow(y_o, 2) + pow(rotate_axis_x - x_o,2) - pow(raio - diametro_esfera/4,2);

            desenha_fio(rotate_axis_x, menorRaiz(a,b,c), PROFUNDIDADE_BASE/2,
                        initial_position_x + diametro_esfera*i,ALTURA_BASE + ALTURA_HASTE + PROFUNDIDADE_HASTE/2,1);
            
            desenha_fio(rotate_axis_x, menorRaiz(a,b,c), PROFUNDIDADE_BASE/2,
                        initial_position_x + diametro_esfera*i,ALTURA_BASE + ALTURA_HASTE + PROFUNDIDADE_HASTE/2, PROFUNDIDADE_BASE - 1);

        }
        else if(i == qtd_esferas - 1 && !control_flag){
            c = pow(y_o, 2) + pow((rotate_axis_x + diametro_esfera*i) - (x_o + diametro_esfera*i),2) - pow(raio,2);
            desenha_esfera(diametro_esfera,
            rotate_axis_x + diametro_esfera*i, menorRaiz(a,b,c), PROFUNDIDADE_BASE/2);

            c = pow(y_o, 2) + pow((rotate_axis_x + diametro_esfera*i) - (x_o + diametro_esfera*i),2) - pow(raio - diametro_esfera/4,2);

            desenha_fio(rotate_axis_x + diametro_esfera*i, menorRaiz(a,b,c), PROFUNDIDADE_BASE/2,
                        initial_position_x + diametro_esfera*i,ALTURA_BASE + ALTURA_HASTE + PROFUNDIDADE_HASTE/2,1);
            
            desenha_fio(rotate_axis_x + diametro_esfera*i, menorRaiz(a,b,c), PROFUNDIDADE_BASE/2,
                        initial_position_x + diametro_esfera*i,ALTURA_BASE + ALTURA_HASTE + PROFUNDIDADE_HASTE/2, PROFUNDIDADE_BASE - 1);
        }
        else{ 
            desenha_esfera(diametro_esfera,
            initial_position_x + diametro_esfera*i, ALTURA_BASE + ALTURA_HASTE/2, PROFUNDIDADE_BASE/2);

            desenha_fio(initial_position_x + diametro_esfera*i, ALTURA_BASE + ALTURA_HASTE/2 + diametro_esfera/2, PROFUNDIDADE_BASE/2,
                        initial_position_x + diametro_esfera*i,ALTURA_BASE + ALTURA_HASTE + PROFUNDIDADE_HASTE/2,1);
            
            desenha_fio(initial_position_x+ diametro_esfera*i, ALTURA_BASE + ALTURA_HASTE/2 + diametro_esfera/2, PROFUNDIDADE_BASE/2,
                        initial_position_x + diametro_esfera*i,ALTURA_BASE + ALTURA_HASTE + PROFUNDIDADE_HASTE/2, PROFUNDIDADE_BASE - 1);
        }
    }

    glFlush();
}

void handleSpecialKeys (int key, int x, int y) {
    float inc = 1;
    switch(key) {
        case GLUT_KEY_RIGHT:
            camroty = inc;
            break;
            
        case GLUT_KEY_LEFT:
            camroty = -inc;
            break;
        
        case GLUT_KEY_UP:
            camrotx = -inc; 
            break;
            
        case GLUT_KEY_DOWN:
            camrotx = inc; 
            break;
    }

    glutPostRedisplay();
}

void update(int value){

    float basis = LARGURA_BASE/2 - diametro_esfera*((qtd_esferas-1) / 2);

    rotate_axis_x += incremento;

    if(rotate_axis_x <= basis-2 || rotate_axis_x >= basis+2)
        incremento = -incremento;
    
    if(abs(rotate_axis_x - basis) <= 0.01)
        control_flag = !control_flag;

    glutPostRedisplay();
    glutTimerFunc(20, update, 0);

}

int main(int argc, char *argv[]) {
    initGlut(&argc, argv);
    inicializacao();
    glutDisplayFunc(desenha);
    glutSpecialFunc(handleSpecialKeys);
    glutTimerFunc(20, update, 0);
    glutMainLoop();
    return 0;
}
