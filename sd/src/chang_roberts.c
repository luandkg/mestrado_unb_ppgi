#include <stdio.h>
#include <stdlib.h>

#define N 5

int processos[N] = {1, 2, 3, 4, 5};
int ativo[N] = {1, 1, 1, 1, 1};

int changRobertsElection(int iniciador) {
    int eleito = processos[iniciador];
    int token = eleito;

    for (int i = 1; i < N; i++) {
        int idx = (iniciador + i) % N;
        if (ativo[idx] && processos[idx] > token) {
            token = processos[idx];
        }
    }
    eleito = token;
    return eleito;
}

int main() {
    printf("--------------------- Chang & Roberts Algorithm --------------------------\n");
    ativo[3] = 0; 
    int iniciador = 1; 
    int lider = changRobertsElection(iniciador);
    printf("\t >> Processo %d iniciou eleição !\n", processos[iniciador]);
    printf("\t >> Novo líder eleito: %d\n", lider);
    return 0;
}
