#include <GL/glut.h>
#include <stdio.h>
#include <cmath>

GLint LARGURA = 600, //largura da janela
      ALTURA = 600; //altura da janela


//a base do pendulo é um cubo
GLfloat LARGURA_BASE = 10, //largura da base do pendulo
        ALTURA_BASE = 0.8, //altura da base do pendulo
        PROFUNDIDADE_BASE = 5.5; //profundidade da base do pendulo

//as hastes do pendulo são cubos
GLfloat LARGURA_HASTE = 0.25, //largura das hastes do pendulo
        ALTURA_HASTE = 5, //altura das hastes do pendulo
        PROFUNDIDADE_HASTE = 0.25; //profundidade das hastes do pendulo

static int menuTotalEsf;

int qtd_esferas = 5; //quantidade total de esferas no pendulo
float diametro_esfera = 1; //diamento das esferas

float camrotx = 0; //variavel que controla a rotação no eixo x
float camroty = 0; //variavel que controla a rotação no eixo y

bool control_flag = true; //flag que controla qual das esferas está em movimento
float raio = 2.75; // raio da circunferencia de trajetoria do pendulo
float incremento = -0.15; //incremento ocorrido a cada frame na posição x da esfera em movimento
float deslocamento_x = LARGURA_BASE/2 - diametro_esfera*((qtd_esferas-1) / 2); // posição atual da esfera em movimento (incia com a esfera da esquerda em repouso)

// propriedades dos materiais relaxionadas aos modelos de iluminação

//esferas
GLfloat matAmbiente_esfera[] = { 0.3f, 0.3f, 0.3f, 1.0f }; //reflexão luz ambiente
GLfloat matDifuso_esfera[] = { 0.6f, 0.6f, 0.6f, 1.0f };  //reflexão luz difusa
GLfloat matEspecular_esfera[] = { 0.9f, 0.9f, 0.9f, 1.0f }; //reflexão luz especular
GLfloat brilho_esfera = 100.0f;   //brilho

//hastes
GLfloat matAmbiente_haste[] = {0.25f, 0.25f, 0.25f, 1.0f};  //reflexão luz ambiente
GLfloat matDifuso_haste[] =  {0.4f, 0.4f, 0.4f, 1.0f};    //reflexão luz difusa
GLfloat matEspecular_haste[] = {0.77f, 0.77f, 0.77f, 1.0f}; 
GLfloat brilho_haste = 50.0f; //brilho

//base
GLfloat matAmbiente_base[] = { 0.25f, 0.15f, 0.05f, 1.0f };  //reflexão luz ambiente
GLfloat matDifuso_base[] = { 0.4f, 0.25f, 0.1f, 1.0f };    //reflexão luz difusa
GLfloat matEspecular_base[] = { 0.1f, 0.1f, 0.1f, 1.0f };//reflexão luz especular
GLfloat brilho_base = 76.8f;//brilho

//fio
GLfloat matAmbiente_fio[] = { 0.8f, 0.8f, 0.85f, 1.0f };   //reflexão luz ambiente
GLfloat matDifuso_fio[] = { 0.9f, 0.9f, 0.95f, 1.0f };     //reflexão luz difusa
GLfloat matEspecular_fio[] = { 0.4f, 0.4f, 0.4f, 1.0f };//reflexão luz especular
GLfloat brilho_fio = 50.0f;  //brilho                             

//caracteristicas da fonte de luz
GLfloat luzAmbiente[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //reflexão luz ambiente
GLfloat luzDifusa[] = { 1.0f, 1.0f, 1.0f, 1.0f  };    //reflexão luz difusa
GLfloat luzEspecular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //reflexão luz especular
GLfloat posicaoLuz[] = { 2.5f, 10.0f, 20.0f, 1.0f }; //brilho


void initGlut(int *argc, char **argv) {
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // Habilita o teste de profundidade
    glutInitWindowSize(LARGURA, ALTURA);
    int largura_tela = glutGet(GLUT_SCREEN_WIDTH);
    int altura_tela = glutGet(GLUT_SCREEN_HEIGHT);
    glutInitWindowPosition((largura_tela - LARGURA) / 2, (altura_tela - ALTURA) / 2); //posiciona janela no centro do display
    glutCreateWindow("Pendulo De Newton");
}

void inicializacao() {
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST); // Habilita o teste de profundidade

    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, (GLfloat)LARGURA / (GLfloat)ALTURA, 1.0, 100.0); // Define a perspectiva

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(2.5, 10, 20, //lookfrom 
              LARGURA_BASE/2, ALTURA_HASTE/2, 0, //lookat 
              0, 1, 0); //vetor normal

    // Ativar a iluminação
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0); 

    //inicializa fonte de luz
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

}

