#include "bst.h"
#include <stdlib.h>
#include <stdio.h>

// Função para inserir um valor na árvore
arvoreBST inserirBST (indiceBST *valor, arvoreBST raiz) {
    // Verifica se a raiz é nula (caso base)
    if (raiz == NULL) {
        // Cria um novo nó se a árvore estiver vazia
        arvoreBST nova = (arvoreBST)malloc(sizeof(struct noBST));
        nova->dado = valor;
        nova->esquerda = NULL;
        nova->direita = NULL;
        return nova;
    } else {
        // Insere o valor na subárvore esquerda ou direita, conforme necessário
        if (valor->chave > raiz->dado->chave) {
            raiz->direita = inserirBST(valor, raiz->direita);
        } else {
            raiz->esquerda = inserirBST(valor, raiz->esquerda);
        }
        return raiz;
    }
}

// Função para calcular a altura de uma árvore
int alturaBST (arvoreBST raiz) {
    // Verifica se a raiz é nula (caso base)
    if (raiz == NULL) {
        return 0;
    } else {
        // Calcula a altura da subárvore esquerda e da subárvore direita
        int alturaEsquerda = alturaBST(raiz->esquerda);
        int alturaDireita = alturaBST(raiz->direita);

        // Compara as alturas das subárvores e retorna a maior altura somada a 1
        if (alturaEsquerda > alturaDireita) {
            return alturaEsquerda + 1;
        } else {
            return alturaDireita + 1;
        }
    }
}

// Função para encontrar o maior entre dois números inteiros
int maiorBST (int a, int b) {
    // Verifica se 'a' é maior que 'b'
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

// Função para encontrar o maior elemento em uma árvore binária de busca, retorna um ponteiro para o índice do nó contendo o maior elemento
indiceBST *maiorElementoBST (arvoreBST raiz) {
    // Verifica se a raiz é nula (caso base)
    if (raiz == NULL) {
        return NULL;
    }

    // Se o nó à direita da raiz for nulo, significa que este é o maior elemento
    if (raiz->direita == NULL) {
        return raiz->dado;
    } else {
        return maiorElementoBST(raiz->direita);
    }
}

// Função para remover um nó da árvore BST
arvoreBST removerBST (int valor, arvoreBST raiz) {
    // Verifica se a raiz é nula (caso base)
    if (raiz == NULL) {
        return NULL; 
    } else if (raiz->dado->chave == valor) {
        // Se o valor a ser removido for encontrado na raiz
        if (raiz->esquerda == NULL) {
            // Retorna a subárvore direita, substituindo a raiz atual
            return raiz->direita;
        }
        if (raiz->direita == NULL) {
            // Retorna a subárvore esquerda, substituindo a raiz atual
            return raiz->esquerda;
        }
        
        // Se a raiz tem ambos os filhos, encontrar o maior elemento na subárvore esquerda
        raiz->dado = maiorElementoBST(raiz->esquerda);
        
        // Remove o nó que continha o maior elemento da subárvore esquerda
        raiz->esquerda = removerBST(raiz->dado->chave, raiz->esquerda);
        return raiz;
    } else if (valor > raiz->dado->chave) {
        // Se o valor a ser removido for maior do que o valor na raiz, a remoção é feita na subárvore direita
        raiz->direita = removerBST(valor, raiz->direita);
    } else {
        // Se o valor a ser removido for menor do que o valor na raiz, a remoção é feita na subárvore esquerda
        raiz->esquerda = removerBST(valor, raiz->esquerda);
    }
    return raiz;
}