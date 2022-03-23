#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#define faux 0
#define vrai 1
#define INFINI 100
typedef char NomSom[20]; //Nom du Sommet
typedef int booleen;
typedef int* Matrice;


//queue stuff

#define QUEUE_EMPTY CHAR_MIN



typedef struct node{
  char *value;
  struct node *next;
} node;

typedef struct{
  node *head;
  node *tail;
  int length;
} queue;


//end queue stuff


typedef struct{
  int n;           //Nombre de sommet
  int nMax;        //Nombre max de sommets
  booleen value;   //graphe value ou non
  NomSom* nomS;    //Nom des sommets
  Matrice element; //existence d'un arc(i,j)
  Matrice valeur;  //cout de l'arc (i,j)
  booleen* marque; // sommet marque (visite) ou non
} GrapheMat;


GrapheMat* creerGrapheMat(int nMax, int value);
void detruireGraphe(GrapheMat* graphe);
void ajouterUnSommet(GrapheMat* graphe, NomSom nom);
void ajouterUnArc(GrapheMat* graphe , NomSom D , NomSom somA , int cout);
void ecrireGraphe(GrapheMat* graphe);
void DFS(GrapheMat* graphe);
void BFS(GrapheMat* graphe , int pos, queue* q1);
void enLargeur(GrapheMat* graphe);
void IterativeDFS(GrapheMat* graphe);
//queue stuff functions

bool enqueue(queue *q, char *value);
char* dequeue(queue *q);
void init_queue(queue *q);
bool empty_queue(queue* q);
