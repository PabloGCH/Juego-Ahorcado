#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include <wchar.h>
#include <locale.h>
#include <time.h>
#define MAX_PALABRAS 30
#define CATEGORIABASE 5
#define MAX_CADENA 50  
#define MIN_CADENA 4     
#define MAX_JUGADORES 5
typedef char Tstring[MAX_CADENA];
typedef Tstring  Tcadena[MAX_PALABRAS];
typedef struct{
	Tstring Nombre;
	int puntos;
	int part_ganadas;
} Tjugador;
//Pasa una palabra a mayusculas
void mayusculas(Tstring pasaje){
	int i;
	int diferencia=(int)'a' -(int) 'A'; //falto escribir el (int)                                     
	int posicion;
	for(i=0;i<strlen(pasaje);i++){
		if(pasaje[i]>='a' && pasaje[i]<='z'){
			posicion=(int)pasaje[i];
			posicion=posicion-diferencia;
			pasaje[i]=(char)posicion;

		}
	}
}
//Muestra las categorias a elegir
	void mostrar_categorias(int cantcategorias,Tcadena categorias){
		int i;
		printf(" Las categorias son....\n\n");
		for(i=0;i<cantcategorias;i++){
			printf(" %d. %s\n",i+1,categorias[i]);
		}
	}
//Valida las categorias ingresadas
	void validar_categoria(Tstring final, Tcadena inicial, int ML) {
	
		bool valido = false;
		int i;
		while (valido==false) {
			for (i = 0; i < ML; i++) {
				if (strcmp(final,inicial[i]) == 0) {
					valido = true;
				}
			}
		
			if (valido==false) {
				printf(" La categoria no es valida, ingrese otra: ");
				fflush(stdin);
				scanf("%[^\n]s", final);
				fflush(stdin);
				mayusculas(final);
			}
		}
	}
//Lee las categorias ingresadas y las valida
	void ingresar_categorias(Tcadena Vcategorias, Tcadena categoriainicial, int *ML)
	{
		system("cls");
		int i,n,j;
		int pi=*ML;
		bool repetido;
		printf("\n Ingrese la cantidad de categorias que quiere agregar: ");
		scanf("%d",&n);
		while((n<1)||(n>CATEGORIABASE) && (*ML+n>CATEGORIABASE)){
			printf(" Ingrese una cantidad de categorias valida: ");
			fflush(stdin);       
			scanf("%d",&n);	
		}
		mostrar_categorias(CATEGORIABASE,categoriainicial);                                      
		for (i = pi ; i < n+pi; i++)
		{
			repetido=true;
			printf(" Ingrese el nombre de una categoria: ");
			fflush(stdin);
			scanf("%[^\n]s", Vcategorias[i]);
			fflush(stdin);
			mayusculas(Vcategorias[i]);
			validar_categoria(Vcategorias[i], categoriainicial, CATEGORIABASE );
			while(repetido==true){
				repetido=false;
				for(j=0;j<*ML;j++){
					if(strcmp(Vcategorias[j],Vcategorias[i])==0){
						repetido=true;
					}
				}  
				if(repetido==true){
					printf(" Ingrese una categoria que no este repetida: ");
					fflush(stdin);
					scanf("%[^\n]s",Vcategorias[i]);
					fflush(stdin);
					mayusculas(Vcategorias[i]);
					validar_categoria(Vcategorias[i], categoriainicial, CATEGORIABASE );
				}
			}
			*ML=*ML+1;
		}
		printf("\n");
		system("PAUSE");
	}
//Valida una palabra
	void validar_palabra(Tstring palabra) 
	{
		while (strlen(palabra)<MIN_CADENA || strlen(palabra)>MAX_CADENA){
				printf(" La palabra ingresada es invalida (Debe tener entre %d y %d caracteres)\n Ingrese otra palabra: ",MIN_CADENA,MAX_CADENA);
				fflush(stdin);
				scanf("%[^\n]s",palabra);
		}
	}
