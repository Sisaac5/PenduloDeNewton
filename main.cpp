#include <GL/glut.h>
#include <stdio.h>
#include <cmath>

GLint LARGURA = 600,
      ALTURA = 600;

GLfloat LARGURA_BASE = 10,
        ALTURA_BASE = 0.8,
        PROFUNDIDADE_BASE = 5.5;

GLfloat LARGURA_HASTE = 0.25,
        ALTURA_HASTE = 5,
        PROFUNDIDADE_HASTE = 0.25;

int qtd_esferas = 5;
float diametro_esfera = 1;

float camrotx = 0;
float camroty = 0;

bool control_flag = true;
float raio = 2.75;
float incremento = -0.15;
float deslocamento_x = LARGURA_BASE/2 - diametro_esfera*((qtd_esferas-1) / 2);

GLfloat matAmbiente_esfera[] = { 0.3f, 0.3f, 0.3f, 1.0f }; 
GLfloat matDifuso_esfera[] = { 0.6f, 0.6f, 0.6f, 1.0f };  
GLfloat matEspecular_esfera[] = { 0.9f, 0.9f, 0.9f, 1.0f }; 
GLfloat brilho_esfera = 100.0f;  

GLfloat matAmbiente_haste[] = {0.25f, 0.25f, 0.25f, 1.0f};  
GLfloat matDifuso_haste[] =  {0.4f, 0.4f, 0.4f, 1.0f};    
GLfloat matEspecular_haste[] = {0.77f, 0.77f, 0.77f, 1.0f}; 
GLfloat brilho_haste = 50.0f; 

GLfloat matAmbiente_base[] = { 0.25f, 0.15f, 0.05f, 1.0f };  
GLfloat matDifuso_base[] = { 0.4f, 0.25f, 0.1f, 1.0f };    
GLfloat matEspecular_base[] = { 0.1f, 0.1f, 0.1f, 1.0f };
GLfloat brilho_base = 76.8f;

GLfloat matAmbiente_fio[] = { 0.8f, 0.8f, 0.85f, 1.0f };   
GLfloat matDifuso_fio[] = { 0.9f, 0.9f, 0.95f, 1.0f };     
GLfloat matEspecular_fio[] = { 0.4f, 0.4f, 0.4f, 1.0f };
GLfloat brilho_fio = 50.0f;                               

GLfloat luzAmbiente[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat luzDifusa[] = { 1.0f, 1.0f, 1.0f, 1.0f  };    
GLfloat luzEspecular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
GLfloat posicaoLuz[] = { 2.5f, 10.0f, 20.0f, 1.0f }; 


static int menuTotalEsf;


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

    // Ativar a iluminação
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);  // Usar GL_LIGHT0

    // Definir a luz
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

}

void desenhaCubo(GLfloat hight, GLfloat width, GLfloat depth,
              float x, float y, float z,
			  GLfloat *matAmbiente, GLfloat *matDifuso, GLfloat *matEspecular, GLfloat brilho){

    GLfloat vertex1[3] = {x - width/2, y, z - depth/2}; 
    GLfloat vertex2[3] = {x - width/2, y + hight, z - depth/2}; 
    GLfloat vertex3[3] = {x - width/2, y + hight, z + depth/2}; 
    GLfloat vertex4[3] = {x - width/2, y, z + depth/2}; 

    GLfloat vertex5[3] = {x + width/2, y, z - depth/2}; 
    GLfloat vertex6[3] = {x + width/2, y + hight, z - depth/2}; 
    GLfloat vertex7[3] = {x + width/2, y + hight, z + depth/2}; 
    GLfloat vertex8[3] = {x + width/2, y, z + depth/2}; 

	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbiente);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifuso);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matEspecular);
    glMaterialf(GL_FRONT, GL_SHININESS, brilho);

    glBegin(GL_QUADS);  // Inicia o desenho dos quadrados

    // Frente
	glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3fv(vertex1);
    glVertex3fv(vertex2);
    glVertex3fv(vertex3);
    glVertex3fv(vertex4);

    // Traseira 
	glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3fv(vertex5);
    glVertex3fv(vertex6);
    glVertex3fv(vertex7);
    glVertex3fv(vertex8);

    // Superior 
	glNormal3f(0.0f, 1.0f, 0.0f); 
    glVertex3fv(vertex2);
    glVertex3fv(vertex3);
    glVertex3fv(vertex7);
    glVertex3fv(vertex6);

    // Inferior 
	glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3fv(vertex1);
    glVertex3fv(vertex4);
    glVertex3fv(vertex8);
    glVertex3fv(vertex5);

    // Lateral direita 
	glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3fv(vertex3);
    glVertex3fv(vertex4);
    glVertex3fv(vertex8);
    glVertex3fv(vertex7);

    // Lateral esquerda 
	glNormal3f(-1.0f, 0.0f, 0.0f);
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
    glPushMatrix();  

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbiente_esfera);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifuso_esfera);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matEspecular_esfera);
    glMaterialf(GL_FRONT, GL_SHININESS, brilho_esfera);

    glTranslatef(x_c, y_c, z_c);
    glColor3f(1.0f, 0.0f, 0.0f);  
    glutSolidSphere(diametro/2, 20, 20); 
    glPopMatrix();
}

