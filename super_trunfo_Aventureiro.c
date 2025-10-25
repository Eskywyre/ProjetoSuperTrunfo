/*
  Super Trunfo - Nivel Aventureiro
  Meta: menu interativo (switch) e comparacao com if-else aninhado.
  Regra geral: maior vence; densidade demografica: menor vence.
*/

#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[40];
    int pop;          // populacao
    float area;       // km2
    float pib;        // trilhoes USD (exemplo didatico)
    int pontos;       // numero de pontos turisticos
    float dens;       // pop/area
} Carta;

void mostrar_cartas(const Carta *a, const Carta *b){
    printf("\nCartas carregadas:\n");
    printf("- %s  (pop=%d, area=%.2f, PIB=%.2f, pts=%d, dens=%.4f)\n",
           a->nome, a->pop, a->area, a->pib, a->pontos, a->dens);
    printf("- %s  (pop=%d, area=%.2f, PIB=%.2f, pts=%d, dens=%.4f)\n\n",
           b->nome, b->pop, b->area, b->pib, b->pontos, b->dens);
}

void resultado(const char *atrib, const char *nomeA, const char *nomeB,
               float vA, float vB, int menorVence){
    printf("Atributo: %s\n", atrib);
    printf("%s: %.4f\n", nomeA, vA);
    printf("%s: %.4f\n", nomeB, vB);

    if (vA == vB){
        printf("Empate!\n");
    } else {
        // if-else aninhado: primeiro empate, depois decide vencedor
        if (!menorVence){
            if (vA > vB) printf("Vence: %s\n", nomeA);
            else         printf("Vence: %s\n", nomeB);
        } else {
            if (vA < vB) printf("Vence: %s\n", nomeA);
            else         printf("Vence: %s\n", nomeB);
        }
    }
    printf("\n");
}

int main(void){
    // duas cartas ja cadastradas (do desafio anterior)
    Carta A = {"Brasil",    214000000, 8515767.0f, 1.90f, 12, 0.0f};
    Carta B = {"Argentina",  45000000, 2780400.0f, 0.60f,  8, 0.0f};
    A.dens = (float)A.pop / A.area;
    B.dens = (float)B.pop / B.area;

    int opcao;
    printf("=== Super Trunfo - Nivel Aventureiro ===\n");
    mostrar_cartas(&A, &B);

    do {
        printf("Menu - escolha um atributo para comparar:\n");
        printf("1) Populacao (maior vence)\n");
        printf("2) Area (maior vence)\n");
        printf("3) PIB (maior vence)\n");
        printf("4) Pontos turisticos (maior vence)\n");
        printf("5) Densidade demografica (menor vence)\n");
        printf("0) Sair\n");
        printf("Opcao: ");
        if (scanf("%d", &opcao) != 1) return 0;

        switch(opcao){
            case 1: // populacao
                resultado("Populacao", A.nome, B.nome, (float)A.pop, (float)B.pop, 0);
                break;
            case 2: // area
                resultado("Area", A.nome, B.nome, A.area, B.area, 0);
                break;
            case 3: // PIB
                resultado("PIB", A.nome, B.nome, A.pib, B.pib, 0);
                break;
            case 4: // pontos turisticos
                resultado("Pontos turisticos", A.nome, B.nome, (float)A.pontos, (float)B.pontos, 0);
                break;
            case 5: // densidade (menor vence)
                resultado("Densidade demografica", A.nome, B.nome, A.dens, B.dens, 1);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                // simples defesa contra opcao invalida
                printf("Opcao invalida. Tente novamente.\n\n");
                break;
        }
    } while(opcao != 0);

    return 0;
}