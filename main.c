#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
#define TAILLE_X 40
#define TAILLE_Y 40

void clrscr(){ // fonction clear
    system("@cls||clear");
}

void murMilieux(int t[TAILLE_X][TAILLE_Y]){
    int i,j=0;
    int n = murAleatoirement();
    for (i=0;i<TAILLE_X-1;i++){
		for(j=0;j<TAILLE_Y-1;j++){
            if (n==2 && (t[i][j-1]==1 || t[i+1][j]==1)){
                t[i][j]=1;
                }
            else{
                t[i][j]=0;
            }
		}
    }
}

void creerZone(int t[TAILLE_X][TAILLE_Y]){
	int i,j=0;

	for (i=0;i<TAILLE_X;i++){
		for(j=0;j<TAILLE_Y;j++){
			if(i==0 || j==0 || i == TAILLE_X -1 || j == TAILLE_Y -1){	//Insérer les murs ici
				t[i][j]=1;
			}
			else if (i==4 && j ==4) {	//Insérer les coordonnées des monstres ici
				t[i][j]=2;
			}
			else if (i==5 && j==5){     //Insérer les coordonnées du deuxième monstres ici
                t[i][j]=2;
			}
			else if (i==8 && j==8){   //Insérer les coordonnées du personnage ici
                t[i][j]=3;
			}
			else{
				t[i][j]=0;
			}

		}
	}


}

void affichage(int tab[TAILLE_X][TAILLE_Y]){
	int i=0;
	int j=0;
	for(i=0;i<TAILLE_X;i++){
		for(j=0;j<TAILLE_Y;j++){
			if(tab[i][j]==0){ //vide
				printf(" ");
			}
			else if(tab[i][j]==1){ //murs
				printf("#");
			}
			else if(tab[i][j]==2){ //monstre
				printf("m");
			}
			else if(tab[i][j]==3){ //perso
                printf("P");
			}
		}
		printf("\n");
	}
}

int murAleatoirement(void){ // Générer des murs aléatoires
   static int first = 0;

   if (first == 0)
   {
      srand (time (NULL));
      first = 1;
   }
   return (rand ()%2);
}

int random (void){ // initialiser un nombre n au hasard pour les déplacements du monstres
   static int first = 0;

   if (first == 0)
   {
      srand (time (NULL));
      first = 1;
   }
   return (rand ()%4);
}

int monstre (int t[TAILLE_X][TAILLE_Y], int x, int y){
    int n = random();
	int monstre=2;
	int done=0;

    if(t[x][y+1]==3 || t[x-1][y]==3 || t[x+1][y]==3 || t[x][y-1]==3){
        done=10; // si un monstre touche le personnage, la partie est finie
	}
	if (n==0 && x< TAILLE_X-1  && y < TAILLE_Y-1 && x>0 && y>0 && t[x][y-1]!=1 && t[x][y-1]!=2){
		//Avancer en avant
		t[x][y] = 0;
		t[x][y-1] = monstre;
		y=y-1;
    }
	else if(n==1 && x< TAILLE_X-1  && y < TAILLE_Y-1 && x>0 && y>0 && t[x+1][y]!=1 && t[x+1][y]!=2){
		//Avancer à droite
		t[x][y] = 0;
		t[x+1][y] = monstre;
		x=x+1;
	}
	else if (n==2 && x<TAILLE_X-1  && y < TAILLE_Y-1 && x>0 && y>0 && t[x-1][y]!=1 && t[x-1][y]!=2){
		//Avancer à gauche
		t[x][y] = 0;
		t[x-1][y] = monstre;
		x=x-1;
	}
	else if(n==3 && x< TAILLE_X-1  && y < TAILLE_Y-1 && x>0 && y>0 && t[x][y+1]!=1 && t[x][y+1]!=2){
		//Avancer en bas
		t[x][y] = 0;
		t[x][y+1] = monstre;
		y=y+1;
	}

return done;
}

int main(){

    int t[TAILLE_X][TAILLE_Y]={0};
	int jeu_fini = 0;			//variable =1 si le joueur a gagné ou 2 si il est mort
	int i,j =0;
	int x=0; //coords monstre x
	int y =0; //coords monstre y
	int e =0; //coords perso x
	int z =0; //coords perso y
	t[x][y]=2;
	int compteur = 0;
    creerZone(t);	//Initialisation de la zone
    void murMilieux(t);
	while(jeu_fini == 0){

		for (i=0;i<TAILLE_X;i++){		//recherche de la nouvelle position du monstre
			for(j=0;j<TAILLE_Y;j++){
				if(t[i][j]==2){
                    affichage(t);	//affichage de la zone
                    x=i;
					y=j;
					compteur = compteur + monstre(t, x, y);
					printf("\n");
					_sleep(1000);
					clrscr();
				}
			}
		}
        compteur ++;

		if(compteur>10){
			jeu_fini = 1;
		}
	}
	printf("\n Vous avez perdu ! \n");
	return 0;
}
