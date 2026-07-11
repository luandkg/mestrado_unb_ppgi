# 📌 Principais algoritmos estudados

- **Algoritmo de eleição de líder**
  - Ex.: Bully Algorithm, Chang & Roberts.
  - Usado para escolher um coordenador entre processos distribuídos.

- **Algoritmos de exclusão mútua distribuída**
  - Ex.: Ricart–Agrawala, Maekawa.
  - Garantem que apenas um processo acesse um recurso crítico por vez, sem um servidor central.

- **Algoritmos de ordenação de eventos**
  - Ex.: Relógios lógicos de Lamport, Relógios vetoriais.
  - Permitem estabelecer ordem parcial de eventos em sistemas sem relógio global.

- **Algoritmos de consenso**
  - Ex.: Paxos, Raft.
  - Usados para garantir que múltiplos nós concordem em um mesmo valor, mesmo diante de falhas.

- **Algoritmos de replicação e consistência**
  - Ex.: Quorum-based protocols, Primary-backup.
  - Mantêm dados replicados consistentes entre diferentes servidores.

- **Algoritmos de difusão/multicast confiável**
  - Ex.: Algoritmos de difusão ordenada (total order broadcast).
  - Garantem que mensagens cheguem a todos os processos na mesma ordem.

- **Algoritmos de detecção de falhas**
  - Ex.: Heartbeat, gossip-based failure detectors.
  - Identificam quando um nó deixou de responder.

- **Algoritmos de balanceamento de carga**
  - Distribuem tarefas entre servidores para otimizar desempenho.