//Lee las palabras ingresadas y las valida
	void ingresar_palabras(Tcadena Vpalabras, Tcadena Vpista, Tcadena Vcate, Tcadena Vcategorias, int ML,int *cantpalabras){
		system("cls");
		int i,n;
		printf("\n Ingrese la cantidad de palabras que quiere agregar: ");
		scanf("%d",&n);
		while((n<1) || (n>MAX_PALABRAS)){
			printf(" Ingrese una cantidad de palabras valida: ");
			fflush(stdin);
			scanf("%d",&n);
		}
		mostrar_categorias(ML,Vcategorias);
		for (i=*cantpalabras;i<n+*cantpalabras;i++){
			printf(" Ingrese una palabra: " );
			fflush(stdin);
			scanf("%[^\n]s",Vpalabras[i]);
			validar_palabra(Vpalabras[i]);
			mayusculas(Vpalabras[i]);
			printf(" Ingrese una pista: ");
			fflush(stdin);
			scanf("%[^\n]s",Vpista[i]);
			printf(" Ingrese la categoria: ");
			fflush(stdin);
			scanf("%[^\n]s",Vcate[i]);
			fflush(stdin);
			mayusculas(Vcate[i]);
			validar_categoria(Vcate[i],Vcategorias,ML);
		}
		*cantpalabras=*cantpalabras+n;
		printf("\n");
	}
//Ordena palabras o categorias, alfabeticamente
	void ordenar_mostrar_alfabeticamente(Tcadena Vordenado,int n){
		int i=1,j;
		Tstring aux;
		bool ordenado = false;
		while((i<n) && (ordenado==false)){        
			ordenado = true;
				for(j=0;j<n-i;j++){                             
		      		if(strcmp(Vordenado[j],Vordenado[j+1])==1){    
				        ordenado = false;
				        strcpy(aux,Vordenado[j]); 
				        strcpy(Vordenado[j],Vordenado[j+1]);
						strcpy(Vordenado[j+1],aux); 
		     		} 
		        }
			i++;
		}
		for(i=0;i<n;i++){
			printf("\n %d. %s",i+1,Vordenado[i]);
		}
		printf("\n");
	}
//Ordena palabras segun la cantidad de caracteres
	void ordenar_mostrar_palabras(Tcadena Vpalabras,int cantpalabras){
		int i=1,j,k;
		Tstring aux;
		bool ordenado = false;
		Tcadena V;
		for(k=0;k<cantpalabras;k++){
			strcpy(V[k],Vpalabras[k]);
		}
		while((i<cantpalabras) && (ordenado==false)){        
			ordenado = true;   
			for(j=0;j<cantpalabras-i;j++){                             
				if(strlen(V[j])<strlen(V[j+1])){    
					ordenado = false;
					strcpy(aux,V[j]); 
					strcpy(V[j],V[j+1]); 
					strcpy(V[j+1],aux); 
				} 
			}
			i++;
		}
		for(i=0;i<cantpalabras;i++){
			printf("\n %d. %s",i+1,V[i]);
		}
		printf("\n");
	}
//Ordena palabras alfabeticamente de una categoria
	void mostrar_palabras_categoria(Tcadena Vcategorias,Tcadena Vcate,Tcadena Vpalabras, int ML,int cantpalabras){
		Tstring cateingresada;
		int n=0,i;
		Tcadena v;
		mostrar_categorias(ML,Vcategorias);
		printf(" Ingrese una categoria: ");
		fflush(stdin);
		scanf("%[^\n]s",cateingresada);
		mayusculas(cateingresada);
		validar_categoria( cateingresada, Vcategorias, ML);
		for(i=0;i<cantpalabras;i++){
			if(strcmp(cateingresada,Vcate[i])==0){
			strcpy(v[n],Vpalabras[i]);
			n=n+1;
			}
		}
		ordenar_mostrar_alfabeticamente(v,n);
	}
