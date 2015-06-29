#ifndef NO_AVL_HPP
#define NO_AVL_HPP

#include <string.h>
#include <malloc.h>
#include <math.h>
#include "debug.h"

template <typename T>
class NoAVL  {
 private:
    int altura;  //!< Representa a altura do nó AVL
    T dado;
    NoAVL<T>* esquerda;
    NoAVL<T>* direita;
    
    int getGtr(int a, int b) {
        if (a > b)
            return a;
        return b;
    }
    static int getAltura(NoAVL<T>* nodo) {
        if (nodo == NULL)
            return -1;
        return nodo->altura;
    }
    NoAVL<T> *rotRS(NoAVL<T> *node) {
        if (node == NULL)
            return NULL;
        NoAVL<T> *tmpNode;
        tmpNode = node->direita;
        node->direita = tmpNode->esquerda;
        tmpNode->esquerda = node;
        node->altura = getGtr(getAltura(node->esquerda),
            getAltura(node->direita)) + 1;
        tmpNode->altura = getGtr(getAltura(tmpNode->esquerda),
            getAltura(tmpNode->direita)) + 1;
        return tmpNode;
    }
    NoAVL<T> *rotLS(NoAVL<T> *node) {
        if (node == NULL)
            return NULL;
        NoAVL<T> *tmpNode;
        tmpNode = node->esquerda;
        node->esquerda = tmpNode->direita;
        tmpNode->direita = node;
        node->altura = getGtr(getAltura(node->direita),
            getAltura(node->esquerda)) + 1;
        tmpNode->altura = getGtr(getAltura(tmpNode->direita),
            getAltura(tmpNode->esquerda)) + 1;
        return tmpNode;
    }
    NoAVL<T> *rotRD(NoAVL<T> *node) {
        node->direita = rotLS(node->direita);
        return rotRS(node);
    }
    NoAVL<T> *rotLD(NoAVL<T> *node) {
        node->esquerda = rotRS(node->esquerda);
        return rotLS(node);
    }
    NoAVL<T> *balanceTree(NoAVL<T> *arv) {
        int diffAlt = getAltura(arv->esquerda) - getAltura(arv->direita);
        if (diffAlt > 1) {
            if (getAltura(arv->esquerda->esquerda) >= getAltura(arv->esquerda->direita)) {
                arv = rotLS(arv);
            } else {
                arv = rotLD(arv);
            }
        } else if (diffAlt < -1) {
            if (getAltura(arv->direita->esquerda) <= getAltura(arv->direita->direita)) {
                arv = rotRS(arv);
            } else {
                arv = rotRD(arv);
            }
        }
        return arv;
    }

 public:
    explicit NoAVL(const T dado) {
        altura = 0;
        esquerda = NULL;
        direita = NULL;
        this->dado = dado;
    }
    virtual ~NoAVL() {
        if (esquerda != NULL)
            delete esquerda;
        if (direita != NULL)
            delete direita;
    }
    int getAltura() {
        return altura;
    }

    NoAVL<T>* getEsquerda() {
        return esquerda;
    }
    NoAVL<T>* getDireita() {
        return direita;
    }
    NoAVL<T>* inserir(const T dado, NoAVL<T>* arv) {
        if (arv == NULL) {
            arv = new NoAVL(dado);
            if (arv == NULL)
                return NULL;
        } else {
            if (strcmp(dado, arv->dado) < 0) {
                arv->esquerda = inserir(dado, arv->esquerda);
            } else {
                arv->direita = inserir(dado, arv->direita);
            }
            arv->altura = getGtr(getAltura(arv->direita),
                                getAltura(arv->esquerda)) + 1;
            arv = balanceTree(arv);
        }
        return arv;
    }
    NoAVL<T>* remover(NoAVL<T>* arv, const T dado) {
        NoAVL<T> *tmpNode, *minNode;
        if (arv == NULL)
            return NULL;
        if (strcmp(arv->dado, dado) == 0) {
            if (arv->esquerda == NULL && arv->direita == NULL) {
                delete this;
                return NULL;
            } else if (arv->esquerda != NULL && arv->direita != NULL) {
                minNode = minimo(arv->direita);
                arv->dado = new T(minNode->dado);
                arv->direita = remover(arv->direita, arv->dado);
                return arv;
            } else if (arv->esquerda != NULL) {
                tmpNode = arv->esquerda;
                arv->esquerda = NULL;
            } else if (arv->direita != NULL) {
                tmpNode = arv->direita;
                arv->direita = NULL;
            }
            delete arv;
            balanceTree(tmpNode);
            return tmpNode;
        }
        if (strcmp(dado, arv->dado) < 0) {
            arv->esquerda = remover(arv->esquerda, dado);
            arv->altura = getGtr(getAltura(arv->esquerda),
                getAltura(arv->direita)) + 1;
            return arv;
        }
        if (strcmp(dado, arv->dado) > 0) {
            arv->direita = remover(arv->direita, dado);
            arv->altura = getGtr(getAltura(arv->esquerda),
                getAltura(arv->direita)) + 1;
            return arv;
        }
        return NULL;
    }
    NoAVL<T>* minimo(NoAVL<T>* nodo) {
        if (nodo->esquerda == NULL)
            return nodo;
        return minimo(nodo->esquerda);
    }
    T getDado() {
        return dado;
    }
    T busca(const T dado, NoAVL<T>* arv) {
        if (arv == NULL)
            throw NULL;
        if (strcmp(dado, arv->dado) < 0)
            return busca(dado, arv->esquerda);
        if (strcmp(dado, arv->dado) > 0)
            return busca(dado, arv->direita);
        return arv->dado;
    }
    void preOrdem(NoAVL<T>* nodo) {
        if (nodo->esquerda != NULL)
            preOrdem(nodo->esquerda);
        if (nodo->direita != NULL)
            preOrdem(nodo->direita);
    }
    void emOrdem(NoAVL<T>* nodo) {
        if (nodo->esquerda != NULL)
            emOrdem(nodo->esquerda);
        if (nodo->direita != NULL)
            emOrdem(nodo->direita);
    }
    void posOrdem(NoAVL<T>* nodo) {
        if (nodo->esquerda != NULL)
            posOrdem(nodo->esquerda);
        if (nodo->direita != NULL)
            posOrdem(nodo->direita);
    }
    
    void encode(int level, T *list) {
        list[level] = dado;
        if (esquerda != NULL)
            esquerda->encode((level * 2) + 1, list);
        if (direita != NULL)
            direita->encode((level * 2) + 2,list);
        return;
    }
    
    T *encode() {
        T *list = (T*)malloc(sizeof(T*) * getNElements());
        memset(list, 0, sizeof(T*) * getNElements());
        list[0] = dado;
        if (esquerda != NULL)
            esquerda->encode(1, list);
        if (direita != NULL)
            direita->encode(2, list);
        return list;
    }
    
    int getNElements() {
        printlndbg("AVL altura: "<< altura);
        return (int)pow(2, altura + 1) - 1;
    }
};

#endif /* NO_AVL_HPP */
