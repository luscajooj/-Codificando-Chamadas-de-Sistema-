#include <stdio.h>      // Biblioteca padrão para entrada e saída, usada para funções como printf
#include <windows.h>    // Biblioteca para funções específicas da API do Windows, incluindo criação de processos

// Função que cria um novo processo
void cria_processo()
{
	STARTUPINFO si;               // Variável que armazena informações de inicialização para o processo filho
	PROCESS_INFORMATION pi;       // Variável que recebe informações sobre o novo processo (filho) e sua thread

	ZeroMemory(&si, sizeof(si));  // Inicializa todos os campos da estrutura STARTUPINFO com zero para evitar lixo de memória
	si.cb = sizeof(si);           // Define o campo cb para especificar o tamanho da estrutura em bytes (de STARTUPINFO)
	ZeroMemory(&pi, sizeof(pi));  // Inicializa todos os campos da estrutura PROCESS_INFORMATION com zero

	// Criação de um novo processo (filho)
	// CreateProcess inicia um novo processo e um novo thread. O primeiro parâmetro (NULL) indica que o caminho do executável será fornecido no próximo parâmetro.
	// O segundo parâmetro (child.exe) é o nome do executável que será iniciado.
	// O terceiro e o quarto parâmetros (NULL, NULL) são ponteiros para blocos de memória que podem ser utilizados para passar informações ao processo e thread.
	// O quinto parâmetro (FALSE) indica que o processo filho não herda os identificadores de segurança do pai.
	// O sexto parâmetro (0) indica que nenhuma opção especial para a criação do processo está sendo usada.
	// O sétimo e o oitavo parâmetros (NULL, NULL) indicam que o novo processo usará o mesmo ambiente de processo/diretório do pai.
	// O nono parâmetro (&si) é um ponteiro para a estrutura STARTUPINFO, que contém informações de inicialização do novo processo.
	// O décimo parâmetro (&pi) é um ponteiro para a estrutura PROCESS_INFORMATION, que recebe informações sobre o novo processo criado, como seu identificador e identificador da thread.
	if (!CreateProcess(NULL, "child.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		// Se CreateProcess falhar (retorna FALSE), uma mensagem de erro é impressa na tela do usuário
		printf("Erro ao criar o processo. Código do erro: %lu\n", GetLastError());
	}
	else
	{
		// Se CreateProcess for bem-sucedido, imprime o PID do novo processo criado
		printf("Processo criado. PID: %lu\n", (unsigned long)pi.dwProcessId);
		CloseHandle(pi.hProcess);  // Fecha o handle do processo, liberando recursos do sistema
		CloseHandle(pi.hThread);   // Fecha o handle da thread, liberando recursos do sistema
	}
}

int main()
{
	// O laço for cria 3 novos processos filhos, chamando a função cria_processo()
	for (int i = 0; i < 3; i++)
	{
		cria_processo();  // Chama a função para criar um novo processo
	}

	// Imprime o PID do processo principal (pai) após a criação dos processos filhos
	printf("Processo principal. PID: %lu\n", (unsigned long)GetCurrentProcessId());

	return 0;  // Retorna 0 para indicar que o programa terminou com sucesso
}

/* Portanto, a resposta à pergunta "Programa 3 (figura 3.32, pág. 187): Incluindo o processo-pai inicial,
quantos processos são criados pelo programa?" é 4. Isso ocorre porque o programa principal cria 3 processos
filhos através da função cria_processo(). Assim, contando o processo pai que executa o código, temos um total de
4 processos ativos no sistema. Cada chamada à função cria_processo resulta na criação de um novo processo, e como não
há compartilhamento de memória entre os processos, cada um opera de forma independente. */
