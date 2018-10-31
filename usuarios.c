#include <stdio.h>
#include <stdlib.h>
#include "libreria.h"
#include "string.h"
#include "ctype.h"
#include <conio.h>


stCelda*arregloUsuActivos;
stCelda*arregloUsuInactivos;


// FUNCIONES VALE TP 2*******************************************************************************************************************************************************************


void cargaInicial()
{

    int cantActivosIniciales=0; //Ver con profe donde va
    cantActivosIniciales=cargarArchivoUsuariosActivosToArreglo(archiUsu,arregloUsuActivos);
    cargarArchivoUsuariosInactivosToArreglo(archiUsu, arregloUsuInactivos);




}

int cantUsuariosActivos(char archiUsu[])
{

    int cantUsuarios=0;
    stCelda aux;

    FILE*archi;

    archi=fopen(archiUsu, "rb");

    if(archi)
    {
        while(fread(&aux,sizeof(stCelda),1,archi)>0)
        {
            if(aux.usr.eliminado==0)
            {
                cantUsuarios++;
            }
        }
    }
    else
    {
        printf("No se pudo abrir el archivo de usuarios");
    }

    return cantUsuarios;
}


int cantUsuariosInactivos(char archiUsu[])
{

    int cantUsuarios=0;
    stCelda aux;

    FILE*archi;

    archi=fopen(archiUsu, "rb");

    if(archi)
    {
        while(fread(&aux,sizeof(stCelda),1,archi)>0)
        {
            if(aux.usr.eliminado==1)
            {
                cantUsuarios++;
            }
        }
    }
    else
    {
        printf("No se pudo abrir el archivo de usuarios");
    }

    return cantUsuarios;
}


int cantUsuariosTotales(char archiUsu[])
{

    int cantUsuarios=0;

    FILE*archi;

    archi=fopen(archiUsu, "rb");

    if(archi)
    {

        fseek(archi, 0, 2); // Se lleva el cursor al final del archivo para calcular desde ahí el peso del mismo

        if(ftell(archi)==0) // Si el tamaño del archivo en bytes es igual a 0, es decir si existe pero no tiene informacion
        {
            cantUsuarios=0; // Se le asigna el valor 1 al primer registro
        }
        else
        {
            cantUsuarios=(ftell(archi)/sizeof(stUsuario)); // Se calcula cuantos registros hay dividiendo el tamñao del archivo por el tamaño de la estructura

        }
        fclose(archi);
    }
    else
    {
        printf("No se pudo abrir el archivo de usuarios");
    }

    return cantUsuarios;
}


int cargarArchivoUsuariosActivosToArreglo(char archiUsu[], stCelda*arregloUsuActivos)
{
    int i=0;
    int dim=cantUsuariosActivos(archiUsu);
    stUsuario aux;

//    stCelda*arregloUsuActivos=NULL; // Inicializo a Null para dejarlo en limpio -- PASADA al main

    arregloUsuActivos=(stCelda*)malloc(sizeof(stCelda)*dim);

    if(arregloUsuActivos==NULL)
    {
        puts("No se puede continuar por error de asignacion de memoria");
        exit(-1);
    }

    else
    {
        FILE*archi;

        archi=fopen(archiUsu, "rb");

        if(archi)
        {

            while(fread(&aux, sizeof(stUsuario), 1, archi)>0)
            {
                if(aux.eliminado==0)
                {
                    arregloUsuActivos[i].usr=aux;
                    arregloUsuActivos[i].listaPelis=inicLista();
                    i++;
                }
            }
            fclose(archi);
        }
        else
        {
            printf("No se pudo abrir el archivo de usuarios");
        }
    }
    return i; //Retorna usuarios activos pasados al arreglo en primera instancia
}


stCelda* cargarArchivoUsuariosInactivosToArreglo(char archiUsu[])
{

    int i=0;
    int dim=cantUsuariosInactivos(archiUsu);
    stCelda aux;

//    stCelda*arregloUsuInactivos=NULL; // Inicializo a Null para dejarlo en limpio -- Pasada al main

    stCelda * arregloUsuInactivos= malloc(sizeof(stCelda)*dim);

    if(arregloUsuInactivos==NULL)
    {
        puts("No se puede continuar por error de asignacion de memoria");
        exit(-1);
    }

    else
    {

        FILE*archi;

        archi=fopen(archiUsu, "rb");

        if(archi)
        {

            while(!feof(archi) && i<dim)
            {
                fread(&aux, sizeof(stCelda), 1, archi);
                if(!feof(archi))
                {
                    fread(&aux, sizeof(stCelda), 1, archi);
                    if(aux.usr.eliminado==1)
                    {
                        arregloUsuInactivos[i]=aux;
                        arregloUsuInactivos[i].listaPelis=inicLista();
                    }
                }
                i++;
            }
            fclose(archi);
        }

        else
        {
            printf("No se pudo abrir el archivo de usuarios");
        }
    }
    return arregloUsuInactivos;
}


