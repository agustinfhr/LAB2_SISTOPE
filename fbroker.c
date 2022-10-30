#include <stdio.h> // entrada y salida
#include <stdlib.h> // memoria dinamica
#include <string.h> // manejo de strings
#include "juego.h" // estructura de datos para los juegos
#include "year.h" // estructura de datos para los anios

//// ******************* Funciones utilizadas por el proceso broker ******************* ////

/*
Entradas: Dos variables int*.
Salidas: -
Descripción: Función que intercambia valores, se crea con el objetivo de utilizarla en la función
            de ordenamiento.
*/
void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 
/*
Entradas: Un arreglo de enteros y un entero.
Salidas: -
Descripción: Función que ordena buscando el valor mínimo dentro del arreglo e intercambio dicho valor con el del
            inicio.
*/
void selectionSort(int arr[], int n)
{
    int i, j, min_idx;
 
    for (i = 0; i < n - 1; i++) {

        // Encontrar el elemento más pequeno en el arreglo.
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
 
        // Intercambiar el elemento mas pequeno con el primer elemento.
        swap(&arr[min_idx], &arr[i]);
    }
}


/*
Entradas: Un arreglo de juegos de tipo juego.
Salidas: Un entero que representa la cantidad de anios distintos que se encuentran en la informacion recibida.
Descripción: Función que se encarga de calcular la cantidad de anios distintos que se encuentran en el arreglo
            de juegos, este valor obtenido ademas sirve para saber la cantidad de procesos hijos a crear.
*/
int calcularAnios(juego *juegos)
{

    // Se definen las variables a utilizar.
    int i;
    int nJuegos = juegos[0].nJuegos;
    int numAnios = 0;
    int anio;
    int aux;
    int ordenar[nJuegos];

    // Se almacenan en el arreglo estatico las fechas (anios) de lanzamiento de los juegos.
    for (i = 0; i < nJuegos; i++)
    {
        ordenar[i] = juegos[i].fecha;
    }
    // Se llama a la funcion encargada de ordenar dichos anios
    selectionSort(ordenar, nJuegos);

    // En este ciclo for se hace el filtro y se conservan los anios que hay pero sin repeticion.
    for (i = 0; i < nJuegos; i++)
    {
        if (anio != ordenar[i])
        {
            anio = ordenar[i];
            numAnios++;
        }
    }

    
    // Se retorna el entero que corresponde a la cantidad de anios distintos que hay en la lista.
    fflush(stdout);
    return(numAnios);

}


