#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "pilas.h"
#include "graficos.h"

// Valores

char As[] 	  = "A";
char dos[] 	  = "2" ;
char tres[]   = "3" ;
char cuatro[] = "4" ;
char cinco[]  = "5" ;
char seis[]   = "6" ;
char siete[]  = "7" ;
char ocho[]   = "8" ;
char nueve[]  = "9" ;
char diez[]   = "10";
char J[] 	  = "J" ;
char Q[] 	  = "Q" ;
char K[]	  = "K" ;

// Imágenes

char corazones[] = "Corazones";
char espadas[]   = "Espadas";
char diamantes[] = "Diamantes";
char treboles[]  = "Treboles";

// Estructura del jugador

typedef struct jugador{
	int suma;
	int num_cartas;
	int ace;
	char arreglo_cartas[100];
}PLAYER;

void barajar_cartas(PILA **baraja){
	int random_c, n_cartas = 0, random_i, temp_v;
	char temp_carta[] = {12,12,12,12,12,12,12,12,12,12,12,12,12};
				//  A, 2, 3, 4, 5, 6, 7, 8, 9,10, J, Q, K
	char temp_img[13][4] = {
		{3, 3, 3, 3},
		{3, 3, 3, 3},
		{3, 3, 3, 3},
		{3, 3, 3, 3},
		{3, 3, 3, 3},
		{3, 3, 3, 3},
		{3, 3, 3, 3},
		{3, 3, 3, 3},
		{3, 3, 3, 3},
		{3, 3, 3, 3},
		{3, 3, 3, 3},
		{3, 3, 3, 3},
		{3, 3, 3, 3}
	};

	while(!isEmpty(*baraja)){
		pop(baraja);
	}
	while(n_cartas < 156){
		random_c = rand() % 13;
		random_i = rand() % 4;
		if(temp_carta[random_c] != 0 && temp_img[random_c][random_i] != 0){
			temp_carta[random_c] -= 1;
			temp_img[random_c][random_i] -= 1;
			temp_v = random_c;
			//if(random_i == 0) 						// Corazones
			if(random_i == 1) temp_v += 100;			// Espadas
			else if(random_i == 2) temp_v += 200;		// Treboles
			else if(random_i == 3) temp_v += 300;		// Diamantes
			push(baraja, temp_v);
			n_cartas++;
		}
	}
}

void repartir_carta(PILA **baraja, char *valor, char *imagen){
	int temp = top(*baraja);

	if(temp < 100) 		strncpy(imagen, corazones, strlen(corazones)), imagen[strlen(corazones)] = '\0';
	else if(temp < 200) strncpy(imagen, espadas, strlen(espadas)), imagen[strlen(espadas)] = '\0', temp-= 100;
	else if(temp < 300) strncpy(imagen, treboles, strlen(treboles)), imagen[strlen(treboles)] = '\0', temp-= 200;
	else if(temp < 400) strncpy(imagen, diamantes, strlen(diamantes)), imagen[strlen(diamantes)] = '\0', temp-= 300;

	if(temp == 0) 	    strncpy(valor, As,     strlen(As)),     valor[strlen(As)]     = '\0';
	else if(temp == 1)  strncpy(valor, J,      strlen(J)),      valor[strlen(J)]      = '\0';
	else if(temp == 2)  strncpy(valor, dos,    strlen(dos)),    valor[strlen(dos)]    = '\0';
	else if(temp == 3)  strncpy(valor, tres,   strlen(tres)),   valor[strlen(tres)]   = '\0';
	else if(temp == 4)  strncpy(valor, cuatro, strlen(cuatro)), valor[strlen(cuatro)] = '\0';
	else if(temp == 5)  strncpy(valor, cinco,  strlen(cinco)),  valor[strlen(cinco)]  = '\0';
	else if(temp == 6)  strncpy(valor, seis,   strlen(seis)),   valor[strlen(seis)]   = '\0';
	else if(temp == 7)  strncpy(valor, siete,  strlen(siete)),  valor[strlen(siete)]  = '\0';
	else if(temp == 8)  strncpy(valor, ocho,   strlen(ocho)),   valor[strlen(ocho)]   = '\0';
	else if(temp == 9)  strncpy(valor, nueve,  strlen(nueve)),  valor[strlen(nueve)]  = '\0';
	else if(temp == 10) strncpy(valor, diez,   strlen(diez)),   valor[strlen(diez)]   = '\0';
	else if(temp == 11) strncpy(valor, Q,      strlen(Q)),      valor[strlen(Q)]      = '\0';
	else if(temp == 12) strncpy(valor, K,     strlen(K)),       valor[strlen(K)]      = '\0';
	pop(&(*baraja));
}

