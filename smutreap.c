#include "smutreap.h"
#include "retangulo.h"
#include "ciruclo.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* O NÓ StNode TEM UMA ÂNCORA, A QUAL POSSUI UMA COORDENADA (x, y).
 * POR ISSO, A ESTRUTURA Ancora POSSUI DOIS CAMPOS (double x, double y). */
struct Ancora{

    double x;
    double y;

};

/* O BOUNDING BOX NADA MAIS É DO QUE UM RETÂNGULO.
 * EXPLICAR MELHOR DEPOIS */
struct BoundingBox{

    double x;
    double y;
    double w;
    double h;

};

/* CADA NÓ (REPRESENTADO COMO StNode) DA ÁRVORE (REPRESENTADA COMO StSmuTreap)
 * POSSUI UMA ÂNCORA, UMA INFORMAÇÃO (NESSE CASO, SERÁ UM RETÂNGULO, CÍRCULO, 
 * LINHA OU TEXTO), UM DESCRITOR (PARA IDENTIFICAÇÃO DO TIPO DA INFORMAÇÃO), 
 * UMA PRIORIDADE (CARACTERÍSTICA DAS SMUTREAPs), E UM BOUNDINGBOX (VAI TER ISSO MESMO?),
 * ALÉM DE DOIS PONTEIROS PARA OS LADOS DESSE NÓ */
struct StNode{

    struct Ancora ancora;
    Info informacao;
    DescritorTipoInfo descritor;
    int prioridade;
    struct BoundingBox *bb; // VAI TER ISSO MESMO?

    struct StNode *esquerdo;
    struct StNode *direito;

};

/* A ÁRVORE CONTÉM, ALÉM DE UM PONTEIRO PARA O PRIMEIRO NÓ DELA, 3 "REGULADORES".
 * hitcount GUARDA A QUANTIDADE DE VEZES QUE O NÓ DEVERÁ TER PARA AUMENTAR SUA PRIORIDADE.
 * promotionRate ARMAZENA O FATOR MULTIPLICATIVO USADO PARA O CÁLCULO DA NOVA PRIORIDADE DO NÓ.
 * epsilon TEM CONSIGO O VALOR USADO NO CÁLCULO DA DISTÂNCIA ENTRE NÓS  */
struct StSmuTreap{

    int hitcount;
    double promotionRate; 
    double epsilon;

    struct StNode *raiz;

};

// O QUE SE CHAMAVA struct Ancora PASSA A SE CHAMAR Ancora
typedef struct Ancora Ancora;
// O QUE SE CHAMAVA struct StNode PASSA A SE CHAMAR StNode
typedef struct StNode StNode;
// O QUE SE CHAMAVA struct StSmuTreap PASSA A SE CHAMAR StSmuTreap
typedef struct StSmuTreap StSmuTreap;

SmuTreap newSmuTreap(int hitCount, double promotionRate, double epsilon){

    StSmuTreap *arvore = (struct StSmuTreap*)malloc(sizeof(struct StSmuTreap));

    if(arvore == NULL){
        printf("Erro na alcocacao de memoria para a criacao da arvore!\n");
        return NULL;
    }

    arvore->hitcount = hitCount;
    arvore->promotionRate = promotionRate;
    arvore->epsilon = epsilon;
    arvore->raiz = NULL;
    
    return arvore;

}

// FUNÇÃO AUXILIAR
Node rotacionarEsquerda(Node n){

    StNode *no = (StNode*)n;
    StNode *auxiliar1 = no->direito;
    StNode *auxiliar2 = auxiliar1->esquerdo;

    auxiliar1->esquerdo = no;
    no->direito = auxiliar2;

    return auxiliar1;

}

// FUNÇÃO AUXILIAR
Node rotacionarDireita(Node n){

    StNode *no = (StNode*)n;
    StNode *auxiliar1 = no->esquerdo;
    StNode *auxiliar2 = auxiliar1->direito;

    auxiliar1->direito = no;
    no->esquerdo = auxiliar2;

    return auxiliar1;
 
}

// EM ANDAMENTO
