#ifndef BST_H
#define BST_H

// Construtor do índice da árvore BST
typedef struct indiceBST {
	int chave;
	int indice;
} indiceBST;

// Construtor dos nós da árvore BST
typedef struct noBST {
    indiceBST *dado;
    struct noBST *esquerda;
    struct noBST *direita;
} noBST;

// Criando ponteiro para a estrutura do nó da árvore BST
typedef noBST *arvoreBST;

// Chamada das funções de manipulação da árvore BST
void inicializarBST (arvoreBST *raiz);
arvoreBST inserirBST (indiceBST *valor, arvoreBST raiz);
int alturaBST (arvoreBST raiz);
int maiorBST (int a, int b);
indiceBST *maiorElementoBST (arvoreBST raiz);
arvoreBST removerBST (int valor, arvoreBST raiz);

#endif