int valor(char *valor_c, int valor_int){
	if(strcmp(valor_c, As) == 0){
		valor_int = 11;
	}
	else if(strcmp(valor_c, J) == 0 || strcmp(valor_c, Q) == 0 || strcmp(valor_c, K) == 0)
		valor_int = 10;
	else
		valor_int = atoi(valor_c);
	return valor_int;
}

int convertir_a_imagenes(char *imagen, int imagen_int){
	if(strcmp(imagen, corazones) == 0) imagen_int = 03, textcolor(LIGHTRED);
	else if(strcmp(imagen, espadas) == 0) imagen_int = 06, textcolor(LIGHTGRAY);
	else if(strcmp(imagen, diamantes) == 0) imagen_int = 04, textcolor(LIGHTRED);
	else if(strcmp(imagen, treboles) == 0) imagen_int = 05, textcolor(LIGHTGRAY);
	return imagen_int;
}

void empezar_juego(PILA **baraja, PLAYER *jugador1, PLAYER *jugador2, PLAYER *jugador3, PLAYER *casa, int valor_int,
				char *valor_c, char *imagen, int num_jugadores)
{
	int i;
	int imagen_int;
	for(i = 0; i < 2; i++){
		repartir_carta(&(*baraja), valor_c, imagen);
		valor_int = valor(valor_c, valor_int);
		jugador1->suma += valor_int;
		jugador1->num_cartas++;

		// printf("Jugador1: ");
		if(valor_int == 11) jugador1->ace = 1;
		imagen_int = convertir_a_imagenes(imagen, imagen_int);
		if(i == 0)
			gotoxy(2, 8);
		else
			gotoxy(2, 10);
		printf("%s%c\n", valor_c, imagen_int);
		textcolor(WHITE);



		if(num_jugadores > 1){
			repartir_carta(&(*baraja), valor_c, imagen);
			valor_int = valor(valor_c, valor_int);
			jugador2->suma += valor_int;
			jugador2->num_cartas++;
			// printf("Jugador2: ");
			if(valor_int == 11) jugador2->ace = 1;
			imagen_int = convertir_a_imagenes(imagen, imagen_int);
			if(i == 0)
				gotoxy(9, 20);
			else if(i == 1)
				gotoxy(13, 20);
			printf("%s%c\n", valor_c, imagen_int);
			textcolor(WHITE);
		}

		if(num_jugadores > 2){
			repartir_carta(&(*baraja), valor_c, imagen);
			valor_int = valor(valor_c, valor_int);
			jugador3->suma += valor_int;
			jugador3->num_cartas++;
			// printf("Jugador3: ");
			if(valor_int == 11) jugador3->ace = 1;
			imagen_int = convertir_a_imagenes(imagen, imagen_int);
			if(i == 0)
				gotoxy(31, 8);
			else
				gotoxy(31, 10);
			printf("%s%c\n", valor_c, imagen_int);
			textcolor(WHITE);
		}

		repartir_carta(&(*baraja), valor_c, imagen);
		valor_int = valor(valor_c, valor_int);
		casa->suma += valor_int;
		casa->num_cartas++;
		// printf("Casa:     ");
		if(valor_int == 11) casa->ace = 1;
		imagen_int = convertir_a_imagenes(imagen, imagen_int);
		if(i == 0)
			gotoxy(9, 2);
		else if(i == 1)
			gotoxy(13, 2);
		printf("%s%c", valor_c, imagen_int);
		textcolor(WHITE);
	}
}

void imprimir(PLAYER *jugador1, PLAYER *jugador2, PLAYER *jugador3, PLAYER *casa, int num_jugadores){
	gotoxy(36, 0);
	printf("Suma J1: ");
	gotoxy(36, 1);
	printf("%d", jugador1->suma);

	if(num_jugadores > 1){
		gotoxy(36, 3);
		printf("Suma J2: ");
		gotoxy(36, 4);
		printf("%d", jugador2->suma);
	}
	if(num_jugadores > 2){
		gotoxy(36, 6);
		printf("Suma J3: ");
		gotoxy(36, 7);
		printf("%d", jugador3->suma);
	}

	gotoxy(36, 9);
	printf("Suma casa: ");
	gotoxy(36, 10);
	printf("%d", casa->suma);
}

void imprimir_mesilla(){
	int i = 0;
	int j = 0;
	textcolor(GREEN);
	printf("%c", 201);
	for(; i< 33; i++){
		printf("%c", 205);
	}
	printf("%c\n", 187);

	 for(; j < 21; j++){
		 printf("%c", 186);
		 for(i = 0; i < 33; i++)
		 	printf(" ");
		 printf("%c\n", 186);
	}
	printf("%c", 200);
	for(i = 0; i< 33; i++){
		printf("%c", 205);
	}
	printf("%c\n", 188);
	textcolor(WHITE);
}