//Guarda la palabra que se esta escribiendo
	void progreso(Tstring palabra, char letra,Tstring muestra){
	
		int i;
		for(i=0;i<strlen(palabra);i++){
			if(palabra[i]==letra){
				muestra[i]=letra;
			}
		}
	}
// Valida que la letra este en la palabra
	bool validar_letra(Tstring palabra,Tstring Vincorrecta,char letra, int error){	
		bool correcto=false;
		int i;
		for(i=0;i<strlen(palabra);i++){
			if(palabra[i]==letra){
				correcto=true;
			}
		}
		return correcto;
	}
//Grafica el ahorcado
	void ahorcado(int error){
		int i;
		char barrainvertida=92;
		printf(" ___________");
		for(i=0;i<5;i++){
			if(i==0){
				printf("\n |/");
			}
			if(i>0){
				printf("\n |");
			} 
			if(i<1){
				printf("        |");
			}
			if((i==1) && (error>0)){
				printf("         O");
			}
			if(i==2){
				if(error>1){
					printf("        /");
				}
				if(error>2){
					printf("|");
				}
				if(error>3){
					printf("%c",barrainvertida);
				}
			}
			if(i==3){
				if(error>4){
					printf("        /");
				}
				if(error>5){
					printf(" %c",barrainvertida);
				}
			}
		}
		printf("_____");
		for(i=0;i<2;i++){
			if(i<1){
				printf("\n |    |");
			}
			if(i==1){
				printf("\n |____|");
			}
		}
	}
//Muestra los resultados del juego y el ganador final
	resultados(Tjugador jugadores[MAX_JUGADORES],int cantjugadores){
		int i;
		int mas_part_ganadas=0;
		int posicion_ganador;
		int posicion_empate;
		bool empate=false;
		for(i=0;i<cantjugadores;i++){
			if(mas_part_ganadas<jugadores[i].part_ganadas){
				mas_part_ganadas=jugadores[i].part_ganadas;
				posicion_ganador=i;
			}
		}
		for(i=0;i<cantjugadores;i++){
			if((jugadores[posicion_ganador].part_ganadas==jugadores[i].part_ganadas) && (i!=posicion_ganador)){
				empate=true;
			}
		}
		if(empate==false){
		printf("\n El ganador del juego es %s con %d partidas ganadas\n",jugadores[posicion_ganador].Nombre,jugadores[posicion_ganador].part_ganadas);
			system("PAUSE");
		} else{
			printf("\n El juego termino en un empate\n");
			system("PAUSE");
		}
	}
//Cuenta las partidas ganadas
	contador_partidas_ganadas(Tjugador jugadores[MAX_JUGADORES],int cantjugadores){
		int i;
		int menorpuntaje=100,posicion_ganador;
		bool empate=false;
		
		for(i=0;i<cantjugadores;i++){
			if(menorpuntaje>jugadores[i].puntos){
				menorpuntaje=jugadores[i].puntos;
				posicion_ganador=i;
			}
		}
		for(i=0;i<cantjugadores;i++){
			if((jugadores[posicion_ganador].puntos==jugadores[i].puntos) && (i!=posicion_ganador)){
				empate=true;
			
			}
			printf("\n %s, puntos %d",jugadores[i].Nombre,jugadores[i].puntos);
		}
		
		if(empate==false){
			jugadores[posicion_ganador].part_ganadas=jugadores[posicion_ganador].part_ganadas+1;
			printf("\n %s gano la partida.\n Partidas ganadas: %d \n",jugadores[posicion_ganador].Nombre,jugadores[posicion_ganador].part_ganadas);
			system("PAUSE");
		} else{
			printf("\n La partida termino en un empate\n");
		}
		for(i=0;i<cantjugadores;i++){
			jugadores[i].puntos=0;
		}
	}
