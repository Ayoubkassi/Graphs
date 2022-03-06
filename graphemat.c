#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphemat.h"

//initializer graphe avec false values

static void razMarque(GrapheMat* graphe){
  for(int i = 0 ; i< graphe->n ; i++)
    graphe->marque[i] = faux;
}

//function rang

static int rang(GrapheMat* graphe , NomSom nom){
  int i = 0;
  booleen trouve = faux;
  while((i< graphe->n) && !trouve){
    trouve = strcmp(graphe->nomS[i], nom) == 0;
    if(!trouve) i++;
  }
  return trouve ? i : -1;
}

GrapheMat* creerGrapheMat(int nMax , int value){
  //Allocation Graphe
  GrapheMat* graphe = (GrapheMat*) malloc(sizeof(GrapheMat));
  graphe->n = 0;
  graphe->nMax = nMax;
  graphe->value = value;
  graphe->nomS = (NomSom*) malloc(sizeof(NomSom) * nMax);
  graphe->marque = (booleen*) malloc(sizeof(booleen) * nMax);
  graphe->element = (int*) malloc(sizeof(int) * nMax * nMax);
  graphe->valeur = (int*) malloc(sizeof(int) * nMax * nMax);


  //Initialisation par default;
  for (int i = 0; i < nMax; i++) {
    for (int j = 0; j < nMax; j++) {
      graphe->element[i*nMax+j] = faux;
      graphe->valeur[i*nMax+j] = INFINI;
    }
  }

  razMarque(graphe);

  return graphe;
}

//detruire graphe

void detruireGraphe(GrapheMat* graphe){
  free(graphe->nomS);
  free(graphe->marque);
  free(graphe->valeur);
  free(graphe->element);
  free(graphe);
}

//ajouter un sommet

void ajouterUnSommet(GrapheMat* graphe , NomSom nom){
  if(rang(graphe , nom) == -1){
    if(graphe->n < graphe->nMax){
      strcpy(graphe->nomS[graphe->n++], nom);
    }else{
      printf("\nNombre de sommets > %d\n", graphe->nMax);
    }
  }else{
    printf("\n%s deja defini\n", nom);
  }
}

//ajouter Un arc

void ajouterUnArc(GrapheMat* graphe , NomSom somD , NomSom somA , int cout){
  int nMax = graphe->nMax;
  int rd = rang(graphe , somD);
  int rg = rang(graphe , somA);
  graphe->element[rd*nMax+rg] = vrai;
  graphe->valeur[rd*nMax+rg] = cout;
}



//ecrireGraphe

void ecrireGraphe(GrapheMat* graphe){
  int nMax = graphe->nMax;

  for(int i = 0 ; i< graphe->n ; i++)
    printf("%s ", graphe->nomS[i]);
  printf(";\n");

  for(int i = 0 ; i < graphe->n ; i++){
    printf("\n%s : ",graphe->nomS[i]);
    for(int j = 0; j< graphe->n ; j++){
      if(graphe->element[i*nMax+j] == vrai){
        printf("%s ", graphe->nomS[j]);
        if(graphe->value){
          printf(" (%d) ", graphe->valeur[i*nMax+j]);
        }
      }
    }
    printf(";");
  }
}

//profondeur

static void profondeur(GrapheMat* graphe , int numSommet){
  int nMax = graphe->nMax;
  graphe->marque[numSommet] = vrai;
  printf("%s\n", graphe->nomS[numSommet]);

  for(int i = 0 ; i< graphe->n ; i++){
    if((graphe->element[numSommet*nMax+i] == vrai) && !graphe->marque[i]){
      profondeur(graphe , i);
    }
  }
}


//DFS

void DFS(GrapheMat* graphe){
  razMarque(graphe);
  for(int i = 0; i< graphe->n ; i++){
    if(!graphe->marque[i])
      profondeur(graphe,i);
  }
}




int main(){

  int choice ;
  int repeat = 1;
  int Maxi = 20;
  GrapheMat* graphe = NULL;
  int valeur;
  char nom1[20];
  char nom2[20];
  int cost;
  char nom[20];


  while(repeat){
  printf("\n\t\tHey Hey And Welcome Again\n");
  printf("\t****************************************\n");
  printf("1 : Creer un Graphe \n");
  printf("2 : Detruire un Graphe \n");
  printf("3 : Ajouter un Sommet \n");
  printf("4 : Ajouter un Arc \n");
  printf("5 : Ecrire Graphe \n");
  printf("6 : DFS \n");
  printf("7 : Exit \n");
  printf("Choisir une commande a faire : ");
  scanf("%d",&choice);



  switch (choice) {
    case 1:
      //do something
      printf("Entrez le nombre maximum du sommet default(20): ");
      scanf("%d",&Maxi);
      printf("Entrez la valeur du graphe value ou non (1/0): " );
      scanf("%d",&valeur);
      graphe = creerGrapheMat(10, valeur);
      printf("\nGraphe creer avec succes\n");
      break;
    case 2:
      detruireGraphe(graphe);
      printf("\nGraphe a été detruit");
      break;
    case 3:

      printf("Ajouter le nom su Sommet : ");
      scanf("%s",nom);
      ajouterUnSommet(graphe,nom);
      printf("\nSommet ajoute avec succes\n");
      break;
    case 4:

      printf("Entrez le nom du premier sommet : ");
      scanf("%s",nom1);
      printf("Entrez le nom du deuxieme sommet : ");
      scanf("%s",nom2);
      printf("Entrez le cout : ");
      scanf("%d",&cost);
      ajouterUnArc(graphe,nom1,nom2,cost);
      printf("\nArc ajoute avec succes\n");
      break;
    case 5:
      printf("Voila le graphe : ");
      ecrireGraphe(graphe);
      printf("\n");
      break;
    case 6:
      printf("Deep First Search : \n");
      DFS(graphe);
      printf("\n");
      break;
    case 7:
      repeat = -1;
      exit(-1);
      break;
    default :
        printf("Choix existe pas veuillez ressayer\n");
        break;
  }

}


  return 0;
}
