#include "libreria.h"



//***********************************************************************************************************************************//
//                                                  FUNCIONES DE VALIDACION
//***********************************************************************************************************************************//


int validarLongPass(char pass[])  /// Valida si la contraseña ingresada tiene mas de 10 caracteres
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


int validacionPass(stCelda arregloUsuActivos[], char nombre[], char pass[]) // Pasa por parámetro la estructura en lugar del archivo
{
    ///Funcion de validacion de password ingresado por usuario a traves de desencriptacion de matriz codificada
    ///Retorna true or false

    int coincidencia=0, i;

//    validos=calcularValidos(arregloUsuActivos); // Esta función no está incluida

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




int cantUsuariosActivos(char archiUsu[]) // Cuenta usuarios activos en archivo inicial
{

    int cantUsuarios=0; // En esta variable se almacenará la cantidad de usuarios activos y será retornada por la función
    stUsuario aux; //Creo celda auxiliar para la carga y el conteo de usuarios activos

    FILE*archi; // Asigna espacio en buffer para almacenar temporariamente los datos en proceso mientras se pasa de la memoria al archivo

    archi=fopen(archiUsu, "rb"); // Abre archivo bajo la modalidad solo lectura

    if(archi) // Si se pudo abrir el archivo
    {
        while(fread(&aux,sizeof(stUsuario),1,archi)>0) // Se leen los registros iterativamente cargando sus datos hasta en una estructura auxiliar hasta llegar al final del archivo(en este caso usamos fread>0)
        {
            if(aux.eliminado==0) // Si están activos
            {
                cantUsuarios++; // Se suman en el acumulador
            }
        }

        fclose(archi); // Se cierra el archivo
    }

    else //Si no se pudo abrir el archivo
    {
        printf("No se pudo abrir el archivo de usuarios"); // Se devuelve mensaje de error
    }

    return cantUsuarios; // Si se pudieron contar, se retorna la cantidad de usuarios activos
}


int cantUsuariosInactivos(char archiUsu[]) // Cuenta usuarios inactivos en archivo inicial
{

    int cantUsuarios=0; // En esta variable se almacenará la cantidad de usuarios inactivos y será retornada por la función
    stCelda aux; // Creo celda auxiliar para la carga y el conteo de usuarios inactivos

    FILE*archi; // Asigna espacio en buffer para almacenar temporariamente los datos en proceso mientras se pasa de la memoria al archivo

    archi=fopen(archiUsu, "rb"); // Se abre el archivo como solo lectura

    if(archi) // Si se pudo abrir el archivo
    {
        while(fread(&aux,sizeof(stCelda),1,archi)>0) // Se leen los registros iterativamente cargando sus datos hasta en una estructura auxiliar hasta llegar al final del archivo(en este caso usamos fread>0)
        {
            if(aux.usr.eliminado==1) // Si el usuario fue eliminado
            {
                cantUsuarios++; //Se acumula en la variable a retornar
            }
        }
        fclose(archi); // Se cierra el archivo
    }
    else
    {
        printf("No se pudo abrir el archivo de usuarios"); // Si no se pudo abrir el archivo se da este mensaje de error
    }

    return cantUsuarios; // Se devuelve la cantidad de usuarios inactivos que existen en el archivo
}


int cantUsuariosTotales(char archiUsu[]) // Función utilizada para contar la cantidad total de registros guardados en el archivo
{

    int cantUsuarios=0; // Variable a retornar

    FILE*archi; //Reserva de espacio en buffer

    archi=fopen(archiUsu, "rb"); //Apertura de archivo como solo lectura

    if(archi) // Si se pudo abrir el archivo
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
        fclose(archi); // Se cierra el archivo
    }
    else
    {
        printf("No se pudo abrir el archivo de usuarios"); // Si no se pudo abrir el archivo se devuelve mensaje de error
    }

    return cantUsuarios; // Se devuelve la cantidad de registros totales contados
}


