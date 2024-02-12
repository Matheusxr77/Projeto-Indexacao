#include "avl.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Função para calcular a altura de um nó
int alturaAVL (arvoreAVL no) {
    if (no == NULL) {
        return -1;
    } else {
        return no->altura;
    }
}

// Função para encontrar o maior elemento na árvore AVL
arvoreAVL maiorElementoAVL (arvoreAVL raiz) {
    // Cria um nó auxiliar e o inicializa com a raiz
    arvoreAVL aux = raiz;

    // Percorre a árvore pela direita até encontrar o último nó
    while (aux != NULL) {
        aux = aux->direita;
    }
    return aux;
}

// Função para calcular o fator de balanceamento de um nó
int fatorBalanceamento (arvoreAVL no) {
    if (no != NULL) {
        return (alturaAVL(no->esquerda) - alturaAVL(no->direita));
    } else {
        return 0;
    }
}

// Função para atualizar a altura de um nó
int atualizarAltura (arvoreAVL no) {
    if (no != NULL) {
        int alturaEsquerda, alturaDireita;

        // Calcula a altura das subárvores esquerda e direita
        alturaEsquerda = alturaAVL(no->esquerda);
        alturaDireita = alturaAVL(no->direita);

        // Atualiza a altura do nó como a altura máxima entre a subárvore à esquerda e à direita, mais 1
        if (alturaEsquerda > alturaDireita) {
            no->altura = alturaEsquerda + 1;
        } else {
            no->altura = alturaDireita + 1;
        }
    }
}

// Função para realizar a rotação simples à esquerda
arvoreAVL rotacaoEsquerdaAVL (arvoreAVL raiz) {
    arvoreAVL aux, temp;
    aux = raiz->direita;
    temp = aux->esquerda;

    // Realiza a rotação
    aux->esquerda = raiz;
    raiz->direita = temp;

    // Atualiza as alturas dos nós afetados
    atualizarAltura(raiz);
    atualizarAltura(aux);
    return aux;
}

// Função para realizar a rotação simples à direita
arvoreAVL rotacaoDireitaAVL (arvoreAVL raiz) {
    arvoreAVL aux, temp;
    aux = raiz->esquerda;
    temp = aux->direita;

    // Realiza a rotação
    aux->direita = raiz;
    raiz->esquerda = temp;

    // Atualiza as alturas dos nós afetados
    atualizarAltura(raiz);
    atualizarAltura(aux);
    return aux;
}

// Função para realizar uma rotação dupla à esquerda (direita-esquerda)
arvoreAVL rotacaoDuplaEsquerdaAVL (arvoreAVL raiz) {
    raiz->direita = rotacaoDireitaAVL(raiz->direita);
    return rotacaoEsquerdaAVL(raiz);
}

// Função para realizar uma rotação dupla à direita (esquerda-direita)
arvoreAVL rotacaoDuplaDireitaAVL (arvoreAVL raiz) {
    raiz->esquerda = rotacaoEsquerdaAVL(raiz->esquerda);
    return rotacaoDireitaAVL(raiz);
}

// Função para balancear a árvore AVL
arvoreAVL balancear (arvoreAVL raiz) {
    // Atualizar a altura do nó atual
    atualizarAltura(raiz);

    // Calcula o fator de balanceamento deste nó para verificar se é necessário reequilibrar
    int balance = fatorBalanceamento(raiz);

    // Realiza as rotações necessárias para reequilibrar a árvore
    if (balance > 1) {
        if (fatorBalanceamento(raiz->esquerda) >= 0) {
            // Rotação Simples à Direita
            return rotacaoDireitaAVL(raiz);
        } else {
            // Rotação Dupla à Direita (Esquerda-Direita)
            return rotacaoDuplaDireitaAVL(raiz);
        }
    }

    if (balance < -1) {
        if (fatorBalanceamento(raiz->direita) <= 0) {
            // Rotação Simples à Esquerda
            return rotacaoEsquerdaAVL(raiz);
        } else {
            // Rotação Dupla à Esquerda (Direita-Esquerda)
            return rotacaoDuplaEsquerdaAVL(raiz);
        }
    }
    // Se o fator de balanceamento estiver fora do intervalo, a árvore já está balanceada
    return raiz;
}

// Função para inserir um valor na árvore AVL
arvoreAVL inserirAVL (indiceAVL *valor, arvoreAVL raiz) {
    if (raiz == NULL) {
        // Cria um novo nó se a árvore estiver vazia
        arvoreAVL novo = (arvoreAVL)malloc(sizeof(struct noAVL));
        novo->dado = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        novo->altura = 0;
        return novo;
    } else if (strcmp(valor->chave, raiz->dado->chave) < 0) {
        // Inserção na subárvore esquerda
        raiz->esquerda = inserirAVL(valor, raiz->esquerda);
    } else if (strcmp(valor->chave, raiz->dado->chave) > 0) {
        // Inserção na subárvore direita
        raiz->direita = inserirAVL(valor, raiz->direita);
    } else {
        // Valor já existe na árvore, nada a fazer
        return raiz;
    }

    // Atualizar a altura do nó atual
    atualizarAltura(raiz);

    // Balancear a árvore após a inserção
    return balancear(raiz);
}

// Função para remover um valor da árvore AVL
arvoreAVL removerAVL (arvoreAVL raiz, char* valor) {
    // Verifica se a árvore está vazia
    if (raiz == NULL) {
        return NULL;
    } else {
        if (strcmp(raiz->dado->chave, valor) == 0) {
            // Se o valor a ser removido é igual ao valor na raiz atual
            if (raiz->esquerda == NULL && raiz->direita == NULL) {
                // Se a raiz não tem filhos
                free(raiz);
                return NULL;
            }
            if (raiz->esquerda == NULL && raiz->direita != NULL) {
                // Se a raiz tem apenas um filho à direita
                arvoreAVL temp = raiz->direita;
                free(raiz);
                return temp;
            }
            if (raiz->esquerda != NULL && raiz->direita == NULL) {
                // Se a raiz tem apenas um filho à esquerda
                arvoreAVL temp = raiz->esquerda;
                free(raiz);
                return temp;
            }
            
            // Se a raiz tem dois filhos
            arvoreAVL temp = maiorElementoAVL(raiz->esquerda);

            // Troca o valor da raiz com o valor do maior elemento encontrado
            strcpy(raiz->dado->chave, temp->dado->chave);
            strcpy(temp->dado->chave, valor);

            // Remove recursivamente o maior elemento da subárvore esquerda
            raiz->esquerda = removerAVL(raiz->esquerda, valor);

            // Retorna a raiz atualizada
            return raiz;
        } else {
            // Se o valor a ser removido for menor ou maior que o valor na raiz
            if (strcmp(raiz->dado->chave, valor) > 0) {
                raiz->esquerda = removerAVL(raiz->esquerda, valor);
            } else {
                raiz->direita = removerAVL(raiz->direita, valor);
            }
        }
    }
    // Atualizar a altura do nó atual
    atualizarAltura(raiz);

    // Balancear a árvore após a remoção
    return balancear(raiz);
}