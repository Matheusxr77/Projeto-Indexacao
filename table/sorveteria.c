#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorveteria.h"

// Inicialização da árvore BST
void inicializarBST (arvoreBST *raiz) {
	*raiz = NULL;
}

// Inicialização da árvore AVL
void inicializarAVL (arvoreAVL *raiz) {
	*raiz = NULL;
}

// Inicialização da árvore RB
void inicializarRB (arvoreRB *raiz) {
	*raiz = NULL;
}

// Função para inicializar uma tabela de sorvetes
int inicializarTabela (tabela *tab) {
	// Inicializa as árvores
	inicializarBST(&tab->indiceArvoreBST);
	inicializarAVL(&tab->indiceArvoreAVL);
	inicializarRB(&tab->indiceArvoreRB);

	// Abre (ou cria, se não existir) o arquivo "dados.dat" em modo de leitura e escrita binária
	tab->arquivo = fopen("dados.dat", "a+b");

	// Carrega os dados das árvores a partir do arquivo ".dat" (se existir)
	tab->indiceArvoreBST = carregarArquivoBST("indicesBST.dat", tab->indiceArvoreBST);
	tab->indiceArvoreAVL = carregarArquivoAVL("indicesAVL.dat", tab->indiceArvoreAVL);
	tab->indiceArvoreRB = carregarArquivoRB("indicesRB.dat", tab->indiceArvoreRB);

	// Verifica se o arquivo "dados.dat" foi aberto com sucesso
	if (tab->arquivo != NULL) {
		return 1;
	} else {
		return 0;
	}
}

// Função para finalizar uma tabela de sorvetes
void finalizarTabela (tabela *tab) {
	// Fecha o arquivo de dados associado à tabela
	fclose(tab->arquivo);

	// Salva os dados da árvore no arquivo ".dat"
	salvarArquivoBST("indicesBST.dat", tab->indiceArvoreBST);
	salvarArquivoAVL("indicesAVL.dat", tab->indiceArvoreAVL);
	salvarArquivoRB("indicesRB.dat", tab->indiceArvoreRB);
}

// Função para adicionar um sorvete à tabela
void adicionarSorvete (tabela *tab, sorvete *p) {
	int posicaoNovoRegistro;

	// Verifica se o arquivo de dados associado à tabela está aberto
	if (tab->arquivo != NULL) {
		// Posiciona o cursor no final do arquivo
		fseek(tab->arquivo, 0L, SEEK_END);

		// Obtém a posição do novo registro
		posicaoNovoRegistro = ftell(tab->arquivo);

		// Adicionar BST - ID
		indiceBST *auxBST = (indiceBST*)malloc(sizeof(indiceBST));
		auxBST->chave = p->id;
		auxBST->indice = posicaoNovoRegistro;
		tab->indiceArvoreBST = inserirBST(auxBST, tab->indiceArvoreBST);

		// Adicionar AVL - Fabricante
		indiceAVL *auxAVL = (indiceAVL*)malloc(sizeof(indiceAVL));
		strcpy(auxAVL->chave, p->fabricante);
		auxAVL->indice = posicaoNovoRegistro;
		tab->indiceArvoreAVL = inserirAVL(auxAVL, tab->indiceArvoreAVL);

		// Adicionar RB - Validade
		indiceRB *auxRB = (indiceRB*)malloc(sizeof(indiceRB));
		auxRB->chave = p->validade;
		auxRB->indice = posicaoNovoRegistro;
		inserirRB(auxRB, &tab->indiceArvoreRB);

		// Escreve os dados do sorvete no arquivo de dados
		fwrite(p, sizeof(sorvete), 1, tab->arquivo);	

		// Escreve o tamanho da string do fabricante e o próprio fabricante no arquivo
		int tamanho = strlen(p->fabricante) + 1;
		fwrite(&tamanho, sizeof(tamanho), 1, tab->arquivo);
		fwrite(p->fabricante, sizeof(char), tamanho, tab->arquivo);
	}
}