int cargarArchiUsuToArreglo(char archiUsu[]) // Función que carga los usuarios activos del archivo en el arreglo dinámico correspondiente
{
    int i=0; // Variable itera asignando la posición del arreglo en la que almacenar el registro leído del archivo
    int flag=0; // Variable que devuelve si la carga del archivo fue exitosa a la función "cargaInicial" para determinar si se inicia el menú o no

    stUsuario aux; // Estructura que contiene a los datos de cada usuario(sin puntero a lista, la que lo incluye es stCelda)

    validos=cantUsuariosActivos(archiUsu); // Calcula la cantidad inicial de usuarios activos en el archivo para poder crear el arreglo dinámico

    arregloUsuActivos=(stCelda*)malloc(sizeof(stCelda)*validos); // Reserva en memoria espacio del tamaño de validos para el arreglo dinámico de usuarios activos

    FILE*archi; // Reserva de espacio en buffer

    archi=fopen(archiUsu, "rb"); // Se abre el archivo como lectura/escritura para que si no existe

    if(archi) // Si se abrió el archivo...
    {
        flag=1;

        while(fread(&aux, sizeof(stUsuario), 1, archi)>0) // Se almacena el registro en una estructura temporaria
        {
            if(aux.eliminado==0) // Si el usuario actual está activo(es decir, no eliminado)
            {
                arregloUsuActivos[i].usr=aux; // Se cargan los datos del usuario(sub estructura stUsuario) en el ADL de usuarios activos
                arregloUsuActivos[i].listaPelis=inicLista(); // Se incializa el puntero de su lista a peliculas vistas en NULL
//                PelisxUsuarioArchivoToADL(arregloUsuActivos, aux.idUsuario, i); // Función que carga las películas vistas por el usuario actual desde el archivo de pelis x usuario
                i++; // Variable que itera para asignar la posición en la que almacenar el registro a guardar
            }
        }
        fclose(archi); // Se cierra el archivo
    }

    else // Si no se pudo abrir el archivo se da mensaje de error
    {
        printf("El archivo de usuarios no existe");
    }

    return flag;
}


void altaUsuarios(char archiUsu[])// Funcion general de alta de usuarios
{

    // Declaración de variables locales
    int validacionPais=0;
    int usuarioExiste=0;
    int longPass=0;
    int i=0;
    char passAux[11];
    char control='s'; // Variable de control para ciclo while principal de solicitud de datos de usuarios


    stUsuario usuAux; // Se crea estructura auxiliar para trabajo temporal

    usuAux.idUsuario=cantUsuariosTotales(archiUsu); // Se iguala el ID por primera vez dentro de la sesión de alta a la cantidad total de registros(activos+eliminados) para inciar e acumular a partir de este valor. Luego se incrementa dentro del while

    FILE *archi; // Asigna espacio en buffer para almacenar temporariamente los datos en proceso mientras se pasa de la memoria al archivo
    archi=fopen(archiUsu, "a+b"); //Se chequea el acceso al archivo bajo la modalidad lectura-escritura. Agrega al final sin borrar la info vigente

    if(archi==NULL) // Chequea si NO se pudo abrir el archivo
    {
        printf("\nNo se pudo abrir el archivo");
        exit(1); // Sale del programa si no se pudo abrir el archivo
    }

    else // Si se pudo abrir el archivo, ejecuta el ingreso de tantos usuarios como la persona desee(var de control)
    {

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
                printf("Ese usuario ya existe, tiene 3 intentos mas\n"); // En total se ofrecen cuatro intentos de ingreso por nombre de usuario existente en la base

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
                    exit(1); // Si supero los 4 intentos sale del programa
                }

                else
                {
                    printf("El ingreso ha sido exitoso\n"); // Confirma si el ingreso del nombre de usuario fue exittoso
                }
            }

            printf("Ingrese la contrasenia(maximo 10 caracteres): ");
            fflush(stdin);
            gets(passAux);
            longPass=validarLongPass(passAux); // Chequea que el nombre de usuario no supere los 10 caracteres mediante un flag

            if(longPass!=0) // Si la clave supera los 10 caracteres le permite al usuario probar 3 veces más
            {
                printf("La contrasenia debe tener 10 caracteres como maximo, tiene 3 intentos mas\n");

                while((longPass!=0) && (i<3))
                {
                    printf("Ingrese una nueva contrasenia: ");
                    fflush(stdin);
                    gets(passAux);
                    longPass=validarLongPass(passAux); // Chequea que el nombre de usuario no supere los 10 caracteres mediante un flag
                    i++;
                }

                if(longPass==0) // Confirma si se valida la longitud del password
                {
                    printf("El ingreso ha sido exitoso\n");
                }

                else
                {
                    printf("\nHa superado los 4 intentos, vuelva a probar mas tarde"); // Si no pudo ingresar un pass de hasta 10 caracteres se cierra el pgma
                    exit(1);
                }

            }

            encriptacionPass(passAux, usuAux.pass); // Se encripta el password ingresado por el usuario

            printf("Ingrese anio de nacimiento: "); //Solicitud de datos del usuario
            scanf("%i", &usuAux.anioNacimiento);

            printf("Ingrese el genero(m/f): "); //Solicitud de datos del usuario
            fflush(stdin);
            scanf("%c", &usuAux.genero);

            do //Solicitud de datos del usuario mientras el país no sea sólo de caracteres
            {
                printf("Ingrese el pais(Solo caracteres): ");
                fflush(stdin);
                gets(usuAux.pais);
                validacionPais=validarTipoChar(usuAux.pais);
            }
            while(validacionPais!=0);

            usuAux.eliminado=0; // Se asigna flag negativo como valor predeterminado

            usuAux.admin=0; // Por defecto NO es administrador

            usuAux.idUsuario++; // Usa cantidad total de usuarios inicial en archivo para asignar el ID que es independiente de si el usuario está o no activo. Ver declaración de variables en esta función

            arregloUsuActivos=realloc(arregloUsuActivos, sizeof(stCelda)*(validos+1)); // Agranda el arreglo en un registro con validos más uno

            arregloUsuActivos[validos].usr=usuAux; // Carga los datos del stUsuario que se está creando en un arreglo auxiliar/temporal que luego se volcará al arreglo de usuarios activos y de ahí se pasará al archivo
            arregloUsuActivos[validos].listaPelis=inicLista(); //Inicializa el puntero a la lista de peliculas en NULL

            validos++; // Incremento el valor de válidos

            fwrite(&usuAux, sizeof(usuAux), 1, archi); // Se graban los datos del nuevo usuario en el archivo

            printf("Desea continuar ingresando usuarios(s/n?"); // Se consulta si se desea continuar ingresando usuarios en esta sesión
            fflush(stdin);
            scanf("%c", &control);

            if(control=='s')
            {
                system("cls");
                puts("****** ALTA DE OTRO USUARIO ******\n");
            }

        }
        fclose(archi); // Cierre del archivo
    }

}


