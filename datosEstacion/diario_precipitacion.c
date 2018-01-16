#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



int main( int argc, char *argv[] ) {

	if(argc==2){
		char* est=argv[1];
		float acumulado=0.0;
		printf("estacion: %s\n", est);
		FILE *fe;
		fe = fopen("datos_meteorologicos.csv" , "r");
		if(fe == NULL){
			perror("Error abrir archivo de lectura");
			return (-1);
		}
		char str2[1024];
		memset( str2, 0, 1024 );
		for(int i=0;i<3;i++){
			fgets (str2, 1024,fe);//descarto las primeras tres lineas
		}
		char *com;
		char dia[10];
	
		memset( str2, 0, 1024 );
		fgets(str2, 1024, fe);
		int ban=1;
		int ultimo=0;
		while(fgets(str2, 1024, fe)!=NULL){//mientras no sea el final, 
			com=strtok(str2, ",");
			//q sea la estacion solicitada
			if(!strcmp(com, est)){
				//buscamos la fecha
				for(int j=0;j<2;j++){
					com=strtok(NULL, ",");				
				}
				//obtenemos el dia
				com=strtok(NULL, " ");
			
				if(ban){//es el primer dia
					strcpy(dia,com);//actualizo dia
					//busco la precipitacion del dia
					for(int k=0;k<5;k++){
						com=strtok(NULL, ",");				
					}
					float fpre = atof(com);
					acumulado = fpre;
					ban=0;
					ultimo=1;
				}
				else{	
				
					if(!strcmp(com, dia)){//si es el mismo dia acumulo
						//busco la precipitacion del dia
						for(int k=0;k<5;k++){
							com=strtok(NULL, ",");				
						}
						float fpre = atof(com);
						acumulado = acumulado + fpre;
					}
					else{
						//si el dia es distito de NULL muestro lo acumulado
						printf("Dia: %s Acumulado: %f\n", dia, acumulado);
						strcpy(dia,com);//actualizo dia
						//busco la precipitacion del dia
						for(int k=0;k<5;k++){
							com=strtok(NULL, ",");				
						}
						float fpre = atof(com);
						acumulado = fpre;
					
					}
				}
			}
			else{
				if(ultimo){
					printf("Dia: %s Acumulado: %f\n", dia, acumulado);
					ultimo=0;
					//printf("salio de getdiario\n");
					fclose(fe);
					return 1;
				}
			
			}
			memset( str2, 0, 1024 );
			
		}
		printf("No se encontro la estacion solicitada\n");
		fclose(fe);
		return (-1);
	}
	else{
		printf("Debe ejecutar: diario n°estacion\n");
		return (-1);
	}
}