// Função para remover um sorvete da tabela
void removerSorvete (tabela *tab, int id) {
	// Procura o sorvete na árvore binária de busca usando o ID
	sorvete *p = procurarSorveteBST(tab, id);

	// Verifica se o sorvete foi encontrado
	if (p == NULL) {
		return;
	} else {
		// Remove o sorvete das árvores
		tab->indiceArvoreBST = removerBST(p->id, tab->indiceArvoreBST);
		tab->indiceArvoreAVL = removerAVL(tab->indiceArvoreAVL, p->fabricante);
		removerRB(&tab->indiceArvoreRB, p->validade);
	}
}

// Função para ler os dados de um novo sorvete
sorvete *lerDados() {
	// Aloca memória para uma nova estrutura de sorvete
	sorvete *novo = (sorvete*) malloc(sizeof(sorvete));
	
	// Aloca memória para um buffer de caracteres para entrada do fabricante
	char *buffer = (char*) malloc(256*sizeof(char));
	
	// Limpa a tela do console
	system("clear");

	// Imprime o cabeçalho da Sorveteria
	printf("|=============================|\n");
	printf("|        Sorveteria BCC       |\n");
	printf("|=============================|\n");
	
	// Limpa o buffer do teclado
	getchar();

	// Solicita e lê o fabricante do sorvete
	printf("| Fabricante: ");
	fgets(buffer, 255,  stdin);
	retirarEnter(buffer);

	// Aloca memória para armazenar o fabricante e copia o conteúdo do buffer para a estrutura
	novo->fabricante = (char*) malloc((strlen(buffer)+1) * sizeof(char));
	strcpy(novo->fabricante, buffer);
	
	// Solicita e lê o sabor do sorvete
	printf("| Sabor: ");
	fgets(novo->sabor, 20,  stdin);
	retirarEnter(novo->sabor);
	
	// Solicita e lê o preço do sorvete
	printf("| Preco: ");
	scanf("%f", &novo->preco);

	// Solicita e lê a validade do sorvete
	printf("| Validade (Ex.: 2025): ");
	scanf("%d", &novo->validade);

	// Solicita e lê o ID do sorvete
	printf("| ID: ");
	scanf("%d", &novo->id);
	printf("|=============================|\n");
	
	// Libera a memória alocada para o buffer
	free(buffer);

	// Retorna o ponteiro para a nova estrutura de sorvete
	return novo;
}

// Função para retirar os espaços
void retirarEnter (char *string) {
	string[strlen(string) -1] = '\0';
}

// Função para procurar um sorvete na árvore de busca binária (BST) com base na chave
sorvete *procurarSorveteBST (tabela *tab, int chave) {
	// Verifica se o arquivo de dados associado à tabela está aberto
    if (tab->arquivo != NULL) {
		// Inicializa um ponteiro para um nó da árvore BST
		noBST *temp;
		temp = tab->indiceArvoreBST;

		// Itera sobre a árvore BST até encontrar o nó com a chave desejada
		while (temp!=NULL) {
			if (temp->dado->chave == chave) {
				// Posiciona o cursor no arquivo de dados na posição do registro do sorvete
				fseek(tab->arquivo, temp->dado->indice, SEEK_SET);

				// Aloca memória para uma nova estrutura de sorvete
				sorvete *encontrado = (sorvete*) malloc(sizeof(sorvete));

				// Lê os dados do sorvete do arquivo de dados
				fread(encontrado, sizeof(sorvete), 1, tab->arquivo);
				
				// Lê o tamanho da string do fabricante e aloca memória para armazená-la
				int tamanho;
				fread(&tamanho, sizeof(int),1, tab->arquivo);
				encontrado->fabricante = (char*)malloc(tamanho*sizeof(char));

				// Lê o fabricante do arquivo de dados e armazena na estrutura do sorvete
				fread(encontrado->fabricante, sizeof(char),tamanho, tab->arquivo);
				
				// Imprime os dados do sorvete encontrado
				printf("|==================================================================================|\n");
				printf("| ID: %d, Sabor: %s, Fabricante: %s, Preco: %.2f, Validade: %d\n", encontrado->id, encontrado->sabor, encontrado->fabricante, encontrado->preco, encontrado->validade);
				printf("|==================================================================================|\n");

				// Retorna o ponteiro para o sorvete encontrado
				return encontrado;
			} else {
				// Se a chave do nó atual for menor que a chave desejada, avança para o nó direito
				if (chave > temp->dado->chave) {
					temp = temp->direita;
				} else {
					temp = temp->esquerda;
				}           
    		}
    	}
    }

	// Se o sorvete não for encontrado, imprime uma mensagem de aviso e retorna NULL
    printf("|=============================|\n");
	printf("|      ID Nao Encontrado      |\n");
	printf("|=============================|\n\n");
    return NULL;
}