void bajaUsuario(char archiUsu[], stCelda* arregloUsuActivos) //Elimina usuarios pasando asignando valor verdadero al campo "eliminado"
{
    char control='n';
    int idUsu=0;
    int posId=0;

    stUsuario usuAux;

    FILE *archi=fopen(archiUsu, "r+b");

    if(archi==NULL)
    {
        printf("No se pudo abrir el archivo");
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
        if(idUsu >=0 && idUsu<validos)
        {
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

                posId=buscarPosUsuarioPorId(idUsu);
                arregloUsuActivos[posId].usr.eliminado=1;

                printf("\nEl usuario se elimino correctamente\n");
                printf("\nNombre del usuario: %s", usuAux.nombreUsuario);
                printf("\nEstado: %i", usuAux.eliminado);

            }

            else // Si no confirma, se sale del programa
            {
                exit(1);
            }
        }
        else
        {
            printf("El usuario indicado no existe");
        }
        fclose(archi);
    }
}


//void modificarUsuario()//Modificacion de usuario para administrador
//{
//    FILE *archi = fopen(archiUsu,"rb+");
//
//    stUsuario aux;
//    int flag=0, id=0, a=0, posId=0;
//    char control='s', passAux[10];
//
//    if(archi!=NULL)
//    {
//        system("cls");
//        printf("\n");
//        printf("\n*****************************************************");
//        printf("\n\tMODIFICACION DE USUARIOS");
//        printf("\n*****************************************************");
//        printf("\n");
//
//        printf("\nIngrese la ID que desea buscar \n");
//        scanf("%i", &id);
//
//        while (!feof(archi)&&flag==0) //Busqueda por id de usuario
//        {
//            fread(&aux,sizeof(stUsuario),1,archi);
//            if(id==aux.idUsuario)
//            {
//                flag=1;
//            }
//        }
//
//        if(flag==1) //En caso de que se encuentre el usuario se muestra por pantalla y se procede a seleccionar el campo a modificar
//        {
//
//            fseek(archi, (id-1)*sizeof(stUsuario), SEEK_SET); // Se lleva el cursor al principio del archivo para moverse desde allí
//            fread(&aux, sizeof(stUsuario), 1, archi); // Lectura del registro indicado
//
//            printf("Los datos del usuario son los siguientes: \n");
//            printf("El ID del usuario es: %i (NO se puede modificar)\n", aux.idUsuario);
//            printf("El nombre del Usuario es: %s \n", aux.nombreUsuario);
//            desencriptacionPass(aux.pass, passAux);
//            printf("Password: %s\n", passAux);
//            printf("El anio de nacimiento del Usuario es: %i \n", aux.anioNacimiento);
//            printf("El genero del Usuario es: %c \n", aux.genero);
//            printf("El pais del Usuario es: %s \n", aux.pais);
//            if(aux.admin==1)
//            {
//                printf("El usuario seleccionado tambien es administrador");
//            }
//            else
//            {
//                printf("El usuario NO tiene permisos de administrador");
//            }
//            if(aux.eliminado==1)
//            {
//                printf("El usuario ha sido marcado como eliminado de la base\n");
//            }
//            else
//            {
//                printf("El usuario esta activo\n");
//            }
//
//            system("pause");
//
//            do
//            {
//                a=menumodif(archiUsu);
//
//                fseek(archi, (id-1)*sizeof(stUsuario), SEEK_SET); // Se lleva el cursor al principio del archivo para moverse desde allí
//                fread(&aux, sizeof(aux), 1, archi); // Lectura del registro indicado
//
//                switch (a)
//                {
//
//                case 1:
//
//                    printf("Ingrese el nuevo nombre del usuario: \n");
//                    fflush(stdin);
//                    gets(aux.nombreUsuario);
//                    strcpy(arregloUsuActivos[posId].usr.nombreUsuario, aux.nombreUsuario);
//                    printf("Desea Modificar otro campo? s/n \n");
//                    fflush(stdin);
//                    scanf("%c", &control);
//                    break;
//
//                case 2:
//
//                    printf("Ingrese el nuevo password del usuario: \n");
//                    fflush(stdin);
//                    gets(passAux);
//                    encriptacionPass(passAux, arregloUsuActivos[posId].usr.pass);
////                    arregloUsuActivos[posId].usr.pass=aux.pass;
//                    printf("Desea Modificar otro campo? s/n \n");
//                    fflush(stdin);
//                    scanf("%c", &control);
//                    break;
//
//                case 3:
//
//                    printf("Ingrese el nuevo anio de nacimiento del usuario: \n");
//                    scanf("%i", &aux.anioNacimiento);
//                    arregloUsuActivos[posId].usr.anioNacimiento=aux.anioNacimiento;
//                    printf("Desea Modificar otro campo? s/n \n");
//                    fflush(stdin);
//                    scanf("%c", &control);
//                    break;
//
//                case 4:
//
//                    printf("Ingrese el nuevo genero del usuario: \n");
//                    fflush(stdin);
//                    scanf ("%c", &aux.genero);
//                    arregloUsuActivos[posId].usr.genero=aux.genero;
//                    printf("Desea Modificar otro campo? s/n \n");
//                    fflush(stdin);
//                    scanf("%c", &control);
//                    break;
//
//                case 5:
//
//                    printf("Ingrese el nuevo pais del usuario: \n");
//                    fflush(stdin);
//                    gets(aux.pais);
//                    strcpy(arregloUsuActivos[posId].usr.pais, aux.pais);
//                    printf("Desea Modificar otro campo? s/n \n");
//                    fflush(stdin);
//                    scanf("%c", &control);
//                    break;
//
//                case 6:
//
//                    printf("Ingrese el nuevo estado en la base del usuario(0 si activo - 1 si eliminado): \n");
//                    scanf("%i", &aux.eliminado);
//                    arregloUsuActivos[posId].usr.eliminado=aux.eliminado;
//                    printf("Desea Modificar otro campo? s/n \n");
//                    fflush(stdin);
//                    scanf("%c", &control);
//                    break;
//
//                case 7:
//
//                    printf("Ingrese el nivel de permisos para este usuario: 0 para usuario sin facultades o 1 para administrador: \n");
//                    scanf("%i", &aux.admin);
//                    arregloUsuActivos[posId].usr.admin=aux.admin;
//                    printf("Desea Modificar otro campo? s/n \n");
//                    fflush(stdin);
//                    scanf("%c", &control);
//                    break;
//
//                default:
//                    exit(1);
//                    break;
//
//                }
//
//                fseek(archi, (id-1)*sizeof(stUsuario), SEEK_SET); // Se lleva el cursor al principio del archivo para moverse desde allí
//                fwrite(&aux, sizeof(aux), 1, archi); // Lectura del registro indicado
//
//            }
//            while(a!=0&&control=='s');
//        }
//
//        else
//        {
//
//            printf("No se encuentra la ID en el archivo \n");
//        }
//        fclose(archi);
//    }
//    else
//    {
//        printf("ERROR \n");
//    }
//}