/*
Entradas: Un char* (nombre del archivo .csv).
Salidas: Un arreglo de juegos, este arreglo es de tipo juego (la estructura definida para el
        almacenamiento de los mismos).
Descripción: Función que lee el archivo recibido, primeramente hace una lectura para saber la cantidad
            de juegos para posteriormente se procede a leer con el objetivo de guardar dichos valores en
            variables creadas en la funcion para despues ser almacenadas en la posicion que le corresponda
            del arreglo de juegos.
*/
juego* leerArchivoEntrada(char *nombreArchivo){

    // Se hacen dos fopen, uno para el archivo y el otro para saber la cantidad de 
    // lineas que tiene el archivo.
    FILE *archivo = fopen(nombreArchivo, "r");
    FILE *lineas = fopen(nombreArchivo, "r");

    // Se definen las variables a utilizar.
    int nJuegos = 0; 
    int count = 0;
    char c;
    char nombre[100];

    // En caso de no estar el archivo, entonces se informa por una impresion de pantalla.
    if(archivo == NULL) {
        printf("No se encuentra el archivo %s\n", nombreArchivo);
        exit(EXIT_FAILURE);
    }
    // Si el archivo es correcto, se hace una lectura para saber el largo (cantidad de juegos).
    for (c = getc(lineas); c != EOF; c = getc(lineas)){
        if (c == '\n') {
            nJuegos = nJuegos + 1;
            
        }
    }
    // Se aumenta el contador por ultima vez para no "salirse del arreglo" al trabajar en el.
    nJuegos++;

    // Se almacena memoria para los juegos a recibir.
    juego* juegos = (juego*)malloc(sizeof(juego)*nJuegos);
    
    // Se crean las variables necesarias para hacer la lectura del archivo y almacenar
    // dichos valores temporales, en la estructura de datos propuesta.
    int id;
    char nombreAux[100];
    char aux;
    char saltarComa;
    int restriccion;
    float precio;
    char proxAux[6];
    int fecha;
    char gratisAux[10];
    char windowsAux[10];
    char macAux[10];
    int largoNombre;
    char lynux[4];
    
    // Mientras no se han leido y procesado todos los juegos
    while (count < nJuegos){
 
        // Primeramente se guarda el id.
        fscanf(archivo, "%d", &id);
        // Se avanza al siguiente valor a leer.
        fscanf(archivo, "%c", &saltarComa);

        int j,i;
        // En este ciclo while se guarda el nombre del juego en la variable creada.
        // Notar que el iterador llega hasta un tamano arbitrario previamente definido
        // como el largo maximo que puede tener un nombre.
        i = 0;
        while(i < 100){

            fscanf(archivo, "%c", &aux);
            if (aux == saltarComa)
            {
                break;
            }     
            nombreAux[i] = aux;   
            i++;
        }
        // Se almacena el largo del nombre para posterior reserva de memoria al guardar
        // en la estructura de datos y trabajar la variable temporal.
        largoNombre = i;

        for (j = 0; j <= i; j++)
        {
            nombre[j] = nombreAux[j];
        }
        
        // Se leen tanto la restriccion de edad del juego como el precio del mismo.
        fscanf(archivo, "%d,%f", &restriccion, &precio);
        
        // Se avanza al siguiente valor a leer.
        fscanf(archivo, "%c", &saltarComa);

        // Se guarda la variable que representa si el juego saldra proximamente.
        // Nuevamente el ciclo llega hasta un valor previamente definido como largo maximo.
        i = 0;
        while(i < 10){

            fscanf(archivo, "%c", &aux);
            if (aux == saltarComa)
            {
                break;
            }     
            proxAux[i] = aux;   
            i++;
        }
        
        // Se aplica el mismo proceso anterior, se trabaja la variable temporal que almaceno
        // los valores.
        char prox[i];
        for (j = 0; j <= i; j++)
        {
            prox[j] = proxAux[j];
        }

        // Se guarda fecha de lanzamiento.
        fscanf(archivo, "%d", &fecha);

        // Se avanza al siguiente valor a leer.
        fscanf(archivo, "%c", &saltarComa);
        
        // Se hace el mismo proceso hecho previamente, se recibe el dato de si el juego es
        // gratis o no y se deja en una variable auxiliar.
        i = 0;
        while(i < 10){

            fscanf(archivo, "%c", &aux);
            if (aux == saltarComa)
            {
                break;
            }     
            gratisAux[i] = aux;   
            i++;
        }

        // Se trabaja la variable auxiliar y se deja en la varible que se usara la momento
        // de trabajar con la estructura de datos.
        char gratis[i];
        for (j = 0; j <= i; j++)
        {
            gratis[j] = gratisAux[j];
        }

        // Se repite el mismo proceso, ahora para guardar el valor que indica si el juego se
        // encuentra disponible en windows o no.
        i = 0;
        while(i < 10){

            fscanf(archivo, "%c", &aux);
            if (aux == saltarComa)
            {
                break;
            }     
            windowsAux[i] = aux;   
            i++;
        }

        // Se deja el valor almacenado temporalmente en la variable que se usa para trabajar
        // con la estructura de datos.
        char windows[i];
        for (j = 0; j <= i; j++)
        {
            windows[j] = windowsAux[j];
        }

        // Se repite el mismo proceso, ahora para guardar el valor que indica si el juego se
        // encuentra disponible en mac o no.
        i = 0;
        while(i < 10){

            fscanf(archivo, "%c", &aux);
            if (aux == saltarComa)
            {
                break;
            }     
            macAux[i] = aux;   
            i++;
        }
        
        // Se deja el valor almacenado temporalmente en la variable que se usa para trabajar
        // con la estructura de datos.
        char mac[6];
        for (j = 0; j < i; j++)
        {
            mac[j] = macAux[j];
        }

        // Se guarda finalmente el dato que corresponde.
        // Notar que no se hace el mismo proceso que con el dato de windows o mac, esto porque
        // estos valores se encuentran entre ',' mientras que el dato correspondiente a linux
        // se encuentra al final, por tanto, solo se recibe.
        fscanf(archivo, "%s", lynux);

        // Finalmente se hace uso de la lista de juegos (estructura de datos tipo juego)
        // Se almacenan los valores utilizando las variables previamente definidas en esta funcion.
        // Notar que se hace uso del count para llevar un orden del arreglo de juegos tipo juego.
        juegos[count].nJuegos = nJuegos;
        juegos[count].id = id;
        juegos[count].nombre = (char*)malloc(largoNombre);
        strcpy(juegos[count].nombre, nombre);
        juegos[count].restriccionEdad = restriccion;
        juegos[count].precio = precio;
        strcpy(juegos[count].prox, prox);
        juegos[count].fecha = fecha;
        strcpy(juegos[count].gratis, gratis);
        strcpy(juegos[count].windows, windows);
        strcpy(juegos[count].mac, mac);
        strcpy(juegos[count].lynux, lynux);
        juegos[count].largoNombre = largoNombre;

        // Se avanza para hacer el mismo proceso con el siguiente juego.
        count++;
    }
    
    // Se cierran los archivos abiertos.
    fclose(archivo);
    fclose(lineas);
    fflush(stdout);
    // Se retorna la lista con los juegos (usando la estructura de datos definida).
    return(juegos);
}

