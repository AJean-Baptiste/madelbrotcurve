#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <complex.h>
#include <stdbool.h>

int N = 255; //nombre d'iterations de la fonction
int dim = 5000; //resolution de l'image

FILE* pgmimg; //création du fichier image

complex fz(complex z,complex c){ //fonction utilisé pour l'ensemble de mandel brot
    complex a = z*z + c;
    return(a);
}

int mandelbrotPoint(complex z, complex c){

    int a = 0;
    for (int i = 0; i < N; i++){ //on applique la fonction de mandelbrot
        z = fz(z,c);
        if (cabs(z) < 4)
            a = 255-i;
        else break;
    }
    return(a);

}

int main() {

    double points = dim; //conversion de la resolution en double

    printf("mise en place de la courbe:\n");

    //creation d'un array de dim x dim valeurs pour l'image
    int ** image;
    image = (int**)malloc(sizeof(int*)*dim);
    for (int i = 0; i < dim; i++)
        image[i] = (int*)malloc(sizeof(int)*dim);
    //////////////////////////////////////////////

    for (int a = 0; a < points; a++){
        for (int b = 0; b < points; b++){
            image[a][b] = 255;
        }
        if (a%(dim/100) == 0) printf("%d pourcent\n", a/(dim/100));
    }

    printf("calcul de la courbe:\n");

    for (int a = 0; a < points; a++){ //boucle tout les x
        for (int b = 0; b < points; b++){ //boucle tout les y onc les deux ensembles efectuents un balayage de gauche a droite et de haut en bas

            double x = (a/(points/3))-2; //on calcule la position x (decouper une ligne de 3 de long en dim points) le -2 ou -1.5 n'est qu'un offset
            double y = (b/(points/3))-1.5; //on calcule la position y

            complex c = x + y*I; //on defini x et y en complexe
            complex z = 0; //on defini z a 0

            image[a][b] = mandelbrotPoint(z,c);
        }
        if (a%(dim/100) == 0) printf("%d pourcent\n", a/(dim/100)); //affichage d'ou en est le programme apres 100 boucle de a
    }

    printf("création de l'image...\n");

    //le reste agit après les calculs et est relativement rapide
    pgmimg = fopen("pgmimg.pgm", "wb");

    fprintf(pgmimg, "P2\n");  
    fprintf(pgmimg, "%d %d\n", dim, dim);  
    fprintf(pgmimg, "255\n");  
    
    int count = 0; 
    
    for (int i = 0; i < dim; i++) { 
        for (int j = 0; j < dim; j++) { 
            
            int temp = image[i][j]; 
            fprintf(pgmimg, "%d ", temp); 

        } 
        fprintf(pgmimg, "\n"); 
    } 
    fclose(pgmimg);

    printf("done !");

}