//Valida si la letra se repitio y tambien que se encuentr entre A y Z
	void letra_repetida(char *letra,int Vletras[25]){
		int i=0;
		bool repite=true;
		int posicion;
		posicion=(int)*letra;
		i=0;
		while((i<25) && repite==true){  //cambiar por i<26 
			if(posicion-65==i){
				if(Vletras[i]==1){
					printf("\n Ingrese una letra no repetida: ");
					fflush(stdin);
					scanf("%c",letra);
					posicion=(int)*letra;
					i=-1;
				}
				if(Vletras[i]<1){
					Vletras[i]=Vletras[i]+1;
					repite=false;
				}
			}
			i++;
		}
		while((*letra<65)||(*letra>90)){  //creo q esta valiacion debe estar dentro del IF
                                                                         // tambien le falta el (int)
			printf("\n Ingrese una letra valida (EN MAYUSCULA):");
			fflush(stdin);
			scanf("%c",letra);
		}	
	}
//partida
	partida(int cantpartidas, int cantjugadores,int cantpalabras, Tjugador jugadores[MAX_JUGADORES],Tcadena Vpalabras,Tcadena Vpista){
		Tstring palabra;
		Tstring muestra;
		Tstring Vincorrectas={""};
		int final_palabra;
		bool win=false;
		int i,k,j,num=0;
		int Vletras[25];
		int error=0;
		char letra=' ';
		printf("\n%d\n",cantjugadores);
		for(k=0;k<cantpartidas;k++){
			for(j=0;j<cantjugadores;j++){
				if(cantpalabras>1){
					num=rand()%cantpalabras;
				}  
				strcpy(palabra,Vpalabras[num]);
				final_palabra=strlen(palabra);
				muestra[final_palabra]='\0';
				for(i=0;i<strlen(palabra);i++){
					muestra[i]='_';
				}
				for(i=0;i<25;i++){
					Vletras[i]=0;
				}
				progreso(palabra, letra, muestra);
				printf("%s\n\n\n",muestra);
				while((error!=6) && (win==false)){
					system("cls");
					ahorcado(error);
					printf("\n\n Pista: %s",Vpista[num]);
					printf("\n %s\n",muestra);
					printf("\n Las letras incorrectas son: %s\n",Vincorrectas);
					if((error!=6) && (win==false)){
						printf(" %s ingrese una letra(En mayusculas): ",jugadores[j].Nombre);
						fflush(stdin);
						scanf("%c",&letra);
						letra_repetida(&letra,Vletras);
						if(validar_letra(palabra,Vincorrectas,letra,error)==false){
							Vincorrectas[error]=letra;
							if(error<5){
								error++;
								jugadores[j].puntos=jugadores[j].puntos+1;
							}
							else{
								error++;
								jugadores[j].puntos=10;
							}
						}
					}
					progreso(palabra, letra, muestra);
					if(strcmp(muestra,palabra)==0){
						win=true;
					}
				}
				printf("\n");
				system("cls");
				win=false;
				ahorcado(error);
				printf("\n\n Pista: %s",Vpista[num]);
				printf("\n %s\n",muestra);
				letra=' ';
				error=0;
				for(i=0;i<6;i++){
					Vincorrectas[i]=' ';
				}
				muestra[MAX_CADENA]='\0';
				system("PAUSE");
		}
		contador_partidas_ganadas(jugadores,cantjugadores);
		}
	}
//inicializacion de los jugadores
	inicializar_jugadores(int *cantjugadores,Tjugador jugadores[MAX_JUGADORES]){
		
		int i;
		printf(" Ingrese la cantidad de usuarios: ");
		fflush(stdin);
		scanf("%d",cantjugadores);
		while((*cantjugadores<=0)||(*cantjugadores>10)){
			printf("\n Ingrese una cantidad de usuarios valida: ");
			fflush(stdin);
			scanf("%d",cantjugadores);
		}

		for(i=0;i<*cantjugadores;i++){
			printf(" Ingrese el nombre del jugador %d: ", i+1);
			fflush(stdin);       
			scanf("%[^\n]s",jugadores[i].Nombre);
			jugadores[i].puntos=0;
			jugadores[i].part_ganadas=0;
		}
		printf("\n");
		system("PAUSE");
		
	}
