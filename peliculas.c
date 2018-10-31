#include <stdio.h>
#include <stdlib.h>
#include "libreria.h"
#include "string.h"
#include "ctype.h"
#include <conio.h>

// ***** TDA LISTAS ******

nodoListaPelicula* inicLista()
{
    return NULL;
}


nodoListaPelicula* crearNodoPeli(stPelicula Peli)
{

    nodoListaPelicula* aux=(nodoListaPelicula*)malloc(sizeof(nodoListaPelicula));
    aux->p=Peli;

    return aux;
}


nodoListaPelicula* agregarNodoPpio(nodoListaPelicula* listaPelis, nodoListaPelicula* nuevoNodo)
{

    if(!listaPelis)
        listaPelis=nuevoNodo;

    else
    {
        nuevoNodo->sig=listaPelis;
        listaPelis=nuevoNodo;
    }

    return listaPelis;

}


nodoListaPelicula* buscarUltimoNodo(nodoListaPelicula* listaPelis)
{

    nodoListaPelicula*seg=listaPelis;

    while(seg->sig!=NULL)
    {
        seg=seg->sig;
    }

    return seg;

}


nodoListaPelicula* agregarNodoFinal(nodoListaPelicula* listaPelis, nodoListaPelicula* nuevoNodo)
{

    if(!listaPelis)
        listaPelis=nuevoNodo;

    else
    {
        nodoListaPelicula*ultimo=buscarUltimoNodo(listaPelis);
        ultimo->sig=nuevoNodo;
    }

    return listaPelis;
}


nodoListaPelicula* agregarNodoEnOrden(nodoListaPelicula* listaPelis, nodoListaPelicula* nuevoNodo)
{

    if(!listaPelis)
        listaPelis=nuevoNodo;

    else
    {
        if(strcmp(listaPelis->p.nombrePelicula, nuevoNodo->p.nombrePelicula)<0)
            listaPelis=agregarNodoPpio(listaPelis, nuevoNodo);

        else
        {
            nodoListaPelicula*ante=listaPelis;
            nodoListaPelicula*seg=listaPelis->sig;
            while(!seg && strcmp(seg->p.nombrePelicula, nuevoNodo->p.nombrePelicula)>=0)
            {
                ante=seg;
                seg=seg->sig;
            }
            nuevoNodo->sig=seg;
            ante->sig=nuevoNodo;
        }
    }

    return listaPelis;

}


void imprimirNodoPelis(nodoListaPelicula* nodoPeli)
{

    system("cls");
    puts("\n\n\t***** PELICULA/S *****\n");
    printf("\n\tNOMBRE: %s", nodoPeli->p.nombrePelicula);
    printf("\n\tDIRECTOR: %s", nodoPeli->p.director);
    printf("\n\tGENERO: %s", nodoPeli->p.genero);
    printf("\n\tPAIS: %s", nodoPeli->p.pais);
    printf("\n\tANIO: %i", nodoPeli->p.anio);
    printf("\n\tVALORACION: %i", nodoPeli->p.valoracion);
    printf("\n\tPM: %i", nodoPeli->p.pm);

}


void mostrarNodoPelis(nodoListaPelicula* listaPelis)
{

    nodoListaPelicula*seg=listaPelis;

    while(seg)
        if(seg->p.eliminado==0) // MUESTRA SOLO PELIS ACTIVAS
        {
            imprimirNodoPelis(seg);
            seg=seg->sig;
        }
}


nodoListaPelicula* borrarPeliPorId(nodoListaPelicula*listaPelis, int id)
{

    nodoListaPelicula*seg;
    nodoListaPelicula*ante;

    if((listaPelis) && (id==listaPelis->p.idPelicula))
    {
        nodoListaPelicula*aux=listaPelis;
        listaPelis=listaPelis->sig;
        free(aux);
    }

    else
    {
        seg=listaPelis;
        while((!seg) && (id!=listaPelis->p.idPelicula))
        {
            ante=seg;
            seg=seg->sig;
        }
        if(!seg)
        {
            ante->sig=seg->sig;
            free(seg);
        }
    }

    return listaPelis;
}


