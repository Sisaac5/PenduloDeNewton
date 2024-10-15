#include <GL/glut.h>
#include <SOIL/SOIL.h>  // Biblioteca SOIL para carregar texturas

GLuint textureID;

// Função para carregar a textura de um arquivo
void loadTexture(const char* filename) {
    // Gera um identificador para a textura
    glGenTextures(1, &textureID);
    
    // Faz a ligação da textura como uma textura 2D
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    // Carrega a imagem da textura usando SOIL
    textureID = SOIL_load_OGL_texture(
        filename, 
        SOIL_LOAD_AUTO, 
        SOIL_CREATE_NEW_ID, 
        SOIL_FLAG_INVERT_Y
    );
    
    if (textureID == 0) {
        printf("Erro ao carregar a textura: %s\n", SOIL_last_result());
    }

    // Define parâmetros de textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

// Função para desenhar um cubo com textura
void drawCube(GLfloat height, GLfloat width, GLfloat depth,
              float x, float y, float z, GLuint textureID) {
    GLfloat vertex1[3] = {x - width / 2, y, z - depth / 2};
    GLfloat vertex2[3] = {x - width / 2, y + height, z - depth / 2};
    GLfloat vertex3[3] = {x - width / 2, y + height, z + depth / 2};
    GLfloat vertex4[3] = {x - width / 2, y, z + depth / 2};

    GLfloat vertex5[3] = {x + width / 2, y, z - depth / 2};
    GLfloat vertex6[3] = {x + width / 2, y + height, z - depth / 2};
    GLfloat vertex7[3] = {x + width / 2, y + height, z + depth / 2};
    GLfloat vertex8[3] = {x + width / 2, y, z + depth / 2};

    // Ativa a textura
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBegin(GL_QUADS);  // Inicia o desenho dos quadrados com textura

    // Frente
    glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertex1);
    glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertex2);
    glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertex3);
    glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertex4);

    // Traseira
    glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertex5);
    glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertex6);
    glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertex7);
    glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertex8);

    // Superior
    glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertex2);
    glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertex3);
    glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertex7);
    glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertex6);

    // Inferior
    glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertex1);
    glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertex4);
    glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertex8);
    glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertex5);

    // Lateral direita
    glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertex3);
    glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertex4);
    glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertex8);
    glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertex7);

    // Lateral esquerda
    glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertex1);
    glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertex2);
    glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertex6);
    glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertex5);

    glEnd();  // Fim do desenho dos quadrados com textura
}

// Função de exibição
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Desenha o cubo com textura
    drawCube(2.0f, 2.0f, 2.0f, 0.0f, 0.0f, -5.0f, textureID);

    glutSwapBuffers();  // Troca os buffers
}

// Inicialização do OpenGL
void init() {
    glEnable(GL_TEXTURE_2D);  // Habilita texturas 2D
    glEnable(GL_DEPTH_TEST);  // Habilita o teste de profundidade

    // Carrega a textura de um arquivo de imagem
    loadTexture("Poliigon_WoodVeneerOak_7760/2K/Poliigon_WoodVeneerOak_7760_BaseColor.jpg");
}

// Função principal
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Cubo com Textura");

    init();

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
