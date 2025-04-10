#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>

// Vértices do Triângulo
GLfloat vertices[3][2] = {{-0.5, -0.5}, {0.5, -0.5}, {0.0, 0.5}};
// Fatores da escala em cada eixo
GLfloat fator_escala_x = 1.0f;
GLfloat fator_escala_y = 1.0f;

void Inicializa() {
    glClearColor(0.0f,  0.0f, 0.0f, 1.0f); // define a cor do fundo
}

// Multiplica o x e y de cada vértice do triângulo pelo fators de escala daquele eixo
void Escalar(GLfloat scale_x, GLfloat scale_y) {
    for (int i =0; i < 3; i++) {
        GLfloat x = vertices[i][0] * scale_x;
        GLfloat y = vertices[i][1] * scale_y;
        vertices[i][0] = x;
        vertices[i][1] = y;
    }
}

void Desenha() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 0.0, 0.0); // Define a cor do triângulo

    // Define os vértices do triângulo
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 3; i++) {
        glVertex2fv(vertices[i]);
    }
    glEnd();

    Escalar(fator_escala_x, fator_escala_y);

    glFlush(); // Aplica as mudanças do buffer
}

int main(int argc, char* argv[]) {
    if (argc <= 2) {
        printf("Forneca os fatores de escala em x e y\n./Escalar [x] [y]\n");
        return -1;
    }
    // Captura os argumentos da linha de comando
    fator_escala_x = atof(argv[1]);
    fator_escala_y = atof(argv[2]);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("Rotaciona Triangulo");

    Inicializa();

    glutDisplayFunc(Desenha);
    glutMainLoop();

    return 0;
}