void imprimirUsuarioSinPass(stUsuario usr) // TP 2: Imprime en pantalla los datos del/los usuario/s pasado/s por parámetro - CON PASSWORD P/ADMIN
{
    puts("\n\n");
    printf("ID del usuario: %i", usr.idUsuario);
    printf("Nombre: %s\n", usr.nombreUsuario);
    printf("Genero: %c\n", usr.genero);
    printf("Pais: %s\n", usr.pais);
    printf("Anio de nacimiento: %i\n", usr.anioNacimiento);


}

void imprimirUsuarioConPass(stUsuario usr) // TP 2: Imprime en pantalla los datos del/los usuario/s pasado/s por parámetro - CON PASSWORD P/USUARIO
{
    char passAux[10];

    puts("\n\n");
    printf("ID del usuario: %i", usr.idUsuario);
    printf("Nombre: %s\n", usr.nombreUsuario);
    desencriptacionPass(usr.pass, passAux);
    printf("Password: %s \n", passAux);
    printf("Genero: %c\n",usr.genero);
    printf("Pais: %s\n", usr.pais);
    printf("Anio de nacimiento: %i\n", usr.anioNacimiento);


}


void mostrarUsuarios() //TP 2: Pasa a la función imprimir usuarios los usuarios activos para mostrar sus datos
{
    int i=0;
    printf("El listado actual de usuarios activos es el siguiente:\n\n");
    while(i<validos)
    {
        if(arregloUsuActivos[i].usr.eliminado==0)
        {
            imprimirUsuarioConPass(arregloUsuActivos[i].usr);
            //mostrarNodoPelis(arregloUsuActivos[i].listaPelis);

        }
        i++;
    }
}



