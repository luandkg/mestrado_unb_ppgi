#include <stdio.h>
#include <stdlib.h>

#define N 5  

int processos[N] = {1, 2, 3, 4, 5}; 
int ativo[N] = {1, 1, 1, 1, 1};     

int bullyElection(int iniciador) {
    int eleito = iniciador;
    for (int i = 0; i < N; i++) {
        if (processos[i] > eleito && ativo[i]) {
            eleito = processos[i];
        }
    }
    return eleito;
}

int main() {
    printf("=== Bully Algorithm ===\n");
    ativo[4] = 0; 
    int iniciador = 2; 
    int lider = bullyElection(processos[iniciador]);
    printf("Processo %d iniciou eleição.\n", processos[iniciador]);
    printf("Novo líder eleito: %d\n", lider);
    return 0;
}
