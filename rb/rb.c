#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

// Função para criar um novo nó em uma árvore RB
arvoreRB criarNo (indiceRB *info) {
	arvoreRB novo = (arvoreRB) malloc(sizeof(noRB));
    novo->dado = info;
	novo->pai = NULL;
    novo->direita = NULL;
    novo->esquerda = NULL;
    novo->cor = VERMELHO;
    return novo;
}

// Função para retornar a cor do no
int Cor (arvoreRB elemento) {
    if (elemento == NULL || elemento->cor == PRETO) {
        return 1;
    } else {
        return 0;
    }
}

// Função para verificar se um nó é a raiz da árvore
int ehRaiz (arvoreRB elemento) {
    if (elemento != NULL && elemento->pai == NULL) {
        return 1;
    } else {
        return 0;
    }
}

// Função para verificar se um nó é filho esquerdo
int ehEsquerdo (arvoreRB elemento) {
    if (elemento->pai != NULL && elemento->pai->esquerda == elemento) {
        return 1;
    } else {
        return 0;
    }
}

// Função para encontrar o irmão de um nó
arvoreRB irmao (arvoreRB elemento) {
    if (elemento == elemento->pai->esquerda) {
        return elemento->pai->direita;
    } else {
        return elemento->pai->esquerda;
    }
}

// Função para encontrar o tio de um nó
arvoreRB tio (arvoreRB elemento) {
    if (ehEsquerdo(elemento->pai)) {
        return elemento->pai->pai->direita;
    } else {
        return elemento->pai->pai->esquerda;
    }
}

// Função para realizar uma rotação simples à direita em uma árvore vermelho-preto
void rotacaoDireitaRB (arvoreRB *raiz, arvoreRB no, int simples) {
    arvoreRB aux, temp;

    // Armazena o nó à esquerda do nó passado como argumento em aux
    aux = no->esquerda;

    // Armazena o filho à direita de aux em temp
    temp = aux->direita;

    // Atualiza os ponteiros para realizar a rotação à direita
    no->esquerda = temp;
    aux->direita = no;

    // Se for uma rotação simples, atualiza as cores dos nós
    if (simples) {
        aux->cor = PRETO;
        no->cor = VERMELHO;
    }

    // Se temp não for nulo, atualiza o pai de temp para nó
    if (temp != NULL) {
        temp->pai = no;
    }

    // Atualiza o pai de aux para o pai de nó
    aux->pai = no->pai;
    
    // Verifica se nó é a raiz da árvore
    if (ehRaiz(no)) {
        *raiz = aux; // Se sim, atualiza a raiz da árvore para aux
    } else {
        // Caso contrário, atualiza o ponteiro do pai de nó para aux
        if (ehEsquerdo(no)) {
            no->pai->esquerda = aux;
        } else {
            no->pai->direita = aux;
        }
    }
    // Atualiza o pai de nó para aux
    no->pai = aux;
}

// Função para realizar a rotação simples à esquerda
void rotacaoEsquerdaRB (arvoreRB *raiz, arvoreRB no, int simples) {
    arvoreRB aux, temp;

    // Armazena o nó à direita do nó passado como argumento em aux
    aux = no->direita;

    // Armazena o filho à esquerda de aux em temp
    temp = aux->esquerda;

    // Atualiza os ponteiros para realizar a rotação à esquerda
    no->direita = temp;
    aux->esquerda = no;

    // Se for uma rotação simples, atualiza as cores dos nós
    if (simples) {
        aux->cor = PRETO;
        no->cor = VERMELHO;
    }

    // Se temp não for nulo, atualiza o pai de temp para nó
    if (temp != NULL) {
        temp->pai = no;
    }

    // Atualiza o pai de aux para o pai de nó
    aux->pai = no->pai;
    
    // Verifica se nó é a raiz da árvore
    if (ehRaiz(no)) {
        *raiz = aux; // Se sim, atualiza a raiz da árvore para aux
    } else {
        // Caso contrário, atualiza o ponteiro do pai de nó para aux
        if (ehEsquerdo(no)) {
            no->pai->esquerda = aux;
        } else {
            no->pai->direita = aux;
        }
    }
    // Atualiza o pai de nó para aux
    no->pai = aux;
}

// Função para realizar a rotação dupla à esquerda
void rotacaoDuplaEsquerdaRB (arvoreRB* raiz, arvoreRB no) {
    // Realiza uma rotação simples à direita no filho à direita de nó
    rotacaoDireitaRB(raiz, no->direita, 0);

    // Realiza uma rotação simples à esquerda em nó
    rotacaoEsquerdaRB(raiz, no, 0);

    // Após as rotações, atualiza as cores dos nós
    no->pai->cor = PRETO;
    no->cor = VERMELHO;
}

