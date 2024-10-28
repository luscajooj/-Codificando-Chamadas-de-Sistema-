#include <stdio.h>      // Biblioteca padr�o para entrada e sa�da, usada para fun��es como printf
#include <windows.h>    // Biblioteca para fun��es espec�ficas da API do Windows, incluindo cria��o de processos

// Fun��o que cria um novo processo
void cria_processo()
{
	STARTUPINFO si;               // Vari�vel que armazena informa��es de inicializa��o para o processo filho
	PROCESS_INFORMATION pi;       // Vari�vel que recebe informa��es sobre o novo processo (filho) e sua thread

	ZeroMemory(&si, sizeof(si));  // Inicializa todos os campos da estrutura STARTUPINFO com zero para evitar lixo de mem�ria
	si.cb = sizeof(si);           // Define o campo cb para especificar o tamanho da estrutura em bytes (de STARTUPINFO)
	ZeroMemory(&pi, sizeof(pi));  // Inicializa todos os campos da estrutura PROCESS_INFORMATION com zero

	// Cria��o de um novo processo (filho)
	// CreateProcess inicia um novo processo e um novo thread. O primeiro par�metro (NULL) indica que o caminho do execut�vel ser� fornecido no pr�ximo par�metro.
	// O segundo par�metro (child.exe) � o nome do execut�vel que ser� iniciado.
	// O terceiro e o quarto par�metros (NULL, NULL) s�o ponteiros para blocos de mem�ria que podem ser utilizados para passar informa��es ao processo e thread.
	// O quinto par�metro (FALSE) indica que o processo filho n�o herda os identificadores de seguran�a do pai.
	// O sexto par�metro (0) indica que nenhuma op��o especial para a cria��o do processo est� sendo usada.
	// O s�timo e o oitavo par�metros (NULL, NULL) indicam que o novo processo usar� o mesmo ambiente de processo/diret�rio do pai.
	// O nono par�metro (&si) � um ponteiro para a estrutura STARTUPINFO, que cont�m informa��es de inicializa��o do novo processo.
	// O d�cimo par�metro (&pi) � um ponteiro para a estrutura PROCESS_INFORMATION, que recebe informa��es sobre o novo processo criado, como seu identificador e identificador da thread.
	if (!CreateProcess(NULL, "child.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
	{
		// Se CreateProcess falhar (retorna FALSE), uma mensagem de erro � impressa na tela do usu�rio
		printf("Erro ao criar o processo. C�digo do erro: %lu\n", GetLastError());
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
	// O la�o for cria 3 novos processos filhos, chamando a fun��o cria_processo()
	for (int i = 0; i < 3; i++)
	{
		cria_processo();  // Chama a fun��o para criar um novo processo
	}

	// Imprime o PID do processo principal (pai) ap�s a cria��o dos processos filhos
	printf("Processo principal. PID: %lu\n", (unsigned long)GetCurrentProcessId());

	return 0;  // Retorna 0 para indicar que o programa terminou com sucesso
}

/* Portanto, a resposta � pergunta "Programa 3 (figura 3.32, p�g. 187): Incluindo o processo-pai inicial,
quantos processos s�o criados pelo programa?" � 4. Isso ocorre porque o programa principal cria 3 processos
filhos atrav�s da fun��o cria_processo(). Assim, contando o processo pai que executa o c�digo, temos um total de
4 processos ativos no sistema. Cada chamada � fun��o cria_processo resulta na cria��o de um novo processo, e como n�o
h� compartilhamento de mem�ria entre os processos, cada um opera de forma independente. */
