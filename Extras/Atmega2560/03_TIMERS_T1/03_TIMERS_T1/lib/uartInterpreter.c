#include "uartInterpreter.h"

void InterpretaComando(char comando[]){
	int aux;
	switch(comando[0]){
		case 'H':
			homing();
			break;
		case 'D':  // acepta grados o porcentaje de flexion? Podria hacer ambos (los grados deberian limitarse)
			if(comando[1]){
				aux = atoi(&comando[1]);
				printf("Flexion degree: %d\r\n", aux);
			}
			break;
		case 'F':
			switch(comando[1]){
				case '1':
					if(comando[2]){
						aux = atoi(&comando[2]);
						if(aux>=-90.0 && aux<=90.0){
							printf("Finger 1, degree: %d\r\n", aux);
							set_degrees_TC1(aux,-180.0,-180.0);
						} else printf("Solo grados entre -90.0° y +90.0°\r\n");
					} else {
						get_degrees_TC1(1,0,0);
					}
					break;
				case '2':
					if(comando[2]){
						aux = atoi(&comando[2]);
						if(aux>=-90.0 && aux<=90.0){
							printf("Finger 2, degree: %d\r\n", aux);
							set_degrees_TC1(-180.0,aux,-180.0);
						}else printf("Solo grados entre -90.0° y +90.0°\r\n");						
					}else {
						get_degrees_TC1(0,1,0);
						}
					break;
				case '3':
					if(comando[2]){
						aux = atoi(&comando[2]);
						if(aux>=-90.0 && aux<=90.0){
							printf("Finger 3, degree: %d\r\n", aux);
							set_degrees_TC1(-180.0,-180.0,aux);
						} else printf("Solo grados entre -90.0° y +90.0°\r\n");
					} else {
						get_degrees_TC1(0,0,1);
					}
					break;
				case '4':
					if(comando[2]){
						aux = atoi(&comando[2]);
						if(aux>=-90.0 && aux<=90.0){
							printf("Finger 4, degree: %d\r\n", aux);
							set_degrees_TC3(aux,-180.0,-180.0);
						}else printf("Solo grados entre -90.0° y +90.0°\r\n");
					}else {
						get_degrees_TC3(1,0,0);
					}
					break;
				case '5':
					if(comando[2]){
						aux = atoi(&comando[2]);
						if(aux>=-90.0 && aux<=90.0){
							printf("Finger 5, degree: %d\r\n", aux);
							set_degrees_TC3(-180.0,aux,-180.0);
						} else printf("Solo grados entre -90.0° y +90.0°\r\n");
					} else {
						get_degrees_TC3(0,1,0);
					}
					break;
				case '6':
					if(comando[2]){
						aux = atoi(&comando[2]);
						if(aux>=-90.0 && aux<=90.0){
							printf("Finger 6, degree: %d\r\n", aux);
							set_degrees_TC3(-180.0,-180.0,aux);
						}else printf("Solo grados entre -90.0° y +90.0°\r\n");
					}else {
						get_degrees_TC3(0,0,1);
					}
					break;
				default:
					printf("Error, ver ayuda del comando Fxnn\r\n");
					break;
			}
			break;
		case 'M':
			printf("Moving hand...\r\n");  // podria ser cerrar y abrir toda la mano, cerrar y abrir dedo por dedo..
			
			break;
		case 'S':
			printf("STOP\r\n");
			
			break;
		case 'C':
			printf("Closing hand...\r\n");
			
			break;
		case 'O':
			printf("Opening hand...\r\n");
			
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
	printf("==== Options: ==== \r\n");
	printf(":H     --> Homing\r\n");
	printf(":Dnn   --> Hand flexion degree, where nn goes from -90° to 90°\r\n");
	printf(":Fxnn  --> Finger flexion degree, where x is number of finger and nn goes from -90° to 90°\r\n");
	printf(":M     --> Move hand indefinitely\r\n");
	printf(":S     --> Stop movement\r\n");
	printf(":C     --> Close hand\r\n");
	printf(":O     --> Open hand\r\n");
	printf(":h     --> Show help\r\n\n");
}
