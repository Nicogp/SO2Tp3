#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



int main( int argc, char *argv[] ) {

	if(argc==2){
		char* est=argv[1];
		char esta[20];
		strcpy(esta, est);
		printf("estacion: %s\n", est);
		FILE *fe;
		fe = fopen("datos_meteorologicos.csv" , "r");
		if(fe == NULL){
			perror("Error abrir archivo de lectura");
			return (-1);
		}
		char str2[1024];
		char stre[1024];
		memset( str2, 0, 1024 );
		memset( stre, 0, 1024 );
		for(int i=0;i<3;i++){
			fgets (str2, 1024,fe);//descarto las primeras tres lineas
		}
		char *com;
		memset( str2, 0, 1024 );
		fgets(str2, 1024, fe);
		int ultimo=0;
		FILE *fss;
		
		while(fgets(str2, 1024, fe)!=NULL){//comprobamos que no sea el final, 
			strcpy(stre, str2);
			com=strtok(str2, ",");
			//compruebo q sea la estacion solicitada
			if(!strcmp(com, esta)){
				char nom[20];
				strcpy(nom, esta);
				strcat(nom, ".txt");
				fss = fopen(nom , "a");
				if(fss == NULL){
					perror("Error abrir archivo de escritura");
					return(-1);
				}

				//printf("str2: %s\n", str2);
				fprintf(fss, "%s\n", stre);
				ultimo=1;
				fclose(fss);
				
			}
			memset( str2, 0, 1024 );
			memset( stre, 0, 1024 );
		}
		if(ultimo==1){
			fclose(fe);
			printf("Se genero el archivo con exito\n");
			
			return 1;
		}
		fclose(fe);
		printf("Numero de estacion erronea\n");
		
		return (-1);

	}
	else{
		printf("Debe ejecutar: descargar n°estacion\n");
		return (-1);
	}
}