// Função para realizar a rotação dupla à direita
void rotacaoDuplaDireitaRB (arvoreRB* raiz, arvoreRB no) {
    // Realiza uma rotação simples à esquerda no filho à esquerda de nó
    rotacaoEsquerdaRB(raiz, no->esquerda, 0);

    // Realiza uma rotação simples à direita em nó
    rotacaoDireitaRB(raiz, no, 0);

    // Após as rotações, atualiza as cores dos nós
    no->pai->cor = PRETO;
    no->cor = VERMELHO;
}

// Função para ajustar a árvore RB
void ajustar (arvoreRB* raiz, arvoreRB no) {
    // Verifica se o nó é a raiz da árvore
    if (ehRaiz(no)) {
        no->cor = PRETO;
        return;
    }

    // Verifica se o pai do nó é vermelho, indicando uma possível violação das propriedades da árvore RB
    else if (no->pai->cor == VERMELHO) {
        // Caso 1: tio vermelho, baixa o preto do avô
        if (Cor(tio(no)) == VERMELHO) {
            no->pai->cor = PRETO;
            tio(no)->cor = PRETO;
            no->pai->pai->cor = VERMELHO;
            ajustar(raiz, no->pai->pai);
        } 

        // Caso 2: tio preto
        else {
            // Nó filho e nó pai, filhos esquerdos
            if (ehEsquerdo(no) && ehEsquerdo(no->pai)) {
                rotacaoDireitaRB(raiz, no->pai->pai, 1);
            }

            // Nó filho e nó pai, filhos direitos
            else if (!ehEsquerdo(no) && !ehEsquerdo(no->pai)) {
                rotacaoEsquerdaRB(raiz, no->pai->pai, 1);
            }

            // Nó filho direito, pai esquerdo
            else if (!ehEsquerdo(no) && ehEsquerdo(no->pai)) {
                rotacaoDuplaDireitaRB(raiz, no->pai->pai);
            }

            // Nó filho esquerdo pai direito
            else if (ehEsquerdo(no) && !ehEsquerdo(no->pai)) {
                rotacaoDuplaEsquerdaRB(raiz, no->pai->pai);
            }
        }
    }
}

// Função para inserir um elemento na árvore
void inserirRB (indiceRB *valor, arvoreRB* raiz) {
    arvoreRB posicao, pai, novo;

    // Inicializa a posição como a raiz da árvore
    posicao = *raiz;

    // Inicializa o pai como nulo
    pai = NULL;

    // Encontra a posição correta para inserir o novo elemento
    while (posicao != NULL) {
        // Atualiza o pai como a posição atual
        pai = posicao;

        // Se o valor a ser inserido for maior que o valor na posição atual, move para a direita
        if (valor->chave > posicao->dado->chave) {
            posicao = posicao->direita;
        } else {
            // Caso contrário, move para a esquerda
            posicao = posicao->esquerda;
        }
    }

    // Cria um novo nó com o valor a ser inserido
    novo = criarNo(valor);
    novo->pai = pai;

    // Se o novo nó for a raiz da árvore, atualiza a raiz
    if (ehRaiz(novo)) {
        *raiz = novo;
    } else {
        // Se o valor a ser inserido for maior que o valor do pai, o novo nó é filho direito do pai
        if (valor->chave > pai->dado->chave) {
            pai->direita = novo;
        } else {
            // Caso contrário, o novo nó é filho esquerdo do pai
            pai->esquerda = novo;
        }
    }

    // Após a inserção, ajusta a árvore para manter as propriedades da árvore RB
    ajustar(raiz, novo);
}


