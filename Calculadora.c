#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "expressao.h"

#ifndef M_PI
#define M_PI 3.14
#endif

// --------------------------------------------------------
// -------------------- PILHAS INTERNAS -------------------
// --------------------------------------------------------

typedef struct {
    float v[512];
    int topo;
} PilhaFloat;

typedef struct {
    char v[512][128];
    int topo;
} PilhaStr;

void pushFloat(PilhaFloat *p, float x) {
    p->v[++p->topo] = x;
}

float popFloat(PilhaFloat *p) {
    return p->v[p->topo--];
}

int emptyFloat(PilhaFloat *p) {
    return p->topo < 0;
}

void pushStr(PilhaStr *p, char *s) {
    strcpy(p->v[++p->topo], s);
}

char *popStr(PilhaStr *p) {
    return p->v[p->topo--];
}


// FUNÇÃO INTERNA: prioridade op 

int prioridade(char c) {
    switch (c) {
        case '^': return 4;
        case '*': case '/': case '%': return 3;
        case '+': case '-': return 2;
    }
    return 0;
}


// INFIXA → POSFIXA (função internal)

void infixaParaPosfixa(const char *expr, char *saida) {
    char op[512];
    int topo = -1;
    int k = 0;

    for (int i = 0; expr[i]; i++) {

        if (isdigit(expr[i]) || expr[i] == '.') {
            saida[k++] = expr[i];
        }
        else if (isalpha(expr[i])) {
            while (isalpha(expr[i])) {
                saida[k++] = expr[i++];
            }
            i--;
            saida[k++] = ' ';
        }
        else if (expr[i] == '(') {
            op[++topo] = '(';
        }
        else if (expr[i] == ')') {
            while (topo >= 0 && op[topo] != '(')
                saida[k++] = op[topo--], saida[k++] = ' ';
            topo--;
        }
        else {
            saida[k++] = ' ';
            while (topo >= 0 && prioridade(op[topo]) >= prioridade(expr[i]))
                saida[k++] = op[topo--], saida[k++] = ' ';
            op[++topo] = expr[i];
        }
    }

    while (topo >= 0) {
        saida[k++] = ' ';
        saida[k++] = op[topo--];
    }

    saida[k] = '\0';
}

// --------------------------------------------------------
// --------------- AVALIAÇÃO DA POSFIXA -------------------
// --------------------------------------------------------

float getValorPosFixa(char *StrPosFixa) {
    PilhaFloat p;
    p.topo = -1;

    char token[64];
    int i = 0;

    while (StrPosFixa[i]) {

        if (isspace(StrPosFixa[i])) { i++; continue; }

        int j = 0;
        while (StrPosFixa[i] && !isspace(StrPosFixa[i]))
            token[j++] = StrPosFixa[i++];
        token[j] = '\0';

        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            pushFloat(&p, atof(token));
        }
        else if (!strcmp(token,"sen")) {
            float x = popFloat(&p);
            pushFloat(&p, sinf(x * M_PI / 180.0f));
        }
        else if (!strcmp(token,"cos")) {
            float x = popFloat(&p);
            pushFloat(&p, cosf(x * M_PI / 180.0f));
        }
        else if (!strcmp(token,"tg")) {
            float x = popFloat(&p);
            pushFloat(&p, tanf(x * M_PI / 180.0f));
        }
        else if (!strcmp(token,"raiz")) {
            float x = popFloat(&p);
            pushFloat(&p, sqrtf(x));
        }
        else if (!strcmp(token,"log")) {
            float x = popFloat(&p);
            pushFloat(&p, log10f(x));
        }
        else {
            float b = popFloat(&p);
            float a = popFloat(&p);

            switch (token[0]) {
                case '+': pushFloat(&p, a + b); break;
                case '-': pushFloat(&p, a - b); break;
                case '*': pushFloat(&p, a * b); break;
                case '/': pushFloat(&p, a / b); break;
                case '%': pushFloat(&p, fmod(a, b)); break;
                case '^': pushFloat(&p, pow(a, b)); break;
                default: return 0; 
            }
        }
    }

    return popFloat(&p);
}


// POSFIXA → INFIXA (pública) 


char *getFormaInFixa(char *Str) {
    static char saida[512];
    PilhaStr p;
    p.topo = -1;

    char token[64];
    int i = 0;

    while (Str[i]) {

        if (isspace(Str[i])) { i++; continue; }

        int j = 0;
        while (Str[i] && !isspace(Str[i]))
            token[j++] = Str[i++];
        token[j] = '\0';

        if (isdigit(token[0]) || token[0] == '.') {
            pushStr(&p, token);
        }
        else if (!strcmp(token, "sen") ||
                 !strcmp(token, "cos") ||
                 !strcmp(token, "tg")  ||
                 !strcmp(token, "raiz")||
                 !strcmp(token, "log")) {

            char op1[128];
            strcpy(op1, popStr(&p));

            char temp[256];
            sprintf(temp, "%s(%s)", token, op1);
            pushStr(&p, temp);
        }
        else {

            char b[128], aStr[128];
            strcpy(b, popStr(&p));
            strcpy(aStr, popStr(&p));

            char temp[256];
            sprintf(temp, "(%s%s%s)", aStr, token, b);
            pushStr(&p, temp);
        }
    }

    if (p.topo != 0)
        return NULL;

    strcpy(saida, p.v[p.topo]);
    return saida;
}