//***********************************************************************************************************************************//
//                                                        TDA Arboles
//***********************************************************************************************************************************//


nodoArbolPelicula * inicArbol()
{
    return NULL;
}

nodoArbolPelicula * crearNodoArbol(stPelicula Pelicula)
{

    nodoArbolPelicula*Aux = (nodoArbolPelicula*)malloc(sizeof(nodoArbolPelicula));
    Aux->p=Pelicula;
    Aux->der=NULL;
    Aux->izq=NULL;
    return Aux;
}

nodoArbolPelicula * insertaNodoArbol(nodoArbolPelicula * Arbol,stPelicula Pelicula)
{

    if (Arbol==NULL){
        Arbol=crearNodoArbol(Pelicula);
    }
    else{
        if(Pelicula.idPelicula>Arbol->p.idPelicula){
            Arbol->der=insertaNodoArbol(Arbol->der,Pelicula);
        }
        else{
            Arbol->izq=insertaNodoArbol(Arbol->izq,Pelicula);
        }
    }
  return Arbol;

}

void preOrder(nodoArbolPelicula*Arbol){
  if(Arbol!=NULL){
    printf("\n-------------Titulo: |%s|",Arbol->p.nombrePelicula);
    printf("\n---------IDPelicula: |%d|",Arbol->p.idPelicula);
    printf("\n---------------Anio: |%d|",Arbol->p.anio);
    printf("\n-------------Genero: |%s|",Arbol->p.genero);
    printf("\n---------Valoracion: |%d|",Arbol->p.valoracion);
    printf("\n----Para mayores de: |%d|",Arbol->p.pm);
    printf("\n-----------Director: |%s|",Arbol->p.director);
    printf("\n---------------Pais: |%s|",Arbol->p.pais);
    puts("\n");
    preOrder(Arbol->izq);
    preOrder(Arbol->der);
  }
}

void inOrder(nodoArbolPelicula*Arbol){

  if(Arbol!=NULL){
    inOrder(Arbol->izq);
    printf("\n-------------Titulo: |%s|",Arbol->p.nombrePelicula);
    printf("\n---------IDPelicula: |%d|",Arbol->p.idPelicula);
    printf("\n---------------Anio: |%d|",Arbol->p.anio);
    printf("\n-------------Genero: |%s|",Arbol->p.genero);
    printf("\n---------Valoracion: |%d|",Arbol->p.valoracion);
    printf("\n----Para mayores de: |%d|",Arbol->p.pm);
    printf("\n-----------Director: |%s|",Arbol->p.director);
    printf("\n---------------Pais: |%s|",Arbol->p.pais);
    puts("\n");
    inOrder(Arbol->der);
    }

}

void postOrder(nodoArbolPelicula*Arbol){

  if(Arbol!=NULL){
    inOrder(Arbol->izq);
    inOrder(Arbol->der);
    printf("\n-------------Titulo: |%s|",Arbol->p.nombrePelicula);
    printf("\n---------IDPelicula: |%d|",Arbol->p.idPelicula);
    printf("\n---------------Anio: |%d|",Arbol->p.anio);
    printf("\n-------------Genero: |%s|",Arbol->p.genero);
    printf("\n---------Valoracion: |%d|",Arbol->p.valoracion);
    printf("\n----Para mayores de: |%d|",Arbol->p.pm);
    printf("\n-----------Director: |%s|",Arbol->p.director);
    printf("\n---------------Pais: |%s|",Arbol->p.pais);
    puts("\n");
    }

}