// Função para imprimir um sorvete da árvore de busca binária (BST)
void imprimirBST (arvoreBST raiz, tabela *tab) {
	// Aloca memória para uma estrutura de sorvete temporária
	sorvete *temp = (sorvete *) malloc (sizeof(sorvete));

	printf("|============================================================================|\n");
	// Verifica se a alocação de memória foi bem-sucedida
	if (!temp) {
		printf("Erro: falha ao alocar memoria.\n");
		return;
	}

	// Posiciona o cursor no arquivo de dados na posição do registro associado à raiz atual
	if (fseek(tab->arquivo, raiz->dado->indice, SEEK_SET) != 0) {
		printf("Erro: falha ao posicionar o ponteiro do arquivo.\n");
		return;
	}

	// Lê os dados do sorvete do arquivo de dados
	if (fread(temp, sizeof(sorvete), 1, tab->arquivo) != 1) {
		printf("Erro: falha ao ler dados do arquivo.\n");
		return;
	}

	// Lê o tamanho da string do fabricante e aloca memória para armazená-la
	int tamanho;
	fread(&tamanho, sizeof(int), 1, tab->arquivo);
	temp->fabricante = (char*)malloc(tamanho);
	fread(temp->fabricante, sizeof(char), tamanho, tab->arquivo);
	
	// Imprime os dados do sorvete associado à raiz atual
	printf("| ID: %d, Sabor: %s, Fabricante: %s, Preco: %.2f, Validade: %d\n", raiz->dado->chave,temp->sabor, temp->fabricante, temp->preco, temp->validade);
	
	// Libera a memória alocada para a estrutura de sorvete temporária
	free(temp);
	printf("|============================================================================|\n");
}

// Função recursiva para percorrer e imprimir os elementos de uma árvore de busca binária (BST) em ordem
void inOrderBST (arvoreBST raiz, tabela *tab) {
	// Verifica se a árvore BST está vazia
	if (tab->indiceArvoreBST == NULL) {
		printf("|=========================|\n");
		printf("|       Arvore Vazia      |\n");
		printf("|=========================|\n");
	
		return;
	}

	// Percorre a árvore BST em ordem
	if (raiz != NULL) {
		// Visita o filho esquerdo
		inOrderBST(raiz->esquerda, tab);

		// Imprime os dados do nó atual
		imprimirBST(raiz, tab);

		// Visita o filho direito
		inOrderBST(raiz->direita, tab);
	}
}