//função que desenha um cubo e recebe como parametros suas dimensões (altura, largura e profundidade)
//as coordenadas (centro da base)
//propriedades luminosas do material 
void desenhaCubo(GLfloat hight, GLfloat width, GLfloat depth,
              float x, float y, float z,
			  GLfloat *matAmbiente, GLfloat *matDifuso, GLfloat *matEspecular, GLfloat brilho){
    
    //define os vertices do cubo de acordo com as coordenadas do centro da base e com as dimensões 
    GLfloat vertex1[3] = {x - width/2, y, z - depth/2}; 
    GLfloat vertex2[3] = {x - width/2, y + hight, z - depth/2}; 
    GLfloat vertex3[3] = {x - width/2, y + hight, z + depth/2}; 
    GLfloat vertex4[3] = {x - width/2, y, z + depth/2}; 

    GLfloat vertex5[3] = {x + width/2, y, z - depth/2}; 
    GLfloat vertex6[3] = {x + width/2, y + hight, z - depth/2}; 
    GLfloat vertex7[3] = {x + width/2, y + hight, z + depth/2}; 
    GLfloat vertex8[3] = {x + width/2, y, z + depth/2}; 

    //define o mateiral de acordo com as caracteristicas entregues como parametro
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbiente);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifuso);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matEspecular);
    glMaterialf(GL_FRONT, GL_SHININESS, brilho);

    //desenha 8 quadrados, para formar um cubo de 8 faces
    glBegin(GL_QUADS);  // Inicia o desenho dos quadrados

    // Frente
	glNormal3f(0.0f, 0.0f, 1.0f); //normal da face
    glVertex3fv(vertex1);
    glVertex3fv(vertex2);
    glVertex3fv(vertex3);
    glVertex3fv(vertex4);

    // Traseira 
	glNormal3f(0.0f, 0.0f, -1.0f); //normal da face
    glVertex3fv(vertex5);
    glVertex3fv(vertex6);
    glVertex3fv(vertex7);
    glVertex3fv(vertex8);

    // Superior 
	glNormal3f(0.0f, 1.0f, 0.0f); //normal da face
    glVertex3fv(vertex2);
    glVertex3fv(vertex3);
    glVertex3fv(vertex7);
    glVertex3fv(vertex6);

    // Inferior 
	glNormal3f(0.0f, -1.0f, 0.0f); //normal da face
    glVertex3fv(vertex1);
    glVertex3fv(vertex4);
    glVertex3fv(vertex8);
    glVertex3fv(vertex5);

    // Lateral direita 
	glNormal3f(1.0f, 0.0f, 0.0f); //normal da face
    glVertex3fv(vertex3);
    glVertex3fv(vertex4);
    glVertex3fv(vertex8);
    glVertex3fv(vertex7);

    // Lateral esquerda 
	glNormal3f(-1.0f, 0.0f, 0.0f); //normal da face
    glVertex3fv(vertex1);
    glVertex3fv(vertex2);
    glVertex3fv(vertex6);
    glVertex3fv(vertex5);

    glEnd();  // Fim do desenho dos quadrados
}