void desenha_fio(float x_1, float y_1, float z_1,
                 float x_2, float y_2, float z_2,
				 GLfloat *matAmbiente, GLfloat *matDifuso, GLfloat *matEspecular, GLfloat brilho){

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbiente_esfera);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifuso_esfera);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matEspecular_esfera);
    glMaterialf(GL_FRONT, GL_SHININESS, brilho_esfera);

    glBegin(GL_LINES);
        glVertex3f(x_1, y_1, z_1);
        glVertex3f(x_2, y_2, z_2);
    glEnd();

}


void posicionarCamera() {
    glTranslatef(LARGURA_BASE/2, ALTURA_BASE + ALTURA_HASTE/2, PROFUNDIDADE_BASE/2);
    glRotatef(camrotx, 1.0, 0.0, 0.0);
    glRotatef(camroty, 0.0, 1.0, 0.0);
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
    glTranslatef(-LARGURA_BASE/2, -(ALTURA_BASE + ALTURA_HASTE/2), -PROFUNDIDADE_BASE/2);

    camrotx = 0;
    camroty = 0;
}

void desenha_base(){
    desenhaCubo(ALTURA_BASE, LARGURA_BASE, PROFUNDIDADE_BASE, 
            LARGURA_BASE/2 ,0, PROFUNDIDADE_BASE /2, 
            matAmbiente_base, matDifuso_base, matEspecular_base, brilho_base);
}

void desenha_hastes(){

        //haste 1
    desenhaCubo(ALTURA_HASTE, LARGURA_HASTE, PROFUNDIDADE_HASTE, 
            1,ALTURA_BASE,1,
			matAmbiente_haste, matDifuso_haste, matEspecular_haste, brilho_haste); // vermelha

    //haste 2
    desenhaCubo(ALTURA_HASTE, LARGURA_HASTE, PROFUNDIDADE_HASTE, 
            LARGURA_BASE - 1,ALTURA_BASE, 1,
			matAmbiente_haste, matDifuso_haste, matEspecular_haste, brilho_haste); //verde

    //haste 3
    desenhaCubo(ALTURA_HASTE, LARGURA_HASTE, PROFUNDIDADE_HASTE, 
            LARGURA_BASE - 1 ,ALTURA_BASE, PROFUNDIDADE_BASE - 1,
			matAmbiente_haste, matDifuso_haste, matEspecular_haste, brilho_haste); //amarelo
    
    //haste 4
    desenhaCubo(ALTURA_HASTE, LARGURA_HASTE, PROFUNDIDADE_HASTE, 
            1, ALTURA_BASE, PROFUNDIDADE_BASE - 1, 
			matAmbiente_haste, matDifuso_haste, matEspecular_haste, brilho_haste); //azul

}

void desenha_suportes(){
        //suportes das cordas
    desenhaCubo(PROFUNDIDADE_HASTE, LARGURA_BASE - 1.5, PROFUNDIDADE_HASTE,
            LARGURA_BASE/2, ALTURA_BASE + ALTURA_HASTE, PROFUNDIDADE_BASE - 1, 
			matAmbiente_haste, matDifuso_haste, matEspecular_haste, brilho_haste);

    desenhaCubo(PROFUNDIDADE_HASTE, LARGURA_BASE - 1.5, PROFUNDIDADE_HASTE, 
            LARGURA_BASE/2, ALTURA_BASE + ALTURA_HASTE, 1,
			matAmbiente_haste, matDifuso_haste, matEspecular_haste, brilho_haste);
}