//***********************************************************************************************************************************//
//                                                        FUNCIONES PARA USUARIOS
//***********************************************************************************************************************************//


void altaUsuario(char archiUsu[], stCelda arregloUsuActivos[]) // Funcion general de alta de usuario
{

    // Declaración de variables locales
    int validacionPais=0;
    int usuarioExiste=0;
    int longPass=0;
    int i=0;
    int tamanioArray=0;
    long cantReg=0;
    char passAux[11];
    char control='s'; // Variable de control para ciclo while principal de solicitud de datos de usuarios
    stUsuario usuAux; // Se crea estructura auxiliar para trabajo temporal

    system("cls");
    printf("\n");
    printf("\n*****************************************************");
    printf("\n\t\tREGISTRO DE NUEVO USUARIO");
    printf("\n*****************************************************");
    printf("\n");

    while(control=='s')
    {

        printf("Ingrese el nombre de usuario: ");
        fflush(stdin);
        gets(usuAux.nombreUsuario);
        usuarioExiste=validarUserExiste(archiUsu, usuAux.nombreUsuario); // Chequea que el nombre de usuario en ingreso no exista en el archivo para evitar que se duplique mediante un flag

        if(usuarioExiste!=0)
        {
            printf("Ese usuario ya existe, tiene 3 intentos mas\n");

            while((usuarioExiste!=0) && (i<3))
            {
                printf("Ingrese un nuevo nombre de usuario: ");
                fflush(stdin);
                gets(usuAux.nombreUsuario);
                usuarioExiste=validarUserExiste(archiUsu, usuAux.nombreUsuario); // Chequea que el nombre de usuario en ingreso no exista en el archivo para evitar que se duplique mediante un flag
                i++;
            }
            if(usuarioExiste!=0)
            {
                printf("\nHa superado los 4 intentos, vuelva a probar mas tarde");
                exit(1);
            }
            else
            {
                printf("El ingreso ha sido exitoso\n");
            }
        }

        printf("Ingrese la contrasenia(maximo 10 caracteres): ");
        fflush(stdin);
        gets(passAux);
        longPass=validarLongPass(passAux); // Chequea que el nombre de usuario no supere los 10 caracteres mediante un flag

        if(longPass!=0)
        {
            printf("La contrasenia debe tener 10 caracteres como maximo, tiene 3 intentos mas\n");

            while((longPass!=0) && (i<3))
            {
                printf("Ingrese una nueva contrasenia: ");
                fflush(stdin);
                gets(passAux);
                longPass=validarLongPass(passAux); // Chequea que el nombre de usuario no supere los 10 caracteres mediante un flag
                i++;;
            }

            if(longPass==0)
            {
                printf("El ingreso ha sido exitoso\n");
            }

            else
            {
                printf("\nHa superado los 4 intentos, vuelva a probar mas tarde");
                exit(1);
            }
        }

        encriptacionPass(passAux, usuAux.pass);

        printf("Ingrese anio de nacimiento: ");
        scanf("%i", &usuAux.anioNacimiento);

        printf("Ingrese el genero(m/f): ");
        fflush(stdin);
        scanf("%c", &usuAux.genero);

        do
        {
            printf("Ingrese el pais(Solo caracteres): ");
            fflush(stdin);
            gets(usuAux.pais);
            validacionPais=validarTipoChar(usuAux.pais);
        }
        while(validacionPais!=0);


//        fseek(archi, 0, 2); // Se lleva el cursor al final del archivo para calcular desde ahí el peso del mismo
//
//        if(ftell(archi)==0) // Si el tamaño del archivo en bytes es igual a 0, es decir si existe pero no tiene informacion
//        {
//            usuAux.idUsuario=1; // Se le asigna el valor 1 al primer registro
//        }
//        else
//        {
//            cantReg=(ftell(archi)/sizeof(stUsuario)); // Se calcula cuantos registros hay dividiendo el tamñao del archivo por el tamaño de la estructura
//            usuAux.idUsuario=cantReg+1; // Se le asigna el ID al usuario en ingreso agregandole 1 la cantidad actual de registros
//        }

        usuAux.eliminado=0; // Se asigna negativo como valor predeterminado

        usuAux.admin=0; // Por defecto NO es administrador


        usuAux.idUsuario=cantUsuariosTotales(archiUsu)+1; ///CHEQUEAR COMO FUNCIONA


        // ver como se usa realloc

        tamanioArray=calcularTamanioArrayUsuarios(arregloUsuActivos); ///Reemplazar funcion con la de Nahuel

        arregloUsuActivos=realloc(arregloUsuActivos, sizeof(stCelda)*(tamanioArray+1));

        arregloUsuActivos[tamanioArray].usr=usuAux;




        printf("Desea continuar ingresando usuarios(s/n?"); // Se consulta si se desea continuar ingresando usuarios en esta sesión
        fflush(stdin);
        scanf("%c", &control);

        if(control=='s')
        {
            system("cls");
            puts("****** ALTA DE OTRO USUARIO ******\n");
        }

    }

//        fclose(archi); // Cierre del archivo
//    }
}



