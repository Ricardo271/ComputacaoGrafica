#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define RAIO_ESTRELA 0.3
#define RAIO_FURO 0.1
#define NUM_PONTOS 5
#define VERTICES_ESTRELA 10

float esquerda = -1.0, direita = 1.0, baixo = -1.0, cima = 1.0;
int largura_janela = 800, altura_janela = 800;

float posicoes_estrela[VERTICES_ESTRELA][2];
int cor_selecionada = 0;
float cores_primarias[][3] = {{0, 0, 1}, {1, 0, 0}, {0, 1, 0}};
char teclas_pressionadas[256];

void mover_estrela(float pontos[][2], int total, float mover_x, float mover_y) {
    for(int i = 0; i < total; i++) {
        pontos[i][0] += mover_x;
        pontos[i][1] += mover_y;
    }
}

void calcular_posicao_media(float centro[2], float pontos[][2], int total) {
    centro[0] = centro[1] = 0.0;
    
    for(int i = 0; i < total; i++) {
        centro[0] += pontos[i][0];
        centro[1] += pontos[i][1];
    }
    
    centro[0] /= total;
    centro[1] /= total;
}

void desenhar_cena() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3fv(cores_primarias[cor_selecionada]);
    
    // Desenha a estrela como um polígono preenchido
    glBegin(GL_POLYGON);
    for(int i = 0; i < VERTICES_ESTRELA; i++) {
        glVertex2fv(posicoes_estrela[i]);
    }
    glEnd();
    
    glutSwapBuffers();
}

void quando_tecla_pressionada(unsigned char tecla, int x, int y) {
    teclas_pressionadas[tecla] = 1;
    
    if(tecla == ' ') {
        cor_selecionada = (cor_selecionada + 1) % 3;
    }
}

void quando_tecla_solta(unsigned char tecla, int x, int y) {
    teclas_pressionadas[tecla] = 0;
}

void configurar_ambiente() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    gluOrtho2D(esquerda, direita, baixo, cima);
    
    // Cria os pontos da estrela alternando entre raio externo e interno
    for(int i = 0; i < NUM_PONTOS; i++) {
        float angulo_base = (2 * M_PI * i) / NUM_PONTOS - M_PI/2;
        
        // Ponta da estrela
        posicoes_estrela[2*i][0] = RAIO_ESTRELA * cos(angulo_base);
        posicoes_estrela[2*i][1] = RAIO_ESTRELA * sin(angulo_base);
        
        // Entrada entre as pontas
        float angulo_meio = angulo_base + M_PI / NUM_PONTOS;
        posicoes_estrela[2*i+1][0] = RAIO_FURO * cos(angulo_meio);
        posicoes_estrela[2*i+1][1] = RAIO_FURO * sin(angulo_meio);
    }
}

void processar_movimento() {
    float velocidade = 0.06;
    float dx = 0.0, dy = 0.0;
    
    if(teclas_pressionadas['w']) dy += velocidade;
    if(teclas_pressionadas['s']) dy -= velocidade;
    if(teclas_pressionadas['a']) dx -= velocidade;
    if(teclas_pressionadas['d']) dx += velocidade;
    
    float centro_atual[2];
    calcular_posicao_media(centro_atual, posicoes_estrela, VERTICES_ESTRELA);
    
    // Impede sair dos limites da tela
    if(centro_atual[0] + dx < esquerda || centro_atual[0] + dx > direita) dx = 0;
    if(centro_atual[1] + dy < baixo || centro_atual[1] + dy > cima) dy = 0;
    
    mover_estrela(posicoes_estrela, VERTICES_ESTRELA, dx, dy);
}

void manter_dentro_tela() {
    float centro[2];
    calcular_posicao_media(centro, posicoes_estrela, VERTICES_ESTRELA);
    
    if(centro[0] < esquerda || centro[0] > direita ||
       centro[1] < baixo || centro[1] > cima) {
        mover_estrela(posicoes_estrela, VERTICES_ESTRELA, -centro[0], -centro[1]);
    }
}

void atualizar_animacao() {
    processar_movimento();
    manter_dentro_tela();
    desenhar_cena();
}
//PARA MOVER O POLIGONO(ESTRELINHA DAORA) APERTE W,S,D,F
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(largura_janela, altura_janela);
    glutCreateWindow("Estrela Interativa");
    
    configurar_ambiente();
    
    glutDisplayFunc(desenhar_cena);
    glutKeyboardFunc(quando_tecla_pressionada);
    glutKeyboardUpFunc(quando_tecla_solta);
    glutIdleFunc(atualizar_animacao);
    
    glutMainLoop();
    
    return 0;
}