nodoArbolPelicula*buscarPeliculaID(nodoArbolPelicula*Arbol,stPelicula Pelicula){

   nodoArbolPelicula*rta=NULL;
   if(Arbol!=NULL){
    if(Pelicula.idPelicula==Arbol->p.idPelicula){
        rta=Arbol;
    }
    else{
        if(Pelicula.idPelicula>Arbol->p.idPelicula){
            rta=buscarPeliculaID(Arbol->der,Pelicula);
        }
        else{
            rta=buscarPeliculaID(Arbol->izq,Pelicula);
        }
    }
   }

return rta;
}

/*void ReemplazarNodoArbol(nodoArbolPelicula*Arbol,nodoArbolPelicula*NuevoNodo){


   if(Arbol->p=NULL){
    if(Arbol->p=Arbol->izq->p){
        Arbol->izq=NuevoNodo;
    }
    else if(Arbol->p=Arbol->der->p){
        Arbol->der=NuevoNodo;
    }
   }
   if(NuevoNodo){
        NuevoNodo->p=Arbol->p;
   }


}*/

/*nodoArbolPelicula*borrarNodoArbolPeli(nodoArbolPelicula*Arbol,stPelicula P){
  A=borrarNodoArbolPeli(A,P);
  if(Arbol!=NULL){
    if(Arbol->p.idPelicula>P.idPelicula){
        if(Arbol->izq!=NULL){
            nodoArbolPelicula*masDer=masDer
        }
    }
  }


}
*/
/*void borrar(tarbol **a, int elem)
{
  void sustituir(tarbol **a, tarbol **aux);
  tarbol *aux;

  if (*a == NULL) /* no existe la clave */
/*    return;

  if ((*a)->clave < elem) borrar(&(*a)->der, elem);
  else if ((*a)->clave > elem) borrar(&(*a)->izq, elem);
  else if ((*a)->clave == elem) {
    aux = *a;
    if ((*a)->izq == NULL) *a = (*a)->der;
    else if ((*a)->der == NULL) *a = (*a)->izq;
    else sustituir(&(*a)->izq, &aux); /* se sustituye por
      la mayor de las menores */

/*    free(aux);
  }
}
*/


//***********************************************************************************************************************************//
//                                                        FUNCIONES PARA PELICULAS
//***********************************************************************************************************************************//

