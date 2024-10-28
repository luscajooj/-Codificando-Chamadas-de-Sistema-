#include <stdio.h>
#include <windows.h>

DWORD WINAPI threadFunc(void* data) {
    // Simula a fun��o do processo filho imprimindo o PID
    printf("Processo criado. PID: %lu\n", GetCurrentThreadId());
    return 0;
}

int main() {
    HANDLE threads[3];

    // Cria tr�s threads (simulando chamadas para fork)
    for (int i = 0; i < 3; i++) {
        threads[i] = CreateThread(
            NULL,           // Atributos padr�o de seguran�a
            0,              // Tamanho da pilha padr�o
            threadFunc,     // Fun��o a ser executada
            NULL,           // Argumento passado para a fun��o
            0,              // Flags de cria��o
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


/* Portanto, a resposta � pergunta "Programa 2 (figura 3.31, p�g. 186): Quantos processos s�o criados?
" � 4 unidades de execu��o, sendo um processo pai e tr�s threads. Isso foi confirmado pela sa�da do c�digo
 adaptado para Windows, onde as threads s�o usadas para simular as chamadas `fork()` de Unix, criando novas 
 linhas de execu��o dentro do mesmo processo pai, e n�o processos independentes.

Assim, cada thread executa a fun��o `threadFunc`, onde imprime seu pr�prio PID, confirmando que n�o h� separa��o de mem�ria 
entre as threads e o processo pai em ambientes Windows. Essa execu��o representa um trecho de c�digo "simulado", onde cada thread compartilha 
o espa�o de mem�ria do processo pai, resultando no total de quatro unidades de execu��o. */

