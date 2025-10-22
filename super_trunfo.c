#include <stdio.h>

int main() {
    // Declaração das variáveis
    float poder1, poder2;

    printf("=== SUPER TRUNFO - COMPARADOR DE CARTAS ===\n");

    // Entrada de dados
    printf("Digite o poder da carta 1: ");
    scanf("%f", &poder1);

    printf("Digite o poder da carta 2: ");
    scanf("%f", &poder2);

    // Estrutura de decisão simples
    if (poder1 > poder2) {
        printf("A carta 1 venceu!\n");
    } 
    else if (poder2 > poder1) {
        printf("A carta 2 venceu!\n");
    } 
    else {
        printf("Empate!\n");
    }

    return 0;
}