// Função para ajustar a árvore RB após uma remoção
void ajustarRemocao (arvoreRB* raiz, arvoreRB filho, arvoreRB pai) {
    arvoreRB irmao;

    // Enquanto o filho for nulo ou preto e não for a raiz da árvore
    while ((filho == NULL || filho->cor == PRETO) && filho != *raiz) {
        // Se o filho for o filho esquerdo do pai
        if (filho == pai->esquerda) {
            irmao = pai->direita;

            // Caso 1: o irmão é vermelho
            if (irmao->cor == VERMELHO) {
                irmao->cor = PRETO;
                pai->cor = VERMELHO;
                rotacaoEsquerdaRB(raiz, pai, 1);
                irmao = pai->direita; 
            }

            // Caso 2: o irmão é preto e ambos os filhos do irmão são pretos ou nulos
            if ((irmao->esquerda == NULL || irmao->esquerda->cor == PRETO) && (irmao->direita == NULL || irmao->direita->cor == PRETO)) {
                irmao->cor = VERMELHO;
                filho = pai;
                pai = filho->pai;
            } else {
                // Caso 3: o irmão é preto e o filho esquerdo do irmão é vermelho e o filho direito do irmão é preto ou nulo
                if (irmao->direita == NULL || irmao->direita->cor == PRETO) {
                    irmao->esquerda->cor = PRETO;
                    irmao->cor = VERMELHO;
                    rotacaoDireitaRB(raiz, irmao, 1);
                    irmao = pai->direita;
                }

                // Caso 4: o irmão é preto e o filho direito do irmão é vermelho
                irmao->cor = pai->cor;
                pai->cor = PRETO;
                irmao->direita->cor = PRETO;
                rotacaoEsquerdaRB(raiz, pai, 1);
                filho = *raiz;
                break; 
            }
        } else { // Se o filho for o filho direito do pai
            // O irmão é o filho esquerdo do pai
            irmao = pai->esquerda; 

            // Caso 1: o irmão é vermelho
            if (irmao->cor == VERMELHO) {
                irmao->cor = PRETO; 
                pai->cor = VERMELHO;
                rotacaoDireitaRB(raiz, pai, 1);
                irmao = pai->esquerda;
            }

            // Caso 2: o irmão é preto e ambos os filhos do irmão são pretos ou nulos
            if ((irmao->direita == NULL || irmao->direita->cor == PRETO) && (irmao->esquerda == NULL || irmao->esquerda->cor == PRETO)) {
                irmao->cor = VERMELHO;
                filho = pai;
                pai = filho->pai;
            } else {
                // Caso 3: o irmão é preto e o filho direito do irmão é vermelho e o filho esquerdo do irmão é preto ou nulo
                if (irmao->esquerda == NULL || irmao->esquerda->cor == PRETO) {
                    irmao->direita->cor = PRETO;
                    irmao->cor = VERMELHO;
                    rotacaoEsquerdaRB(raiz, irmao, 1);
                    irmao = pai->esquerda;
                }

                // Caso 4: o irmão é preto e o filho esquerdo do irmão é vermelho
                irmao->cor = pai->cor;
                pai->cor = PRETO;
                irmao->esquerda->cor = PRETO;
                rotacaoDireitaRB(raiz, pai, 1);
                filho = *raiz;
                break;
            }
        }
    }

    // Define a cor do filho como preto
    if (filho != NULL) {
        filho->cor = PRETO; 
    }
}

// Função para realizar a busca de uma chave na árvore RB
arvoreRB buscar (arvoreRB raiz, int chave) {
    // Se a árvore está vazia ou a chave é encontrada na raiz, retorna a raiz
    if (raiz == NULL || raiz->dado->chave == chave) {
        return raiz;
    } else {
        if (chave < raiz->dado->chave) {
            // Se a chave é menor que a raiz, busca na subárvore esquerda
            return buscar(raiz->esquerda, chave);
        } else {
            // Se a chave não é menor que a raiz, busca na subárvore direita
            return buscar(raiz->direita, chave);
        }
    }
}

// Função para remover um valor da árvore RB
void removerRB (arvoreRB* raiz, int chave) {
    arvoreRB filho, pai, sucessor, removido;
    int corRemovida;

    // Encontra o nó a ser removido
    removido = buscar(*raiz, chave);

    // Se o nó não for encontrado, retorna
    if (removido == NULL) {
        return;
    }

    // Se o nó tiver dois filhos
    if (removido->esquerda != NULL && removido->direita != NULL) {
        // Encontra o sucessor do nó
        sucessor = removido->direita;

        // Encontra o nó mais à esquerda da subárvore direita
        while (sucessor->esquerda!= NULL) {
            sucessor = sucessor->esquerda;
        }
        
        removido->dado = sucessor->dado;
        removido = sucessor;
    }

    // Armazena a cor do nó removido
    corRemovida = removido->cor;

    // Se o nó removido não tiver filho esquerdo
    if (removido->esquerda == NULL) {
        filho = removido->direita;
    } else {
        filho = removido->esquerda;
    }

    // Obtém o pai do nó removido
    pai = removido->pai;

    // Se o filho não for nulo
    if (filho != NULL) {
        filho->pai = pai;
    }

    // Se o pai for nulo, significa que o nó removido era a raiz
    if (pai == NULL) {
        *raiz = filho;
    } else {
        // Se o nó removido for o filho  do pai
        if (removido == pai->esquerda) {
            pai->esquerda = filho;
        } else {
            pai->direita = filho;
        }
    }

    // Se a cor do nó removido era preto
    if (corRemovida == PRETO) {
        ajustarRemocao(raiz, filho, pai);
    }

    // Libera a memória ocupada pelo nó removido
    free(removido);
}