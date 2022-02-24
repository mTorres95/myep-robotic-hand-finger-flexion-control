#include "uartInterpreter.h"

void InterpretaComando(char comando[]){
	int aux;
/*	int move = 0;*/
	switch(comando[0]){
		case 'A':
 		 	switch (comando[1]) {
				case 'm':
					if(comando[2]){
						aux = atoi(&comando[2]);
						if (aux<max_degree && aux>=-90.0){
							min_degree = aux;
						}
						if (!(min_degree<=init_degree)){
							init_degree = min_degree;
							printf("Initial degree: %d\r\n", (int)init_degree);
						}
					}
					printf("Minimum degree: %d\r\n", (int)min_degree);
					break;
				case 'M':
					if(comando[2]){
						aux = atoi(&comando[2]);
						if (aux>min_degree && aux<=90.0){
							max_degree = aux;
						}
						if (!(max_degree>=init_degree)){
							init_degree = max_degree;
							printf("Initial degree: %d\r\n", (int)init_degree);
						}
					}
					printf("Maximum degree: %d\r\n", (int)max_degree);
					break;
 				case 'i':
 					if(comando[2]){
	 					aux = atoi(&comando[2]);
	 					if (aux<=max_degree && aux>=min_degree){
		 					init_degree = aux;
	 					}
 					}
 					printf("Initial degree: %d\r\n", (int)init_degree);
 					break;
				default:
					printf("The command wasn't recognized, try using the help command (:h).\r\n");
					break;
		 	} 
		 	break;
		case 'F':
			switch(comando[1]){
				case '1':
					if(comando[2]){
						aux = atoi(&comando[2]);
						if(aux>=min_degree && aux<=max_degree){
							printf("Finger 1, degree: %d\r\n", aux);
							finger1_degree(aux);
						} else printf("Solo grados entre %d y %d\r\n",(int)min_degree,(int)max_degree);
					} else {
						get_degrees_TC1(1,0);
					}
					break;
				case '2':
					if(comando[2]){
						aux = atoi(&comando[2]);
						if(aux>=min_degree && aux<=max_degree){
							printf("Finger 2, degree: %d\r\n", aux);
							finger2_degree(aux);
						} else printf("Solo grados entre %d y %d\r\n",(int)min_degree,(int)max_degree);						
					} else {
						get_degrees_TC1(0,1);
						}
					break;
				case '3':
					if(comando[2]){
						aux = atoi(&comando[2]);
						if(aux>=min_degree && aux<=max_degree){
							printf("Finger 3, degree: %d\r\n", aux);
							finger3_degree(aux);
						} else printf("Solo grados entre %d y %d\r\n",(int)min_degree,(int)max_degree);
					}else {
						get_degrees_TC0(1,0);
					}
					break;
				case '4':
					if(comando[2]){
						aux = atoi(&comando[2]);
						if(aux>=min_degree && aux<=max_degree){
							printf("Finger 4, degree: %d\r\n", aux);
							finger4_degree(aux);
						} else printf("Solo grados entre %d y %d\r\n",(int)min_degree,(int)max_degree);
					}else {
						get_degrees_TC0(0,1);
					}
					break;
				case '5':
					if(comando[2]){
						aux = atoi(&comando[2]);
						if(aux>=min_degree && aux<=max_degree){
							printf("Finger 5, degree: %d\r\n", aux);
							finger5_degree(aux);
						} else printf("Solo grados entre %d y %d\r\n",(int)min_degree,(int)max_degree);
					}else {
						get_degrees_TC2(1,0);
					}
					break;				
				default:
					printf("Error\r\n");
					break;
			}
			break;
// 		case 'M':
// 			printf("Moving hand...\r\n");  // podria ser cerrar y abrir toda la mano, cerrar y abrir dedo por dedo..
// 			move = 1;
// 			while(move){
// 				for(int i=min_degree; i<max_degree; i++){
// 					hand_degree(i);
// 				}
// 				for(int i=max_degree; i>min_degree; i--){
// 					hand_degree(i);
// 				}
// 			}
// 			break;
// 		case 'S':
// 			printf("STOP\r\n");
// 			move = 0;
// 			break;
		case 'C':
			printf("Closing hand...\r\n");
			hand_degree(min_degree);
			break;
		case 'O':
			printf("Opening hand...\r\n");
			hand_degree(max_degree);
			break;
		case 'R':
			printf("Reset to initial position.\r\n");
			hand_degree(init_degree);
			break;
		case 'h':
			help();
			break;
		default:
			printf("The command wasn't recognized, try using the help command (:h).\r\n");
			break;
	}
}

void help(){
	printf("\r\n================= Options: ================= \r\n");
	printf(":Amnn	--> Set minimum aceptable degree\r\n");
	printf(":AMnn	--> Set maximum aceptable degree\r\n");
	printf(":Ainn	--> Set initial degree\r\n");
	//printf(":Dnn	--> Hand flexion degree, nn is degrees [%d, %d]\r\n", (int)min_degree, (int)max_degree);
	printf(":Fxnn	--> Finger flexion degree, x is finger\r");
	printf("         [1,5], nn is degrees [%d, %d]\r\n", (int)min_degree, (int)max_degree);
	//printf(":M		--> Move hand indefinitely\r\n");
	//printf(":S		--> Stop movement\r\n");
	printf(":C		--> Close hand\r\n");
	printf(":O		--> Open hand\r\n");
	printf(":R		--> Reset hand\r\n");
	printf(":h		--> Show help\r\n\r\n");
}
