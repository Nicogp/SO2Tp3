#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



int main( int argc, char *argv[] ) {

	if(argc==2){
		float acumulado=0.0;
		char* est=argv[1];
		printf("estacion: %s\n", est);
		FILE *fe;
		fe = fopen("datos_meteorologicos.csv" , "r");
		if(fe == NULL){
			perror("Error abrir archivo de lectura");
			return (-1);
		}
		char str2[1024];
		char strp[1024];
		memset( str2, 0, 1024 );
		memset( strp, 0, 1024 );
		for(int i=0;i<3;i++){
			fgets (str2, 1024,fe);//descarto las primeras tres lineas
		}
		char *com;
		char *com2;
		char mes[10];
	
		memset( str2, 0, 1024 );
		fgets(str2, 1024, fe);
		int ban=1;
		int ultimo=0;
		while(fgets(str2, 1024, fe)!=NULL){//comprobamos que no sea el final, 
			strcpy(strp, str2);
			com=strtok(str2, ",");
			//q sea la estacion solicitada
			if(!strcmp(com, est)){
				//buscamos la fecha
				for(int j=0;j<2;j++){
					com=strtok(NULL, ",");				
				}
				//obtenemos el mes
				com=strtok(NULL, " ");
				com2=strtok(com, "/");
				com2=strtok(NULL,"/");//com2 es el mes obtenido
				//printf("strp: %s\n", strp);
				//com=strtok(str2, ",");
			
				if(ban){//es el primer dia
					strcpy(mes,com2);//actualizo mes
					//busco la precipitacion del dia q esta en strp
					com=strtok(strp, ",");	
					for(int k=0;k<7;k++){
						com=strtok(NULL, ",");
					}
					float fpre = atof(com);
					acumulado = fpre;
					ban=0;
					ultimo=1;
				}
				else{	
				
					if(!strcmp(com2, mes)){//si es el mismo mes acumulo
						//busco la precipitacion del dia q esta en strp
						com=strtok(strp, ",");	
						for(int k=0;k<7;k++){
							com=strtok(NULL, ",");				
						}
						float fpre = atof(com);
						acumulado = acumulado + fpre;
					}
					else{
						//si el dia es distito de NULL muestro lo acumulado
						printf("Mes: %s Acumulado: %f\n", mes, acumulado);
						strcpy(mes,com2);//actualizo mes
						//busco la precipitacion del dia q esta en strp
						com=strtok(strp, ",");	
						for(int k=0;k<7;k++){
							com=strtok(NULL, ",");				
						}
						float fpre = atof(com);
						acumulado = fpre;
						
					}
				}
			}
			else{
				if(ultimo){
					printf("Mes: %s Acumulado: %f\n", mes, acumulado);
					ultimo=0;
					return 1;
				}
			
			}
			memset( str2, 0, 1024 );
			memset( strp, 0, 1024 );
			
		}
		printf("No se encontro la estacion solicitada\n");
		fclose(fe);
		return (-1);

	}
	else{
		printf("Debe ejecutar: mensual n°estacion\n");
		return (-1);
	}
}
