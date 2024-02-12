#ifndef AVL_H
#define AVL_H

// Construtor do índice da árvore AVL
typedef struct indiceAVL {
	char chave[80];
	int indice;
} indiceAVL;

// Construtor dos nós da árvore AVL
typedef struct noAVL {
    indiceAVL *dado;
    int valor;
    int altura;
    struct noAVL* esquerda;
    struct noAVL* direita;
} noAVL;

// Criando ponteiro para a estrutura do nó da árvore AVL
typedef noAVL *arvoreAVL;

// Chamada das funções de manipulação da árvore AVL
void inicializarAVL (arvoreAVL *raiz);
int alturaAVL (arvoreAVL no);
arvoreAVL maiorElementoAVL (arvoreAVL raiz);
int fatorBalanceamento (arvoreAVL no);
int atualizarAltura (arvoreAVL no);
arvoreAVL rotacaoEsquerdaAVL (arvoreAVL raiz);
arvoreAVL rotacaoDireitaAVL (arvoreAVL raiz);
arvoreAVL rotacaoDuplaEsquerdaAVL (arvoreAVL raiz);
arvoreAVL rotacaoDuplaDireitaAVL (arvoreAVL raiz);
arvoreAVL balancear (arvoreAVL raiz);
arvoreAVL inserirAVL (indiceAVL *valor, arvoreAVL raiz);
arvoreAVL removerAVL (arvoreAVL raiz, char* valor);

#endif