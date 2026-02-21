#include <stdio.h>
#include <string.h>
#include <locale.h>   // Necessário para acentuação correta

/*
 * Estrutura: Territorio
 * Armazena informações básicas de um território:
 * - nome: nome do território (ex: "Brasil")
 * - cor: cor do exército que ocupa o território (ex: "Verde")
 * - tropas: quantidade de tropas posicionadas no território
 */
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {
    // Configura o locale para permitir acentuação
    // Use "pt_BR.UTF-8" se o terminal for UTF-8 (Linux, PowerShell novo)
    // Use "Portuguese_Brazil.1252" se for CMD antigo do Windows
    setlocale(LC_ALL, "pt_BR.UTF-8");

    // Declaração de um vetor para armazenar 5 territórios
    struct Territorio territorios[5];
    int i;

    printf("=== Cadastro de Territórios ===\n\n");

    // Entrada de dados: cadastro dos 5 territórios
    for (i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);

        printf("Nome: ");
        scanf(" %29[^\n]", territorios[i].nome);  // Lê até 29 caracteres, incluindo espaços

        printf("Cor do exército: ");
        scanf(" %9s", territorios[i].cor);        // Lê até 9 caracteres (sem espaços)

        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n");

    }
           
    // Exibição dos dados cadastrados
    printf("=== Lista de Territórios Cadastrados ===\n\n");
    for (i = 0; i < 5; i++) {
        printf("Território %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exército: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
        printf("---------------------------\n");
    }
    
        // Pausa antes de encerrar o programa
    printf("\nPressione ENTER para fechar...");
    getchar(); // consome o \n pendente do último scanf
    getchar(); // espera ENTER real
    
    return 0;
}
