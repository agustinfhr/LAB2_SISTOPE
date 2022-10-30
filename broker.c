#include <stdio.h> // Entrada y salida.
#include <stdlib.h> // Memoria dinamica.
#include <unistd.h> // Uso de fork().
#include <sys/wait.h>  // Constantes simbolicas (waitpid(), wait(), etc).
#include <sys/types.h> // Uso de tipos de datos pid_t.
#include <string.h> // Manejo de strings.

#include "fbroker.h" // Funciones del broker.
#include "juego.h"  // Se inclute la estructura definida para los juegos.
#include "year.h"  // Se inclute la estructura definida para los anios.


// definicion para los pipes
#define LECTURA 0
#define ESCRITURA 1


int main(int argc, char* argv[]) {

    printf("\n Argumento i %s", argv[0]);
    printf("\n Argumento o %s", argv[1]);
    printf("\n Argumento d %s", argv[2]);
    printf("\n Argumento p %s", argv[3]);
    printf("\n Argumento n %s", argv[4]);   

    int num_work = atoi(argv[4]);
    printf("\n num work %d", num_work);  
    

    int proceso = 0;

    // Se forman las pipes
    int** fd = (int**)malloc(sizeof(int*)*num_work);  // Padre => Hijo
    int** fd2 = (int**)malloc(sizeof(int*)*num_work); // Hijo => Padre


    // Definicion de pipes siendo esto una matriz que [i][j], siendo por ejemplo [0][j]
    // la pipe del primer hijo 
    for(int i = 0; i < num_work;i++) {
      fd[i] = (int*)malloc(sizeof(int)*2);
      fd2[i] = (int*)malloc(sizeof(int)*2);
    }

    juego * juegos = (juego*)malloc(sizeof(juego));

    // Se llama a la funcion encargada de leer el archivo de entrada, para posteriormente guardar
    // esa informacion en el arreglo creado previamente.
    juegos = leerArchivoEntrada(argv[0]);
    
    int numAnios;
    numAnios = calcularAnios(juegos);
    
    printf("\n numAnios %d", numAnios);


    // se crea el buffer
    year * buffer = (year*)malloc(sizeof(year)*numAnios);

    // se definen variables para almacenar el pid tanto del padre broker como del hijo worker
    pid_t child_pid, parent_pid;

       

    for (proceso = 0; proceso < num_work; proceso++)
    {
        // se crean los pipes
        pipe(fd[proceso]);
        pipe(fd2[proceso]);

        // SI es el padre broker
        if ((child_pid = fork()) != 0)
        {
            // se cierran los extremos que no se utilizan
            //close(fd[proceso][LECTURA]);
            //close(fd2[proceso][ESCRITURA]);

        } else { // SI es hjo worker

            // se cierran los extremos que no se utilizan
            //close(fd[proceso][ESCRITURA]);
            //close(fd2[proceso][LECTURA]);
            
            //char numAniosArg[10];
            //sprintf(numAniosArg, "%d", numAnios);
            //char *const argv2[] = {numAniosArg,NULL};
            
            //dup2(fd2[proceso][ESCRITURA], STDOUT_FILENO);
    
            printf("\n proceso %d", proceso);
            //execv("./worker", argv2);

            break;
            
        }
        
    }


    if (child_pid != 0) // Padre 
    {
        //FILE *archivo = fopen(argv[0], "r");
        FILE *lineas = fopen(argv[0], "r");

        int random = 0;
        int nJuegos = 0; 
        char c;

        for (c = getc(lineas); c != EOF; c = getc(lineas)){
            if (c == '\n') {
                nJuegos = nJuegos + 1;
            
            }
        }
        /*
        for (int i = 0; i < nJuegos; i++)
        {
            close(fd[random][ESCRITURA]);
            close(fd2[random][LECTURA]);
            buffer[0].numAnio = 99;
        }
        */
        close(fd[random][LECTURA]);
        close(fd2[random][ESCRITURA]);
        buffer[0].numAnio = 99;
        printf("\n valor buffer %d\n", buffer[0].numAnio);

        int posicion = 0;
        juego * linea = (juego*)malloc(sizeof(juego));

        for (int i = 0; i < nJuegos; i++)
        {
          
          // Para cada linea leida, se pasa la informacion al
          // proceso elegido aleatoriamente.
          
          // random = rand()%cantidadHebras;

          linea = leerArchivoPorLinea(argv[0],posicion);

          write(fd[random][ESCRITURA], &buffer[0], sizeof(year));
          fflush(stdout);

          // padre lee los datos escritos por el hijo 
          read(fd2[random][LECTURA], &buffer[0], sizeof(year));
          fflush(stdin);   

          posicion = linea[0].posicion;

        }
        /*
        write(fd[random][ESCRITURA], &buffer[0], sizeof(year));
        fflush(stdout);

        // padre lee los datos escritos por el hijo 
        read(fd2[random][LECTURA], &buffer[0], sizeof(year));
        fflush(stdin);
        */
        /*
        int posicion = 0;
        juego * linea = (juego*)malloc(sizeof(juego));
        linea = leerArchivoPorLinea(argv[0],posicion);
        */
        /*
        printf("\n id: %d \n", linea[0].id);
        printf("\n nombre: %s \n", linea[0].nombre);
        printf("\n restriccionEdad: %d \n", linea[0].restriccionEdad);
        printf("\n precio: %.2f \n", linea[0].precio);
        printf("\n prox: %s \n", linea[0].prox);
        printf("\n fecha: %d \n", linea[0].fecha);
        printf("\n gratis: %s \n", linea[0].gratis);
        printf("\n windows: %s \n", linea[0].windows);
        printf("\n mac: %s \n", linea[0].mac);
        printf("\n linux: %s \n", linea[0].lynux);

        posicion = linea[0].posicion;
        
        linea = leerArchivoPorLinea(argv[0],posicion);

        printf("\n id: %d \n", linea[0].id);
        printf("\n nombre: %s \n", linea[0].nombre);
        printf("\n restriccionEdad: %d \n", linea[0].restriccionEdad);
        printf("\n precio: %.2f \n", linea[0].precio);
        printf("\n prox: %s \n", linea[0].prox);
        printf("\n fecha: %d \n", linea[0].fecha);
        printf("\n gratis: %s \n", linea[0].gratis);
        printf("\n windows: %s \n", linea[0].windows);
        printf("\n mac: %s \n", linea[0].mac);
        printf("\n linux: %s \n", linea[0].lynux);
        */

        //fclose(archivo);    
        fclose(lineas);
        

    } else { // hijo
        
        close(fd[proceso][ESCRITURA]);
        close(fd2[proceso][LECTURA]);

        //read(fd[proceso][LECTURA], &buffer[0], sizeof(year));
        //fflush(stdin);

        char numAniosArg[10];
        sprintf(numAniosArg, "%d", numAnios);
        char *const argv2[] = {numAniosArg,NULL};

        dup2(fd[proceso][LECTURA], STDIN_FILENO);    
        dup2(fd2[proceso][ESCRITURA], STDOUT_FILENO);
    
        //printf("\n proceso %d", proceso);
        execv("./worker", argv2);

        fflush(stdout);
        fflush(stdin);
        wait(NULL);

    }

    // El broker leerá el archivo de entrada linea por linea y mediante
    // un randomizer elegirá a q worker corresponde dicha linea
    // Mientras no se lea todo el archivo, se elegirá en cada linea
    // un worker (aleatoriamente) para trabajar dicha linea de codigo
    // Cuando no queden lineas por leer, el broker avisará a cada
    // worker con la palabra "FIN", indicando q no deben esperar más
    // lineas del broker.

    
    

    if (child_pid != 0) // padre 
    {
        printf("\n valor buffer %d\n", buffer[0].numAnio);
    }


    


    printf("\n fin del progrema broker\n");
    return(0);

}

