#include <stdio.h> // Entrada y salida.
#include <stdlib.h> // Memoria dinamica.
#include <unistd.h> // Uso de fork().
#include <sys/wait.h>  // Constantes simbolicas (waitpid(), wait(), etc).
#include <sys/types.h> // Uso de tipos de datos pid_t.
#include <string.h> // Manejo de strings.




/* ------------------------- MAIN ------------------------- */

int main(int argc, char **argv) {

    extern char *optarg; // Almacena los argumentos.
    extern int optind; // Indica el numero de argumentos
	int in, err = 0; // Entero in para iterar getopt y bandera err para notificar error.
    // Banderas para notificar cuando falte un argumento.
    int iflag = 0, oflag = 0, dflag = 0, pflag = 0, nflag = 0, bflag = 0;
    // Variables para almacenar los argumentos (anio de inicio del juego y precio minimo del juego).
    int d = 0, p = 0, n = 0; 

    /*
    _____________________
    Entrada por terminal
    ---------------------
    -i filename: archivo de entrada
    -o filename: archivo de salida
    -d: año de inicio del juego
    -p: precio minimo del juego
    -n: cantidad de workers a generar
    -b: bandera que indica si se entregan los resultados por consola (opcional)

    -i -o -d -p -n 
    -i -o -d -p -n -b
    ____________________
    */
    
    // Variables para almacenar los nombres de archivo ingresados por consola.
    char *filename_in = NULL;
    char *filename_out = NULL;

    printf("\n comienzo del progrema \n");
    // Se define el uso idoneo al momento de ejecutar.
    char uso[] = "Uso: %s -i \"nombre_archivo_entrada\" -o \"nombre_archivo_salida\" -d \"anio_inicio\" -p \"precio_min\" -n \"workers\" \n ";

    // Uso del getopt, se trabaja en el ciclo while la recepcion de elementos ingresados por consola.
    while((in = getopt(argc, argv, "i:o:d:p:n:b")) != -1) 
        switch(in) {
            case 'i': // Archivo de entrada.
                iflag = 1;
                filename_in = optarg;
                break;

            case 'o': // Archivo de salida.
                oflag = 1;
                filename_out = optarg;
                break;

            case 'd': // Anio de lanzamiento del juego.
                dflag = 1;
                sscanf(optarg, "%d", &d);
                break;

            case 'p': // Precio minimo del juego.
                pflag = 1;
                sscanf(optarg, "%d", &p);
                break;
            
            case 'n': // numero de workers a generar.
                nflag = 1;
                sscanf(optarg, "%d", &n);
                break;

            case 'b': // Bandera para mostrar resultados por consola.
                bflag = 1;
                break;

            case '?': // En caso de encontrar un error, se modifica el valor usado como bandera.
				err = 1;
				break;
		    }
        
            // se verifica si se escribio bien (falta de parametros).
            if(iflag == 0){
                fprintf(stderr, "%s: Falta parametro -i \n", argv[0]);
                fprintf(stderr, uso, argv[0]);
                exit(1);
            }

            if(oflag == 0){
                fprintf(stderr, "%s: Falta parametro -o \n", argv[0]);
                fprintf(stderr, uso, argv[0]);
                    exit(1);
            }

            if(dflag == 0){
                fprintf(stderr, "%s: Falta parametro -d \n", argv[0]);
                fprintf(stderr, uso, argv[0]);
                    exit(1);
            }


            if(pflag == 0){
                fprintf(stderr, "%s: Falta parametro -p \n", argv[0]);
                fprintf(stderr, uso, argv[0]);
                exit(1);
            }


            if(nflag == 0){
                fprintf(stderr, "%s: Falta parametro -n \n", argv[0]);
                fprintf(stderr, uso, argv[0]);
                    exit(1);
            }

            // Se verifica correcta sistaxis.
            if(optind < argc){
                for(;optind<argc;optind++){
                    printf("Argumento no permitido:\"%s\"\n", argv[optind]);
                }
                printf("La sistaxis es: -i \"nombre_archivo_entrada\" -o \"nombre_archivo_salida\" -d \"anio_inicio\" -p \"precio_min\" -n \"workers\" \n ");
                exit(1);
            }

            // Se imprimen errores.
            if(err){
                fprintf(stderr, uso, argv[0]);
                exit(1);
            } 


    // Verificar si los valores ingresados son correctos.
    if(d <= 0) {
        fprintf(stderr, "%s: El numero del anio debe ser positivo\n", argv[0]);
        exit(1);
    }

    if(p <= 0){
        fprintf(stderr, "%s: El precio del juego debe ser positivo\n", argv[0]);
        exit(1);
    }

    if(n <= 0){
        fprintf(stderr, "%s: El numero de workers debe ser positivo\n", argv[0]);
        exit(1);
    }




    //// ******************* Fin getopt ******************* ////


    pid_t child_pid;
    int status;

    //srand(NULL);

    printf("\n -i: %s", filename_in);
    printf("\n -o: %s", filename_out);
    printf("\n -d: %d", d);
    printf("\n -p: %d", p);
    printf("\n -n: %d", n);

    // SI ES EL PADRE
    if ((child_pid = fork()) != 0){
        
        int pid2 = wait(&status);


    } else { // SI ES HIJO, INICIO DEL BROKER   

        char arg1[20], arg2[20], arg3[20], arg4[20], arg5[20];
        sprintf(arg1, "%s", filename_in);
        sprintf(arg2, "%s", filename_out);
        sprintf(arg3, "%d", d);
        sprintf(arg4, "%d", p);
        sprintf(arg5, "%d", n);
        
        char *const argv2[] = {arg1,arg2,arg3,arg4,arg5,NULL};
        execv("./broker", argv2);

    }
  
    printf("\n fin del programa principal \n");
    return(0);

}