void bajaUsuario(char archiUsu[]) //Elimina usuarios pasando usuario.eliminado a valor verdadero
{
    char control='n';
    int idUsu=0;

    stUsuario usuAux;

    FILE *archi;

    archi=fopen(archiUsu, "r+b");

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
        printf("\n\tBAJA DE USUARIOS");
        printf("\n*****************************************************");
        printf("\n");

        printf("\nIngrese el ID del usuario a eliminar: ");
        scanf("%i", &idUsu);
        printf("\nEsta seguro de que desea eliminar el usuario(s/n?"); // Chequea nuevamente si quiere avanzar con la baja de la pelicula
        fflush(stdin);
        scanf("%c", &control);
        if(control=='s') // Si confirma, se avanza
        {
            fseek(archi, (idUsu-1)*sizeof(stUsuario), SEEK_SET); // Se lleva el cursor al principio del archivo para moverse desde allí
            fread(&usuAux, sizeof(stUsuario), 1, archi); // Lectura del registro indicado
            usuAux.eliminado=1; // Se cambia el estado del usuario a a eliminar
            fseek(archi, (idUsu-1)*sizeof(stUsuario), SEEK_SET); // Se lleva el cursor al principio del archivo para moverse desde allí
            fwrite(&usuAux, sizeof(usuAux), 1, archi); // Escribo el nuevo valor de eliminado en el archivo
            printf("\nEl usuario se elimino correctamente\n");
            printf("\nNombre del usuario: %s", usuAux.nombreUsuario);
            printf("\nEstado: %i", usuAux.eliminado);
        }
        else // Si no confirma, se sale del programa
        {
            exit(1);
        }
        fclose(archi);
    }
}


void mostrarUserParaModif(char archiUsu[])//Modificacion de usuario para administrador
{
    FILE *archi = fopen(archiUsu,"rb+");
    stUsuario aux;
    //  int dim=30;
    //  int pelisVistas[dim];
//    int cantPelisVistas=0;
    int i=0, flag=0, id=0, a=0;
    char control='s', passAux[10];
    if(archi!=NULL)
    {
        system("cls");
        printf("\n");
        printf("\n*****************************************************");
        printf("\n\tMODIFICACION DE USUARIOS");
        printf("\n*****************************************************");
        printf("\n");
        printf("\nIngrese la ID que desea buscar \n");

        scanf("%i", &id);

        while (!feof(archi)&&flag==0) //Busqueda por id de usuario
        {
            fread(&aux,sizeof(stUsuario),1,archi);
            if(id==aux.idUsuario)
            {
                flag=1;
            }
        }

        if(flag==1) //En caso de que se encuentre el usuario se muestra por pantalla y se procede a seleccionar el campo a modificar
        {

            fseek(archi, (id-1)*sizeof(stUsuario), SEEK_SET); // Se lleva el cursor al principio del archivo para moverse desde allí
            fread(&aux, sizeof(stUsuario), 1, archi); // Lectura del registro indicado

            printf("Los datos del usuario son los siguientes: \n");
            printf("El nombre del Usuario es: %s \n", aux.nombreUsuario);
            desencriptacionPass(aux.pass, passAux);
            printf("Password: %s\n", passAux);
            printf("El anio de nacimiento del Usuario es: %i \n", aux.anioNacimiento);
            printf("El genero del Usuario es: %c \n", aux.genero);
            printf("El nombre del Usuario es: %s \n", aux.pais);
            printf("IDs de Peliculas vistas: \n");
            if(aux.eliminado==1)
            {
                printf("El usuario ha sido marcado como eliminado de la base\n");
            }
            else
            {
                printf("El usuario esta activo\n");
            }
//            for(i=0; i<aux.cantVistas; i++)
//            {
//                printf("%i \n", aux.peliculasVistas[i]);
//            }
            system("pause");

            do
            {
                a=menumodif(archiUsu);

                fseek(archi, (id-1)*sizeof(stUsuario), SEEK_SET); // Se lleva el cursor al principio del archivo para moverse desde allí
                fread(&aux, sizeof(aux), 1, archi); // Lectura del registro indicado

                switch (a)
                {

                case 1:

                    printf("Ingrese el nuevo nombre del usuario: \n");
                    fflush(stdin);
                    gets(aux.nombreUsuario);
                    printf("Desea Modificar otro campo? s/n \n");
                    fflush(stdin);
                    scanf("%c", &control);
                    break;

                case 2:

                    printf("Ingrese el nuevo password del usuario: \n");
                    fflush(stdin);
                    gets(passAux);
                    encriptacionPass(passAux, aux.pass);
                    printf("Desea Modificar otro campo? s/n \n");
                    fflush(stdin);
                    scanf("%c", &control);
                    break;

                case 3:

                    printf("Ingrese el nuevo anio de nacimiento del usuario: \n");
                    scanf("%i", &aux.anioNacimiento);
                    printf("Desea Modificar otro campo? s/n \n");
                    fflush(stdin);
                    scanf("%c", &control);
                    break;

                case 4:

                    printf("Ingrese el nuevo genero del usuario: \n");
                    fflush(stdin);
                    scanf ("%c", &aux.genero);
                    printf("Desea Modificar otro campo? s/n \n");
                    fflush(stdin);
                    scanf("%c", &control);
                    break;

                case 5:

                    printf("Ingrese el nuevo pais del usuario: \n");
                    fflush(stdin);
                    gets(aux.pais);
                    printf("Desea Modificar otro campo? s/n \n");
                    fflush(stdin);
                    scanf("%c", &control);
                    break;

                case 6:

                    printf("Ingrese el nuevo estado en la base del usuario(0 si activo - 1 si eliminado): \n");
                    scanf("%i", &aux.eliminado);
                    printf("Desea Modificar otro campo? s/n \n");
                    fflush(stdin);
                    scanf("%c", &control);
                    break;

//               case 7:
                    //                 cantPelisVistas=registroPelisVistas(pelisVistas[dim], dim);
                    //               printf("El usuario ha visto %i peliculas", cantPelisVistas);

                    break;

                default:
                    exit(1);
                    break;

                }

                fseek(archi, (id-1)*sizeof(stUsuario), SEEK_SET); // Se lleva el cursor al principio del archivo para moverse desde allí
                fwrite(&aux, sizeof(aux), 1, archi); // Lectura del registro indicado

            }
            while(a!=0&&control=='s');
        }

        else
        {

            printf("No se encuentra la ID en el archivo \n");
        }
        fclose(archi);
    }
    else
    {
        printf("ERROR \n");
    }
}