void altaPelicula(char archiPeli[]) // Funcion general de alta de películas
{
    // Declaración de variables locales
    int validacionPais=0;
    int validacionDirector=0;
    int validacionGenero=0;
    int peliculaExiste=0;
    int cantReg=0;
    int i=0;
    char control='s'; // Variable de control para ciclo while principal de solicitud de los datos de peliculas
    stPelicula peliAux; // Se crea estructura auxiliar para trabajo temporal

    FILE *archi; // Asigna espacio en buffer para almacenar temporariamente los datos en proceso mientras se pasa de la memoria al archivo

    archi=fopen(archiPeli, "a+b"); //Se chequea el acceso al archivo bajo la modalidad lectura-escritura

    if(archi==NULL) // Chequea si se puede abrir el archivo usando sólo lectura
    {
        printf("\nNo se pudo abrir el archivo");
        exit(1); // Sale del programa si no se pudo abrir el archivo
    }

    else
    {
        system("cls"); // Limpio pantalla
        printf("\n");
        printf("\n*****************************************************");
        printf("\n\t\tALTA DE PELICULAS");
        printf("\n*****************************************************");
        printf("\n");

        while(control=='s')
        {

            printf("Ingrese el nombre de la pelicula: ");
            fflush(stdin);
            gets(peliAux.nombrePelicula);
            peliculaExiste=validarPeliExiste(archiPeli, peliAux.nombrePelicula); // Chequea que el nombre de la pelicula en cuestión no exista en el archivo para evitar que se duplique mediante un flag

            if(peliculaExiste!=0)
            {
                printf("Ya existe una pelicula con ese nombre, desea continuar intentandolo(s/n)?\n");
                fflush(stdin);
                gets(peliAux.nombrePelicula);

                while((peliculaExiste!=0) && (i<3))
                {
                    printf("Ingrese el nombre de la pelicula nuevamente: ");
                    fflush(stdin);
                    gets(peliAux.nombrePelicula);
                    peliculaExiste=validarPeliExiste(archiPeli, peliAux.nombrePelicula); // Chequea que el nombre de usuario en ingreso no exista en el archivo para evitar que se duplique mediante un flag
                    i++;
                }
                if(peliculaExiste!=0)
                {
                    printf("\nHa superado los 4 intentos, vuelva a probar mas tarde");
                    exit(1);
                }
                else
                {
                    printf("El ingreso ha sido exitoso\n");
                }
            }

            do
            {
                printf("Ingrese el nombre del director de la pelicula(Solo caracteres): ");
                fflush(stdin);
                gets(peliAux.director);
                validacionDirector=validarTipoChar(peliAux.director);
            }
            while(validacionDirector!=0);

            do
            {
                printf("Ingrese el genero(Solo caracteres): ");
                fflush(stdin);
                gets(peliAux.genero);
                validacionGenero=validarTipoChar(peliAux.genero);
            }
            while(validacionGenero!=0);

            do
            {
                printf("Ingrese el pais(Solo caracteres): ");
                fflush(stdin);
                gets(peliAux.pais);
                validacionPais=validarTipoChar(peliAux.pais);
            }
            while(validacionPais!=0);

            do
            {
                printf("Ingrese el anio: ");
                scanf("%i", &peliAux.anio);
            }
            while(peliAux.anio<1895 || peliAux.anio>2018);

            do
            {
                printf("Ingrese la valoracion(Escala del 1 al 5: 1 pesima - 5 excelente): ");
                scanf("%i", &peliAux.valoracion);
            }
            while((peliAux.valoracion<0) || (peliAux.valoracion>5));

            do
            {
                printf("Ingrese la categoria de la pelicula(0 si es ATP - 13 si es para mayores de 13 anios - 16 y 18 respectivamente): ");
                scanf("%i", &peliAux.pm);
            }
            while(peliAux.pm<0 || peliAux.pm>18);

            fseek(archi, 0, 2); // Se lleva el cursor al final del archivo para calcular desde ahí el peso del mismo

            if(ftell(archi)==0) // Si el tamaño del archivo en bytes es igual a 0, es decir si existe pero no tiene informacion
            {
                peliAux.idPelicula=1; // Se le asigna el valor 1 al primer registro
            }
            else
            {
                cantReg=(ftell(archi)/sizeof(stPelicula)); // Se calcula cuantos registros hay dividiendo el tamñao del archivo por el tamaño de la estructura
                peliAux.idPelicula=cantReg+1; // Se le asigna el ID al usuario en ingreso agregandole 1 la cantidad actual de registros
            }

            peliAux.eliminado=0; // Se asigna negativo como valor predeterminado

            fwrite(&peliAux, sizeof(stPelicula), 1, archi); // Se graba los datos capturados en el archivo

            printf("Desea continuar ingresando peliculas(s/n?"); // Se consulta si se desea continuar ingresando usuarios en esta sesión
            fflush(stdin);
            scanf("%c", &control);

            if(control=='s')
            {
                system("cls"); // Inicia nueva pantalla de carga de peliculas
                puts("****** ALTA DE OTRA PELICULA ******\n");
            }
        }
        fclose(archi); // Cierre del archivo
    }
}


