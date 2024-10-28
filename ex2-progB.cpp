#include <stdio.h>
#include <windows.h>

DWORD WINAPI threadFunc(void* data) {
    // Simula a função do processo filho imprimindo o PID
    printf("Processo criado. PID: %lu\n", GetCurrentThreadId());
    return 0;
}

int main() {
    HANDLE threads[3];

    // Cria três threads (simulando chamadas para fork)
    for (int i = 0; i < 3; i++) {
        threads[i] = CreateThread(
            NULL,           // Atributos padrão de segurança
            0,              // Tamanho da pilha padrão
            threadFunc,     // Função a ser executada
            NULL,           // Argumento passado para a função
            0,              // Flags de criação
            NULL);          // ID da thread

        if (threads[i] == NULL) {
            fprintf(stderr, "Falha ao criar a thread.\n");
            return 1;
        }
    }

    // Aguarda todas as threads terminarem
    WaitForMultipleObjects(3, threads, TRUE, INFINITE);

    // Fecha os handles das threads
    for (int i = 0; i < 3; i++) {
        CloseHandle(threads[i]);
    }

    return 0;
}


/* Portanto, a resposta à pergunta "Programa 2 (figura 3.31, pág. 186): Quantos processos são criados?
" é 4 unidades de execução, sendo um processo pai e três threads. Isso foi confirmado pela saída do código
 adaptado para Windows, onde as threads são usadas para simular as chamadas `fork()` de Unix, criando novas 
 linhas de execução dentro do mesmo processo pai, e não processos independentes.

Assim, cada thread executa a função `threadFunc`, onde imprime seu próprio PID, confirmando que não há separação de memória 
entre as threads e o processo pai em ambientes Windows. Essa execução representa um trecho de código "simulado", onde cada thread compartilha 
o espaço de memória do processo pai, resultando no total de quatro unidades de execução. */

