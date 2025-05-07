#ifndef _SMUTREAP_H_
#define _SMUTREAP_H_

#include <stdbool.h>

/*
 * Uma SmuTreap é uma treap espacial com promoção dinâmica de nós mais usados.
 * Assim como qualquer Treap, a SmuTreap associa a cada nó inserido na árvore 
 * uma prioriodade. A SmuTreap permite que esta prioridade seja alterada
 * posteriormente, por dois meios:
 * (a) diretamente pelas operações promoteNodeSmuT e demoteNodeSmuT;
 * (b) indiretamente pela frequência com que o nó é selecionado.
 *
 * Em relação ao item (b), dois parâmetros, informados na criação da árvore, são 
 * considerados: hitCount, promotionRate. O primeiro (hitCount) é a quantidade 
 * de vezes que o nó deve ser selecionado para que tenha sua prioridade aumentada. 
 * O segundo é o fator multiplicativo usado para calcular a nova prioridade do nó.
 *
 * A cada nó r da Árvore é associado um ponto de 2 dimensões (r.x e r.y), denominado 
 * âncora, uma informação relacionada tal ponto e um "descritor" do tipo da informação. 
 * O significado dos valores de tal descritor é definido pela aplicação. A âncora 
 * determina a relação de ordem entre os elementos armazenados na árvore. Sejam dois 
 * nós da árvore: s e t. 
 * s < t: se (s.x < t.x) OU (s.x = t.x E s.y < t.y)
 *
 * A SmuTreap implementa 2 percursos: em largura e em profundidade. Tais percursos 
 * recebem como parâmetro uma função que processa a informação associada ao nó visitado.
 *
 * Também sao providas operações de seleção espacial:
 * A PRIMEIRA seleciona os nós da árvore cujas âncoras sao internas a uma região retangular.
 * A SEGUNDA seleciona os nós da árvore cujas informações associadas podem ser consideradas 
 * internas a uma região retangular. Esta operação recebe por parâmetro uma função que
 * decide se tal informação é considerada (ou não) interna.
 * A TERCEIRA, similarmente, seleciona os nós da árvore cujo um dado ponto é interno à 
 * informação associada ao nó.
 *
 * A SmuTreap é uma estrutura que se rearranja dinamicamente visando tornar consultas mais 
 * eficientes, a saber:
 *
 * (a) Cada nó da árvore mantém o bounding box (mínimo) que engloba as âncoras de suas 
 * sub-árvores. Este bounding box é usado para otimizar as operações de busca espacial.
 * (b) Nós mais selecionados são posicionados mais próximos a raiz. 
 *
 * Quando for necessario comparar a igualdade de coordenada (por exemplo, comparar a âncora 
 * de um nó com um outro ponto), aceita-se uma pequena discrepância entre a coordenada da 
 * âncora (anc.x, anc.y) e o ponto (x, y) de epsilon unidades. 
 * Ou seja, distancia(anc,x,y) < epsilon.
 *
 * Módulo a ser implementado para o trabalho 1 da disciplina "Estrutura de Dados 2",
 * do curso de Bacharelado em Ciência da Computação da Universidade Estadual de Londrina, 
 * no primeiro semestre de 2025. Obviamente, é expressamente proibido usar ferramentas de 
 * geração automática de código para fazer a implementção deste módulo. Qualquer duvida ou 
 * inconsistencia, favor reportar rapidamente para que correções possam ser rapidamente efetuadas.
 */

// EM VEZ DE SER typedef struct StSmuTreap SmuTreap, É void* PARA PODER SER USADO QUALQUER TIPO DE DADO
typedef void* SmuTreap;
typedef void* Node;
typedef void* Info;
typedef int DescritorTipoInfo;

typedef void (*FCalculaBoundingBox)(Info i, double *x, double *y, double *w, double *h);

SmuTreap newSmuTreap(int hitCount, double promotionRate, double epsilon);

Node insertSmuT(SmuTreap t, double x, double y, Info i, DescritorTipoInfo d, FCalculaBoundingBox fCalcBb);

#endif