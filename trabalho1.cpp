//--------------------------------------------------------------
// NOMES DOS RESPONS�VEIS: Maria Fernanda Basso Santos E blablabla
//--------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <string.h>

// ######### ESCREVA O NROUSP DO PRIMEIRO INTEGRANTE AQUI
char* nroUSP1() {
    return("11208197");
}

// ######### ESCREVA O NROUSP DO SEGUNDO INTEGRANTE AQUI (OU DEIXE ZERO)
char* nroUSP2() {
    return("0000000");
}

// ######### ESCREVA O NRO DO SEU GRUPO TAL QUAL CADASTRADO (LINK NO PDF DO EP)
char* grupo() {
    return("17");
}


// elementos da matriz esparsa (use tambem se quiser criar listas auxiliares)
typedef struct estr {
    int info;
    int lin;
    int col;
    struct estr *proxC;   // ponteiro para a direita
    struct estr *proxL;   // ponteiro para baixo
} NO;

// matriz 10 x 10 (a linha e coluna 0 s�o desprezadas)
typedef struct {
    NO* LIN[11];
    NO* COL[11];
} LISTASCR;

// funcao principal
void substituir(LISTASCR* m, int i, int j);


//------------------------------------------
// O EP consiste em implementar esta funcao
// e outras funcoes auxiliares que esta
// necessitar
//------------------------------------------

//minhas funcoes auxiliares
void inicializarMatriz (LISTASCR* m) {
    for (int i = 1; i <= 10; i++) {
        m->LIN[i] = NULL;
        m->COL[i] = NULL;
    }
}

NO* buscaElemento (LISTASCR* m, int f, int g, NO* *antL, NO* *antC) {
    NO* p = m->LIN[f];
    for (int k = 1; k <= g; k++) {
        if (p != NULL) {
            if (p->col < g) {
                *antL = p;
                p = p->proxC;
            } else if (p->col == g) break;
            else p = NULL;
        }
    }

    NO* q = m->COL[g];
    for (int k = 1; k <= f; k++) {
        if (q) {
            if (q->lin < f) {
                *antC = q;
                q = q->proxL;
            } else if (q->lin == f) break;
            else q = NULL;
        }
    }

    return p;
}

bool inserirMatriz(LISTASCR* m, int i, int j, int ch) {
    if (i < 1 || i > 10 || j < 1 || j > 10) return false;
    NO* antL = NULL;
    NO* antC = NULL;
    NO* p = buscaElemento(m, i, j, &antL, &antC);
    if (p != NULL) return false;
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->info = ch;
    novo->lin = i;
    novo->col = j;
    if(antL != NULL) {
        novo->proxL = antL->proxC;
        antL->proxC = novo;
    } else{
        novo->proxL = m->LIN[i];
        m->LIN[i] = novo;
    }
    if (antC != NULL) {
        novo->proxC = antC->proxL;
        antC->proxL = novo;
    } else{
        novo->proxC = m->COL[j];
        m->COL[j] = novo;
    }
    return true;
}

void exibirMatriz (LISTASCR* m) {
    for (int h = 1; h <= 10; h++) {
        NO* n = m->LIN[h];
        for (int l = 1; l <= 10; l++) {
            if (n && n->col == l) {
                printf("%d ", n->info);
                n = n->proxC;
            } else printf("0 ");
        }
        printf("\n");
    }
}

void inserirMatrizSubst2 (LISTASCR* m, int i, int j, int ch) {
    NO* antL = NULL;
    NO* antC = NULL;
    NO* b = buscaElemento(m, i, j, &antL, &antC);
    if (b != NULL) b->info = ch;
    else {
        NO* novo = (NO*) malloc(sizeof(NO));
        novo->info = ch;
        novo->lin = i;
        novo->col = j;
        if(antL != NULL) {
            novo->proxL = antL->proxC;
            antL->proxC = novo;
        } else{
            novo->proxL = m->LIN[i];
            m->LIN[i] = novo;
        }
        if (antC != NULL) {
            novo->proxC = antC->proxL;
            antC->proxL = novo;
        } else{
            novo->proxC = m->COL[j];
            m->COL[j] = novo;
        }
    }
}

void inserirMatrizSubst(LISTASCR* m, int iverdadeiro, int cont, int jverdadeiro, int ch) {
    NO* antL = NULL;
    NO* antC = NULL;
    NO* q = buscaElemento(m, cont, jverdadeiro, &antL, &antC);
    if (q != NULL){
        inserirMatrizSubst2 (m, iverdadeiro, cont, (q->info));
        q->info = ch;
    } else {
        NO* novo = (NO*) malloc(sizeof(NO));
        novo->info = ch;
        novo->lin = cont;
        novo->col = jverdadeiro;
        if(antL != NULL) {
            novo->proxL = antL->proxC;
            antL->proxC = novo;
        } else{
            novo->proxL = m->LIN[cont];
            m->LIN[cont] = novo;
        }
        if (antC != NULL) {
            novo->proxC = antC->proxL;
            antC->proxL = novo;
        } else{
            novo->proxC = m->COL[jverdadeiro];
            m->COL[jverdadeiro] = novo;
        }
    }
}

void excluirMatrizSubst(LISTASCR* m, int iverdadeiro, int i, int jverdadeiro) {
    NO* antL1 = NULL;
    NO* antC1 = NULL;
    NO* q = buscaElemento(m, i, jverdadeiro, &antL1, &antC1);
    if (q) {
        inserirMatrizSubst2(m, iverdadeiro, i, (q->info));
        if(antL1 != NULL) {
            antL1->proxC = q->proxC;
        } else{
            m->LIN[i] = q->proxC;
        }
        if (antC1 != NULL) {
            antC1->proxL = q->proxL;
        } else{
            m->COL[jverdadeiro] = q->proxL;
        }
        free(q);
    }
}

void substituir(LISTASCR* m, int i, int j) {
    int nroElem;
    if (i > j) nroElem = j-1;
    else nroElem = i-1;
    NO* pont = m->LIN[i];
    for (int hum = 1; hum <= nroElem; hum++) {
        if (pont->col == hum){
            inserirMatrizSubst(m, i, hum, j, (pont->info));
            pont = pont->proxC;
        }
        else excluirMatrizSubst(m, i, hum, j);
    }
}

int main () {
    LISTASCR m;
    inicializarMatriz(&m);
    while (true) {
        int comando = 0;
        printf("1 - inserir\n");
        printf("2 - substituir\n");
        printf("3 - exibir\n");
        printf("4 - fechar\n");
        printf("Digite um comando\n");
        scanf("%d", &comando);

        if(comando == 1) {
            int i = 0, j = 0, ch = 0;
            printf("Digite a linha:");
            scanf ("%d", &i);
            printf("Digite a coluna:");
            scanf ("%d", &j);
            printf("Digite a chave:");
            scanf ("%d", &ch);
            bool in = inserirMatriz(&m, i, j, ch);
            if (in == false) printf("Deu erro\n");
        } else if(comando == 2) {
            int d = 0, e = 0;
            printf("Digite a linha:");
            scanf ("%d", &d);
            printf("Digite a coluna:");
            scanf ("%d", &e);
            substituir(&m, d, e);
        } else if(comando == 3) exibirMatriz(&m);
        else if (comando == 4) break;
        else printf("Numero invalido\n");
    }
    return 0;
}

// por favor nao entregue sua fun��o main() nem seu c�digo de teste

