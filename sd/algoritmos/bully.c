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
    printf("------------------------------ Bully Algorithm ------------------------------\n");
    ativo[4] = 0; 
    int iniciador = 2; 
    int lider = bullyElection(processos[iniciador]);
    printf("\t >> Processo %d iniciou eleição.\n", processos[iniciador]);
    printf("\t >> Novo líder eleito: %d\n", lider);
    return 0;
}

/*
 * Bully Algorithm (Algoritmo Valentão)
 *
 * O Bully Algorithm é um método de eleição de coordenador em sistemas distribuídos.
 * Cada processo possui um identificador único (ID). Quando o coordenador atual falha,
 * um processo inicia uma eleição enviando mensagens para todos os processos com ID maior.
 *
 * Regras principais:
 * 1. Se nenhum processo com ID maior responder, o iniciador se declara coordenador.
 * 2. Se algum processo com ID maior responder, esse processo assume a eleição.
 * 3. O vencedor (processo com maior ID ativo) anuncia sua vitória para todos.
 * 4. Caso um processo com ID maior retorne ao sistema, ele pode iniciar nova eleição
 *    e "derrubar" o coordenador atual.
 *
 * Vantagens:
 * - Simples de implementar.
 * - Garante sempre um coordenador único.
 *
 * Desvantagens:
 * - Pode gerar muitas mensagens em sistemas grandes.
 * - Não considera desempenho ou carga, apenas o maior ID.
 *
 * Aplicações:
 * - Bancos de dados distribuídos.
 * - Sistemas de clusters.
 * - Redes peer-to-peer.
 */