//função que retorna a menor raiz de uma equação do segundo grau. Necessaria para verificar a posição em y das esferas em movimento
//recebe os coeficientes a, b e c da equação
double menorRaiz(double a, double b, double c) {
    if (a == 0) { //verifica se os parametros são de uma equação do segundo grau
       printf("Não é uma equação do segundo grau.\n");
        return NAN;  
    }

    double delta = b*b - 4*a*c; // calcula o delta

    if (delta > 0) {
        double x1 = (-b + sqrt(delta)) / (2*a);
        double x2 = (-b - sqrt(delta)) / (2*a); //calcula as duas raizes 
        return (x1 < x2) ? x1 : x2;  //retorna a menor delas
    } else if (delta == 0) { 
        return -b / (2*a);  //se existir apenas uma raiz, retorna a raiz existente
    } else {
        printf("A equação não possui raízes reais.\n"); //tratamento para raizes imaginarias
        return NAN;  
    }
}

//funcao que desenha uma esfera e recebe como paramentros 
//diametro da esfera e coordenadas do centro da esfera

void desenha_esfera(float diametro, float x_c, float y_c, float z_c){
    glPushMatrix();  //guarda o estado atual da matriz de transformação

    //caracteristicas luminosas do material da esfera
    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbiente_esfera);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifuso_esfera);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matEspecular_esfera);
    glMaterialf(GL_FRONT, GL_SHININESS, brilho_esfera);

    //translada para o centro da esfera passado como parametro
    glTranslatef(x_c, y_c, z_c);

    glutSolidSphere(diametro/2, 20, 20);  //desenha a esfera

    glPopMatrix(); //restaura a matriz de transformação para o estado anterior
}

//função que densenha os fios do pendulo e recebe como parametros
//ponto que começa o fio e ponto que termina o fio
//caracteristicas luminosas do material
void desenha_fio(float x_1, float y_1, float z_1,
                 float x_2, float y_2, float z_2,
				 GLfloat *matAmbiente, GLfloat *matDifuso, GLfloat *matEspecular, GLfloat brilho){
    
    //caracteristicas luminosas do material
    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbiente_esfera);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDifuso_esfera);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matEspecular_esfera);
    glMaterialf(GL_FRONT, GL_SHININESS, brilho_esfera);

    //desenha linhas com o material
    glBegin(GL_LINES);
        glVertex3f(x_1, y_1, z_1);
        glVertex3f(x_2, y_2, z_2);
    glEnd();

}

//função que atualiza a matriz de transformação de acordo com as rotações feitas pelo botão
void posicionarCamera() {
    glTranslatef(LARGURA_BASE/2, ALTURA_BASE + ALTURA_HASTE/2, PROFUNDIDADE_BASE/2); //translação dos eixos para o meio do pendulo
    glRotatef(camrotx, 1.0, 0.0, 0.0); //rotação em x controlado pela variavel camrotx
    glRotatef(camroty, 0.0, 1.0, 0.0); //rotação em y controlado pela variavel camroty
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz); //redefine a posição da luz
    glTranslatef(-LARGURA_BASE/2, -(ALTURA_BASE + ALTURA_HASTE/2), -PROFUNDIDADE_BASE/2); //translada os eixos para posição original

    camrotx = 0; //zera as variaveis de controle 
    camroty = 0;
}

//função que desenha a base do pendulo
void desenha_base(){
    desenhaCubo(ALTURA_BASE, LARGURA_BASE, PROFUNDIDADE_BASE, //dimensoes
            LARGURA_BASE/2 ,0, PROFUNDIDADE_BASE /2, //coordenadas
            matAmbiente_base, matDifuso_base, matEspecular_base, brilho_base); //material
}

//função que desenha as hastes do pendulo
void desenha_hastes(){

    //haste 1
    desenhaCubo(ALTURA_HASTE, LARGURA_HASTE, PROFUNDIDADE_HASTE, 
            1,ALTURA_BASE,1,
			matAmbiente_haste, matDifuso_haste, matEspecular_haste, brilho_haste); 

    //haste 2
    desenhaCubo(ALTURA_HASTE, LARGURA_HASTE, PROFUNDIDADE_HASTE, 
            LARGURA_BASE - 1,ALTURA_BASE, 1,
			matAmbiente_haste, matDifuso_haste, matEspecular_haste, brilho_haste); 

    //haste 3
    desenhaCubo(ALTURA_HASTE, LARGURA_HASTE, PROFUNDIDADE_HASTE, 
            LARGURA_BASE - 1 ,ALTURA_BASE, PROFUNDIDADE_BASE - 1,
			matAmbiente_haste, matDifuso_haste, matEspecular_haste, brilho_haste); 
    
    //haste 4
    desenhaCubo(ALTURA_HASTE, LARGURA_HASTE, PROFUNDIDADE_HASTE, 
            1, ALTURA_BASE, PROFUNDIDADE_BASE - 1, 
			matAmbiente_haste, matDifuso_haste, matEspecular_haste, brilho_haste); 

}