void bajaPelicula(char archiPeli[])//Elimina peliculas pasando usuario.eliminado a valor verdadero
{
    char control='n';
    int idPeli=0;

    stPelicula peliAux;

    FILE *archi;

    archi=fopen(archiPeli, "r+b");

    if(archi==NULL)
    {
        printf("No se pudo abrir el archivo para consultar si la pelicula ya existe");
        exit(1);
    }

    else
    {
        system("cls");
        printf("\n");
        printf("\n*****************************************************");
        printf("\n\tBAJA DE PELICULAS");
        printf("\n*****************************************************");
        printf("\n");

        printf("\nIngrese el ID de la pelicula a eliminar: ");
        scanf("%i", &idPeli);
        printf("\nEsta seguro de que desea eliminar la pelicula(s/n?"); // Chequea nuevamente si quiere avanzar con la baja de la pelicula
        fflush(stdin);
        scanf("%c", &control);
        if(control=='s') // Si confirma, se avanza
        {
            fseek(archi, (idPeli-1)*sizeof(stPelicula), SEEK_SET); // Se lleva el cursor al principio del archivo para moverse desde allí
            fread(&peliAux, sizeof(stPelicula), 1, archi); // Lectura del registro indicado
            peliAux.eliminado=1; // Se cambia el estado de la pelicula a eliminada
            fseek(archi, (idPeli-1)*sizeof(stPelicula), SEEK_SET); // Se lleva el cursor al principio del archivo para moverse desde allí
            fwrite(&peliAux, sizeof(peliAux), 1, archi); // Escribo el nuevo valor de eliminado en el archivo
            printf("\nLa pelicula se elimino correctamente\n");
            printf("\nNombre de la pelicula: %s", peliAux.nombrePelicula);
            printf("\nEstado: %i", peliAux.eliminado);
        }
        else // Si no confirma, se sale del programa
        {
            exit(1);
        }
        fclose(archi);
    }
}

