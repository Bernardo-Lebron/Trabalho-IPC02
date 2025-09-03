#ifndef CABECALHO_H
#define CABECALHO_H

typedef struct Funcao {
    char nome[50];
    int id;
    struct Funcao* proxima;
} Funcao;

typedef struct Processo {
    int pid;
    char nome[50];
    int prioridade;
    char estado[20];
    int numdechamadas;
    Funcao* pilha;
    struct Processo* proximo;
} Processo;

void atividade_escolhida(int escolha);
void criar_novo_processo();
void executar_novo_processo();
void imprimir_fila(Processo* fila, char* nomeFila);
void imprimir_estado_atual_do_sistema();
void cancelar_processo();

#endif //CABECALHO_H