/* Inclusão de bibliotecas */
#include <stdio.h>   // Contém funções básicas de entrada e saída

/* Declaração e inicialização de variável global */
int value = 5; // Variável do tipo inteiro, que possui o nome value e o valor 5. Essa variável simula o valor inicial que o processo pai (originalmente no Linux) teria

/* Função principal*/
int main() {
    // Adição de 15 ao valor da variável global
    value += 15;  // Agora 'value' será igual a 20

    // Imprime o valor da variável 'value' no console, com a mensagem "CHILD: value = "
    // Como 'value' foi incrementado anteriormente, a saída será "CHILD: value = 20"
    printf("CHILD: value = %d\n", value);  

    // Retorna 0 para indicar que o programa terminou com sucesso
    return 0;
}
 