void mostrarUser(char archiUsu[], char nombreUsuario[])//Se Muestra info almacenada al Usuario
{
    FILE *archi = fopen(archiUsu,"rb+");
    stUsuario aux;
    int i=0, flag=0;
    char passAux[10];
    if(archi!=NULL)
    {
        while (!feof(archi)&&flag==0) //Busqueda por nombre del usuario para luego mostrar por pantalla
        {
            fread(&aux,sizeof(stUsuario),1,archi);
            if(strcmp(nombreUsuario,aux.nombreUsuario)==0)
            {
                printf("Sus datos son los siguientes: \n");
                printf("Nombre del Usuario es: %s \n", aux.nombreUsuario);
                desencriptacionPass(aux.pass, passAux);
                printf("Password: %s\n", passAux);
                printf("Su anio de nacimiento es: %i \n", aux.anioNacimiento);
                printf("Su genero es: %c \n", aux.genero);
                printf("Su Pais de nacimiento es: %s \n", aux.pais);
//                printf("IDs de sus Peliculas vistas: \n");
//                for(i=0; i<aux.cantVistas; i++)
//                {
//                    printf("%i \n", aux.peliculasVistas[i]);
//                }
                flag=1;

            }
            else
                printf("Error \n");
            fclose(archi);
        }
    }
    else
        printf("ERROR \n");
}


//void desencriptacionPass(int mEncriptada[2][5], char pass[])
//{
//    int i=0,j=0,k=0;
//
//    int inversa[2][2]= {{5,-3}, {-3,2}};   //Matriz inversa de Matriz LLave
//
//    int  desencriptada[2][5];
//
//    char passbeta[10];
//
//    mostrarPass(2,5,mEncriptada);
//
//    system("pause");
//
//    for (j=0; j<5; j++)
//    {
//        for (i=0; i<2; i++)
//        {
//            productoDeMatrices(inversa,mEncriptada,desencriptada); //Multiplicacion por la inversa para desencriptacion
//        }
//    }
//
//      mostrarPass(2,5,desencriptada);
//
//    system("pause");
//
//    for(j=0; j<5; j++)     //Conversion de matriz a arreglo
//    {
//        for(i=0; i<2; i++)
//        {
//            pass[k]=desencriptada[i][j]; //Conversion de enteros a char
//            k++;
//        }
//    }
//
//}