// Função para procurar um sorvete na árvore de busca binária (BST) com base na chave
sorvete *procurarSorveteRB (tabela *tab, int chave) {
	// Verifica se o arquivo de dados associado à tabela está aberto
    if (tab->arquivo != NULL) {
		// Inicializa um ponteiro para um nó da árvore RB
		noRB *temp;
		temp = tab->indiceArvoreRB;

		// Itera sobre a árvore RB até encontrar o nó com a chave desejada
		while (temp!=NULL) {
			if (temp->dado->chave == chave) {
				// Posiciona o cursor no arquivo de dados na posição do registro do sorvete
				fseek(tab->arquivo, temp->dado->indice, SEEK_SET);

				// Aloca memória para uma nova estrutura de sorvete
				sorvete *encontrado = (sorvete*) malloc(sizeof(sorvete));

				// Lê os dados do sorvete do arquivo de dados
				fread(encontrado, sizeof(sorvete), 1, tab->arquivo);
				
				// Lê o tamanho da string do fabricante e aloca memória para armazená-la
				int tamanho;
				fread(&tamanho, sizeof(int), 1, tab->arquivo);
				encontrado->fabricante = (char*)malloc(tamanho*sizeof(char));

				// Lê o fabricante do arquivo de dados e armazena na estrutura do sorvete
				fread(encontrado->fabricante, sizeof(char), tamanho, tab->arquivo);
				
				// Imprime os dados do sorvete encontrado
				printf("|==================================================================================|\n");
				printf("| ID: %d, Sabor: %s, Fabricante: %s, Preco: %.2f, Validade: %d\n", encontrado->id, encontrado->sabor, encontrado->fabricante, encontrado->preco, encontrado->validade);
				printf("|==================================================================================|\n");
				
				// Retorna o ponteiro para o sorvete encontrado
				return encontrado;
			} else {
				// Se a chave do nó atual for menor que a chave desejada, avança para o nó direito
				if (chave > temp->dado->chave) {
					temp = temp->direita;
				} else {
					temp = temp->esquerda;
				}                
	    	}
	    }
    }

	// Se o sorvete não for encontrado, imprime uma mensagem de aviso e retorna NULL
   	printf("|=========================|\n");
	printf("| Validade Nao Encontrada |\n");
	printf("|=========================|\n");
    return NULL;
}

// Função responsável por buscar um nó com uma chave específica na árvore RB
void buscarRB (int chave, arvoreRB raiz, tabela *tab) {
    // Verifica se a raiz atual da árvore RB não é nula
	if (raiz != NULL) {
		// Busca recursivamente na subárvore esquerda
        buscarRB(chave,raiz->esquerda, tab);

		// Verifica se a chave do nó atual é igual à chave procurada
        if (chave == raiz->dado->chave) {
			// Se a chave for encontrada, imprime os dados do nó
            imprimirRB(raiz, tab);
        }

		// Busca recursivamente na subárvore direita
        buscarRB(chave,raiz->direita, tab);
    }

	// Se a raiz for nula e a árvore RB estiver vazia
    else if (tab->indiceArvoreRB == NULL) {
		// Imprime uma mensagem informando que a validade não foi encontrada
    	printf("|=========================|\n");
		printf("| Validade Nao Encontrada |\n");
		printf("|=========================|\n");
	    return;
    }
}

// Função para imprimir um sorvete da árvore RB
void imprimirRB (arvoreRB raiz, tabela *tab) {
	// Aloca memória para uma estrutura de sorvete temporária
	sorvete *temp = (sorvete*) malloc(sizeof(sorvete));
	printf("|==================================================================================|\n");
	
	// Verifica se a alocação de memória foi bem-sucedida
	if (!temp) {
		printf("Erro: falha ao alocar memoria.\n");
		return;
	}

	// Posiciona o cursor no arquivo de dados na posição do registro associado ao nó atual da árvore RB
	if (fseek(tab->arquivo, raiz->dado->indice, SEEK_SET) != 0) {
		printf("Erro: falha ao posicionar o ponteiro do arquivo.\n");
		return;
	}

	// Lê os dados do sorvete do arquivo de dados
	if (fread(temp, sizeof(sorvete), 1, tab->arquivo) != 1) {
		printf("Erro: falha ao ler dados do arquivo.\n");
		return;
	}

	// Lê o tamanho da string do fabricante e aloca memória para armazená-la
	int tamanho;
	fread(&tamanho, sizeof(int), 1, tab->arquivo);
	temp->fabricante = (char*)malloc(tamanho);
	fread(temp->fabricante, sizeof(char),tamanho, tab->arquivo);
	
	// Imprime os dados do sorvete associado ao nó atual da árvore RB
	printf("| Validade: %d, Sabor: %s, Fabricante: %s, Preco: %.2f, ID: %d\n", raiz->dado->chave, temp->sabor, temp->fabricante, temp->preco, temp->id);
	
	// Libera a memória alocada para a estrutura de sorvete temporária
	free(temp);
	printf("|==================================================================================|\n");
}

