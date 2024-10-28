/* Inclusão de bibliotecas */
#include <windows.h> // Contém funções específicas para Windows
#include <stdio.h>   // Contém funções básicas de entrada e saída

/* Declaração e inicialização de variável global */
int value = 5; // Variável do tipo inteiro, que possui o nome value e o valor 5. Essa variável simula o valor inicial que o processo pai (originalmente no Linux) teria

/* Função principal*/
int main() 
{
    /* Declaração de variáveis locais */
    STARTUPINFO si; // Variável que armazena informações de inicialização para o processo filho
    PROCESS_INFORMATION pi; // Variável que recebe informações sobre o novo processo (filho) e sua thread 

    /* Inicialização de estruturas para evitar comportamentos indesejados */
    ZeroMemory(&si, sizeof(si)); // Função que zera todos os campos da estrutura si com zero (zera a memória do endereço de STARTUPINFO)
    si.cb = sizeof(si); // Define o campo cb para especificar o tamanho da estutura em bytes (de STARTUPINFO)
    ZeroMemory(&pi, sizeof(pi)); // Função que zera todos os campos da estrutura pi com zero (zera a memória do endereço de PROCESS_INFORMATION)


    /* Criação de um novo processo (filho) */

    // Como no Windows não há fork(), usamos CreateProcess() para iniciar um novo processo e um novo thread, com uma estrutura condicional if que verifica se a chamada da função foi bem-sucedida
    if (CreateProcess(NULL, "child.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) // O primeiro parâmetro (NULL), significa que o caminho do executável será fornecido no próximo parâmetro; O segundo parâmetro (child.exe) é o nome do executável que será iniciado; O terceiro e o quarto parâmetros (NULL, NULL) são ponteiros para blocos de memória que podem ser utilizados para passar informações para o processo e o thread; O quinto parâmetro (FALSE) indica que o processo filho não herda os identificadores de segurança do pai; O sexto parâmetro (0) indica que nenhuma opção especial para a criação do processo está sendo usada; O sétimo parágrafo e o oitavo parágrafos (NULL, NULL) indica que o novo processo usará o mesmo ambiente de processo/diretório do pai; O nono parâmetro (&si) é um ponteiro de STARTUPINFO, que contém informações de inicialização do novo processo; O décimo parâmetro (&pi) é um ponteiro de PROCESS_INFORMATION, que recebe informações sobre o novo processo criado, como seu identificador e identificador do thread.
    {
        // Se CreateProcess retornar sucesso (um valor diferente de zero), o processo filho é iniciado, com a função WaitForSingleObject, que equivale ao wait() do Linux, onde o processo pai aguarda o processo filho terminar
        WaitForSingleObject(pi.hProcess, INFINITE); // O parimeiro parâmetro (pi.hProcess) é um identificador para o processo filho que foi criado e o segundo parâmeteo (INFINITE) indica que o processo pai não continuará sua execução indefinidamente, até que o processo filho termine

        // Quando o processo filho terminar, o processo pai fecha os handles (identificadores/referências) abertos para o processo (pi.hProcess) e para a thread (pi.hThread) do filho, liberando recursos do sistema
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        // Impressão do valor da variável value no processo pai, que permanece 5, pois no Windows, o processo pai e o filho não compartilham memória (diferente do fork() no Linux), então a alteração no valor do filho não afeta o pai
        printf("PARENT: value = %d\n", value); // LINHA A
    } else 
    {   
        // Se CreateProcess retornar uma falha (um valor igual a zero), uma mensagem de erro é impressa na tela do usuário
        fprintf(stderr, "CreateProcess falhou.\n");
        return 1;
    }

    // Retorna 0 para indicar que o programa terminou com sucesso
    return 0;
}

/* Portanto, a resposta à pergunta "Programa 1 (figura 3.30, pág. 185): Que saída haverá na linha A?" é 5. Isso foi confirmado através da segunda saída durante a execução do código, pois o valor da variável no processo pai permanece inalterado, uma vez que não há compartilhamento de memória entre o processo pai e o processo filho em ambientes Windows. 
Também é possível observar que na primeira execução temos o valor do processo filho, que é 20, resultante do incremento de 15 na variável global que já possuía o valor 5. Essa execução representa um trecho de código "truncado" dentro do código principal, onde o processo filho altera seu próprio valor sem impactar o processo pai.* */