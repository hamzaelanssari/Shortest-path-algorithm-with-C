#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF 1000000000
#define TAILLE_MAX 50

struct Vol    /*Creation de la structure Vol qui contient (le nom d'a�roport d'origine , le nom d'a�roport de destination , 
			l'indice de l'a�roport d'origine , l'indice de l'a�roport de destination , la dur�e de vol*/
{

	char Nom_Aeroport_Origine[TAILLE_MAX];
	char Nom_Aeroport_Destination[TAILLE_MAX];
	int Indice_Origine;
	int Indice_Destination;
	int  Duree_Vol;
};
 
// une structure pour repr�senter un graphe orient�.
struct Graph
{
    int NbrAeroports, NbrVols;
    // NbrAeroports est le nombre de sommets et NbrVols est le nombre d'ar�tes.
 
    struct Vol* Vol;
    // Cette structure contient une autre structure que nous avons d�j� cr��s.c-�-d on a  cr�� une variable(Vol) de type Vol.
};
// cr��r un graphe de type Graph
struct Graph* creerGraph(int NbrAeroports, int NbrVols)
{
    struct Graph* graph = (struct Graph*) malloc( sizeof(struct Graph));//Allouer de l'espace au structure Graph
 // attribuer des valeurs aux �l�ments de structure pris par l'utilisateur.
    graph->NbrAeroports = NbrAeroports;   //graph->NbrAeroports= nombre des sommets(a�roports) pris par l'utilisateur.
 
    graph->NbrVols = NbrVols;             //graph->NbrVols= nombre des ar�tes(Vols) pris par l'utilisateur.
 
    graph->Vol = (struct Vol*) malloc( graph->NbrVols * sizeof( struct Vol ) );  
	
 //Cr�ation de structures de type "Vol" dans la structure "Graph", le nombre de structures de type Vol est �gal au nombre de vols.
    return graph;
}
 
 	char *rechercher(Graph* graph,int indice){ // fonction qui trouve le nom de l aeroport par son indice
 		int i;
 		int N=graph->NbrVols;
 		for(i=0;i<N;i++){
 			if(graph->Vol[i].Indice_Origine==indice)
 			return graph->Vol[i].Nom_Aeroport_Origine;
 			if(graph->Vol[i].Indice_Destination==indice)
 			return graph->Vol[i].Nom_Aeroport_Destination;
		 }
	 }

 
void BellmanFord(struct Graph* graph, int Aeroport_Origine, char Nom_Aept_Origine[TAILLE_MAX]) // fonction initiale pour calculer la plus courte duree entre les aeroports
{   
	int Indice_Apt_Origine = Aeroport_Origine;
    int NbrAeroports = graph->NbrAeroports;   //donner � NbrAeroports le nombre des sommets c-�-d     NbrAeroports = nombre des sommets(Aeroports)
 
    int NbrVols = graph->NbrVols;    //en donner � NbrVols le nombre des ar�tes  c-�-d     NbrVols = nombre des ar�tes(Vols)
 
    int Sauvegarder_Duree[NbrAeroports]; //Sauvegarder_Duree[NbrAeroports] est un tableau pour enregistrer les valeurs des Durees
 
    int i,j;
 
    // C�est la premi�re �tape que nous connaissons, nous initialisons toute la Duree � l�infini sauf l'Origine.
    // Nous assignons la Duree Origine � 0 (z�ro)
 
    for (i = 0; i < NbrAeroports; i++)
        Sauvegarder_Duree[i] = INF;//initialisons toute la Duree � l�infini qu'on l'a repr�sent� 1000000000
 
    Sauvegarder_Duree[Indice_Apt_Origine] = 0;// la Duree de l'a�roport d'origine toujours �gal � 0
 
    // Le plus court chemin du graphe contenant un NbrSommets sommets ne contient jamais d'ar�tes "Sommets-1"
    for (i = 1; i <NbrAeroports; i++)
    {
        for (j = 0; j < NbrVols; j++)
        {
            int x = graph->Vol[j].Indice_Origine;// copier nombre de sommet Origine de l'ar�te j dans x

            int y = graph->Vol[j].Indice_Destination;// copier nombre de sommet destination de l'ar�te j dans y

            int Duree_Vol = graph->Vol[j].Duree_Vol;// copier Duree_Vol de l'ar�te j dans Duree_Vol
 
            if (Sauvegarder_Duree[x] + Duree_Vol < Sauvegarder_Duree[y])
                Sauvegarder_Duree[y] = Sauvegarder_Duree[x] + Duree_Vol;
        }
    }
    
    //En fait, jusqu'� pr�sent, le plus court chemin trouv�. Mais Bellman Ford v�rifie le cycle de bord n�gatif. Dans cette �tape, nous v�rifions que
 
    //Durees les plus courtes si le graphique ne contient pas de cycle de Duree_Vol n�gatif.
    
    //S�il n�y a pas de stabilisation � la N ime it�ration, il existe alors un circuit absorbant dans le graphe.
 
    // Si nous obtenons un chemin plus court, alors il y a un circuit absorbant.
    
    //Notons que les dur�es sont toujours positives donc il n y aura jamais de circuit absorbant donc la partie suivante du code c'est seulement pour l'exp�rimentation
    // et pour appliquer l'algorithme de Bellman-Ford en complet.
    i=0;
    while(i<NbrVols)
    {
        int x = graph->Vol[i].Indice_Origine;

 
        int y = graph->Vol[i].Indice_Destination;

        int Duree_Vol = graph->Vol[i].Duree_Vol;
 
        if (Sauvegarder_Duree[x] + Duree_Vol < Sauvegarder_Duree[y])
            printf("Ce graphe contient un circuit absorbant\n");
        i++;
    }
 

        printf("\nAeroport d origine    \t\t     Aeroport\t  \t    Duree\n"); // Pour afficher le r�sultat final
    int k;
 
    for (k = 0; k < NbrAeroports; ++k){
        printf("%s                                  %s                 \t %d\n",Nom_Aept_Origine ,rechercher(graph,k), Sauvegarder_Duree[k]);
    }
 
    return;
}
 