// Função recursiva para percorrer e imprimir os elementos de uma árvore RB em ordem
void inOrderRB (arvoreRB raiz, tabela *tab) {
	// Verifica se a árvore RB está vazia
	if (tab->indiceArvoreRB == NULL) {
		// Se estiver vazia, imprime uma mensagem informando que a árvore está vazia e retorna
		printf("|=========================|\n");
		printf("|       Arvore Vazia      |\n");
		printf("|=========================|\n");
		return;
	}

	// Se a árvore não estiver vazia e a raiz atual não for nula
	else if (raiz != NULL) {
		// Percorre a subárvore esquerda em ordem
		inOrderRB(raiz->esquerda, tab);

		// Imprime os dados do nó atual
		imprimirRB(raiz, tab);

		// Percorre a subárvore direita em ordem
		inOrderRB(raiz->direita, tab);
	}
}

// Função para procurar um sorvete na árvore AVL com base na chave
sorvete* procurarSorveteAVL (tabela *tab, char *chave) {
	// Verifica se o arquivo de dados associado à tabela está aberto
    if (tab->arquivo != NULL) {
		// Inicializa um ponteiro para um nó da árvore AVL
		noAVL *temp;
		temp = tab->indiceArvoreAVL;

		// Itera sobre a árvore AVL até encontrar o nó com a chave desejada
		while (temp!=NULL) {
			// Compara as chaves para encontrar o nó desejado
			if (strcmp(temp->dado->chave,chave) == 0) {
				// Posiciona o cursor no arquivo de dados na posição do registro do sorvete
				fseek(tab->arquivo, temp->dado->indice, SEEK_SET);

				// Aloca memória para uma nova estrutura de sorvete
				sorvete *encontrado = (sorvete*) malloc(sizeof(sorvete));
				
				// Lê os dados do sorvete do arquivo de dados
				fread(encontrado, sizeof(sorvete), 1, tab->arquivo);

				// Lê o tamanho da string do fabricante e aloca memória para armazená-la
				int tamanho;
				fread(&tamanho, sizeof(int), 1, tab->arquivo);
				encontrado->fabricante = (char*)malloc(tamanho*sizeof(char));

				// Lê o fabricante do arquivo de dados e armazena na estrutura do sorvete
				fread(encontrado->fabricante, sizeof(char), tamanho, tab->arquivo);

				// Imprime os dados do sorvete encontrado
				printf("|==================================================================================|\n");
				printf("| ID: %d, Sabor: %s, Fabricante: %s, Preco: %.2f, Validade: %d\n", encontrado->id, encontrado->sabor, encontrado->fabricante, encontrado->preco, encontrado->validade);
				printf("|==================================================================================|\n");
				
				// Retorna o ponteiro para o sorvete encontrado
				return encontrado;
			} else {
				// Se a chave do nó atual for menor que a chave desejada, avança para o nó direito
				if (strcmp(chave, temp->dado->chave) > 0) {
					temp = temp->direita;
				} else {
					temp = temp->esquerda;
				}
	        }
    	}
    }

	// Se o fabricante não for encontrado, imprime uma mensagem de aviso e retorna NULL
    printf("|=================================|\n");
	printf("|    Fabricante Nao Encontrado    |\n");
	printf("|=================================|\n");
    return NULL;
}

// Função para imprimir um sorvete da árvore AVL
void imprimirAVL (arvoreAVL raiz, tabela *tab) {
	// Aloca memória para uma estrutura de sorvete temporária
	sorvete *temp = (sorvete*) malloc(sizeof(sorvete));
	printf("|============================================================================|\n");

	// Verifica se a alocação de memória foi bem-sucedida
	if (!temp) {
		printf("Erro: falha ao alocar memoria.\n");
		return;
	}

	// Posiciona o cursor no arquivo de dados na posição do registro associado ao nó atual da árvore AVL
	if (fseek(tab->arquivo, raiz->dado->indice, SEEK_SET) != 0) {
		printf("Erro: falha ao posicionar o ponteiro do arquivo.\n");
		return;
	}

	// Lê os dados do sorvete do arquivo de dados
	if (fread(temp, sizeof(sorvete), 1, tab->arquivo) != 1) {
		printf("Erro: falha ao ler dados do arquivo.\n");
		return;
	}

	// Imprime os dados do sorvete associado ao nó atual da árvore AVL
	printf("| Fabricante: %s, Sabor: %s, Preco: %.2f, Validade: %d, ID: %d\n", raiz->dado->chave, temp->sabor, temp->preco, temp->validade, temp->id);
	
	// Libera a memória alocada para a estrutura de sorvete temporária
	free(temp);
	printf("|============================================================================|\n");
}