void desencriptacionPass(int mEncriptada[2][5], char pass[])
{
    int i=0,j=0,k=0;

    int inversa[2][2]= {{5,-3}, {-3,2}};   ///Matriz inversa de Matriz LLave

    int  desencriptada[2][5];

    ///char passbeta[10];

    ///mostrarPass(2,5,mEncriptada);

    ///system("pause");

    for (j=0; j<5; j++)
    {
        for (i=0; i<2; i++)
        {
            productoDeMatrices(inversa,mEncriptada,desencriptada); ///Multiplicacion por la inversa para desencriptacion
        }
    }

    ///  mostrarPass(2,5,desencriptada);

    ///system("pause");

    for(j=0; j<5; j++)     ///Conversion de matriz a arreglo
    {
        for(i=0; i<2; i++)
        {
            pass[k]=desencriptada[i][j]; ///Conversion de enteros a char
            k++;
        }
    }

}

//void productoDeMatrices(int Mat[2][2],int Pass[2][5],int Prod[2][5]) //Funcion para Multiplicacion de Matrices
//{
//    int i,j;
//
//    for (i=0; i<2; i++)
//    {
//        for (j=0; j<5; j++)
//        {
//            Prod[i][j]=(Mat[i][0]*Pass[0][j]+Mat[i][1]*Pass[1][j]);
//        }
//    }
//}

void productoDeMatrices(int Mat[2][2],int Pass[2][5],int Prod[2][5]) ///Funcion para Multiplicacion de Matrices
{
    int i,j;

    for (i=0; i<2; i++)
    {
        for (j=0; j<5; j++)
        {
            Prod[i][j]=(Mat[i][0]*Pass[0][j]+Mat[i][1]*Pass[1][j]);
        }
    }
}


//void encriptacionPass(char pass[], int mEncriptada[2][5]) //Funcion para encriptacion de password
//{
//    int validos,j, i, k=0;
//
//    // Definimos la matriz llave con la que encriptamos el password
//    // en nuestro caso le asginamos el valor numerico de las primeras cuatro letras del nombre del grupo GUMT
//
//    int matrizLLave[2][2]= {{2,3},{3,5}};
//
//    int matrizPass[2][5];
//
//    // Validamos la longitud del password para que en caso de ser inferior a 10 caracteres completar con espacios la matriz
//
//    validos=strlen(pass);
//
//    if (validos<10)
//    {
//        for (i=validos; i<10; i++)
//        {
//            pass[i]='\0';
//        }
//    }
//
//    if (validos==10)
//    {
//        pass[validos+1]='\0';
//    }
//
//    //Conversion de password a Matriz para su posterior multiplicacion
//
//    for(j=0; j<5; j++)
//    {
//        for(i=0; i<2; i++)
//        {
//            for(i=0; i<2; i++)
//            {
//                matrizPass[i][j]=pass[k];
//                k++;
//            }
//        }
//    }
//
//
//    //Funciones agregadas para verificar, en caso de error, que muestre si el proceso anterior se realizo correctamente
//
//    //mostrarPass(2,5,matrizPass);
//
//    //system("pause");
//
//
//    //Encriptacion de matrices a traves de multiplicacion de password por matriz llave
//
//    productoDeMatrices(matrizLLave, matrizPass, mEncriptada);
//
//    //Funciones agregadas para verificar, en caso de error, que muestre si el proceso anterior se realizo correctamente
//
//    //mostrarPass(2,5,mEncriptada);
//
//    //system("pause");
//}

void encriptacionPass(char pass[], int mEncriptada[2][5]) ///Funcion para encriptacion de password
{
    int validos,j, i, k=0;

    /// Definimos la matriz llave con la que encriptamos el password
    /// en nuestro caso le asginamos el valor numerico de las primeras cuatro letras del nombre del grupo GUMT

    int matrizLLave[2][2]= {{2,3},{3,5}};

    int matrizPass[2][5];

    /// Validamos la longitud del password para que en caso de ser inferior a 10 caracteres completar con espacios la matriz

    validos=strlen(pass);

    if (validos<10)
    {
        for (i=validos; i<10; i++)
        {
            pass[i]='\0';
        }
    }

    if (validos==10)
    {
        pass[validos+1]='\0';
    }

    ///Conversion de password a Matriz para su posterior multiplicacion

    for(j=0; j<5; j++)
    {
        for(i=0; i<2; i++)
        {
            for(i=0; i<2; i++)
            {
                matrizPass[i][j]=pass[k];
                k++;
            }
        }
    }


    ///Funciones agregadas para verificar, en caso de error, que muestre si el proceso anterior se realizo correctamente

    ///mostrarPass(2,5,matrizPass);

    ///system("pause");


    ///Encriptacion de matrices a traves de multiplicacion de password por matriz llave

    productoDeMatrices(matrizLLave, matrizPass, mEncriptada);

    ///Funciones agregadas para verificar, en caso de error, que muestre si el proceso anterior se realizo correctamente

    ///mostrarPass(2,5,mEncriptada);

    ///system("pause");
}


