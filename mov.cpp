#include <GL/glut.h>

// Definir a posição inicial da câmera
GLfloat camposx = 0.0f, camposy = 0.0f, camposz = 5.0f;  // Câmera posicionada a 5 unidades no eixo Z
GLfloat alvox = 0.0f, alvoy = 0.0f, alvoz = 0.0f;        // Câmera olhando para a origem (0, 0, 0)

// Função para configurar a câmera usando gluLookAt
void posicionarCamara() {
    gluLookAt(camposx, camposy, camposz,  // Posição da câmera
              alvox, alvoy, alvoz,        // Ponto para onde a câmera está olhando (origem)
              0.0f, 1.0f, 0.0f);         // Vetor "up" (eixo Y positivo)
}

// Função para desenhar a cena
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();  // Carrega a matriz identidade para reiniciar qualquer transformação anterior
    posicionarCamara();  // Configura a câmera
    
    // Desenha o primeiro cubo na origem (não transladado)
    glPushMatrix();  // Salva a matriz atual
    glColor3f(1.0f, 0.0f, 0.0f);  // Define a cor do cubo (vermelho)
    glutSolidCube(1.0);  // Desenha um cubo de tamanho 1 na origem
    glPopMatrix();  // Restaura a matriz
    
    // Desenha o segundo cubo transladado para a direita (3, 0, 0)
    glPushMatrix();
    glTranslatef(3.0f, 0.0f, 0.0f);  // Translada o cubo 3 unidades no eixo X
    glColor3f(0.0f, 1.0f, 0.0f);  // Define a cor do cubo (verde)
    glutSolidCube(1.0);  // Desenha o cubo
    glPopMatrix();
    
    // Desenha o terceiro cubo transladado para cima (0, 3, 0)
    glPushMatrix();
    glTranslatef(0.0f, 3.0f, 0.0f);  // Translada o cubo 3 unidades no eixo Y
    glColor3f(0.0f, 0.0f, 1.0f);  // Define a cor do cubo (azul)
    glutSolidCube(1.0);  // Desenha o cubo
    glPopMatrix();
    
    glFlush();
}

// Função de inicialização
void init() {
    glEnable(GL_DEPTH_TEST);  // Habilita teste de profundidade para renderizar objetos 3D corretamente
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Define a cor de fundo (preto)
}

// Função principal
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);  // Ativa o buffer de profundidade
    glutInitWindowSize(800, 600);  // Tamanho da janela
    glutCreateWindow("Câmera e Translações OpenGL");  // Cria a janela
    
    init();  // Chama a função de inicialização
    glutDisplayFunc(display);  // Registra a função de desenho
    
    glutMainLoop();  // Entra no loop principal do OpenGL
    return 0;
}
