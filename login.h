/* Funciones referentes al login de usuarios. Utilizando arboles binarios
*  Fecha: 30/11/2017
*  Elaborado por: John Sebastian Nieto gil
*  Elaborado por: Ricardo Andres Villalobos
*/
#define RESERVAR_USUARIO (Usuario *)malloc(sizeof(Usuario))

//Estructura tipo lista arbol
struct Usuario
{
	int id;
	char user[10];
	char pass[10];
	Usuario *izq, *der;
}usu, *pUsu = &usu; //uVariables tipo usuario para el manejo de archivos

int idUser = 0;
//Prototipo de funciones


//Prototipo de funciones
bool guardarUsuarioArchivo(Usuario* );
void mostrarArbol(Usuario *, int);
int loguear(Usuario *);
bool inicializarUsuarios(Usuario* &);
Usuario *crearUsuario(char [], char []);
void insertarUsuario(Usuario *&, char [], char []);
int busqueda(Usuario *usuario, char [], char []);


//Carga los usuarios almecenados desde un archuvo
bool inicializarUsuarios(Usuario* &nodo)
{
	FILE *archivo;
	
	archivo = fopen("datos/usuarios.txt", "rb");
	
	if(archivo == NULL)
	{
		return false;
	}
	else
	{
		while(fread(pUsu, sizeof(*pUsu), 1, archivo))
		{
			insertarUsuario(nodo, pUsu->user, pUsu->pass);
		}
	}
	fclose(archivo);
}

//Guarda los datos del struct en un archivo
bool guardarUsuarioArchivo(Usuario* nuevoNodo)
{
	FILE *archivo;
	
	archivo = fopen("datos/usuarios.txt", "ab");
	
	if(archivo == NULL)
	{
		return false;
	}
	fwrite(nuevoNodo,sizeof(*nuevoNodo),1,archivo);
	rewind(archivo);
	fclose(archivo);
}


//crea un nuevo nodo para el usuario
Usuario *crearUsuario(char user[], char pass[])
{
	Usuario *nuevoNodo = RESERVAR_USUARIO;
	idUser += 1;
	nuevoNodo->id = idUser;
	strcpy(nuevoNodo->user, user);
	strcpy(nuevoNodo->pass, pass);
	nuevoNodo->der = NULL;
	nuevoNodo->izq = NULL;
	guardarUsuarioArchivo(nuevoNodo);
	return nuevoNodo;
}

//Inserta los usuario en el arbol, ordenandos por nombre de usuario
void insertarUsuario(Usuario *&usuario, char user[], char pass[])
{
	char userLista[10];

	if(usuario== NULL)
	{
		Usuario *nuevoNodo = crearUsuario(user, pass);
		usuario = nuevoNodo;
	}
	else
	{ 
		strcpy(userLista, usuario->user);

		if(strcmp(user, userLista) == 0)
		{
			printf("\nEl usuario ya exite");
		}
		else
		{
			if(strcmp(user, userLista) < 0)
			{
				insertarUsuario(usuario->izq, user, pass);
			}
			else
			{
				insertarUsuario(usuario->der, user, pass);
			}
		}

			
	}
}

//muestra todos los usuarios del arbol en recorrido inorden
void mostrarArbol(Usuario *usuario, int cont)
{
	if (usuario == NULL)
	{
		return;
	}
	else
	{
		mostrarArbol(usuario->der,cont+1);
		for(int i=0;i<cont;i++)
		{
			printf("   ");
		}
		printf("%s\n",usuario->user);
		mostrarArbol(usuario->izq,cont+1);
	}
}


//Solicita el loggin y retorna si es autenticado.
int loguear(Usuario *usuario)
{
	int loggin = 0;
	char user[10];
	char pass[10];

	fflush(stdin);
	printf("Usuario: ");
	getchar();
	fgets(user, 10, stdin);
	fflush(stdin);

	printf("Contrasena: ");
	fgets(pass, 10, stdin);
	fflush(stdin);

	loggin = busqueda(usuario, user, pass);
	
	if(loggin != 0)
	{
		printf("\nAutenticado.");
	}
	else
	{
		printf("\nNo autenticado.");
	}

	return loggin;
}

//Verifica si el usuario y la contraseña son correcta
int busqueda(Usuario *usuario, char user[], char pass[])
{
	if(usuario == NULL)
	{
		return 0;
	}
	else if((strcmp(usuario->user, user) == 0) && (strcmp(usuario->pass, pass) == 0))
	{
		return usuario->id;
	}
	else if(strcmp(usuario->user, user) > 0)
	{
		return busqueda(usuario->izq,user,pass);
	}
	else
	{
		return busqueda(usuario->der,user,pass);
	}
}