void desenha_esferas_pendulo(){
    float initial_position_x = LARGURA_BASE/2 - diametro_esfera*((qtd_esferas-1) / 2);

    double y_o = ALTURA_BASE + ALTURA_HASTE + PROFUNDIDADE_HASTE/2;
    
    double a = 1;
    double b = -2*y_o;
    double c;

    int indice_esfera_movimento = control_flag ? 0 : qtd_esferas - 1;

    for(int i = 0; i < qtd_esferas; i++){

        if(i == indice_esfera_movimento){
            c = pow(y_o, 2) + pow((deslocamento_x + diametro_esfera*i) - (initial_position_x + diametro_esfera*i),2) - pow(raio,2);

            desenha_esfera(diametro_esfera,
                        deslocamento_x + diametro_esfera*i, menorRaiz(a,b,c), PROFUNDIDADE_BASE/2);

            desenha_fio(deslocamento_x + diametro_esfera*i, menorRaiz(a,b,c) + diametro_esfera/2, PROFUNDIDADE_BASE/2,
                        initial_position_x + diametro_esfera*i,ALTURA_BASE + ALTURA_HASTE + PROFUNDIDADE_HASTE/2,1,
						matAmbiente_fio, matDifuso_fio, matEspecular_fio, brilho_fio);
            
            desenha_fio(deslocamento_x + diametro_esfera*i, menorRaiz(a,b,c) + diametro_esfera/2, PROFUNDIDADE_BASE/2,
                        initial_position_x + diametro_esfera*i,ALTURA_BASE + ALTURA_HASTE + PROFUNDIDADE_HASTE/2, PROFUNDIDADE_BASE - 1,
						matAmbiente_fio, matDifuso_fio, matEspecular_fio, brilho_fio);
        }
        else{ 
            desenha_esfera(diametro_esfera,
                        initial_position_x + diametro_esfera*i, ALTURA_BASE + ALTURA_HASTE/2, PROFUNDIDADE_BASE/2);

            desenha_fio(initial_position_x + diametro_esfera*i, ALTURA_BASE + ALTURA_HASTE/2 + diametro_esfera/2, PROFUNDIDADE_BASE/2,
                        initial_position_x + diametro_esfera*i,ALTURA_BASE + ALTURA_HASTE + PROFUNDIDADE_HASTE/2,1,
						matAmbiente_fio, matDifuso_fio, matEspecular_fio, brilho_fio);
            
            desenha_fio(initial_position_x+ diametro_esfera*i, ALTURA_BASE + ALTURA_HASTE/2 + diametro_esfera/2, PROFUNDIDADE_BASE/2,
                        initial_position_x + diametro_esfera*i,ALTURA_BASE + ALTURA_HASTE + PROFUNDIDADE_HASTE/2, PROFUNDIDADE_BASE - 1,
						matAmbiente_fio, matDifuso_fio, matEspecular_fio, brilho_fio);
        }
    }
}

void desenha() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    posicionarCamera();

    desenha_base();
    desenha_hastes();
    desenha_suportes();
    desenha_esferas_pendulo();

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

    deslocamento_x += incremento;

    if(deslocamento_x <= basis-2 || deslocamento_x >= basis+2)
        incremento = -incremento;
    
    if(abs(deslocamento_x - basis) <= 0.01)
        control_flag = !control_flag;

    glutPostRedisplay();
    glutTimerFunc(20, update, 0);

}

void handleMenuTotalEsf(int m) { 
    qtd_esferas = m;
    deslocamento_x = LARGURA_BASE/2 - diametro_esfera*((qtd_esferas-1) / 2);
    control_flag = true;
    incremento = -0.15;
    glutPostRedisplay();
}

void prepararMenu() {
    menuTotalEsf = glutCreateMenu(handleMenuTotalEsf);
    glutAddMenuEntry("1", 1);
    glutAddMenuEntry("2", 2);
    glutAddMenuEntry("3", 3);
    glutAddMenuEntry("4", 4);
    glutAddMenuEntry("5", 5);
    glutAddMenuEntry("6", 6);
    glutAddMenuEntry("7", 7);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
}

int main(int argc, char *argv[]) {
    initGlut(&argc, argv);
    inicializacao();
    
    prepararMenu();

    glutDisplayFunc(desenha);
    //glutMouseFunc(handleMouse);
    glutSpecialFunc(handleSpecialKeys);
    glutTimerFunc(20, update, 0);
    glutMainLoop();
    return 0;
}