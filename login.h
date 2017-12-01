/* Funciones del programa. Utilizando arboles binarios
*  Fecha: 25/11/2017
*  Elaborado por: John Sebastian Nieto gil
*  Elaborado por: Ricardo Andres Villalobos
*/
#define RESERVAR_USUARIO (Usuario *)malloc(sizeof(Usuario))

struct Usuario
{
	int id;
	char user[10];
	char pass[10];
	Usuario *izq, *der;
}usu, *pUsu = &usu;

int idUser = 0;
//Prototipo de funciones

Usuario *crearUsuario(char user[], char pass[]);
void insertarUsuario(Usuario *&usuario, char user[], char pass[]);
int busqueda(Usuario *usuario, char user[], char pass[]);

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
			printf("\npU: %s", pUsu->user);
			insertarUsuario(nodo, pUsu->user, pUsu->pass);
			//insertarUsuario(nodo, nodo->user, nodo->pass);
		}
	}
	fclose(archivo);
}

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

void mostrarArbol(Usuario *usuario, int cont){
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

int busqueda(Usuario *usuario, char user[], char pass[]){
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