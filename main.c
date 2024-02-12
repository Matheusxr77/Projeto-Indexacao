#include <stdio.h>
#include <stdlib.h>
#include "table/sorveteria.h"
#include "table/sorveteria.c"

// Função principal
int main (int argc, char *argv[]) {
    // Declaração da tabela
	tabela tabela;

    // Declaração das variáveis
	int opcao, valor;

    // Inicialização da tabela
	inicializarTabela(&tabela);

    // Função de limpeza da tela
	system("clear");
    
    // Laço de repetição que exibe as opções
	while(1) {
        // Menu principal de exibição de opções
		printf("|========================|\n");
		printf("|     Sorveteria BCC     |\n");
		printf("|========================|\n");
		printf("|========================|\n");
		printf("| 1 - Adicionar          |\n");
		printf("| 2 - Procurar           |\n");
		printf("| 3 - Remover            |\n");
		printf("| 4 - Em Ordem           |\n");
		printf("| 5 - Limpar tela        |\n");
		printf("| 99 - Sair              |\n");
		printf("|========================|\n");
		scanf("%d", &opcao);

        // Laço de escolha da opção 
		switch (opcao) {		
            case 1:
                // Chamada da função que adiciona um sorvete no arquivo
                adicionarSorvete(&tabela, lerDados());
                break;
            case 2:
                // Função de limpeza da tela
                system("clear");

                // Menu de busca por cada tipo de índice
                printf("|===========================|\n");
                printf("|       Sorveteria BCC      |\n");
                printf("|===========================|\n");
                printf("|===========================|\n");
                printf("| 1 - Procurar (ID)         |\n");
                printf("| 2 - Procurar (Fabricante) |\n");
                printf("| 3 - Procurar (Validade)   |\n");
                printf("|===========================|\n");
                scanf("%d", &opcao);

                // Laço de busca por cada tipo de índice
                switch (opcao) {
                    // Busca por ID
                    case 1:
                        // Função de limpeza da tela
                        system("clear");

                        // Exibição de menu e pedido do número do ID para busca
                        printf("|==========================|\n");
                        printf("|      Sorveteria BCC      |\n");
                        printf("|==========================|\n");
                        printf("\nInforme o numero de ID que deseja buscar: ");

                        // Leitura do número do ID fornecido pelo usuário
                        scanf("%d", &valor);

                        // Chamada da função de busca pelo índice BST, passando o número do ID
                        sorvete *sorvete = procurarSorveteBST(&tabela, valor);
                        break;
                    
                    // Busca por Fabricante
                    case 2:
                        // Função de limpeza da tela
                        system("clear");

                        // Exibição de menu e pedido do nome do fabricante para busca
                        printf("|==========================|\n");
                        printf("|      Sorveteria BCC      |\n");
                        printf("|==========================|\n");
                        printf("\nInforme o nome do fabricante que deseja buscar: ");

                        // Limpeza do buffer do teclado para evitar problemas com fgets
                        while(getchar() != '\n');

                        // Declaração do array de caracteres para armazenar o nome do fabricante
                        char fabricante[200];

                        // Leitura do nome do fabricante fornecido pelo usuário usando fgets
                        fgets(fabricante, 200, stdin);

                        // Remoção do caractere de nova linha do final do nome do fabricante
                        fabricante[strcspn(fabricante, "\n")] = 0;

                        // Chamada da função de busca pelo índice AVL, passando o nome do fabricante
                        sorvete = procurarSorveteAVL(&tabela, fabricante);
                        break;
                    
                    // Busca por Validade
                    case 3:
                        // Função de limpeza da tela
                        system("clear");

                        // Exibição de menu e pedido do número da validade para busca
                        printf("|==========================|\n");
                        printf("|      Sorveteria BCC      |\n");
                        printf("|==========================|\n");
                        printf("\nInforme a validade que deseja buscar: ");

                        // Leitura do número da validade fornecido pelo usuário
                        scanf("%d", &valor);

                        // Chamada da função de busca pelo índice RB
                        buscarRB(valor, tabela.indiceArvoreRB, &tabela);
                        break;
                }
                break;
            case 3:
                // Função de limpeza da tela
                system("clear");
                printf("|==========================|\n");
                printf("|      Sorveteria BCC      |\n");
                printf("|==========================|\n");
                printf("\nInforme o numero de ID que deseja remover: ");

                // Leitura do número do ID fornecido pelo usuário
                scanf("%d", &valor);

                // Chamada da função de remoção
                removerSorvete(&tabela, valor);
                break;
            case 4:
                // Função de limpeza da tela
                system("clear");
                printf("|==========================|\n");
                printf("|      Sorveteria BCC      |\n");
                printf("|==========================|\n");
                printf("\nInOrder da Arvore BST - (ID):\n");

                // Chamada da função inorder da BST
                inOrderBST(tabela.indiceArvoreBST, &tabela);
                printf("\n");
                printf("\nInOrder da Arvore AVL - (Fabricante):\n");

                // Chamada da função inorder da AVL
                inOrderAVL(tabela.indiceArvoreAVL, &tabela);
                printf("\n");
                printf("\nInOrder da Arvore RB - (Validade):\n");
                
                // Chamada da função inorder da RB
                inOrderRB(tabela.indiceArvoreRB, &tabela);
                printf("\n");
                break;
            case 5:
                // Função de limpeza da tela
                system("clear");
                break;
            case 99:
                // Função de limpeza da tela
                system("clear");
                printf("|===================================|\n");
                printf("|           Sorveteria BCC          |\n");
                printf("|===================================|\n");
                printf("|===================================|\n");
                printf("|        Obrigado pelo Acesso       |\n");
                printf("|  By: Matheus Marcos (3° Periodo)  |\n");
                printf("|===================================|\n");

                // Chamada da função de finalização da tabela
                finalizarTabela(&tabela);
                exit(0);
            default:
                printf("Opção invalida, tente novamente.\n");
		}
	}
}