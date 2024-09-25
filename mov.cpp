#include <GL/glut.h>
#include <math.h>

// Posição inicial da câmera e ângulos de rotação
float posX = 0.0f, posY = 0.0f, posZ = 5.0f;
float yaw = -90.0f, pitch = 0.0f;
int windowWidth = 600, windowHeight = 600; // Tamanho da janela
float camSpeed = 0.05f;

// Função para configurar a câmera
void atualizarCamera() {
    float frontX = cosf(yaw * M_PI / 180.0f) * cosf(pitch * M_PI / 180.0f);
    float frontY = sinf(pitch * M_PI / 180.0f);
    float frontZ = sinf(yaw * M_PI / 180.0f) * cosf(pitch * M_PI / 180.0f);

    // Definir para onde a câmera está olhando
    gluLookAt(posX, posY, posZ, posX + frontX, posY + frontY, posZ + frontZ, 0.0f, 1.0f, 0.0f);
}

// Callback para o movimento do mouse
void movimentoMouse(int x, int y) {
    int centerX = windowWidth / 2;
    int centerY = windowHeight / 2;

    if (x == centerX && y == centerY) {
        // Se o cursor já estiver no centro, não faz nada
        return;
    }

    // Calcula o deslocamento do mouse
    float offsetX = x - centerX;
    float offsetY = centerY - y; // Invertido porque o eixo Y é invertido

    float sensitivity = 0.1f; // Sensibilidade do mouse
    offsetX *= sensitivity;
    offsetY *= sensitivity;

    yaw += offsetX;
    pitch += offsetY;

    // Limitar o pitch para evitar "olhar para trás"
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    // Reposiciona o cursor no centro da janela
    glutWarpPointer(centerX, centerY);

    glutPostRedisplay(); // Atualiza a tela
}

// Callback para o movimento do teclado
void teclado(unsigned char key, int x, int y) {
    float frontX = cosf(yaw * M_PI / 180.0f) * cosf(pitch * M_PI / 180.0f);
    float frontY = sinf(pitch * M_PI / 180.0f);
    float frontZ = sinf(yaw * M_PI / 180.0f) * cosf(pitch * M_PI / 180.0f);

    // Vetor "frontal"
    float front[3] = { frontX, frontY, frontZ };

    // Vetor "direito" (cross entre front e o vetor para cima (0,1,0))
    float right[3] = { sinf(yaw * M_PI / 180.0f), 0.0f, -cosf(yaw * M_PI / 180.0f) };

    switch (key) {
        case 'w': // Move para frente
            posX += front[0] * camSpeed;
            posY += front[1] * camSpeed;
            posZ += front[2] * camSpeed;
            break;
        case 's': // Move para trás
            posX -= front[0] * camSpeed;
            posY -= front[1] * camSpeed;
            posZ -= front[2] * camSpeed;
            break;
        case 'a': // Move para a esquerda
            posX -= right[0] * camSpeed;
            posZ -= right[2] * camSpeed;
            break;
        case 'd': // Move para a direita
            posX += right[0] * camSpeed;
            posZ += right[2] * camSpeed;
            break;
    }
    glutPostRedisplay(); // Atualiza a tela
}

// Função de renderização
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    atualizarCamera();

    // Aqui você pode desenhar o "mundo" (cubos, etc.)
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f, -1.0f, -1.0f);
    glVertex3f( 1.0f,  1.0f, -1.0f);
    glVertex3f(-1.0f,  1.0f, -1.0f);
    glEnd();

    glutSwapBuffers();
}

// Inicialização
void init() {
    glEnable(GL_DEPTH_TEST); // Habilita teste de profundidade
    glClearColor(0.5f, 0.7f, 1.0f, 1.0f);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Movimento de Mouse Centralizado");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(teclado);
    glutPassiveMotionFunc(movimentoMouse); // Função para capturar o movimento do mouse

    // Centraliza o cursor ao iniciar
    glutWarpPointer(windowWidth / 2, windowHeight / 2);

    glutMainLoop();
    return 0;
}
