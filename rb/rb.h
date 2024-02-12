#ifndef RB_H
#define RB_H

// Enumeração do chamado das cores
enum Cor {
    VERMELHO,
    PRETO
};

// Construtor do índice da árvore RB
typedef struct indiceRB {
	int chave;
	int indice;
} indiceRB;

// Construtor dos nós da árvore RB
typedef struct noRB {
    enum Cor cor;
    int altura;
    indiceRB *dado;
    struct noRB *esquerda;
    struct noRB *direita;
    struct noRB *pai;
} noRB;

// Criando ponteiro para a estrutura do nó da árvore BST
typedef noRB* arvoreRB;

// Chamada das funções de manipulação da árvore RB
void inicializarRB (arvoreRB *raiz);
arvoreRB criarNo (indiceRB *info);
int Cor (arvoreRB elemento);
int ehRaiz (arvoreRB elemento);
int ehEsquerdo (arvoreRB elemento);
arvoreRB irmao (arvoreRB elemento);
arvoreRB tio (arvoreRB elemento);
void rotacaoDireitaRB (arvoreRB *raiz, arvoreRB no, int simples);
void rotacaoEsquerdaRB (arvoreRB *raiz, arvoreRB no, int simples);
void rotacaoDuplaEsquerdaRB (arvoreRB* raiz, arvoreRB no);
void rotacaoDuplaDireitaRB (arvoreRB* raiz, arvoreRB no);
void ajustar (arvoreRB* raiz, arvoreRB no);
void inserirRB (indiceRB *valor, arvoreRB* raiz);
void ajustarRemocao (arvoreRB* raiz, arvoreRB filho, arvoreRB pai);
arvoreRB buscar (arvoreRB raiz, int chave);
void removerRB (arvoreRB* raiz, int chave);

#endif