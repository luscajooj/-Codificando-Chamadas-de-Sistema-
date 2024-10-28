#include <stdio.h>    // Inclui funções básicas de entrada e saída
#include <windows.h>  // Inclui funções específicas para a manipulação de threads no Windows

/* Função que será executada por cada thread */
DWORD WINAPI threadFunc(void* data) {
    // Simula a função do processo filho imprimindo o PID da thread atual
    printf("Processo criado. PID: %lu\n", GetCurrentThreadId()); // GetCurrentThreadId() obtém o ID da thread atual, que simula o PID de um processo no Windows
    return 0;
}

int main() {
    /* Declaração de um array de handles para threads */
    HANDLE threads[3]; // Array para armazenar os handles das três threads que serão criadas, simulando processos filhos

    /* Criação de três threads (simulando três processos filhos) */
    for (int i = 0; i < 3; i++) {
        threads[i] = CreateThread(
            NULL,           // NULL indica que os atributos padrão de segurança são aplicados à thread
            0,              // Define o tamanho da pilha como padrão do sistema 
            threadFunc,     // Função a ser executada pela thread
            NULL,           // Argumento passado para a função threadFunc, que não é necessário neste caso
            0,              // Flags de criação, onde 0 indica que a thread começa a ser executada imediatamente
            NULL);          // ID da thread, que não precisa ser armazenado explicitamente

        if (threads[i] == NULL) {
            // Caso CreateThread falhe, imprime mensagem de erro e encerra o programa
            fprintf(stderr, "Falha ao criar a thread.\n");
            return 1;
        }
    }

    /* Espera todas as threads terminarem sua execução */
    // WaitForMultipleObjects aguarda que todas as threads terminem antes de prosseguir
    // O primeiro parâmetro (3) indica o número de threads a serem aguardadas
    // O segundo parâmetro é o array de handles para as threads
    // O terceiro parâmetro (TRUE) indica que queremos aguardar todas as threads simultaneamente
    // O último parâmetro (INFINITE) faz com que o programa espere indefinidamente até que todas as threads terminem
    WaitForMultipleObjects(3, threads, TRUE, INFINITE);

    /* Libera recursos do sistema fechando os handles das threads */
    for (int i = 0; i < 3; i++) {
        CloseHandle(threads[i]); // Fecha o handle de cada thread, liberando recursos alocados para cada uma delas
    }

    return 0; // Retorna 0 para indicar que o programa terminou com sucesso
}

/* Portanto, a resposta à pergunta "Programa 2 (figura 3.31, pág. 186): Quantos processos são criados?" é 4 unidades de execução, sendo um processo pai e três threads. Isso foi confirmado pela saída do código adaptado para Windows, onde as threads são usadas para simular as chamadas `fork()` de Unix, criando novas linhas de execução dentro do mesmo processo pai, e não processos independentes.

Assim, cada thread executa a função `threadFunc`, onde imprime seu próprio PID, confirmando que não há separação de memória entre as threads e o processo pai em ambientes Windows. Essa execução representa um trecho de código "simulado", onde cada thread compartilha o espaço de memória do processo pai, resultando no total de quatro unidades de execução. */
