#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define SENS 16

struct Estacion{
   	char  Numero[50];
	char  Estacion[50];
	char  Id_Loc[50];
	char  Fecha[50];
	int   sensores[SENS];
};


int main( int argc, char *argv[] ) {

	if(argc==2){
		int var = atoi(argv[1]);
		if(var>15 || var<0 || var == 5){
			printf("Numero de variable erroneo\n");
			return -1;
		}
		float acumulado=0.0;
		float contador=0.0;
		float promedio=0.0;
		FILE *fe;
		fe = fopen("datos_meteorologicos.csv" , "r");
		if(fe == NULL){
			perror("Error abrir archivo de lectura");
			return(-1);
		}
		char str2[1024];
		struct Estacion estacion1;
		strcpy( estacion1.Numero, "Nueva");//defino el objeto Numero de estacion1 como "Nueva" para luego comparar
		memset( str2, 0, 1024 );
		int ii=0;
		while(fgets (str2, 1024,fe)!=NULL){
			if(ii<3|| !strcmp(str2, "\n")){			

			}
			else{
				char *com;
				com=strtok(str2, ",");
				/**es la primera comprobacion para la estacion Numero!=com y Numero!=0 guardo numero y compruebo q
					 valor tiene la variable solicitada*/
				if(strcmp( estacion1.Numero, com )&& !strcmp( estacion1.Numero, "Nueva" )){
					strcpy( estacion1.Numero, com);
					com=strtok(NULL, ",");//cortamos el Nombre, no lo usamos
					strcpy( estacion1.Estacion, com);
					com=strtok(NULL, ",");//cordtamos Id_Loc, no lo usamos
					strcpy( estacion1.Id_Loc, com);
					com=strtok(NULL, ",");//cortamos fecha, no la usamos
					int j=0;
					while(j!=var){
						com=strtok(NULL, ",");//posiciono en la variable deseada
						j++;
					}
					com=strtok(NULL, ",");//extraigo la variable deseada
					if(strcmp( com, "--")){ //si es distinto de -- lo acumulo
						float fpre = atof(com);
						acumulado = acumulado + fpre;
						contador=contador+1.0;			
					}
				}
				else{
					/**en caso de ser falso preguntamos si ya es otra linea de la misma estacion, comprobamos los sensores*/
					if(!strcmp( estacion1.Numero, com )){
						com=strtok(NULL, ",");//cortamos el Nombre, no lo usamos
						com=strtok(NULL, ",");//cordtamos Id_Loc, no lo usamos
						com=strtok(NULL, ",");//cortamos fecha, no la usamos
						int j=0;
						while(j!=var){
							com=strtok(NULL, ",");//posiciono en la variable deseada
							j++;
						}
						com=strtok(NULL, ",");//extraigo la variable deseada
						if(strcmp( com, "--")){ //si es distinto de -- lo acumulo
							float fpre = atof(com);
							acumulado = acumulado + fpre;
							contador=contador+1.0;			
						}
					}
					else{
						promedio=acumulado/contador;
						//mostramos la ultima estacion
						printf("Estacion: %s  Promedio: %f\n", estacion1.Numero, promedio);
						acumulado=0.0;
						contador=0.0;
						promedio=0.0;
						memset( estacion1.Numero, 0, 50 );
						strcpy( estacion1.Numero, com);
						com=strtok(NULL, ",");
						com=strtok(NULL, ",");
						com=strtok(NULL, ",");//para la fecha, no lo usamos
						int j=0;
						while(j!=var){
							com=strtok(NULL, ",");//posiciono en la variable deseada
							j++;
						}
						com=strtok(NULL, ",");//extraigo la variable deseada
						if(strcmp( com, "--")){ //si es distinto de -- lo acumulo
							float fpre = atof(com);
							acumulado = acumulado + fpre;
							contador=contador+1.0;			
						}
					}
				}
			}
			memset( str2, 0, 1024 );
			ii=ii+1;
		}
		promedio=acumulado/contador;
		printf("Estacion: %s  Promedio: %f\n", estacion1.Numero, promedio);//mostramos la ultima estacion
		fclose(fe);
		return 0;
	}
	else{
		printf("Debe ejecutar: promedio n°variable\n");
		return (-1);
	}
}



