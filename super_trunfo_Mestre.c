/*
  Super Trunfo - Nivel Mestre
  Meta: escolher 2 atributos via menus dinamicos (switch),
  comparar cada um (densidade menor vence), somar e decidir a rodada.
  Usei if-else, ternario e tratamento simples de entradas invalidas.
*/

#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[40];
    int pop;       // populacao
    float area;    // km2
    float pib;     // trilhoes USD (exemplo didatico)
    int pontos;    // pontos turisticos
    float dens;    // pop/area
} Carta;

typedef enum {
    ATR_POP = 1,
    ATR_AREA = 2,
    ATR_PIB = 3,
    ATR_PONTOS = 4,
    ATR_DENS = 5
} Atributo;

const char* nome_atrib(Atributo a){
    switch(a){
        case ATR_POP:    return "Populacao";
        case ATR_AREA:   return "Area";
        case ATR_PIB:    return "PIB";
        case ATR_PONTOS: return "Pontos turisticos";
        case ATR_DENS:   return "Densidade demografica";
        default:         return "Desconhecido";
    }
}

float valor_attr(const Carta* c, Atributo a){
    switch(a){
        case ATR_POP:    return (float)c->pop;
        case ATR_AREA:   return c->area;
        case ATR_PIB:    return c->pib;
        case ATR_PONTOS: return (float)c->pontos;
        case ATR_DENS:   return c->dens;
        default:         return 0.0f;
    }
}

int densidade_inverte(Atributo a){ return a == ATR_DENS; }

void mostrar_cartas(const Carta* A, const Carta* B){
    printf("\nCartas:\n");
    printf("- %s  (pop=%d, area=%.2f, PIB=%.2f, pts=%d, dens=%.6f)\n",
           A->nome, A->pop, A->area, A->pib, A->pontos, A->dens);
    printf("- %s  (pop=%d, area=%.2f, PIB=%.2f, pts=%d, dens=%.6f)\n\n",
           B->nome, B->pop, B->area, B->pib, B->pontos, B->dens);
}

/* compara um atributo: retorna 0 se A vence, 1 se B vence, -1 empate */
int compara_um(const Carta* A, const Carta* B, Atributo atr){
    float vA = valor_attr(A, atr);
    float vB = valor_attr(B, atr);
    int invert = densidade_inverte(atr); // menor vence se densidade

    // uso ternario pra decidir comparacao
    if (!invert) {
        return (vA > vB) ? 0 : (vB > vA) ? 1 : -1;
    } else {
        return (vA < vB) ? 0 : (vB < vA) ? 1 : -1;
    }
}

/* imprime bloco de resultado de um atributo */
void imprime_bloco_atrib(const Carta* A, const Carta* B, Atributo atr){
    float vA = valor_attr(A, atr);
    float vB = valor_attr(B, atr);
    int invert = densidade_inverte(atr);

    printf("Atributo: %s%s\n",
           nome_atrib(atr),
           invert ? " (menor vence)" : " (maior vence)");
    printf("%s: %.6f\n", A->nome, vA);
    printf("%s: %.6f\n", B->nome, vB);

    int w = compara_um(A, B, atr);
    if (w == -1) printf("Resultado: Empate\n\n");
    else printf("Vence neste atributo: %s\n\n", w == 0 ? A->nome : B->nome);
}

/* menu 1: mostra todas as opcoes; menu 2: esconde a que ja foi escolhida */
Atributo menu_escolha_primeiro(){
    int op;
    while (1){
        printf("Escolha o PRIMEIRO atributo:\n");
        printf("1) Populacao (maior vence)\n");
        printf("2) Area (maior vence)\n");
        printf("3) PIB (maior vence)\n");
        printf("4) Pontos turisticos (maior vence)\n");
        printf("5) Densidade demografica (menor vence)\n");
        printf("Opcao: ");
        if (scanf("%d", &op) != 1) { return ATR_POP; }

        switch(op){
            case 1: case 2: case 3: case 4: case 5:
                return (Atributo)op;
            default:
                printf("Opcao invalida.\n\n");
        }
    }
}

Atributo menu_escolha_segundo(Atributo primeiro){
    int op;
    while (1){
        printf("\nEscolha o SEGUNDO atributo (diferente do primeiro):\n");
        if (primeiro != ATR_POP)    printf("1) Populacao\n");
        if (primeiro != ATR_AREA)   printf("2) Area\n");
        if (primeiro != ATR_PIB)    printf("3) PIB\n");
        if (primeiro != ATR_PONTOS) printf("4) Pontos turisticos\n");
        if (primeiro != ATR_DENS)   printf("5) Densidade demografica\n");
        printf("Opcao: ");
        if (scanf("%d", &op) != 1) { return (primeiro == ATR_POP) ? ATR_AREA : ATR_POP; }

        switch(op){
            case 1: case 2: case 3: case 4: case 5:
                if (op == primeiro) { printf("Nao pode repetir o mesmo atributo.\n"); break; }
                return (Atributo)op;
            default:
                printf("Opcao invalida.\n");
        }
    }
}

int main(void){
    // cartas pre-cadastradas
    Carta A = {"Brasil",    214000000, 8515767.0f, 1.90f, 12, 0.0f};
    Carta B = {"Argentina",  45000000, 2780400.0f, 0.60f,  8, 0.0f};
    A.dens = (float)A.pop / A.area;
    B.dens = (float)B.pop / B.area;

    printf("=== Super Trunfo - Nivel Mestre ===\n");
    mostrar_cartas(&A, &B);

    // menus dinamicos
    Atributo atr1 = menu_escolha_primeiro();
    Atributo atr2 = menu_escolha_segundo(atr1);

    // mostra comparacao de cada atributo
    imprime_bloco_atrib(&A, &B, atr1);
    imprime_bloco_atrib(&A, &B, atr2);

    // soma valores (densidade nao inverte na soma)
    float a1 = valor_attr(&A, atr1), b1 = valor_attr(&B, atr1);
    float a2 = valor_attr(&A, atr2), b2 = valor_attr(&B, atr2);
    float somaA = a1 + a2;
    float somaB = b1 + b2;

    printf("Soma dos atributos:\n");
    printf("%s: %.6f\n", A.nome, somaA);
    printf("%s: %.6f\n", B.nome, somaB);

    if (somaA == somaB) {
        printf("Empate!\n");
    } else {
        const char* vencedor = (somaA > somaB) ? A.nome : B.nome;
        printf("Vence a rodada: %s\n", vencedor);
    }

    return 0;
}