void mostrarPeliParaModif(char archiPeli[])//Modificacion de peliculas para administrador
{
    FILE *archi = fopen(archiPeli,"rb+");
    stPelicula aux;
    int flag=0, id=0, a=0;
    char control='s';
    if(archi!=NULL)
    {
        system("cls");
        printf("\n");
        printf("\n*****************************************************");
        printf("\n\tMODIFICACION DE PELICULAS");
        printf("\n*****************************************************");
        printf("\n");
        printf("\nIngrese la ID que desea buscar \n");

        scanf("%i", &id);

        while (!feof(archi)&&flag==0) //Busqueda por id de pelicula
        {
            fread(&aux,sizeof(stPelicula),1,archi);
            if(id==aux.idPelicula)
            {
                flag=1;
            }
        }

        if(flag==1) //En caso de que se encuentre la pelicula se muestra por pantalla y se procede a seleccionar el campo a modificar
        {

            fseek(archi, (id-1)*sizeof(stPelicula), SEEK_SET); // Se lleva el cursor al principio del archivo para moverse desde allí
            fread(&aux, sizeof(stPelicula), 1, archi); // Lectura del registro indicado

            printf("Los datos de la pelicula son los siguientes: \n");
            printf("El nombre de la pelicula es: %s \n", aux.nombrePelicula);
            printf("El director de la pelicula es: %s \n", aux.director);
            printf("El anio de filmacion de la pelicula es: %i \n", aux.anio);
            printf("El genero de la pelicula es: %s \n", aux.genero);
            printf("El pais de origen de la pelicula es: %s \n", aux.pais);

            printf("La valoracion de la pelicula es: %i \n", aux.valoracion);
            printf("La clasificacion de la pelicula es: %i \n", aux.pm);
            if(aux.eliminado==1)
            {
                printf("La pelicula ha sido marcada como eliminada de catalogo\n");
            }
            else
            {
                printf("La pelicula esta en catalogo\n");
            }

            system("pause");

            do
            {
                a=menuModifPelis(archiPeli);

                fseek(archi, (id-1)*sizeof(stPelicula), SEEK_SET); // Se lleva el cursor al principio del archivo para moverse desde allí
                fread(&aux, sizeof(aux), 1, archi); // Lectura del registro indicado

                switch (a)
                {

                case 1:

                    printf("Ingrese el nuevo nombre de la pelicula: \n");
                    fflush(stdin);
                    gets(aux.nombrePelicula);
                    printf("Desea Modificar otro campo? s/n \n");
                    fflush(stdin);
                    scanf("%c", &control);
                    break;

                case 2:
                    printf("Ingrese el nuevo director de la pelicula: \n");
                    fflush(stdin);
                    gets(aux.director);
                    printf("Desea Modificar otro campo? s/n \n");
                    fflush(stdin);
                    scanf("%c", &control);
                    break;

                case 3:

                    printf("Ingrese el nuevo anio de filmacion de la pelicula: \n");
                    scanf("%i", &aux.anio);
                    printf("Desea Modificar otro campo? s/n \n");
                    fflush(stdin);
                    scanf("%c", &control);
                    break;

                case 4:

                    printf("Ingrese el nuevo genero de la pelicula: \n");
                    fflush(stdin);
                    gets(aux.genero);
                    printf("Desea Modificar otro campo? s/n \n");
                    fflush(stdin);
                    scanf("%c", &control);
                    break;

                case 5:

                    printf("Ingrese el nuevo pais de origen de la pelicula: \n");
                    fflush(stdin);
                    gets(aux.pais);
                    printf("Desea Modificar otro campo? s/n \n");
                    fflush(stdin);
                    scanf("%c", &control);
                    break;

                case 6:

                    printf("Ingrese la nueva valoracion de la pelicula(Escala del 1 al 5: 1 pesima - 5 excelente): \n");
                    scanf("%i", &aux.valoracion);
                    printf("Desea Modificar otro campo? s/n \n");
                    fflush(stdin);
                    scanf("%c", &control);
                    break;

                case 7:

                    printf("Ingrese la nueva clasificacion de la pelicula(0 si es ATP - 13 si es para mayores de 13 anios - 16 y 18 respectivamente: \n");
                    scanf("%i", &aux.pm);
                    printf("Desea Modificar otro campo? s/n \n");
                    fflush(stdin);
                    scanf("%c", &control);
                    break;

                case 8:

                    printf("Ingrese el nuevo estado en catalogo de la pelicula(0 si activa - 1 si eliminada): \n");
                    scanf("%i", &aux.eliminado);
                    printf("Desea Modificar otro campo? s/n \n");
                    fflush(stdin);
                    scanf("%c", &control);
                    break;

                default:
                    exit(1);
                    break;

                }

                fseek(archi, (id-1)*sizeof(stPelicula), SEEK_SET); // Se lleva el cursor al principio del archivo para moverse desde allí
                fwrite(&aux, sizeof(aux), 1, archi); // Lectura del registro indicado

            }
            while(a!=0&&control=='s'); // Mientras se desee continuar
        }

        else
        {

            printf("No se encuentra la ID en el archivo \n"); // Muestra este error en caso que ese ID no se encuentre graado en el archivo
        }
        fclose(archi);
    }
    else
    {
        printf("ERROR \n"); // Muestra error si no se pudo abrir el archivo
    }
}

void consultaPeliAdmin(char archiPeli[])//Se Muestra info por ID al Admin
{
    FILE *archi;

    archi=fopen(archiPeli,"rb");

    stPelicula array[50];

    int validos=0, id=0, i = 0, flag=0;

    if(archi==NULL)
    {
        printf("ERROR");
    }
    else
    {
        printf("Ingrese el ID de la pelicula que desea consultar: \n");
        scanf("%i", &id);
        validos=cargarArrayPeliculas(archiPeli, array);//se carga el array de usuarios y devuelve los validos
        for (i=0; i<validos; i++)
        {
            if(id==array[i].idPelicula)//busqueda en el array hasta encontrar el id y mostrarlo por pantalla
            {
                printf("Pelicula: %s \n", array[i].nombrePelicula);
                printf("Director: %s \n", array[i].director);
                printf("Genero: %s \n", array[i].genero);
                printf("Pais: %s \n", array[i].pais);
                printf("Año: %i \n", array[i].anio);
                printf("Valoracion: %i \n", array[i].valoracion);
                printf("Calificacion: %i \n", array[i].pm);
                if(array[i].eliminado==1)
                {
                    printf("La pelicula fue marcada como eliminada en el catalogo");
                }
                else
                {
                    printf("La pelicula figura activa en el catalogo");
                }
                printf("\n \n");
                flag=1;
            }
        }
        if(flag==0) //Flag en caso de no encontrar el id
        {
            printf("No se encuentra el id \n");
        }

        fclose(archi);

    }

    system("pause");

}


