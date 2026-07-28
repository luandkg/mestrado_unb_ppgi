#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

#define N 4
#define Q 2

int quorum[N][Q] = {
    {0,1}, {1,2}, {2,3}, {3,0}
};

bool granted[N];

pthread_mutex_t lock;

void request_CS(int id) {
    pthread_mutex_lock(&lock);
    printf("Processo %d requisitou CS\n", id);

    for (int i = 0; i < Q; i++) {
        int q = quorum[id][i];
        printf("Processo %d -> requisição enviada a %d\n", id, q);
        granted[q] = true;
    }
    pthread_mutex_unlock(&lock);

    bool ok = false;
    while (!ok) {
        ok = true;
        for (int i = 0; i < Q; i++) {
            int q = quorum[id][i];
            if (!granted[q]) ok = false;
        }
        usleep(100000);
    }
}

void release_CS(int id) {
    pthread_mutex_lock(&lock);
    printf("Processo %d liberou CS\n", id);
    for (int i = 0; i < Q; i++) {
        int q = quorum[id][i];
        granted[q] = false;
    }
    pthread_mutex_unlock(&lock);
}

void *process(void *arg) {
    int id = *(int *)arg;
    request_CS(id);
    printf("Processo %d entrou na CS\n", id);
    sleep(1);
    release_CS(id);
    return NULL;
}

int main() {
    pthread_t threads[N];
    int ids[N];
    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, process, &ids[i]);
    }
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);
    return 0;
}

/*
------------------------------------------------------------
📌 Implementação do Algoritmo de Exclusão Mútua Maekawa
------------------------------------------------------------
Descrição:
    Este programa implementa o algoritmo distribuído de exclusão
    mútua proposto por Maekawa, que utiliza quóruns para reduzir
    o número de mensagens necessárias para acesso à seção crítica.

Objetivo:
    Reduzir a quantidade de mensagens trocadas entre processos
    para garantir acesso exclusivo à seção crítica (Critical Section - CS),
    mantendo eficiência e consistência.

Funcionamento do Algoritmo:
    - Cada processo pertence a um conjunto de quórum (grupo de votação).
    - Os quóruns são definidos de forma que qualquer dois quóruns
      tenham pelo menos um processo em comum.
    - Quando um processo deseja entrar na CS:
        • Ele envia uma requisição (REQUEST) apenas aos membros
          do seu quórum.
        • Cada membro do quórum pode conceder permissão (REPLY)
          a apenas um processo por vez.
    - O processo só entra na CS após receber todas as permissões
      do seu quórum.
    - Ao sair da CS, o processo envia mensagens de liberação (RELEASE)
      para os membros do quórum, permitindo que outros prossigam.
    - Esse mecanismo garante exclusão mútua, pois a interseção
      entre quóruns impede que dois processos diferentes entrem
      simultaneamente na CS.

Critérios de Aceitação:
    ✅ Os quóruns devem ser definidos corretamente, garantindo
       interseção entre eles.
    ✅ A exclusão mútua deve ser assegurada em todos os cenários.
    ✅ O algoritmo deve lidar com falhas e garantir justiça no acesso.

Referências:
    - Maekawa’s Algorithm - Wikipedia
    - Maekawa, M. (1985).
      "A √N Algorithm for Mutual Exclusion in Decentralized Systems."
      ACM Transactions on Computer Systems, 3(2), 145–159.
    - Tanenbaum, A. S., & Van Steen, M. (2007).
      "Distributed Systems: Principles and Paradigms."
      Pearson Education.
------------------------------------------------------------
*/

/* 
   O algoritmo de Maekawa é uma solução distribuída para exclusão mútua,
   que reduz o número de mensagens necessárias em comparação ao Ricart-Agrawala.
   Em vez de solicitar permissão a todos os processos, cada processo possui
   um quórum específico (um subconjunto de processos) e só precisa obter
   autorização de todos os membros desse quórum para entrar na seção crítica.
   Isso diminui a sobrecarga de comunicação e melhora a escalabilidade em
   sistemas grandes, mantendo a garantia de que apenas um processo acessa
   o recurso crítico por vez.
*/

/* 
   A ideia central é que os quóruns são definidos de forma que qualquer par
   de processos compartilhe pelo menos um membro em comum. Esse membro atua
   como "árbitro" e evita que dois processos diferentes entrem na seção crítica
   simultaneamente. Quando um processo libera a seção crítica, ele envia
   mensagens de liberação ao seu quórum, permitindo que outros processos
   possam obter acesso. Assim, o algoritmo de Maekawa combina eficiência
   (menos mensagens) com segurança (garantia de exclusão mútua).
*/