int main(){
	srand(time(NULL));
	PILA *baraja = NULL;
	PLAYER jugador1;
	jugador1.num_cartas = 0;
	jugador1.suma = 0;
	jugador1.ace = 0;

	PLAYER jugador2;
	jugador2.num_cartas = 0;
	jugador2.suma = 0;
	jugador2.ace = 0;

	PLAYER jugador3;
	jugador3.num_cartas = 0;
	jugador3.suma = 0;
	jugador3.ace = 0;

	PLAYER casa;
	casa.num_cartas = 0;
	casa.suma = 0;
	casa.ace = 0;

	char valor_c[3];
	char imagen[10];
	char op = 'y';
	int valor_int = 0, imagen_int;
	int win = 0;
	barajar_cartas(&baraja);
	gotoxy(0,23);
	int num_jugadores;
	textcolor(WHITE);
	printf("De cuantos jugadores? ");
	fflush(stdin);
	scanf("%d", &num_jugadores);

	while(!isEmpty(baraja)){

		gotoxy(0,0);
		imprimir_mesilla();
		empezar_juego(&baraja, &jugador1, &jugador2, &jugador3, &casa, valor_int, valor_c, imagen, num_jugadores);
		imprimir(&jugador1, &jugador2, &jugador3, &casa, num_jugadores);



		while(op != 'n' && jugador1.num_cartas < 5 && jugador1.suma <= 21){
			gotoxy(36, 0);
			printf("Suma J1: ");
			gotoxy(36, 1);
			printf("%d", jugador1.suma);
			gotoxy(54, 23);
			printf(" ");
			gotoxy(0, 23);
			printf("Turno del jugador 1: Si desea otra carta presione 'y'.");
			fflush(stdin);
			scanf("%c", &op);

			if(op == 'y'){
				repartir_carta(&baraja, valor_c, imagen);
				valor_int = valor(valor_c, valor_int);
				jugador1.suma += valor_int;
				jugador1.num_cartas++;
				if(valor_int == 11) jugador1.ace++;
				if(jugador1.suma > 21 && jugador1.ace > 0) jugador1.suma -= 10, jugador1.ace--;
				imagen_int = convertir_a_imagenes(imagen, imagen_int);

				if(jugador1.num_cartas == 3)
					gotoxy(2, 12);
				else if(jugador1.num_cartas == 4)
					gotoxy(2, 14);
				else if(jugador1.num_cartas == 5)
					gotoxy(2, 16);

				printf("%s%c", valor_c, imagen_int);
				textcolor(WHITE);
				gotoxy(36, 0);
				printf("Suma J1: ");
				gotoxy(36, 1);
				printf("%d", jugador1.suma);
			}
		}
		op = 'y';

		if(num_jugadores > 1){
			// printf("--------------TURNO DEL JUGADOR 2---------------------\n");
			while(op != 'n' && jugador2.num_cartas < 5 && jugador2.suma <= 21){

				gotoxy(36, 3);
				printf("Suma J2: ");
				gotoxy(36, 4);
				printf("%d", jugador2.suma);
				gotoxy(54, 23);
				printf(" ");
				gotoxy(0, 23);
				printf("Turno del jugador 2: Si desea otra carta presione 'y'.");
				fflush(stdin);
				scanf("%c", &op);
				if(op == 'y'){
					repartir_carta(&baraja, valor_c, imagen);
					valor_int = valor(valor_c, valor_int);
					jugador2.suma += valor_int;
					jugador2.num_cartas++;
					if(valor_int == 11) jugador2.ace++;
					if(jugador2.suma > 21 && jugador2.ace > 0) jugador2.suma -= 10, jugador2.ace--;
					imagen_int = convertir_a_imagenes(imagen, imagen_int);

					if(jugador2.num_cartas == 3)
						gotoxy(17, 20);
					else if(jugador2.num_cartas == 4)
						gotoxy(21, 20);
					else if(jugador2.num_cartas == 5)
						gotoxy(25, 20);

					printf("%s%c", valor_c, imagen_int);
					textcolor(WHITE);
					gotoxy(36, 3);
					printf("Suma J2: ");
					gotoxy(36, 4);
					printf("%d", jugador2.suma);
				}
			}
			op = 'y';
		}

		if(num_jugadores > 2){
			// printf("--------------TURNO DEL JUGADOR 3---------------------\n");
			while(op != 'n' && jugador3.num_cartas < 5 && jugador3.suma <= 21){

				gotoxy(36, 6);
				printf("Suma J3: ");
				gotoxy(36, 7);
				printf("%d", jugador3.suma);
				gotoxy(54, 23);
				printf(" ");
				gotoxy(0, 23);
				printf("Turno del jugador 3: Si desea otra carta presione 'y'.");
				fflush(stdin);
				scanf("%c", &op);
				if(op == 'y'){
					repartir_carta(&baraja, valor_c, imagen);
					valor_int = valor(valor_c, valor_int);
					jugador3.suma += valor_int;
					jugador3.num_cartas++;
					if(valor_int == 11) jugador3.ace++;
					if(jugador3.suma > 21 && jugador3.ace > 0) jugador3.suma -= 10, jugador3.ace--;
					imagen_int = convertir_a_imagenes(imagen, imagen_int);

					if(jugador3.num_cartas == 3)
						gotoxy(31, 12);
					else if(jugador3.num_cartas == 4)
						gotoxy(31, 14);
					else if(jugador3.num_cartas == 5)
						gotoxy(31, 16);

					printf("%s%c", valor_c, imagen_int);
					textcolor(WHITE);
					gotoxy(36, 6);
					printf("Suma J3: ");
					gotoxy(36, 7);
					printf("%d", jugador3.suma);

				}
			}
		}

		//printf("--------------TURNO DE LA CASA---------------------\n");
		// Turno de la casa

		while(((jugador1.suma > casa.suma && jugador1.suma < 22) || (jugador2.suma > casa.suma && jugador2.suma < 22) ||
				(jugador3.suma > casa.suma && jugador3.suma < 22)) && casa.num_cartas <= 5 && casa.suma <= 21)
		{
			gotoxy(36, 9);
			printf("Suma casa: ");
			gotoxy(36, 10);
			printf("%d", casa.suma);
			repartir_carta(&baraja, valor_c, imagen);
			valor_int = valor(valor_c, valor_int);
			casa.suma += valor_int;
			casa.num_cartas++;
			if(valor_int == 11) casa.ace++;
			if(casa.suma > 21 && casa.ace > 0) casa.suma -= 10, casa.ace--;
			imagen_int = convertir_a_imagenes(imagen, imagen_int);

			if(casa.num_cartas == 3)
				gotoxy(17, 2);
			else if(casa.num_cartas == 4)
				gotoxy(21, 2);
			else if(casa.num_cartas == 5)
				gotoxy(25, 2);

			printf("%s%c", valor_c, imagen_int);
			textcolor(WHITE);
			gotoxy(36, 9);
			printf("Suma casa: ");
			gotoxy(36, 10);
			printf("%d", casa.suma);
		}


		imprimir(&jugador1, &jugador2, &jugador3, &casa, num_jugadores);


		gotoxy(51, 0);
		if(jugador1.num_cartas == 5 && jugador1.suma < 22) printf("El jugador 1 gano.\n");
		else if(jugador1.suma > casa.suma && jugador1.suma < 22) printf("El jugador 1 gano.\n");
		else if(jugador1.suma < 22 && casa.suma > 21) printf("El jugador 1 gano.\n");
		else printf("El jugador 1 perdio.\n");

		gotoxy(51, 3);
		if(num_jugadores > 1){
			if(jugador2.num_cartas == 5 && jugador2.suma < 22) printf("El jugador 2 gano.\n");
			else if(jugador2.suma > casa.suma && jugador2.suma < 22) printf("El jugador 2 gano.\n");
			else if(jugador2.suma < 22 && casa.suma > 21) printf("El jugador 2 gano.\n");
			else printf("El jugador 2 perdio.\n");
		}

		gotoxy(51, 6);
		if(num_jugadores > 2){
			if(jugador3.num_cartas == 5 && jugador3.suma < 22) printf("El jugador 3 gano.\n");
			else if(jugador3.suma > casa.suma && jugador3.suma < 22) printf("El jugador 3 gano.\n");
			else if(jugador3.suma < 22 && casa.suma > 21) printf("El jugador 3 gano.\n");
			else printf("El jugador 3 perdio.\n");
		}

		jugador1.num_cartas = 0;
		jugador1.suma = 0;
		jugador1.ace = 0;

		jugador2.num_cartas = 0;
		jugador2.suma = 0;
		jugador2.ace = 0;

		jugador3.num_cartas = 0;
		jugador3.suma = 0;
		jugador3.ace = 0;

		casa.num_cartas = 0;
		casa.suma = 0;
		casa.ace = 0;

		win = 0;
		op = 'y';
		gotoxy(0,24);
		system("PAUSE");
		system("CLS");
	}

	system("PAUSE");
	return 0;
}