void insertar(stPelicula array[], int i)
{
    stPelicula aux=array[i+1];

    while(i>=0 && strcmpi(array[i+1].genero,array[i].genero)<0)
    {
        array[i+1]=array[i];
        i--;
    }
    array[i+1]=aux;
}


int cargarArrayPeliculas(char archiPeli[], stPelicula array[])
{
    FILE *archi;

    archi=fopen(archiPeli, "rb");

    stPelicula peli;

    int i=0, validos=0;

    if (archi==NULL)
    {
        printf("\n ERROR");
    }
    else
    {
        for(i=0; !feof(archi); i++)
        {
            fread(&peli, sizeof(stPelicula), 1, archi);

            if(!feof(archi))
            {
                array[i]=peli;
            }
        }
        fclose(archi);
    }

    validos=i-1;

    return validos;
}


void ordenarGenero (char archiPeli[])
{
    FILE *archi;

    archi=fopen(archiPeli,"rb");

    stPelicula arraydepeliculas[50];

    int validos=0;

    int i = 0;

    if(archi==NULL)
    {
        printf("ERROR");
    }
    else
    {
        validos=cargarArrayPeliculas(archiPeli, arraydepeliculas);//se carga el array de peliculas

        while (i<validos-1)//se recorre el array comparando los generos de las peliculas y ordenando de mayor a menor
        {
            insertar(arraydepeliculas,i);
            i++;
        }

        mostrarArrayPeliculas(arraydepeliculas, validos);//se muestra el array por pantalla
        fclose(archi);
    }

    system("pause");

}


void ordenarTitulo(char archiPeli[])
{
    FILE *archi;

    archi=fopen(archiPeli,"rb");

    stPelicula arraydepeliculas[50];

    int validos=0;

    if(archi==NULL)
    {
        printf("ERROR");
    }
    else
    {
        validos=cargarArrayPeliculas(archiPeli,arraydepeliculas);//se carga el array de peliculas y se verifican los validos
        ordenacionSeleccion(arraydepeliculas,validos);//se ordenan por el metodo de ordenacion por seleccion
        mostrarArrayPeliculas(arraydepeliculas, validos); //se muestran por pantalla
        fclose(archi);
    }
    system("pause");
}

void ordenacionSeleccion(stPelicula array[], int validos)
{
    int posmenor;
    stPelicula aux;
    int i = 0;
    while (i<validos-1)
    {
        posmenor=posicionMenor(array,i,validos);
        aux = array[posmenor];
        array[posmenor]= array[i];
        array[i]=aux;
        i++;
    }
}

int posicionMenor(stPelicula array[], int pos, int validos)
{
    char menor[30];
    strcpy(menor,array[pos].nombrePelicula);
    int posmenor=pos;
    int i=pos+1;
    while (i<validos)
    {
        if (strcmpi(menor,array[i].nombrePelicula)> 0)
        {
            strcpy(menor, array[i].nombrePelicula);
            posmenor=i;
        }
        i++;
    }
    return posmenor;
}