int main()
{
    int NbrAeroports,NbrVols;
	int Ind_Aeroport_Calcul;
	char Nom_Aeroport_Calcul[TAILLE_MAX];
	  //NbrAeroports = nombre de sommets(A�roports), NbrVols = nombre des ar�tes(Nbr de vols)
    //  notre infomations(Universite /DEPARTEMENT/Filiere Ingenieur/ MODULE/
    printf("=========================================================\n\n"); 
    printf("Universite Hassan II Casablanca \n");  
    printf("Ecole Normale Superieure de l'Enseignement Technique Departement Mathematique et informatique \n\n"); 
    printf(" DEPARTEMENT INFORMATIQUE \n"); 
    printf("Filiere Ingenieur :BDCC (Big data et Cloud Computing)\n"); 
    printf(" ETUDIANT :HAMZA EL ANSSARI && HAMZA GUEDDI\n");
    printf(" MODULE DE RECHERCHE OPERATIONNELLE \n"); 
    printf("===========================================================\n"); 
    printf(" ***bonjour*** \n\n"); 
    printf("===========================================================\n\n\n\n");  
    //donner � l'utilisateur pour entrer nombre des aeroports , nombre des Vols et les donnees de l'a�roport � calculer//
	printf("Veuillez entrer le nombre des Aeroports :"); 
    scanf("%d",&NbrAeroports); 
    printf("Veuillez entrer le nombre de vols :");
    scanf("%d",&NbrVols);
    getchar();
    printf("\n Attention! Il faut numeroter les sommets du graphe entre 0 et %d\n\n\n",NbrAeroports-1); 
    printf("Veuillez entrer le nom d aeroport pour calculer sa Duree\n");
    gets(Nom_Aeroport_Calcul);
    printf("Veuillez entrer son indice\n");
    scanf("%d",&Ind_Aeroport_Calcul);
    getchar(); // pour �viter le probl�me de gets qui vient apr�s scanf
 // appel fonction ( creerGraph ) pour allouer de l'espace � ces nombreux sommets et ar�tes
    struct Graph* graph = creerGraph(NbrAeroports, NbrVols);
    int i;
    
    for(i=0;i<NbrVols;i++){
        printf("\nEntrer Origine , destination et la duree du vol %d\n",i+1);     //Cette partie invite l'utilisateur � remplir tout le graphe (aeroports , vols) et indices des aeroports
        printf("\nNom Aeroport Origine:");
        gets(graph->Vol[i].Nom_Aeroport_Origine);
        printf("\nIndice Origine:");
        scanf("%d",&graph->Vol[i].Indice_Origine);
        getchar();
        printf("\nNom Aeroport Destination:");
        gets(graph->Vol[i].Nom_Aeroport_Destination);
        printf("\nIndice Destination:");
        scanf("%d",&graph->Vol[i].Indice_Destination);
        getchar();
        printf("\nDuree_Vol:");
        scanf("%d",&graph->Vol[i].Duree_Vol);
        getchar();
    }
    printf("La duree entre l aeroport %s et les autres aeroports:",graph->Vol[0].Nom_Aeroport_Origine);
   BellmanFord(graph, Ind_Aeroport_Calcul,Nom_Aeroport_Calcul);
    //passage du graphe cr�� et de l'aeroport � calculer (indice et nom) � la fonction d�algorithme de Bellman Ford
 
    return 0;
}
