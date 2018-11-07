#include "libreria.h"

//***** TDA LISTAS ******

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


void imprimirNodoPelis(stPelicula p) /// SE PASA LA ESTRUCTURA A IMPRIMIR DIRECTAMENTE EN LUGAR DE PASAR EL NODO QUE LA CONTIENE
{

    system("cls");
    puts("\n\n\t***** PELICULA/S *****\n");
    printf("\n\tNOMBRE: %s", p.nombrePelicula);
    printf("\n\tDIRECTOR: %s", p.director);
    printf("\n\tGENERO: %s", p.genero);
    printf("\n\tPAIS: %s", p.pais);
    printf("\n\tANIO: %i", p.anio);
    printf("\n\tVALORACION: %i", p.valoracion);
    printf("\n\tPM: %i", p.pm);

}


void mostrarNodoPelis(nodoListaPelicula* listaPelis)
{

    nodoListaPelicula*seg=listaPelis;

    while(seg)
        if(seg->p.eliminado==0) // MUESTRA SOLO PELIS ACTIVAS
        {
            imprimirNodoPelis(seg->p);
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


////***********************************************************************************************************************************//
////                                                        TDA Arboles
////***********************************************************************************************************************************//


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

    if (Arbol==NULL)
    {
        Arbol=crearNodoArbol(Pelicula);
    }
    else
    {
        if(Pelicula.idPelicula>Arbol->p.idPelicula)
        {
            Arbol->der=insertaNodoArbol(Arbol->der,Pelicula);
        }
        else
        {
            Arbol->izq=insertaNodoArbol(Arbol->izq,Pelicula);
        }
    }
    return Arbol;

}

void preOrder(nodoArbolPelicula*Arbol)
{
    if(Arbol!=NULL)
    {
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

void inOrder(nodoArbolPelicula*Arbol)
{

    if(Arbol!=NULL)
    {
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

void postOrder(nodoArbolPelicula*Arbol)
{

    if(Arbol!=NULL)
    {
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


nodoArbolPelicula*buscarPeliculaID(nodoArbolPelicula*Arbol,int id)
{

    nodoArbolPelicula*rta=NULL;
    if(Arbol!=NULL)
    {
        if(Arbol->p.idPelicula==id)
        {
            rta=Arbol;
        }
        else
        {
            if(Arbol->p.idPelicula>id)
            {
                rta=buscarPeliculaID(Arbol->der,id);
            }
            else
            {
                rta=buscarPeliculaID(Arbol->izq,id);
            }
        }
    }

    return rta;
}

/////*void ReemplazarNodoArbol(nodoArbolPelicula*Arbol,nodoArbolPelicula*NuevoNodo){
////
////
////   if(Arbol->p=NULL){
////    if(Arbol->p=Arbol->izq->p){
////        Arbol->izq=NuevoNodo;
////    }
////    else if(Arbol->p=Arbol->der->p){
////        Arbol->der=NuevoNodo;
////    }
////   }
////   if(NuevoNodo){
////        NuevoNodo->p=Arbol->p;
////   }
////
////
////}*/
////
/////*nodoArbolPelicula*borrarNodoArbolPeli(nodoArbolPelicula*Arbol,stPelicula P){
////  A=borrarNodoArbolPeli(A,P);
////  if(Arbol!=NULL){
////    if(Arbol->p.idPelicula>P.idPelicula){
////        if(Arbol->izq!=NULL){
////            nodoArbolPelicula*masDer=masDer
////        }
////    }
////  }
////
////
////}
////*/
////
/////*void borrar(tarbol **a, int elem)
////{
////  void sustituir(tarbol **a, tarbol **aux);
////  tarbol *aux;
////
////  if (*a == NULL) /* no existe la clave */
/////*    return;
////
////  if ((*a)->clave < elem) borrar(&(*a)->der, elem);
////  else if ((*a)->clave > elem) borrar(&(*a)->izq, elem);
////  else if ((*a)->clave == elem) {
////    aux = *a;
////    if ((*a)->izq == NULL) *a = (*a)->der;
////    else if ((*a)->der == NULL) *a = (*a)->izq;
////    else sustituir(&(*a)->izq, &aux); /* se sustituye por
////      la mayor de las menores */
////
/////*    free(aux);
////  }
////}
////*/
//
//
//***********************************************************************************************************************************//
//                                                        FUNCIONES PARA PELICULAS
//***********************************************************************************************************************************//

void altaPelicula(nodoArbolPelicula*ArbolPelis) // Funcion general de alta de pel�culas
{
    // Declaraci�n de variables locales
    int validacionPais=0;
    int validacionDirector=0;
    int validacionGenero=0;
    int peliculaExiste=0;
    int cantReg=0;
    int i=0;
    char control='s'; // Variable de control para ciclo while principal de solicitud de los datos de peliculas
    stPelicula peliAux; // Se crea estructura auxiliar para trabajo temporal

    FILE *archi; // Asigna espacio en buffer para almacenar temporariamente los datos en proceso mientras se pasa de la memoria al archivo

    archi=fopen(ARCHIPELI, "a+b"); //Se chequea el acceso al archivo bajo la modalidad lectura-escritura

    if(archi==NULL) // Chequea si se puede abrir el archivo usando s�lo lectura
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
            peliculaExiste=validarPeliExiste(peliAux.nombrePelicula); // Chequea que el nombre de la pelicula en cuesti�n no exista en el archivo para evitar que se duplique mediante un flag

            if(!peliculaExiste)
            {
                printf("Ya existe una pelicula con ese nombre, desea continuar intentandolo(s/n)?\n");
                fflush(stdin);
                gets(peliAux.nombrePelicula);

                while((peliculaExiste!=0) && (i<3))
                {
                    printf("Ingrese el nombre de la pelicula nuevamente: ");
                    fflush(stdin);
                    gets(peliAux.nombrePelicula);
                    peliculaExiste=validarPeliExiste(peliAux.nombrePelicula); // Chequea que el nombre de usuario en ingreso no exista en el archivo para evitar que se duplique mediante un flag
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

            fseek(archi, 0, 2); // Se lleva el cursor al final del archivo para calcular desde ah� el peso del mismo

            if(ftell(archi)==0) // Si el tama�o del archivo en bytes es igual a 0, es decir si existe pero no tiene informacion
            {
                peliAux.idPelicula=1; // Se le asigna el valor 1 al primer registro
            }
            else
            {
                cantReg=(ftell(archi)/sizeof(stPelicula)); // Se calcula cuantos registros hay dividiendo el tam�ao del archivo por el tama�o de la estructura
                peliAux.idPelicula=cantReg+1; // Se le asigna el ID al usuario en ingreso agregandole 1 la cantidad actual de registros
            }

            peliAux.eliminado=0; // Se asigna negativo como valor predeterminado

            fwrite(&peliAux, sizeof(stPelicula), 1, archi); // Se graba los datos capturados en el archivo

            insertaNodoArbol(ArbolPelis, peliAux);///Se agrega peli al arbol

            printf("Desea continuar ingresando peliculas(s/n?"); // Se consulta si se desea continuar ingresando usuarios en esta sesi�n
            fflush(stdin);
            scanf("%c", &control);

            if(control=='s')
            {
                system("cls"); // Inicia nueva pantalla de carga de peliculas
                puts("****** ALTA DE OTRA PELICULA ******\n");
            }
        }
    }
}


void bajaPelicula()//Elimina peliculas pasando usuario.eliminado a valor verdadero
{
    char control='n';
    int idPeli=0;

    stPelicula peliAux;

    FILE *archi;

    archi=fopen(ARCHIPELI, "r+b");

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
            fseek(archi, (idPeli-1)*sizeof(stPelicula), SEEK_SET); // Se lleva el cursor al principio del archivo para moverse desde all�
            fread(&peliAux, sizeof(stPelicula), 1, archi); // Lectura del registro indicado
            peliAux.eliminado=1; // Se cambia el estado de la pelicula a eliminada
            fseek(archi, (idPeli-1)*sizeof(stPelicula), SEEK_SET); // Se lleva el cursor al principio del archivo para moverse desde all�
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

void mostrarPeliParaModif(nodoArbolPelicula*ArbolPelis)//Modificacion de peliculas para administrador
{
    FILE *archi = fopen(ARCHIPELI,"rb+");
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

            fseek(archi, (id-1)*sizeof(stPelicula), SEEK_SET); // Se lleva el cursor al principio del archivo para moverse desde all�
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
                a=menuModifPelis(ArbolPelis);

                fseek(archi, (id-1)*sizeof(stPelicula), SEEK_SET); // Se lleva el cursor al principio del archivo para moverse desde all�
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

                fseek(archi, (id-1)*sizeof(stPelicula), SEEK_SET); // Se lleva el cursor al principio del archivo para moverse desde all�
                fwrite(&aux, sizeof(aux), 1, archi); // Lectura del registro indicado
                modificarPeliEnArbol(ArbolPelis, aux);

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

void consultaPeliAdmin()//Se Muestra info por ID al Admin
{
    FILE *archi;

    archi=fopen(ARCHIPELI,"rb");

    stPelicula arregloPelis[100];

    int validos=0, id=0, i = 0, flag=0;

    if(archi==NULL)
    {
        printf("ERROR");
    }
    else
    {
        printf("Ingrese el ID de la pelicula que desea consultar: \n");
        scanf("%i", &id);
        validos=cargarArregloPeliculas(arregloPelis);//se carga el array de usuarios y devuelve los validos
        for (i=0; i<validos; i++)
        {
            if(id==arregloPelis[i].idPelicula)//busqueda en el array hasta encontrar el id y mostrarlo por pantalla
            {
                printf("Pelicula: %s \n", arregloPelis[i].nombrePelicula);
                printf("Director: %s \n", arregloPelis[i].director);
                printf("Genero: %s \n", arregloPelis[i].genero);
                printf("Pais: %s \n", arregloPelis[i].pais);
                printf("A�o: %i \n", arregloPelis[i].anio);
                printf("Valoracion: %i \n", arregloPelis[i].valoracion);
                printf("Calificacion: %i \n", arregloPelis[i].pm);
                if(arregloPelis[i].eliminado==1)
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


void insertar(stPelicula arregloPelis[], int posicion)
{
    stPelicula aux=arregloPelis[posicion+1];

    while(posicion>=0 && strcmpi(arregloPelis[posicion+1].genero,arregloPelis[posicion].genero)<0)
    {
        arregloPelis[posicion+1]=arregloPelis[posicion];
        posicion--;
    }
    arregloPelis[posicion+1]=aux;
}


int cargarArregloPeliculas(stPelicula arregloPelis[])
{
    FILE *archi;

    archi=fopen(ARCHIPELI, "rb");

    stPelicula peli;

    int i=0, validosPelis=0;

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
                arregloPelis[i]=peli;
            }
        }
        fclose(archi);
    }

    validosPelis=i-1;

    return validosPelis;
}


void ordenarGenero ()
{
    FILE *archi;

    archi=fopen(ARCHIPELI,"rb");

    stPelicula arregloPelis[100];

    int validosPelis=0;

    int i = 0;

    if(archi==NULL)
    {
        printf("ERROR");
    }
    else
    {
        validosPelis=cargarArregloPeliculas(arregloPelis);//se carga el array de peliculas

        while (i<validosPelis-1)//se recorre el array comparando los generos de las peliculas y ordenando de mayor a menor
        {
            insertar(arregloPelis,i);
            i++;
        }

//        mostrarArregloPelis(arregloPelis, validosPelis);//se muestra el array por pantalla
        fclose(archi);
    }

    system("pause");

}


void ordenarTitulo()
{
    FILE *archi;

    archi=fopen(ARCHIPELI,"rb");

    stPelicula arregloPelis[50];

    int validosPelis=0;

    if(archi==NULL)
    {
        printf("ERROR");
    }
    else
    {
        validosPelis=cargarArregloPeliculas(arregloPelis);//se carga el array de peliculas y se verifican los validos
        ordenacionSeleccion(arregloPelis,validosPelis);//se ordenan por el metodo de ordenacion por seleccion
//        mostrarArregloPelis(arregloPelis, validosPelis); //se muestran por pantalla
        fclose(archi);
    }
    system("pause");
}

void ordenacionSeleccion(stPelicula arregloPelis[], int validosPelis)
{
    int posmenor;
    stPelicula aux;
    int i = 0;
    while (i<validosPelis-1)
    {
        posmenor=posicionMenor(arregloPelis,i,validosPelis);
        aux = arregloPelis[posmenor];
        arregloPelis[posmenor]= arregloPelis[i];
        arregloPelis[i]=aux;
        i++;
    }
}

int posicionMenor(stPelicula arregloPelis[], int pos, int validosPelis)
{
    char menor[30];
    strcpy(menor,arregloPelis[pos].nombrePelicula);
    int posmenor=pos;
    int i=pos+1;
    while (i<validosPelis)
    {
        if (strcmpi(menor,arregloPelis[i].nombrePelicula)> 0)
        {
            strcpy(menor, arregloPelis[i].nombrePelicula);
            posmenor=i;
        }
        i++;
    }
    return posmenor;
}

int validarPeliExiste(char nombrePelicula[]) // Valida si el nombre del usuario ingresado actualmente ya existe en el archivo
{
    stPelicula peliAux; // Se crea estructura auxiliar para trabajo temporal
    int flag=0;

    FILE * archi;

    archi=fopen(ARCHIPELI, "rb"); // Abre al archivo en modo s�lo lectura para chequear acceso

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

    return flag; // Devuelve el valor de flag para su proceso en la funci�n que la invoca
}

stPelicula verPelicula(char nombreUsuario[], stCelda*arregloUsuActivos, int validos, nodoArbolPelicula*ArbolPelis)
{
    int id=0;
    printf("Ingrese el ID de la pelicula que desea ver: \n");
    scanf("%i", &id);
    nodoArbolPelicula * auxPeli=buscarPeliculaID(ArbolPelis, id);
    if(auxPeli)
    {
        printf("Disfrute de : \n\n");
        printf("Pelicula: %s \n", auxPeli->p.nombrePelicula);
        printf("Del Director: %s \n", auxPeli->p.director);
        printf("\n \n");
        nodoListaPelicula*NodoAux=crearNodoPeli(auxPeli->p);
        cargarPeliAUser(arregloUsuActivos,validos, nombreUsuario, NodoAux);
    }

    else //En caso de no encontrar el id
    {
        printf("No se encuentra la pelicula \n");
    }

    system("pause");
    return auxPeli->p;
}

void cargarPeliAUser(stCelda arregloUsuActivos[],int validos, char nombreUsuario[], nodoListaPelicula* Peli)
{
    int posicion=buscarPosicionUsuario(nombreUsuario, arregloUsuActivos, validos);
    agregarNodoFinal(arregloUsuActivos[posicion].listaPelis, Peli);
}

//int validarPeliExiste(char nombrePeli[]) // Valida si el nombre de la pelicula ingresada actualmente ya existe en el archivo
//{
//    int flag=buscarPelixNombre(nombrePeli);
//    return flag; // Devuelve el valor de flag para su proceso en la funci�n que la invoca
//}

int buscarPelixNombre(nodoArbolPelicula* ArbolPelis,char PeliBuscada[])
{
    int flag=0;
    if(ArbolPelis!=NULL)
    {
        if(strcmp(ArbolPelis->p.nombrePelicula,PeliBuscada)==0)///Si encuentra la pelicula se corta la ejecucion de la funcion
        {
            flag=1;
        }
        else
        {
            flag=buscarPelixNombre(ArbolPelis->der,PeliBuscada);
            flag=buscarPelixNombre(ArbolPelis->izq,PeliBuscada);
        }
    }

    return flag;
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

        while(!feof(archi)) // Lectura de los datos que existen ene el archivo(Como funci�n devuelve la cantidad de datos le�dos)
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

void modificarPeliEnArbol(nodoArbolPelicula * ArbolPelis,stPelicula PeliculaToModificar)
{
    nodoArbolPelicula * NodoAux=buscarPeliculaID(ArbolPelis, PeliculaToModificar.idPelicula);
    NodoAux->p=PeliculaToModificar;
}

//void mostrarArrayPeliculas(stPelicula array[], int validos)
//{
//    int i;
//    printf("El listado actual de peliculas existentes es el siguiente:\n\n");
//    for (i=0; i<validos; i++)
//    {
//        if(array[i].eliminado!=1)
//        {
//            printf("ID Pelicula: %i \n", array[i].idPelicula);
//            printf("Pelicula: %s \n", array[i].nombrePelicula);
//            printf("Director: %s \n", array[i].director);
//            printf("Genero: %s \n", array[i].genero);
//            printf("Pais: %s \n", array[i].pais);
//            printf("A�o: %i \n", array[i].anio);
//            printf("Valoracion: %i \n", array[i].valoracion);
//            printf("Calificacion: %i \n", array[i].pm);
//            printf("\n \n");
//        }
//    }
//}