int verPelicula(char archiPeli[])
{
    FILE *archi;

    archi=fopen(archiPeli,"rb+");

    stPelicula array[50];

    int validos=0, id=0, i = 0, flagid=0;

    if(archi==NULL)
    {
        printf("ERROR");
    }
    else
    {
        printf("Ingrese el ID de la pelicula que desea ver: \n");
        scanf("%i", &id);
        validos=cargarArrayPeliculas(archiPeli, array);//se carga el array de usuarios y devuelve los validos
        for (i=0; i<validos; i++)
        {
            if(id==array[i].idPelicula)//busqueda en el array hasta encontrar el id y mostrarlo por pantalla
            {
                flagid=1;
                printf("Disfrute de : \n\n");
                printf("Pelicula: %s \n", array[i].nombrePelicula);
                printf("Del Director: %s \n", array[i].director);
                printf("\n \n");
            }
        }
        if(flagid==0) //Flag en caso de no encontrar el id
        {
            printf("No se encuentra la pelicula \n");
            id=0; //En caso de no encontrar la pelicula retornara ID=0, es decir Falso
        }
        fclose(archi);

    }

    system("pause");
    return id;
}


int validarPeliExiste(char archiPeli[], char nombrePelicula[]) // Valida si el nombre del usuario ingresado actualmente ya existe en el archivo
{
    stPelicula peliAux; // Se crea estructura auxiliar para trabajo temporal
    int flag=0;

    FILE * archi;

    archi=fopen(archiPeli, "rb"); // Abre al archivo en modo sólo lectura para chequear acceso

    if(archi==NULL)
    {
        printf("No se pudo abrir el archivo para consultar si la pelicula ya existe");
        exit(1);
    }

    else
    {

        while((fread(&peliAux, sizeof(stPelicula), 1, archi)>0) && (flag!=1))  // Realiza el proceso mientras haya registros en el archivo
        {
            if(strcmp(peliAux.nombrePelicula, nombrePelicula)==0)  //Chequea si ambos strings son iguales
            {
                flag=1; // Si ambos strings son iguales, asigno valor 1 a flag como positivo
            }
        }
    }

    fclose(archi); // Cierra el archivo

    return flag; // Devuelve el valor de flag para su proceso en la función que la invoca
}

void mostrarPeliculas(char archiPeli[]) // Funcion auxiliar usada para chequear que el sistema funcione correctamente visualizando los registros ingresados por pantalla -
{
    stPelicula peliAux;

    FILE * archi;

    archi=fopen(archiPeli, "rb");

    if(archi==NULL)
    {
        printf("No se pudo abrir el archivo");
    }

    else
    {

        while(!feof(archi)) // Lectura de los datos que existen ene el archivo(Como función devuelve la cantidad de datos leídos)
        {
            fread(&peliAux, sizeof(stPelicula), 1, archi);
            if(!feof(archi)&&peliAux.eliminado!=1)//Validacion de fin de archivo y pelicula no eliminada
            {
                printf("ID: %i\n", peliAux.idPelicula);
                printf("Nombre de peli: %s\n", peliAux.nombrePelicula);
                printf("Anio: %i\n", peliAux.anio);
                printf("Genero: %s\n", peliAux.genero);
                printf("Pais: %s\n", peliAux.pais);
                printf("Director %s\n", peliAux.director);
                printf("Valoracion: %i\n", peliAux.valoracion);
                printf("PM: %i\n", peliAux.pm);
                printf("Estado en la base: %i\n\n", peliAux.eliminado);

            }
        }
        fclose(archi);
    }
}

void mostrarArrayPeliculas(stPelicula array[], int validos)
{
    int i;
    printf("El listado actual de peliculas existentes es el siguiente:\n\n");
    for (i=0; i<validos; i++)
    {
        if(array[i].eliminado!=1)
        {
            printf("ID Pelicula: %i \n", array[i].idPelicula);
            printf("Pelicula: %s \n", array[i].nombrePelicula);
            printf("Director: %s \n", array[i].director);
            printf("Genero: %s \n", array[i].genero);
            printf("Pais: %s \n", array[i].pais);
            printf("Año: %i \n", array[i].anio);
            printf("Valoracion: %i \n", array[i].valoracion);
            printf("Calificacion: %i \n", array[i].pm);
            printf("\n \n");
        }
    }
}
