#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cabecalho.h"

int main() {
    int escolha;
    char entrada[10];

    do {
        printf("\n\t\t ---- MENU ----\n\n");
        printf(" 1 - Criar novo processo.\n");
        printf(" 2 - Executar processo.\n");
        printf(" 3 - Imprimir estado atual do sistema.\n");
        printf(" 4 - Cancelar processo.\n");
        printf(" 0 - Sair.\n\n");

        printf("Escolha uma atividade que deseja realizar: ");
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strlen(entrada)-1]= '\0';

        // VALIDA A ENTRADA SOMENTE SE FOR UM NUMERO E ESTIVER ENTRE O INTERVALO DE 0 E 4
        if (sscanf(entrada, "%d", &escolha) != 1 || escolha < 0 || escolha > 4) {
            printf("\nAtividade invalida! Tente novamente.\n");
        } else {
            atividade_escolhida(escolha);
        }

    } while (escolha != 0);

    
    return 0;
}