void mostrarArrayUsuarios(stUsuario array[], int validos)//Muestra los datos de usuarios por pantalla
{
    //stUsuario aux;
    int i=0, j=0;
    char passAux[10];
    printf("El listado actual de usuarios existentes es el siguiente:\n\n");
    for (i=0; i<validos; i++)
    {
        if(array[i].eliminado!=1)
        {
            printf("El ID del Usuario es: %i \n", array[i].idUsuario);
            printf("El nombre del Usuario es: %s \n", array[i].nombreUsuario);
            desencriptacionPass(array[i].pass, passAux);
            printf("Password: %s \n", passAux);
            printf("El anio de nacimiento del Usuario es: %i \n", array[i].anioNacimiento);
            printf("El genero del Usuario es: %c \n", array[i].genero);
            printf("El nombre del Usuario es: %s \n", array[i].pais);
            printf("IDs de Peliculas vistas: \n");
//            for(j=0; j<array[i].cantVistas; j++)
//            {
//                printf("%i \n", array[i].peliculasVistas[j]);
//            }
            printf("\n \n");
        }
    }

}

int cargarArrayUsuarios(char archiUsu[], stUsuario array[])//Se pasan los datos de usuarios a un arreglo y devuelve la cantidad de registros almacenados(validos)
{
    FILE *archi;

    archi=fopen(archiUsu, "rb");

    stUsuario aux;

    int i=0, validos=0;

    if (archi==NULL)
    {
        printf("\n ERROR");
    }
    else
    {
        for(i=0; !feof(archi); i++)
        {
            fread(&aux, sizeof(stUsuario), 1, archi);

            if(!feof(archi))
            {
                array[i]=aux;
            }
        }
        fclose(archi);
    }

    validos=i-1;

    return validos;
}

void listadoUsuarios(char archiUsu[])//Se Muestra Listado de Usuarios al Admin
{
    FILE *archi;

    archi=fopen(archiUsu,"rb");

    stUsuario arraydeusuarios[50];

    int validos=0;

    if(archi==NULL)
    {
        printf("ERROR");
    }
    else
    {
        validos=cargarArrayUsuarios(archiUsu, arraydeusuarios);//se carga el array de usuarios y devuelve los validos
        mostrarArrayUsuarios(arraydeusuarios, validos);//se muestra el array por pantalla
    }

    system("pause");

    fclose(archi);

}

