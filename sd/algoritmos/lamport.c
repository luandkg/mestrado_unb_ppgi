/*
 * Relógios Lógicos de Lamport com Timeline
 * 5 processos, 30 eventos
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_PROCESSES 5
#define NUM_EVENTS 30

typedef struct {
    int id;
    int clock;
} Process;

// Função para registrar eventos na timeline
void timeline(const char *event, int pid, int clock, int target) {
    if (target == -1)
        printf("[Timeline] Processo %d %s | Clock = %d\n", pid, event, clock);
    else
        printf("[Timeline] Processo %d %s para %d | Clock = %d\n", pid, event, target, clock);
}

// Evento local
void local_event(Process *p) {
    p->clock++;
    timeline("executou evento local", p->id, p->clock, -1);
}

// Envio de mensagem
int send_message(Process *sender, int receiver_id) {
    sender->clock++;
    timeline("enviou mensagem", sender->id, sender->clock, receiver_id);
    return sender->clock;
}

// Recebimento de mensagem
void receive_message(Process *receiver, int msg_clock, int sender_id) {
    receiver->clock = (receiver->clock > msg_clock ? receiver->clock : msg_clock) + 1;
    timeline("recebeu mensagem", receiver->id, receiver->clock, sender_id);
}

int main() {
    Process processes[NUM_PROCESSES];
    for (int i = 0; i < NUM_PROCESSES; i++) {
        processes[i].id = i + 1;
        processes[i].clock = 0;
        timeline("foi criado", processes[i].id, processes[i].clock, -1);
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

            int msg_clock = send_message(&processes[p], processes[receiver].id);
            receive_message(&processes[receiver], msg_clock, processes[p].id);
        }
    }

    printf("\n=== Estado final dos relógios ===\n");
    for (int i = 0; i < NUM_PROCESSES; i++) {
        printf("Processo %d: Clock = %d\n", processes[i].id, processes[i].clock);
    }

    return 0;
}

/*
 * Algoritmo de Relógios Lógicos de Lamport
 *
 * 📌 Descrição:
 * O algoritmo de Lamport é um mecanismo de ordenação parcial de eventos
 * em sistemas distribuídos. Ele permite estabelecer uma noção de tempo lógico
 * sem depender de um relógio físico global.
 *
 * 🎯 Objetivo:
 * - Garantir que a relação de causalidade entre eventos seja preservada.
 * - Estabelecer uma ordem consistente de eventos em múltiplos processos.
 *
 * ⚙️ Funcionamento:
 * - Cada processo mantém um contador inteiro chamado "relógio lógico".
 * - Em cada evento local, o processo incrementa seu relógio.
 * - Ao enviar uma mensagem, o processo incrementa o relógio e anexa o valor.
 * - Ao receber uma mensagem, o processo atualiza seu relógio para:
 *      max(clock_local, clock_recebido) + 1
 *
 * ✅ Critérios de Aceitação:
 * - Os timestamps devem ser atualizados corretamente a cada evento local.
 * - Mensagens enviadas devem carregar o timestamp atual.
 * - O receptor deve atualizar seu relógio lógico com base no maior valor recebido.
 * - A ordenação parcial de eventos deve ser garantida em todos os cenários.
 *
 * 📚 Referências:
 * - Lamport, L. (1978). "Time, Clocks, and the Ordering of Events in a Distributed System".
 *   Communications of the ACM, 21(7), 558–565.
 * - Tanenbaum, A. S., & Van Steen, M. (2007). "Distributed Systems: Principles and Paradigms".
 *   Pearson Education.
 */