juego* leerArchivoPorLinea(char *nombreArchivo, int posicion)
{
    
    //
    int id;
    char nombreAux[100];
    char aux;
    char saltarComa;
    int restriccion;
    float precio;
    char proxAux[6];
    int fecha;
    char gratisAux[10];
    char windowsAux[10];
    char macAux[10];
    int largoNombre;
    char lynux[4];

    //
    FILE *archivo = fopen(nombreArchivo, "r");

    fseek( archivo, posicion, SEEK_SET);
    
    // Se almacena memoria para los juegos a recibir.
    juego* linea = (juego*)malloc(sizeof(juego));

    // Primeramente se guarda el id.
    fscanf(archivo, "%d", &id);

    // Se avanza al siguiente valor a leer.
    fscanf(archivo, "%c", &saltarComa);
        
    int i,j;
    char nombre[100];
    // Se guarda la variable que representa si el juego saldra proximamente.
    // Nuevamente el ciclo llega hasta un valor previamente definido como largo maximo.
    i = 0;
    while(i < 100){
        fscanf(archivo, "%c", &aux);
        if (aux == saltarComa)
        {
            break;
        }     
        nombreAux[i] = aux;   
        i++;
    }
    largoNombre = i;    

    for (j = 0; j <= i; j++)
    {
        nombre[j] = nombreAux[j];
    }

    // Se leen tanto la restriccion de edad del juego como el precio del mismo.
    fscanf(archivo, "%d,%f", &restriccion, &precio);
        
    // Se avanza al siguiente valor a leer.
    fscanf(archivo, "%c", &saltarComa);

    // Se guarda la variable que representa si el juego saldra proximamente.
    // Nuevamente el ciclo llega hasta un valor previamente definido como largo maximo.
    i = 0;
    while(i < 10){

        fscanf(archivo, "%c", &aux);
        if (aux == saltarComa)
        {
            break;
        }     
        proxAux[i] = aux;   
        i++;
    }

        
    // Se aplica el mismo proceso anterior, se trabaja la variable temporal que almaceno
    // los valores.
    char prox[i];
    for (j = 0; j <= i; j++)
    {
        prox[j] = proxAux[j];
    }

    // Se guarda fecha de lanzamiento.
    fscanf(archivo, "%d", &fecha);

    // Se avanza al siguiente valor a leer.
    fscanf(archivo, "%c", &saltarComa);
        
    // Se hace el mismo proceso hecho previamente, se recibe el dato de si el juego es
    // gratis o no y se deja en una variable auxiliar.
    i = 0;
    while(i < 10){

        fscanf(archivo, "%c", &aux);
        if (aux == saltarComa)
        {
            break;
        }     
        gratisAux[i] = aux;   
        i++;
    }

    // Se trabaja la variable auxiliar y se deja en la varible que se usara la momento
    // de trabajar con la estructura de datos.
    char gratis[i];
    for (j = 0; j <= i; j++)
    {
        gratis[j] = gratisAux[j];
    }

    // Se repite el mismo proceso, ahora para guardar el valor que indica si el juego se
    // encuentra disponible en windows o no.
    i = 0;
    while(i < 10){

        fscanf(archivo, "%c", &aux);
        if (aux == saltarComa)
        {
            break;
        }     
        windowsAux[i] = aux;   
        i++;
    }

    // Se deja el valor almacenado temporalmente en la variable que se usa para trabajar
    // con la estructura de datos.
    char windows[i];
    for (j = 0; j <= i; j++)
    {
        windows[j] = windowsAux[j];
    }

    // Se repite el mismo proceso, ahora para guardar el valor que indica si el juego se
    // encuentra disponible en mac o no.
    i = 0;
    while(i < 10){

        fscanf(archivo, "%c", &aux);
        if (aux == saltarComa)
        {
            break;
        }     
        macAux[i] = aux;   
        i++;
    }
        
    // Se deja el valor almacenado temporalmente en la variable que se usa para trabajar        
    // con la estructura de datos.
    char mac[6];
    for (j = 0; j < i; j++)
    {
        mac[j] = macAux[j];
    }

    // Se guarda finalmente el dato que corresponde.
    // Notar que no se hace el mismo proceso que con el dato de windows o mac, esto porque
    // estos valores se encuentran entre ',' mientras que el dato correspondiente a linux
    // se encuentra al final, por tanto, solo se recibe.
    fscanf(archivo, "%s", lynux);

    // Finalmente se hace uso de la lista de juegos (estructura de datos tipo juego)
    // Se almacenan los valores utilizando las variables previamente definidas en esta funcion.
    // Notar que se hace uso del count para llevar un orden del arreglo de juegos tipo juego.
    linea[0].nJuegos = 0;
    linea[0].id = id;
    linea[0].nombre = (char*)malloc(largoNombre);
    strcpy(linea[0].nombre, nombre);
    linea[0].restriccionEdad = restriccion;
    linea[0].precio = precio;
    strcpy(linea[0].prox, prox);
    linea[0].fecha = fecha;
    strcpy(linea[0].gratis, gratis);
    strcpy(linea[0].windows, windows);
    strcpy(linea[0].mac, mac);
    strcpy(linea[0].lynux, lynux);
    linea[0].largoNombre = largoNombre;

    linea[0].posicion = ftell(archivo);

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
    
    */    
    fclose(archivo);    
    return(linea);
}


