//inicializacion de la partida
	void iniciar_partida(Tcadena Vcategorias,Tcadena Vpalabras,Tcadena Vpista,Tcadena Vcate,int cantpalabras){
		
		Tjugador jugadores[MAX_JUGADORES];
		int cantpartidas,cantjugadores=0;
		srand(time(NULL));
		printf("\n Ingrese la cantidad de partidas que desea jugar: ");
		fflush(stdin);
		scanf("%d",&cantpartidas);
		while((cantpartidas<=0)||(cantpartidas>10)){
			printf("\n Ingrese una cantidad de partidas valida: ");
			fflush(stdin);
			scanf("%d",&cantpartidas);
		}
		inicializar_jugadores(&cantjugadores,jugadores);
		partida(cantpartidas,cantjugadores,cantpalabras,jugadores,Vpalabras,Vpista);
		resultados(jugadores,cantjugadores);
	} 
//Barritas de las opciones
	void barras_de_opciones(){
		printf("\n-----------------------------------------------------------------------------------------------------------------\n");
		return;
	}
//Programa principal
	int main() {
		setlocale(LC_ALL, "");
		Tcadena categoriainicial= {"PELICULAS","GRUPOS MUSICALES","PAISES","COMIDAS","MARCAS DE AUTO"};
		Tcadena Vcategorias;
		Tcadena Vpalabras, Vpista, Vcate;
		int ML=0,cantpalabras=0;
		char eleccion='0';
		while(eleccion!='6'){
			printf("\n Menu");
			barras_de_opciones();
			printf(" Elija una opcion...\n 1.Agregar categorías \n 2.Ingresar palabras \n 3.Mostrar categorías alfabéticamente \n 4.Mostrar palabras ordenadas por cantidad de caracteres de forma decreciente \n 5.Mostrar palabras por categoría ordenadas alfabeticamente\n 6.Jugar ");
			barras_de_opciones();
			printf("\n Ingrese un numero: ");
			fflush(stdin);
			scanf("%c",&eleccion);
			if((eleccion=='6') && (cantpalabras==0)){
				printf(" Debe ingresar al menos una palabra para jugar\n");
				eleccion='0';
				system("PAUSE");
			}
			switch(eleccion){
				case '1':
					if(ML<CATEGORIABASE){
						ingresar_categorias(Vcategorias,categoriainicial,&ML);
						break;
					}
					else{
						printf("\n No puede ingresar mas categorias\n");
						system("PAUSE");
						break;
					}
				case '2':
				if(ML>=1){
						ingresar_palabras(Vpalabras, Vpista, Vcate, Vcategorias, ML,&cantpalabras);
					}
					else {
						printf("\n Debe ingresar al menos una categoria\n");
					}
					system("PAUSE");
					break;
				case '3':
					if(ML>=2){
						ordenar_mostrar_alfabeticamente(Vcategorias,ML);
					}
					else{
						printf("\n Debe ingresar al menos 2 categorias\n");
					}
					system("PAUSE");
					break;
				case '4':
					if(cantpalabras>=2){
						ordenar_mostrar_palabras(Vpalabras,cantpalabras);
					}
					else{
						printf("\n Debe ingresar al menos 2 palabras\n");
					}
					system("PAUSE");
					break;
				case '5':
					if(cantpalabras>=1){
						mostrar_palabras_categoria(Vcategorias,Vcate,Vpalabras,ML,cantpalabras);
					}
					else{
						printf("\n Debe ingresar al menos 1 palabra\n");
					}
					system("PAUSE");
					break;
				case '6':
					iniciar_partida(Vcategorias,Vpalabras,Vpista,Vcate,cantpalabras);
					break;
				}
			if((eleccion>'6') || (eleccion<'1')){
				printf(" La eleccion introducida no es valida\n");
				system("PAUSE");
			}
		system("cls");
		}
		return 0;
	}