//função que desenha os suportes dos fios (dastes horizontais)
void desenha_suportes(){
        
    desenhaCubo(PROFUNDIDADE_HASTE, LARGURA_BASE - 1.5, PROFUNDIDADE_HASTE,
            LARGURA_BASE/2, ALTURA_BASE + ALTURA_HASTE, PROFUNDIDADE_BASE - 1, 
			matAmbiente_haste, matDifuso_haste, matEspecular_haste, brilho_haste);

    desenhaCubo(PROFUNDIDADE_HASTE, LARGURA_BASE - 1.5, PROFUNDIDADE_HASTE, 
            LARGURA_BASE/2, ALTURA_BASE + ALTURA_HASTE, 1,
			matAmbiente_haste, matDifuso_haste, matEspecular_haste, brilho_haste);
}

//função responsavel por desenhar as esferas amarradas no pendulo e por controlar seus posicionamentos
void desenha_esferas_pendulo(){
    float initial_position_x = LARGURA_BASE/2 - diametro_esfera*((qtd_esferas-1) / 2); //coordenada em x que da primeria esfera em repouso

    double y_o = ALTURA_BASE + ALTURA_HASTE + PROFUNDIDADE_HASTE/2; //coordenada y do centro da circunferencia que descreve o movimento do pendulo
    
    double a = 1; //coeficiente a da equação de segundo grau
    double b = -2*y_o; //coeficiente b da equação de segundo grau
    double c; //coeficiente c da equação de segundo grau (calculado a cada rederização da esfera em movimento)

    int indice_esfera_movimento = control_flag ? 0 : qtd_esferas - 1; //verifica qual esfeferas está em moviemento

    for(int i = 0; i < qtd_esferas; i++){

        if(i == indice_esfera_movimento){//desenha a esfera em movimento
            c = pow(y_o, 2) + pow((deslocamento_x + diametro_esfera*i) - (initial_position_x + diametro_esfera*i),2) - pow(raio,2); //coeficiente c da eq do segundo grau calculado de acordo com a posição atual da esfera em x

            desenha_esfera(diametro_esfera,
                        deslocamento_x + diametro_esfera*i, menorRaiz(a,b,c), PROFUNDIDADE_BASE/2); //desenha a esfera em movimento com base no valor atual do x e do resultado da equação, com o valor de z fixo

            //desenha os fios conectados ao suporte do pendulo e a parte superior da esfera
            desenha_fio(deslocamento_x + diametro_esfera*i, menorRaiz(a,b,c) + diametro_esfera/2, PROFUNDIDADE_BASE/2,
                        initial_position_x + diametro_esfera*i,ALTURA_BASE + ALTURA_HASTE + PROFUNDIDADE_HASTE/2,1,
						matAmbiente_fio, matDifuso_fio, matEspecular_fio, brilho_fio);
            
            desenha_fio(deslocamento_x + diametro_esfera*i, menorRaiz(a,b,c) + diametro_esfera/2, PROFUNDIDADE_BASE/2,
                        initial_position_x + diametro_esfera*i,ALTURA_BASE + ALTURA_HASTE + PROFUNDIDADE_HASTE/2, PROFUNDIDADE_BASE - 1,
						matAmbiente_fio, matDifuso_fio, matEspecular_fio, brilho_fio);
        }
        else{ //desenha as esfereras que não se movimentam
            desenha_esfera(diametro_esfera, //posição fixa calculada de acordo com o numero de esferas e com o diametro da esfera
                        initial_position_x + diametro_esfera*i, ALTURA_BASE + ALTURA_HASTE/2, PROFUNDIDADE_BASE/2);
            //desenha os fios conectados ao suporte do pendulo e a parte superior da esfera
            desenha_fio(initial_position_x + diametro_esfera*i, ALTURA_BASE + ALTURA_HASTE/2 + diametro_esfera/2, PROFUNDIDADE_BASE/2,
                        initial_position_x + diametro_esfera*i,ALTURA_BASE + ALTURA_HASTE + PROFUNDIDADE_HASTE/2,1,
						matAmbiente_fio, matDifuso_fio, matEspecular_fio, brilho_fio);
            //desenha os fios conectados ao suporte do pendulo e a parte superior da esfera
            desenha_fio(initial_position_x+ diametro_esfera*i, ALTURA_BASE + ALTURA_HASTE/2 + diametro_esfera/2, PROFUNDIDADE_BASE/2,
                        initial_position_x + diametro_esfera*i,ALTURA_BASE + ALTURA_HASTE + PROFUNDIDADE_HASTE/2, PROFUNDIDADE_BASE - 1,
						matAmbiente_fio, matDifuso_fio, matEspecular_fio, brilho_fio);
        }
    }
}

