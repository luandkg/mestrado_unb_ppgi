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

/*
------------------------------------------------------------
📌 Implementação do Algoritmo de Eleição Chang & Roberts
------------------------------------------------------------

Descrição:
    Este programa implementa o algoritmo circular de eleição
    de líder proposto por Chang & Roberts, utilizado em sistemas
    distribuídos com topologia em anel.

Objetivo:
    Garantir uma eleição eficiente em topologia anel, assegurando
    que todos os processos participem da escolha do coordenador.

Funcionamento do Algoritmo:
    - Cada processo possui um identificador único (ID).
    - Quando um processo inicia uma eleição, ele envia uma mensagem
      contendo seu próprio ID ao próximo processo no anel.
    - Ao receber uma mensagem de eleição:
        • Se o ID recebido for maior que o seu, o processo repassa
          a mensagem adiante.
        • Se o ID recebido for menor que o seu, o processo substitui
          o ID pela sua própria identificação e envia ao próximo.
        • Se o ID recebido for igual ao seu, significa que a mensagem
          percorreu todo o anel e este processo é eleito líder.
    - Após a eleição, uma mensagem de anúncio é propagada para que
      todos os processos reconheçam o novo coordenador.

Critérios de Aceitação:
    ✅ O líder deve ser corretamente eleito após a propagação
       das mensagens pelo anel.
    ✅ Todos os processos devem reconhecer o novo líder.
    ✅ O algoritmo deve lidar com falhas e garantir consistência
       na eleição.

Referências:
    - Chang & Roberts Algorithm - Wikipedia
    - Chang, E., & Roberts, R. (1979). "An Improved Algorithm for
      Decentralized Election in Distributed Systems."
      ACM Communications, 22(5), 337–339.
    - Tanenbaum, A. S., & Van Steen, M. (2007).
      "Distributed Systems: Principles and Paradigms."
      Pearson Education.
------------------------------------------------------------
*/
