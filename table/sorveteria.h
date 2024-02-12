#ifndef SORVETERIA_H
#define SORVETERIA_H

// Chamada dos arquivos das arvores
#include "../bst/bst.c"
#include "../bst/bst.h"
#include "../avl/avl.c"
#include "../avl/avl.h"
#include "../rb/rb.c"
#include "../rb/rb.h"

// Definindo tamanho máximo
#define TAM_MAX 80

// Construtor dos sorvetes
typedef struct sorvete {
    int id;
	char sabor[TAM_MAX];
	char *fabricante;
	float preco;
	int validade;
} sorvete;

// Construtor da tabela
typedef struct tabela {
	FILE *arquivo;
	arvoreBST indiceArvoreBST;
	arvoreAVL indiceArvoreAVL;
	arvoreRB indiceArvoreRB;
} tabela;

// Chamada da função de inicialização da tabela
int inicializarTabela (tabela *tab);

// Chamada da função de finalizanação da tabela
void finalizarTabela (tabela *tab);

// Chamada da função de adicionar um novo sorvete
void adicionarSorvete (tabela *tab, sorvete *p);

// Chamada da função de remover sorvete da tabela
void removerSorvete (tabela *tab, int id);

// Chamada da função de ler as informações dos sorvetes
sorvete *lerDados();

// Chamada da função de retirar os espaços
void retirarEnter (char *string);

// Chamada das funções de busca dentro das árvores
sorvete *procurarSorveteBST (tabela *tab, int chave);
sorvete *procurarSorveteAVL (tabela *tab, char *chave); 
sorvete *procurarSorveteRB (tabela *tab, int chave); 
void buscarRB (int chave, arvoreRB raiz, tabela *tab);

// Chamada da funções de impressão das árvores
void imprimirBST (arvoreBST raiz, tabela *tab);
void imprimirAVL (arvoreAVL raiz, tabela *tab);
void imprimirRB (arvoreRB raiz, tabela *tab);

// Chamada das funções de impressão das árvore em ordem
void inOrderBST (arvoreBST raiz, tabela *tab);
void inOrderAVL (arvoreAVL raiz, tabela *tab);
void inOrderRB (arvoreRB raiz, tabela *tab);

// Chamada das funções de salvar o arquivo nas árvores
void salvarArquivoBST (char *sabor, arvoreBST arvore);
void salvarArquivoAVL (char *sabor, arvoreAVL arvore);
void salvarArquivoRB (char *sabor, arvoreRB arvore);

// Chamada das funções para salvar o auxiliar da árvore
void salvarAuxiliarBST (arvoreBST raiz, FILE *arq);
void salvarAuxiliarAVL (arvoreAVL raiz, FILE *arq);
void salvarAuxiliarRB (arvoreRB raiz, FILE *arq);

// Chamada das funções de carregamento dos itens presentes nos arquivos
arvoreBST carregarArquivoBST (char *sabor, arvoreBST arvore);
arvoreAVL carregarArquivoAVL (char *sabor, arvoreAVL arvore);
arvoreRB carregarArquivoRB (char *sabor, arvoreRB arvore);

#endif