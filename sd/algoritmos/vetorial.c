#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_PROCESSES 5
#define NUM_EVENTS 20

typedef struct {
    int id;
    int clock[NUM_PROCESSES];
} Process;

// Função para imprimir vetor
void print_vector(int v[]) {
    printf("[");
    for (int i = 0; i < NUM_PROCESSES; i++) {
        printf("%d", v[i]);
        if (i < NUM_PROCESSES - 1) printf(", ");
    }
    printf("]");
}

// Evento local
void local_event(Process *p) {
    p->clock[p->id]++;
    printf("Processo %d executou evento local. Vetor = ", p->id);
    print_vector(p->clock);
    printf("\n");
}

// Envio de mensagem
void send_message(Process *sender, Process *receiver) {
    sender->clock[sender->id]++;
    printf("Processo %d enviou mensagem para %d. Vetor = ", sender->id, receiver->id);
    print_vector(sender->clock);
    printf("\n");

    // Recepção
    for (int i = 0; i < NUM_PROCESSES; i++) {
        receiver->clock[i] = (receiver->clock[i] > sender->clock[i] ? receiver->clock[i] : sender->clock[i]);
    }
    receiver->clock[receiver->id]++;
    printf("Processo %d recebeu mensagem de %d. Vetor atualizado = ", receiver->id, sender->id);
    print_vector(receiver->clock);
    printf("\n");
}

// Comparação de vetores: retorna -1 se A < B, 1 se A > B, 0 se concorrentes
int compare_vectors(int a[], int b[]) {
    int less = 0, greater = 0;
    for (int i = 0; i < NUM_PROCESSES; i++) {
        if (a[i] < b[i]) less = 1;
        if (a[i] > b[i]) greater = 1;
    }
    if (less && !greater) return -1; // a ocorreu antes de b
    if (greater && !less) return 1;  // a ocorreu depois de b
    return 0; // concorrentes
}

int main() {
    Process processes[NUM_PROCESSES];
    for (int i = 0; i < NUM_PROCESSES; i++) {
        processes[i].id = i;
        for (int j = 0; j < NUM_PROCESSES; j++) {
            processes[i].clock[j] = 0;
        }
        printf("Processo %d criado. Vetor inicial = ", processes[i].id);
        print_vector(processes[i].clock);
        printf("\n");
    }

    srand(time(NULL));

    for (int e = 0; e < NUM_EVENTS; e++) {
        int action = rand() % 2; // 0 = evento local, 1 = envio de mensagem
        int p = rand() % NUM_PROCESSES;

        if (action == 0) {
            local_event(&processes[p]);
        } else {
            int receiver = rand() % NUM_PROCESSES;
            while (receiver == p) receiver = rand() % NUM_PROCESSES;
            send_message(&processes[p], &processes[receiver]);
        }
    }

    printf("\n=== Estado final dos vetores ===\n");
    for (int i = 0; i < NUM_PROCESSES; i++) {
        printf("Processo %d: ", processes[i].id);
        print_vector(processes[i].clock);
        printf("\n");
    }

    // Exemplo de comparação entre dois processos
    int result = compare_vectors(processes[0].clock, processes[1].clock);
    if (result == -1) printf("Eventos do P0 ocorreram antes dos do P1.\n");
    else if (result == 1) printf("Eventos do P0 ocorreram depois dos do P1.\n");
    else printf("Eventos do P0 e P1 são concorrentes.\n");

    return 0;
}

/*
 * Algoritmo de Relógios Vetoriais
 *
 * 📌 Descrição:
 * Relógios vetoriais são uma extensão dos relógios lógicos de Lamport,
 * utilizados para estabelecer uma ordenação de eventos em sistemas distribuídos
 * e, principalmente, para detectar relações de causalidade entre eles.
 *
 * 🎯 Objetivo:
 * - Detectar corretamente se um evento ocorreu antes de outro (causalidade),
 *   ou se dois eventos são concorrentes (sem relação causal).
 * - Fornecer uma ordenação mais precisa que os relógios de Lamport.
 *
 * ⚙️ Funcionamento:
 * - Cada processo mantém um vetor de inteiros, com tamanho igual ao número de processos.
 * - Em cada evento local, o processo incrementa sua própria posição no vetor.
 * - Ao enviar uma mensagem, o processo incrementa sua posição e anexa o vetor completo.
 * - Ao receber uma mensagem, o processo atualiza seu vetor tomando o máximo
 *   entre cada posição local e a posição recebida, e depois incrementa sua própria posição.
 *
 * ✅ Critérios de Aceitação:
 * - Vetores de timestamps devem ser atualizados corretamente a cada evento local.
 * - Mensagens enviadas devem carregar o vetor de timestamps atual.
 * - O receptor deve atualizar seu vetor com base no maior valor recebido em cada posição.
 * - A comparação entre vetores deve permitir identificar:
 *      - Evento A → Evento B (A ocorreu antes de B).
 *      - Evento B → Evento A (B ocorreu antes de A).
 *      - Eventos concorrentes (não há relação causal).
 *
 * 📚 Referências:
 * - Fidge, C. J. (1988). "Timestamps in Message-Passing Systems That Preserve the Partial Ordering".
 *   Proceedings of the 11th Australian Computer Science Conference.
 * - Mattern, F. (1989). "Virtual Time and Global States of Distributed Systems".
 *   In Parallel and Distributed Algorithms.
 * - Tanenbaum, A. S., & Van Steen, M. (2007). "Distributed Systems: Principles and Paradigms".
 *   Pearson Education.
 */