int buscarPosicionUsuario(stCelda* arregloUsuActivos, char nombreUsuario[])
{
    int i, flag=0;
    for(i=0; i<validos&&flag==0; i++)
    {
        if(strcmp(arregloUsuActivos[i].usr.nombreUsuario, nombreUsuario)==0)
            flag=1;
    }
    return flag;
}


int buscarPosUsuarioPorId(int id)
{
    int i, flag=0;
    for(i=0; i<validos&&flag==0; i++)
    {
        if(arregloUsuActivos[i].usr.idUsuario==id)
            flag=1;
    }
    return flag;
}


void consultarUsuario()
{

    int opcion=0, pos=0;

    system("cls");
    printf("\n");
    printf("\n*****************************************************");
    printf("\n\t\tCONSULTA DE USUARIO");
    printf("\n*****************************************************");
    printf("\n");

    printf("Desea buscar al usuario por ID(1) o por nombre(2)? Ingrese su opcion: ");
    fflush(stdin);
    scanf("%i", &opcion);

    if(opcion==1)
    {
        int idAux;
        printf("\nIngrese el ID del usuario a consultar: ");
        fflush(stdin);
        scanf("%i", &idAux);
        pos=buscarPosUsuarioPorId(idAux);
        if(arregloUsuActivos[pos].usr.eliminado==0)
        {
            printf("Los datos del usuario consultado son: \n");
            imprimirUsuarioSinPass(arregloUsuActivos[pos].usr);
        }
        else
        {
            printf("El usuario buscado esta eliminado");
        }
    }

    if(opcion==2)
    {
        char nombreAux[15];
        printf("\nIngrese el nombre del usuario a consultar: ");
        fflush(stdin);
        gets(nombreAux);
        pos=buscarPosicionUsuario(arregloUsuActivos, nombreAux);
        if(arregloUsuActivos[pos].usr.eliminado==0)
        {
            printf("Los datos del usuario consultado son: \n");
            imprimirUsuarioSinPass(arregloUsuActivos[pos].usr);
        }
        else
        {
            printf("El usuario buscado esta eliminado");
        }

    }

}





// ********************* FUNCIONES DE PASS

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