void desenha() {//desenha toda a cena
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    posicionarCamera(); //posição da camera atualizada todas as vezes, para verificar se o pendulo foi rotacionado

    desenha_base();
    desenha_hastes();
    desenha_suportes();
    desenha_esferas_pendulo();

    glFlush();
}

//função que lida com os botões do teclado setinhas que rotacionam
void handleSpecialKeys (int key, int x, int y) {
    float inc = 1;
    switch(key) { //muda a variavel de rotação de acordo com a setinha pressionada
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

    glutPostRedisplay(); //renderiza tudo novamente 
}

void update(int value){ //função chamada a cada 20 ms para atualizar a posição da esfera em movimento

    float basis = LARGURA_BASE/2 - diametro_esfera*((qtd_esferas-1) / 2); //posição da primeira esfera em repouso

    deslocamento_x += incremento; //incrementa a posição atual da esfera em moviemento no eixo x

    if(deslocamento_x <= basis-2 || deslocamento_x >= basis+2) //verifica o deslocamento foi maior ou igual a 2
        incremento = -incremento; //se isso for verdade, a esfera deve iniciar seu caminho de volta para a posição inicial. isso é feio multiplicanto o incremento por -1, fazendo que a esfera faça o caminho inverso ao anterior
    
    if(abs(deslocamento_x - basis) <= 0.01) //se a esfera voltar para a posição inicial, a flag de controle comuta e o movimento de outra esfera se inicia
        control_flag = !control_flag;

    glutPostRedisplay();
    glutTimerFunc(20, update, 0); //função chamada a cada 20ms

}

void handleMenuTotalEsf(int m) { //se a quantidade de esferas for alterada pelo menu, as variávais de controle são resetadas
    qtd_esferas = m; //muda o numero de esferas

    //reseta variaveis
    deslocamento_x = LARGURA_BASE/2 - diametro_esfera*((qtd_esferas-1) / 2);
    control_flag = true;
    incremento = -0.15;
    glutPostRedisplay();
}

//cria o menu de quantidade de esferas pelo click com botão direito
void prepararMenu() {
    menuTotalEsf = glutCreateMenu(handleMenuTotalEsf); //a função chamada após o fim do menu foi a que muda o número de esferas e reseta variaveis
    glutAddMenuEntry("1", 1);//opcoes do número de esferas
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
    inicializacao();//função de inicialização definida no início
    
    prepararMenu(); // menu de mudança da quanitade de esferas
 
    glutDisplayFunc(desenha); //função que renderiza os objetos
    //glutMouseFunc(handleMouse);
    glutSpecialFunc(handleSpecialKeys); //função que espera pelos botões dos teclado
    glutTimerFunc(20, update, 0);
    glutMainLoop();
    return 0;
}