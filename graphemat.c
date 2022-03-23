#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphemat.h"
#include <sys/queue.h>



//Matrix

//initializer graphe avec false values

//queue stuff

char* dequeue(queue *q){
  if(q->head == NULL) return QUEUE_EMPTY;
  node *tmp = q->head;
  char* result = tmp->value;
  q->head = q->head->next;
  if(q->head == NULL){
    q->tail = NULL;
  }
  q->length--;
  return result;
}

bool enqueue(queue *q, char *value){
  node *newnode = malloc(sizeof(node));
  if(newnode == NULL) return false;
  newnode->value = value;
  newnode->next = NULL;
  if(q->tail != NULL){
    q->tail->next = newnode;
  }
  q->tail = newnode;
  if(q->head == NULL){
    q->head = newnode;
  }
  q->length++;
  return true;
}

void init_queue(queue *q){
  q->head = NULL;
  q->tail = NULL;
  q->length = 0;
}

bool empty_queue(queue* q){
  return q->length == 0;
}


static void razMarque(GrapheMat* graphe){
  for(int i = 0 ; i< graphe->n ; i++)
    graphe->marque[i] = faux;
}

static void ecrireEtape(Matrice a , Matrice p , int k , int ns , int nMax){
  printf("Passage par le sommet numero : %d\n\n",k);

  for(int i =0 ; i<ns ; i++){
    for(int j = 0 ; j<ns ; j++){
      if(a[i*nMax+k] == INFINI){
        printf(" %3s","*");
      }else{
        printf(" %3d",a[i*nMax+j]);
      }
    }
    printf("%6s"," ");
    for(int j = 0; j< ns ; j++){
      printf("%3d", p[i*nMax+j]);
    }
    printf("\n");
  }
  printf("\n\n");
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

static void profondeurLimite(GrapheMat* graphe , int numSommet , int limit){
  int nMax = graphe->nMax;
  graphe->marque[numSommet] = vrai;
  printf("%s ,", graphe->nomS[numSommet]);
  int callNumbers = 0;

  for(int i = 0 ; i< graphe->n ; i++){
    //ajouter une condition pour l'arret du profondeur dans un certain niveau
    if((graphe->element[numSommet*nMax+i] == vrai) && !graphe->marque[i]){
      ++callNumbers;
      if(callNumbers<=limit)
        profondeur(graphe , i);
      else
        break;
    }
  }
}

//WHAT IS The fucking solution : is that
//we gonna apply DFS but at each level we going to stop in a level and this level will be incremented each time

//Start Iterative DFS

void IterativeDFS(GrapheMat* graphe){
    //On va appeler une DFS Pour chaque graphe limite
  razMarque(graphe);
  for(int j = 0 ; j< graphe-> n ; j++){
    printf("\nDFS For level %d is : \n",j);
    for(int i = 0; i< graphe->n ; i++){
      if(!graphe->marque[i])
        profondeurLimite(graphe,i,j);
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


void enLargeur(GrapheMat* graphe){
  razMarque(graphe);
  queue *q1;
  init_queue(q1);
  for(int i = 0; i< graphe->n ; i++){
    if(!graphe->marque[i])
      BFS(graphe,i,q1);
  }
}

void BFS(GrapheMat* graphe , int pos , queue *q1){
  //creer une pile pour stocker les donnes
  //Creation d'une queue est l'initialiser
  int nMax = graphe->nMax;
  //marquer le sommet courrant comme visite
  graphe->marque[pos] = vrai;
  enqueue(q1,graphe->nomS[pos]);

  char *t;
  while((empty_queue(q1)) == false){
    t = dequeue(q1);
    printf("%s \n",t);
    //chercher les noued connecter avec et empiler les dans le pile
    for(int i = 0 ; i< graphe->n ; i++){
      if((graphe->element[pos*nMax+i] == vrai) && !graphe->marque[i]){
        enqueue(q1,graphe->nomS[i]);
        graphe->marque[i] = vrai;
      }
    }
  }
}



//so the algorithm is :
//1 - get every node level -> level to stop in
//2- how using queue , for each root , we gonna impelement BFS adn get all childs of that level
//3- implement recursive DFS with limit condition
//4- limit is DFS until one of last childs then getback

// void InsideLimitedDfs(GrapheMat* graphe , int node , int limit){
//   int nMax = graphe->nMax;
//   //so search over all nodes and add them into initialize stack
//   graphe->marque[node] = vrai;
//   for(int i = 0 ; i< graphe->n ; i++){
//     //verifier qu'il a une relation et que c'etais pas encore visite
//     //verifier la limite est encore non acheve
//     if((graphe->element[node*nMax+i] == vrai) && (graphe->marque[i] == faux)){
//       InsideLimitedDfs(graphe , i , limit);
//     }
//   }
//
//
// }

void InsideLimitedDfs(GrapheMat* graphe , int nodePos , int limit){
  int nMax = graphe->nMax;
  graphe->marque[nodePos] = vrai;
  printf("%s ,", graphe->nomS[nodePos]);


  if(limit == 1){
    //return coupure
  }else if(limit == 0){
    return -1;
  }
  else{
    for(int i=0 ; graphe->n ; i++){
      if((graphe->element[nodePos*nMax+i] == vrai) && !graphe->marque[i]){
        InsideLimitedDfs(graphe , i , limit - 1);
      }
    }
  }

}


//the algorithm is too simple , we gonna start by the roor node
//get all her childs
//make recursive call with limit parameter
//at each iteration we process --limit;
//end as condition of stop if limit = 0 we gonna stop and go into the next childs

void LimitedDfs(GrapheMat* graphe, int limit){
  razMarque(graphe);
  //for(int i = 0 ; i < graphe->n ; i++){
    //if(!graphe->marque[i])
    //get all childs of first node
    int nMax = graphe->nMax;
    int FirstNodeChilds[30];
    int childNum = 0;
    int pos=0;
    for(int i = 0 ; i < graphe->n ; i++){
      if((graphe->element[pos*nMax+i] == vrai) && pos != i){
        //printf("child is : %d",i);
        FirstNodeChilds[childNum++]=i;
      }
    }
    //call it with root
    InsideLimitedDfs(graphe , 0 , limit);
    //call it with all childs one by one in the queue
    for(int i = 0 ; i< childNum; i++){
      InsideLimitedDfs(graphe , FirstNodeChilds[i] , limit - 1);
    }

  //}
}

//Floyd
static void initFloyd(GrapheMat* graphe , Matrice* a , Matrice* p){
  int nMax = graphe->nMax;

  Matrice ta = (int*) malloc(sizeof(int) *nMax *nMax);
  Matrice tp = (int*) malloc(sizeof(int) *nMax *nMax);

  for(int i = 0 ;  i<graphe->n ; i++){
    for(int j = 0 ; j< graphe->n ; j++){
      ta[i*nMax+j] = graphe->valeur[i*nMax+j];
      tp[i*nMax+j] = i;
    }
  }

  *a = ta;
  *p = tp;
}

void floyd(GrapheMat* graphe){
  Matrice a , p;
  int n = graphe->n;
  int nMax = graphe->nMax;

  initFloyd(graphe,&a, &p);

  for(int k=0 ; k<n ; k++){
    for(int i = 0 ; i<n ; i++){
      for(int j = 0 ; j<n ; j++){
        if((a[i*nMax+k] != INFINI) && (a[k*nMax+j] != INFINI) && (a[i*nMax+k]+a[k*nMax+j] < a[i*nMax+j]) ){
          a[i*nMax+j] = a[i*nMax+k] + a[k*nMax+j];
          p[i*nMax+j] = p[k*nMax+j];
        }
      }
    }
    ecrireEtape(a, p , k , n, nMax);
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
  int nbSommet;
  int nbArc;


  while(repeat){
  printf("\n\t\tHey Hey And Welcome Again Ait Lahcen\n");
  printf("\t****************************************\n");
  printf("1 : Creer un Graphe \n");
  printf("2 : Detruire un Graphe \n");
  printf("3 : Ajouter un Sommet \n");
  printf("4 : Ajouter un Arc \n");
  printf("5 : Ecrire Graphe \n");
  printf("6 : DFS Algorithm\n");
  printf("7 : BFS algorithm\n");
  printf("8 : Limited DFS Algorithm\n");
  printf("9 : Floyd Algorithm\n");
  printf("10 : Exit \n");
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
      printf("Entrez le nombre de sommet : ");
      scanf("%d",&nbSommet);
      for(int i =0 ; i<nbSommet ; i++){
        printf("Ajouter le nom du  Sommet : ");
        scanf("%s",nom);
        ajouterUnSommet(graphe,nom);
        printf("\nSommet %d ajoute avec succes\n",i);
      }
      break;

    case 4:

      printf("Entrez le nombre d\'arc : ");
      scanf("%d",&nbArc);
      for(int i = 0 ; i< nbArc ; i++){
        printf("Entrez le nom du premier sommet : ");
        scanf("%s",nom1);
        printf("Entrez le nom du deuxieme sommet : ");
        scanf("%s",nom2);
        printf("Entrez le cout : ");
        scanf("%d",&cost);
        ajouterUnArc(graphe,nom1,nom2,cost);
        printf("\nArc %d ajoute avec succes\n",i);
      }
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
      printf("\n\nBreath First Search : \n");
      enLargeur(graphe);
      printf("\n");
      break;

    case 8:
      printf("\n\nLimited DFS Algorithm : \n");
      LimitedDfs(graphe,1);
      printf("\n");
      break;
    case 9:
      printf("\n\nFloyd Algorithm : ");
      floyd(graphe);
      break;

    case 10:
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
