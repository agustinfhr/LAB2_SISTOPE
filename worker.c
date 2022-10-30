#include <stdio.h> // Entrada y salida.
#include <stdlib.h> // Memoria dinamica.
#include <unistd.h> // Uso de fork().
#include <sys/wait.h>  // Constantes simbolicas (waitpid(), wait(), etc).
#include <sys/types.h> // Uso de tipos de datos pid_t.
#include <string.h> // Manejo de strings.

#include "year.h"  // Se inclute la estructura definida para los anios.


int main(int argc, char* argv[]) {

    pid_t parent_pid;
    parent_pid = getpid();

    printf("\n mi pid %d",parent_pid);

    int numAnios = atoi(argv[0]);
    
    year * years = (year*)malloc(sizeof(year)*numAnios);

    for (int i = 0; i < 3; i++)
    {
        read(STDIN_FILENO, years, sizeof(year));
        fflush(stdin);

        years[0].numAnio = years[0].numAnio + 1;

        write(STDOUT_FILENO, years, sizeof(year));
        fflush(stdout);
    }
    
    /*
    read(STDIN_FILENO, years, sizeof(year));
    fflush(stdin);

    years[0].numAnio = 100;

    write(STDOUT_FILENO, years, sizeof(year));
    */
    
    printf("\n fin del progrema worker\n");
    return(0);



}