void consultaUsuarioAdmin(char archiUsu[])//Se Muestra info por ID al Admin
{
    FILE *archi;

    archi=fopen(archiUsu,"rb");

    stUsuario arraydeusuarios[50];

    int validos=0, id=0, i = 0, j=0, flag=0;

    char passAux[10];

    if(archi==NULL)
    {
        printf("ERROR");
    }
    else
    {
        printf("Ingrese el ID del usuario que desea consultar la informacion: \n");
        scanf("%i", &id);
        validos=cargarArrayUsuarios(archiUsu, arraydeusuarios);//se carga el array de usuarios y devuelve los validos
        for (i=0; i<validos; i++)
        {
            if(id==arraydeusuarios[i].idUsuario&&arraydeusuarios[i].eliminado!=1)//busqueda en el array hasta encontrar el id y mostrarlo por pantalla
            {
                printf("El nombre del Usuario es: %s \n", arraydeusuarios[i].nombreUsuario);
                desencriptacionPass(arraydeusuarios[i].pass, passAux);
                printf("Password: %s", passAux);
                printf("El anio de nacimiento del Usuario es: %i \n", arraydeusuarios[i].anioNacimiento);
                printf("El genero del Usuario es: %c \n", arraydeusuarios[i].genero);
                printf("El Usuario es de: %s \n", arraydeusuarios[i].pais);
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

void consultaUsuario(char archiUsu[], char nombreUsuario [])//Se Muestra info por Nombre al Usuario
{
    FILE *archi;

    archi=fopen(archiUsu,"rb");

    stUsuario usuAux;

    int j=0, flag=0;

    char passAux[10];

    if(archi==NULL)
    {
        printf("ERROR");
    }
    else
    {
        fread(&usuAux, sizeof(stUsuario), 1, archi); // Lectura del registro indicado
        while(!feof(archi)&&flag!=1)
        {
            if(strcmpi(nombreUsuario,usuAux.nombreUsuario)==0)//busqueda en el array hasta encontrar el nombre y mostrarlo por pantalla
            {
                printf("Nombre: %s \n", usuAux.nombreUsuario);
                desencriptacionPass(usuAux.pass, passAux);
                printf("Password: %s \n", passAux);
                printf("Anio de nacimiento: %i \n", usuAux.anioNacimiento);
                printf("Genero: %c \n", usuAux.genero);
                printf("Pais de nacimiento: %s \n", usuAux.pais);
                printf("\n \n");
                flag=1;
            }
            else
            {
                fread(&usuAux, sizeof(stUsuario), 1, archi);
            }
        }
        if(flag==0) //Flag en caso de no encontrar el usuario
        {
            printf("Error \n");
        }

        fclose(archi);

    }

    system("pause");

}

void cargarPeliAUser(stCelda arregloUsuActivos[], int validos, char nombreUsuario[],nodoListaPelicula Peli)
{
    int posicion=buscarPosicionUsuario(arregloUsuActivos, validos, nombreUsuario);
    agregarNodoFinal(arregloUsuActivos[posicion].listaPelis, Peli);
}

//***********************************************************************************************************************************//
//                                                  FUNCIONES DE VALIDACION
//***********************************************************************************************************************************//

//int validarLongPass(char pass[])  // Valida si la contraseña ingresada tiene más de 10 caracteres
//{
//    int flag=0;
//
//    if(strlen(pass)>10)  //Chequea la longitud del nombre de usuario ya que el máximo son 10 caracteres. Devuelve 1 si positivo
//    {
//        flag=1;
//    }
//    return flag;
//}

int validarLongPass(char pass[])  /// Valida si la contrase�a ingresada tiene m�s de 10 caracteres
{
    int flag=0;

    if(strlen(pass)>10)  ///Chequea la longitud del nombre de usuario ya que el m�ximo son 10 caracteres. Devuelve 1 si positivo
    {
        flag=1;
    }
    return flag;
}

int validarUserExiste(char archiUsu[], char nombreUsuario[]) // Valida si el nombre del usuario ingresado actualmente ya existe en el archivo
{
    stUsuario usuAux; // Se crea estructura auxiliar para trabajo temporal
    int flag=0;

    FILE * archi;

    archi=fopen(archiUsu, "rb"); // Abre al archivo en modo sólo lectura para chequear acceso

    if(archi==NULL)
    {
        printf("No se pudo abrir el archivo para consultar si el usuario ya existe");
        exit(1);
    }

    else
    {

        while((fread(&usuAux, sizeof(stUsuario), 1, archi)>0) && (flag!=1))  // Realiza el proceso mientras haya registros en el archivo
        {
            if(strcmp(usuAux.nombreUsuario, nombreUsuario)==0)  //Chequea si ambos strings son iguales
            {
                flag=1; // Si ambos strings son iguales, asigno valor 1 a flag como positivo
            }
        }
    }

    fclose(archi); // Cierra el archivo

    return flag; // Devuelve el valor de flag para su proceso en la función que la invoca
}

int validarTipoAlfanumerico(char cadena[])  // Devuelve 1 si la variable analizada es cadena, 0 si no lo es
{

    int i=0;
    int j=0;
    int flag=0;

    j=strlen(cadena);

    while((i<j) && (flag==0))
    {
        if(isalnum(cadena[i])!=0)
        {
            i++;
        }
        else
        {
            flag=1;
        }
    }
    return flag;
}


int validarTipoChar(char cadena[])  // Devuelve 1 si la variable analizada es cadena, 0 si no lo es
{

    int i=0;
    int j=0;
    int flag=0;

    j=strlen(cadena);

    while((i<j) && (flag==0))
    {
        if(isalpha(cadena[i])!=0)
        {
            i++;
        }
        else
        {
            flag=1;
        }
    }
    return flag;
}

//int validacionPass(char archiUsu[], char nombre[], char pass[])
//{
//    //Funcion de validacion de password ingresado por usuario a traves de desencriptacion de matriz codificada
//    //Retorna true or false
//
//    stUsuario usuario;
//
//    int coincidencia=0;
//
//    char passGuardado[11];
//
//    FILE *archi;
//
//    archi=fopen(archiUsu, "rb");
//
//    if (archi==NULL)
//    {
//        printf("No se pudo abrir el archivo");
//    }
//    else
//    {
//        while ((fread(&usuario, sizeof(stUsuario), 1,archi)>0 && coincidencia==0))
//        {
//            if(strcmpi(usuario.nombreUsuario,nombre)==0) //Validacion nombre de usuario
//            {
//                desencriptacionPass(usuario.pass, passGuardado);
//                if(strcmpi(pass,passGuardado)==0)//Validacion Password
//                {
//                    coincidencia=1;//flag
//                }
//
//            }
//            else
//            {
//                coincidencia=0;
//            }
//        }
//
//        fclose(archi);
//    }
//
//    return coincidencia;
//}


int validacionPass(stCelda arregloUsuActivos[], char nombre[], char pass[]) // Pasa por parámetro la estructura en lugar del archivo
{
    ///Funcion de validacion de password ingresado por usuario a traves de desencriptacion de matriz codificada
    ///Retorna true or false

    int coincidencia=0, i, validos;

    validos=calcularValidos(arregloUsuActivos); // Esta función no está incluida

    char passGuardado[11];

    for(i=0; i<validos&&coincidencia==0; i++)
    {
        if(strcmpi(arregloUsuActivos[i].usr.nombreUsuario,nombre)==0) ///Validacion nombre de usuario
        {
            desencriptacionPass(arregloUsuActivos[i].usr.pass, passGuardado);
            if(strcmpi(pass,passGuardado)==0)///Validacion Password
            {
                coincidencia=1;///flag
            }

        }
        else
        {
            coincidencia=0;
        }
    }


    return coincidencia;
}

//int validacionPassAdmin(char pass[]) //No se pasa por parametro el nombre del administrador ya que estos poseen un solo nombre de usuario
//{
//    //Funcion de validacion de password ingresado por administrador a traves de desencriptacion de matriz codificada y comparacion con la ingresada
//    //Retorna true or false
//
//    int coincidencia=0;
//
//    char passAdmin[11];
//
//    int passEncriptada[2][5]= {{557,566,499,208,0},{894,907,798,312,0}};
//
//    FILE *archi;
//
//    archi=fopen(archiUsu, "rb");
//
//    if (archi==NULL)
//    {
//        printf("No se pudo abrir el archivo");
//    }
//    else
//    {
//        desencriptacionPass(passEncriptada, passAdmin);
//        if(strcmpi(pass,passAdmin)==0)//Validacion Password
//        {
//            coincidencia=1;//flag
//        }
//
//        else
//        {
//                coincidencia=0;
//        }
//    }
//
//    return coincidencia;
//}


int validacionPassAdmin(char pass[]) ///No se pasa por parametro el nombre del administrador ya que el admin poseen un solo nombre de usuario
{
    ///Funcion de validacion de password ingresado por administrador a traves de desencriptacion de matriz codificada y comparacion con la ingresada
    /// Retorna true or false

    int coincidencia=0;

    char passAdmin[11];

    int passEncriptada[2][5]= {{557,566,499,208,0},{894,907,798,312,0}};

    desencriptacionPass(passEncriptada, passAdmin);
    if(strcmpi(pass,passAdmin)==0)//Validacion Password
    {
        coincidencia=1;//flag
    }

    else
    {
        coincidencia=0;
    }


    return coincidencia;
}


void mostrarUsuarios(char archiUsu[]) // Funcion auxiliar usada para chequear que el sistema funcione correctamente visualizando los registros ingresados por pantalla -
{
    char passAux[11];

    stUsuario usuAux;

    FILE * archi;

    archi=fopen(archiUsu, "rb");

    if(archi==NULL)
    {
        printf("No se pudo abrir el archivo");
    }

    else
    {

        while(!feof(archi)) // Lectura de los datos que existen ene el archivo(Como función devuelve la cantidad de datos leídos)
        {
            fread(&usuAux, sizeof(stUsuario), 1, archi);
            if(!feof(archi)&&usuAux.eliminado!=1) //Validacion de fin de archivo y usuario no eliminado
            {
                printf("ID: %i\n", usuAux.idUsuario);
                printf("Nombre de usuario: %s\n", usuAux.nombreUsuario);
                desencriptacionPass(usuAux.pass, passAux);
                printf("Password: %s\n", passAux);
                printf("Anio de nacimiento: %i\n", usuAux.anioNacimiento);
                printf("Genero: %c\n", usuAux.genero);
                printf("Pais: %s\n", usuAux.pais);
                printf("Estado en la base: %i\n\n", usuAux.eliminado);
            }
        }

        fclose(archi);

    }

}


void mostrarPass(int f,int c,int M[f][c]) //Funcion para mostrar matrices por pantalla (utilizada para verificacion de procesos)
{
    int i, j;

    printf("\n");

    printf("*********\n");

    for (i=0; i<f; i++)
    {
        for (j=0; j<c; j++)
        {
            printf("%i  ", M[i][j]);
        }
        printf("\n");
    }
    printf("\n*********");
}

int buscarPosicionUsuario(stCelda arregloUsuActivos, int validos, char nombreUsuario[])
{
    int i, flag=0;
    for(i=0; i<validos&&flag==0; i++)
    {
        if(strcmp(arregloUsuActivos[i].usr.nombreUsuario, nombreUsuario))
            flag=1
    }
    return i;
}
