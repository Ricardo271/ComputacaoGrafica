//Programa para rotacionar um quadrado em torno de seu baricentro sem usar as funções do OpenGL

#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

// Ângulo de rotação
GLfloat angle = 0.0;
// Coordenadas dos vértices do quadrado
GLfloat vertices[4][2] = {{-0.5, -0.5}, {0.5, -0.5}, {0.5, 0.5}, {-0.5, 0.5}};
GLfloat angulo;

// Função para calcular o baricentro do quadrado
void calcularBaricentro(GLfloat *baricentro)
{
    for (int i = 0; i < 2; i++) {
        baricentro[i] = 0.0;
        for (int j = 0; j < 4; j++) {
            baricentro[i] += vertices[j][i]; }
        baricentro[i] /= 4.0;
    }
}

// Função para realizar a rotação
void rotacionar(){
    GLfloat baricentro[2]; 
    calcularBaricentro(baricentro);
    GLfloat cos_angulo = cos(angulo * 3.1429 / 180); 
    GLfloat sin_angulo = sin(angulo * 3.1429 / 180); 
    for (int i = 0; i < 4; i++) {
        // a formula de rotacao em relacao à origem
        // x' = xcosO - ysinO
        // y' = xsinO + ycosO 
        GLfloat x = vertices[i][0] - baricentro[0]; // fazemos a origem ser o bariecentro, logo subtraimos todas coordenadas pelo baricentro
        GLfloat y = vertices[i][1] - baricentro[1];
        vertices[i][0] = x * cos_angulo - y * sin_angulo + baricentro[0]; // somamos o baricentro de volta
        vertices[i][1] = x * sin_angulo + y * cos_angulo + baricentro[1]; 
    }
}

// Função para desenhar o quadrado
void desenharQuadrado()
{ 
    glColor3f(1.0, 0.0, 0.0); // Cor vermelha
    glBegin(GL_QUADS);
    for (int i = 0; i < 4; i++) {
        glVertex2fv(vertices[i]);
    }
    glEnd();
}

// Função de renderização
void display() { 
    glClear(GL_COLOR_BUFFER_BIT);
    // Rotacionando em torno do baricentro
    rotacionar();
    // Desenhando o quadrado
    desenharQuadrado();
    glutSwapBuffers();
}

// Função de inicialização 
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char **argv){
    if (argc <= 1) {
        printf("Forneca o angulo em graus que deseja rotacionar o quadrado\n.");
        return -1;
    }
    angulo = atof(argv[1]);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Quadrado Rotacionado em torno do Baricentro (Manual)"); init();
    
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