// Função recursiva para percorrer e imprimir os elementos de uma árvore AVL em ordem
void inOrderAVL (arvoreAVL raiz, tabela *tab) {
	// Verifica se a árvore AVL está vazia
	if (tab->indiceArvoreAVL == NULL) {
		// Se estiver vazia, imprime uma mensagem informando que a árvore está vazia e retorna
		printf("|=========================|\n");
		printf("|       Arvore Vazia      |\n");
		printf("|=========================|\n");
		return;
	}

	// Se a árvore não estiver vazia e a raiz atual não for nula
	else if (raiz != NULL) {
		// Percorre a subárvore esquerda em ordem
		inOrderAVL(raiz->esquerda, tab);

		// Imprime os dados do nó atual
		imprimirAVL(raiz, tab);
		
		// Percorre a subárvore esquerda em ordem
		inOrderAVL(raiz->direita, tab);
	}
}

// Função para salvar o arquivo da árvore de busca binária
void salvarArquivoBST (char *sabor, arvoreBST arvore) {
	// Declaração de um ponteiro para arquivo
	FILE *arq;

	// Abre o arquivo especificado em modo de escrita binária
	arq = fopen(sabor, "wb");

	// Verifica se o arquivo foi aberto com sucesso e não está vazio
	if (arq != NULL) {
		// Chama a função auxiliar para salvar a árvore no arquivo
		salvarAuxiliarBST(arvore, arq);

		// Fecha o arquivo após a operação de escrita
		fclose(arq);
	}
}

// Função para salvar a árvore auxiliar da BST
void salvarAuxiliarBST (arvoreBST raiz, FILE *arq) {
    // Verifica se a raiz da árvore não é nula
    if (raiz != NULL) {
        // Escreve o conteúdo do nó atual no arquivo
        fwrite(raiz->dado, sizeof(indiceBST), 1, arq);
        
        // Chama recursivamente a função para salvar os nós da subárvore esquerda
        salvarAuxiliarBST(raiz->esquerda, arq);
        
        // Chama recursivamente a função para salvar os nós da subárvore direita
        salvarAuxiliarBST(raiz->direita, arq);
    }
}

// Função para carregar o arquivo com itens da árvore de busca binária
arvoreBST carregarArquivoBST (char *sabor, arvoreBST arvore) {
	// Declaração de um ponteiro para arquivo
	FILE *arq;

	// Abre o arquivo especificado em modo de escrita binária
	arq = fopen(sabor, "rb");
	indiceBST *temp;

	// Verifica se o arquivo foi aberto com sucesso e não está vazio
	if (arq != NULL) {
		// Aloca memória para um nó temporário
		temp = (indiceBST*) malloc(sizeof(indiceBST));

		// Enquanto conseguir ler um nó do arquivo
		while (fread(temp, sizeof(indiceBST), 1, arq)) {
			// Insere o nó temporário na árvore
			arvore = inserirBST(temp, arvore);			

			// Aloca memória para o próximo nó
			temp = (indiceBST*) malloc(sizeof(indiceBST));
		}

		// Fecha o arquivo após a leitura
		fclose(arq);
	}

	// Retorna a árvore atualizada
	return arvore;
}

// Função para salvar o arquivo da árvore AVL
void salvarArquivoAVL (char *sabor, arvoreAVL arvore) {
	// Declaração de um ponteiro para arquivo
	FILE *arq;

	// Abre o arquivo especificado em modo de escrita binária
	arq = fopen(sabor, "wb");

	// Verifica se o arquivo foi aberto com sucesso e não está vazio
	if (arq != NULL) {
		// Chama a função auxiliar para salvar a árvore no arquivo
		salvarAuxiliarAVL(arvore, arq);

		// Fecha o arquivo após a operação de escrita
		fclose(arq);
	}
}

