#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cabecalho.h"

Processo* filaAlta = NULL;
Processo* filaMedia = NULL;
Processo* filaBaixa = NULL;
Processo* listaFinalizados = NULL;

int proximoPID = 1;

void atividade_escolhida(int escolha) { 
    switch (escolha)
    {
    case 1: 
        criar_novo_processo();
        break;
    case 2: 
        executar_novo_processo();
        break;
    case 3: 
        imprimir_estado_atual_do_sistema();
        break;
    case 4: 
        cancelar_processo();
        break;
    case 0: 
        printf(" Encerrando o programa...");
        break;
    }
}

void criar_novo_processo() {
    char nome[50];
    char entrada[20];
    int prioridade, numChamadas;

    printf("\n--- Criar Novo Processo ---\n");

    // LIMPA O BUFFER DO TECLADO
    while (getchar() != '\n');

    // PEDE O NOME DO PROCESSO PARA O USUÁRIO
    printf("Nome do processo: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strlen(nome)-1] = '\0';

    // PEDE A PRIORIDADE AO USUÁRIO
    do {
        printf("Prioridade (1 = alta, 2 = media, 3 = baixa): ");
        fgets(entrada, sizeof(entrada), stdin); // CONVERTE A STRING DE ENTRADA PARA UM INTEIRO. SE A CONVERSÃO NÃO FOR BEM SUCEDIDA RETORNA DIFERENTE DE 1
        if (sscanf(entrada, "%d", &prioridade) != 1 || prioridade < 1 || prioridade > 3) {
            printf("Prioridade invalida! Tente novamente.\n");
        } else {
            break;
        }
    } while (1);

    // PEDE O NÚMERO DE CHAMADAS DA FUNÇÃO
    printf("Numero de chamadas de funcao: ");
    scanf("%d", &numChamadas);

    // ALOCA O PROCESSO (PARTE QUE ACHO DIFÍCIL)
    Processo* novo = (Processo*) malloc(sizeof(Processo));
    if (novo == NULL) {
        printf("Erro de alocacao!\n");
        return;
    }

    novo->pid = proximoPID++;
    strcpy(novo->nome, nome);
    novo->prioridade = prioridade;
    strcpy(novo->estado, "Pronto");
    novo->numdechamadas = numChamadas;
    novo->pilha = NULL;
    novo->proximo = NULL;

    // Criar a pilha de funções
    for (int i = 1; i <= numChamadas; i++) {
        Funcao* func = (Funcao*) malloc(sizeof(Funcao));
        if (func == NULL) {
            printf("Erro ao alocar funcao.\n");
            return;
        }
        sprintf(func->nome, "funcao_%d", i);  // Nome fictício da função
        func->id = i;
        func->proxima = novo->pilha; // Empilha
        novo->pilha = func;
    }

    // Inserir o processo na fila correta
    Processo** fila;
    if (prioridade == 1) fila = &filaAlta;
    else if (prioridade == 2) fila = &filaMedia;
    else fila = &filaBaixa;

    // Inserção no fim da fila
    if (*fila == NULL) {
        *fila = novo;
    } else {
        Processo* atual = *fila;
        while (atual->proximo != NULL)
            atual = atual->proximo;
        atual->proximo = novo;
    }

    printf("Processo criado com sucesso! PID = %d\n", novo->pid);
}

void executar_novo_processo() {
    printf("\n--- Executar Processo ---\n");

    Processo* processo = NULL;
    Processo** fila = NULL;

    // Escolhe a fila de maior prioridade que não esteja vazia
    if (filaAlta != NULL) {
        fila = &filaAlta;
    } else if (filaMedia != NULL) {
        fila = &filaMedia;
    } else if (filaBaixa != NULL) {
        fila = &filaBaixa;
    } else {
        printf("Nenhum processo para executar.\n");
        return;
    }

    // Remove o primeiro processo da fila
    processo = *fila;
    *fila = (*fila)->proximo;
    processo->proximo = NULL;

    // Muda estado
    strcpy(processo->estado, "Executando");
    printf("Executando processo PID %d (%s)...\n", processo->pid, processo->nome);

    // Esvazia a pilha de funções
    while (processo->pilha != NULL) {
        Funcao* temp = processo->pilha;
        processo->pilha = processo->pilha->proxima;
        printf(" - Executando funcao: %s (id %d)\n", temp->nome, temp->id);
        free(temp);
    }

    // Marca como finalizado
    strcpy(processo->estado, "Finalizado");

    // Adiciona na lista de finalizados
    processo->proximo = listaFinalizados;
    listaFinalizados = processo;

    printf("Processo %d finalizado com sucesso!\n", processo->pid);
}

void imprimir_fila(Processo* fila, char* nomeFila) {
    printf("\nFila de prioridade %s:\n", nomeFila);
    if (fila == NULL) {
        printf(" [vazia]\n");
    } else {
        Processo* p = fila;
        while (p != NULL) {
            printf(" PID: %d | Nome: %s | Estado: %s | Chamadas: %d\n", 
                   p->pid, p->nome, p->estado, p->numdechamadas);
            p = p->proximo;
        }
    }
}

void imprimir_estado_atual_do_sistema() {
    printf("\n--- Estado Atual do Sistema ---\n");

    imprimir_fila(filaAlta, "Alta");
    imprimir_fila(filaMedia, "Media");
    imprimir_fila(filaBaixa, "Baixa");

    printf("\nProcessos Finalizados:\n");
    if (listaFinalizados == NULL) {
        printf(" [nenhum finalizado]\n");
    } else {
        Processo* p = listaFinalizados;
        while (p != NULL) {
            printf(" PID: %d | Nome: %s | Estado: %s\n", p->pid, p->nome, p->estado);
            p = p->proximo;
        }
    }
}

void cancelar_processo() {
    int pid;
    printf("\n--- Cancelar Processo ---\n");
    printf("Informe o PID do processo a ser cancelado: ");
    scanf("%d", &pid);

    Processo** filas[] = { &filaAlta, &filaMedia, &filaBaixa };

    for (int i = 0; i < 3; i++) {
        Processo** fila = filas[i];
        Processo* atual = *fila;
        Processo* anterior = NULL;

        while (atual != NULL) {
            if (atual->pid == pid) {
                if (anterior == NULL)
                    *fila = atual->proximo; // início da fila
                else
                    anterior->proximo = atual->proximo;

                // Liberar pilha
                while (atual->pilha != NULL) {
                    Funcao* temp = atual->pilha;
                    atual->pilha = temp->proxima;
                    free(temp);
                }

                free(atual);
                printf("Processo PID %d cancelado com sucesso.\n", pid);
                return;
            }

            anterior = atual;
            atual = atual->proximo;
        }
    }

    printf("Processo com PID %d nao encontrado nas filas.\n", pid);
}