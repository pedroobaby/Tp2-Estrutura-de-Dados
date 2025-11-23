#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expressao.h"

int main() {
    char expr[512];
    Expressao E;

    printf("==== TESTES AUTOMATICOS ====\n\n");

    // ---------- TESTE 1 ----------
    strcpy(E.posFixa, "3 4 + 5 *");
    printf("PosFixa: %s\n", E.posFixa);
    printf("InFixa : %s\n", getFormaInFixa(E.posFixa));
    printf("Valor  : %.2f\n\n", getValorPosFixa(E.posFixa));

    // ---------- TESTE 2 ----------
    strcpy(E.posFixa, "7 2 * 4 +");
    printf("PosFixa: %s\n", E.posFixa);
    printf("InFixa : %s\n", getFormaInFixa(E.posFixa));
    printf("Valor  : %.2f\n\n", getValorPosFixa(E.posFixa));

    // ---------- TESTE 3 ----------
    strcpy(E.posFixa, "8 5 2 4 + * +");
    printf("PosFixa: %s\n", E.posFixa);
    printf("InFixa : %s\n", getFormaInFixa(E.posFixa));
    printf("Valor  : %.2f\n\n", getValorPosFixa(E.posFixa));

    // ---------- TESTE 4 ----------
    strcpy(E.posFixa, "6 2 / 3 + 4 *");
    printf("PosFixa: %s\n", E.posFixa);
    printf("InFixa : %s\n", getFormaInFixa(E.posFixa));
    printf("Valor  : %.2f\n\n", getValorPosFixa(E.posFixa));

    // ---------- TESTE 5 ----------
    strcpy(E.posFixa, "9 5 2 8 * 4 + * +");
    printf("PosFixa: %s\n", E.posFixa);
    printf("InFixa : %s\n", getFormaInFixa(E.posFixa));
    printf("Valor  : %.2f\n\n", getValorPosFixa(E.posFixa));

    // ---------- TESTE 6 ----------
    strcpy(E.posFixa, "2 3 + log 5 /");
    printf("PosFixa: %s\n", E.posFixa);
    printf("InFixa : %s\n", getFormaInFixa(E.posFixa));
    printf("Valor  : %.5f\n\n", getValorPosFixa(E.posFixa));

    // ---------- TESTE 7 ----------
    strcpy(E.posFixa, "10 log 3 ^ 2 +");
    printf("PosFixa: %s\n", E.posFixa);
    printf("InFixa : %s\n", getFormaInFixa(E.posFixa));
    printf("Valor  : %.5f\n\n", getValorPosFixa(E.posFixa));

    // ---------- TESTE 8 ----------
    strcpy(E.posFixa, "45 60 + 30 cos *");
    printf("PosFixa: %s\n", E.posFixa);
    printf("InFixa : %s\n", getFormaInFixa(E.posFixa));
    printf("Valor  : %.5f\n\n", getValorPosFixa(E.posFixa));

    // ---------- TESTE 9 ----------
    strcpy(E.posFixa, "0.5 45 sen 2 ^ +");
    printf("PosFixa: %s\n", E.posFixa);
    printf("InFixa : %s\n", getFormaInFixa(E.posFixa));
    printf("Valor  : %.5f\n\n", getValorPosFixa(E.posFixa));

    printf("==== TESTE MANUAL ====\n");
    printf("Digite uma expressão pos-fixa (ou 'sair'): \n");

    while (1) {
        printf("\nposfixa> ");
        fgets(expr, 512, stdin);

        if (strncmp(expr, "sair", 4) == 0) break;

        expr[strcspn(expr, "\n")] = 0; // remove \n

        char *inf = getFormaInFixa(expr);
        if (!inf) {
            printf("Expressao invalida.\n");
            continue;
        }

        printf("InFixa : %s\n", inf);
        printf("Valor  : %.5f\n", getValorPosFixa(expr));
    }

    return 0;
}
