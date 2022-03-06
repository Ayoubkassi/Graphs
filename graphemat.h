#include <stdio.h>

#define faux 0
#define vrai 1
#define INFINI 100
typedef char NomSom[20]; //Nom du Sommet
typedef int booleen;
typedef int* Matrice;

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
void BFS(GrapheMat* graphe);
