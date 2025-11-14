#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define TAMANHO_HABILIDADE 5

#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5


////// Inicia o tabuleiro com água //////
void inicializarTabuleiro(int tab[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tab[i][j] = AGUA;
        }
    }
}


/////// Mostrar tabuleiro
void exibirTabuleiro(int tab[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n    ");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++)
        printf("%2d ", i);

    printf("\n--------------------------------------\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d| ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%2d ", tab[i][j]);
        }
        printf("\n");
    }

    printf("--------------------------------------\n");
    printf("Legenda: 0=Agua  3=Navio  5=Habilidade\n");
}


/////// Colocar navios em (horizontal, vertical, diagonal) /////
int posicionarNavio(int tab[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int col, char orientacao) {

    ////// teste /////
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha, c = col;

        if (orientacao == 'H' || orientacao == 'h') {
            c += i;
        } else if (orientacao == 'V' || orientacao == 'v') {
            l += i;
        } else if (orientacao == 'D' || orientacao == 'd') {
            l += i; c += i;
        } else if (orientacao == 'A' || orientacao == 'a') {
            l += i; c -= i;
        } else {
            return 0;
        }

        if (l < 0 || l >= TAMANHO_TABULEIRO || c < 0 || c >= TAMANHO_TABULEIRO)
            return 0;
    }

    ///// aplicação /////
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha, c = col;

        if (orientacao == 'H' || orientacao == 'h') c += i;
        else if (orientacao == 'V' || orientacao == 'v') l += i;
        else if (orientacao == 'D' || orientacao == 'd') { l += i; c += i; }
        else if (orientacao == 'A' || orientacao == 'a') { l += i; c -= i; }

        tab[l][c] = NAVIO;
    }

    return 1;
}


///// Cone /////
void gerarHabilidadeCone(int hab[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;

    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            hab[i][j] = (abs(j - centro) <= i) ? 1 : 0;
        }
    }
}

///// Cruz ////
void gerarHabilidadeCruz(int hab[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;

    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (i == centro || j == centro)
                hab[i][j] = 1;
            else
                hab[i][j] = 0;
        }
    }
}

//// Octaedro ////
void gerarHabilidadeOctaedro(int hab[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;

    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (abs(i - centro) + abs(j - centro) <= centro)
                hab[i][j] = 1;
            else
                hab[i][j] = 0;
        }
    }
}


////// Aplicar habilidade no tabuleiro /////
void aplicarHabilidade(int tab[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                       int hab[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
                       int origem_linha, int origem_coluna) {

    int centro = TAMANHO_HABILIDADE / 2;

    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {

            if (hab[i][j] == 1) {
                int l = origem_linha + (i - centro);
                int c = origem_coluna + (j - centro);

                // verifica se bate com o tabuleiro
                if (l >= 0 && l < TAMANHO_TABULEIRO &&
                    c >= 0 && c < TAMANHO_TABULEIRO) {

                    if (tab[l][c] == AGUA) {
                        tab[l][c] = HABILIDADE;
                    }
                }
            }
        }
    }
}


///// main ////
int main() {

    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int octa[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    inicializarTabuleiro(tabuleiro);

    printf("Tabuleiro iniciado:\n");
    exibirTabuleiro(tabuleiro);

    /////  navios ////
    posicionarNavio(tabuleiro, 1, 1, 'H');
    posicionarNavio(tabuleiro, 3, 8, 'V');
    posicionarNavio(tabuleiro, 5, 1, 'D');
    posicionarNavio(tabuleiro, 1, 8, 'A');

    printf("\nCom navios:\n");
    exibirTabuleiro(tabuleiro);

    gerarHabilidadeCone(cone);
    gerarHabilidadeCruz(cruz);
    gerarHabilidadeOctaedro(octa);

    aplicarHabilidade(tabuleiro, cone, 2, 4);
    aplicarHabilidade(tabuleiro, cruz, 7, 7);
    aplicarHabilidade(tabuleiro, octa, 5, 5);

    printf("\nFinal:\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}