// Função para salvar a árvore auxiliar da AVL
void salvarAuxiliarAVL (arvoreAVL raiz, FILE *arq) {
	// Verifica se a raiz da árvore não é nula
	if (raiz != NULL) {	
		// Escreve o conteúdo do nó atual no arquivo
		fwrite(raiz->dado, sizeof(indiceAVL), 1, arq);

		// Chama recursivamente a função para salvar os nós da subárvore esquerda
		salvarAuxiliarAVL(raiz->esquerda, arq);

		// Chama recursivamente a função para salvar os nós da subárvore direita
		salvarAuxiliarAVL(raiz->direita, arq);
	}
}

// Função para carregar o arquivo com itens da árvore AVL
arvoreAVL carregarArquivoAVL (char *sabor, arvoreAVL arvore) {
	// Declaração de um ponteiro para arquivo
	FILE *arq;

	// Abre o arquivo especificado em modo de escrita binária
	arq = fopen(sabor, "rb");
	indiceAVL *temp;

	// Verifica se o arquivo foi aberto com sucesso e não está vazio
	if (arq != NULL) {
		// Aloca memória para um nó temporário
		temp = (indiceAVL*) malloc(sizeof(indiceAVL));

		// Enquanto conseguir ler um nó do arquivo
		while(fread(temp, sizeof(indiceAVL), 1, arq)) {
			// Insere o nó temporário na árvore
			arvore = inserirAVL(temp, arvore);			

			// Aloca memória para o próximo nó
			temp = (indiceAVL*) malloc(sizeof(indiceAVL));
		}

		// Fecha o arquivo após a leitura
		fclose(arq);
	}

	// Retorna a árvore atualizada
	return arvore;
}

// Função para salvar o arquivo da árvore RB
void salvarArquivoRB (char *sabor, arvoreRB arvore) {
	// Declaração de um ponteiro para arquivo
	FILE *arq;

	// Abre o arquivo especificado em modo de escrita binária
	arq = fopen(sabor, "wb");

	// Verifica se o arquivo foi aberto com sucesso e não está vazio
	if (arq != NULL) {
		// Chama a função auxiliar para salvar a árvore no arquivo
		salvarAuxiliarRB(arvore, arq);

		// Fecha o arquivo após a operação de escrita
		fclose(arq);
	}
}

// Função para salvar a árvore auxiliar da RB
void salvarAuxiliarRB (arvoreRB raiz, FILE *arq) {
	// Verifica se a raiz da árvore não é nula
	if (raiz != NULL) {		
		// Escreve o conteúdo do nó atual no arquivo
		fwrite(raiz->dado, sizeof(indiceRB), 1, arq);

		// Chama recursivamente a função para salvar os nós da subárvore esquerda
		salvarAuxiliarRB(raiz->esquerda, arq);

		// Chama recursivamente a função para salvar os nós da subárvore direita
		salvarAuxiliarRB(raiz->direita, arq);
	}
}

// Função para carregar o arquivo com itens da árvore RB
arvoreRB carregarArquivoRB (char *sabor, arvoreRB arvore) {
	// Declaração de um ponteiro para arquivo
	FILE *arq;

	// Abre o arquivo especificado em modo de escrita binária
	arq = fopen(sabor, "rb");
	indiceRB *temp;

	// Verifica se o arquivo foi aberto com sucesso e não está vazio
	if (arq != NULL) {
		// Aloca memória para um nó temporário
		temp = (indiceRB*) malloc(sizeof(indiceRB));

		// Enquanto conseguir ler um nó do arquivo
		while (fread(temp, sizeof(indiceRB), 1, arq)) {
			// Insere o nó temporário na árvore
			inserirRB(temp, &arvore);			

			// Aloca memória para o próximo nó
			temp = (indiceRB*) malloc(sizeof(indiceRB));
		}

		// Fecha o arquivo após a leitura
		fclose(arq);
	}

	// Retorna a árvore atualizada
	return arvore;
}