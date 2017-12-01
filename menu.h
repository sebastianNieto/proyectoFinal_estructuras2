/* Menú que muestra las diferentes opciones para navegar por el programa
*  Fecha: 30/11/2017
*  Elaborado por: John Sebastian Nieto gil
*  Elaborado por: Ricardo Andres Villalobos
*/

#define PAUSE printf("\nPresione una tecla para continuar");getchar()


void menuMusica(int, ListaReproduccion*);
int menu();

//Variables globales para los contadores de id en los arboles de musica y listas de reproduccion
int id = 0;
int idContarMusic = 0;

int menu()
{

	int loggin = 0;
	int iniciar = 0;
	int opcion = 0;
	int subOpcion = 0;
	char user[10];
	char pass[10];
	char opc;

	Usuario* usuario = NULL;
	ListaReproduccion* listaReproduccion = NULL;

	inicializarUsuarios(usuario);

	do
	{
		loggin = 0;
		system("clear");
		printf("Proyecto final: Music\n");
		printf("\n1. Iniciar session");
		printf("\n2. registrarse");
		printf("\n3. usuarios");
		printf("\n0. Salir");
		printf("\n\nIngrese la opcion: ");
		scanf("%d", &opcion);
		
		switch(opcion)
		{
			case 0:
				printf("\nVuelve pronto...\n\n");
				loggin = 0;
				break;

			case 1:
				do
				{
					loggin = loguear(usuario);

					if(loggin == 0)
					{
						printf("\nDesea intentarlo nuevamente? S/N ");
						scanf("%c", &opc);

						if(opc == 's' || opc == 'S')
						{
							iniciar = 0;
						}
						else
						{
							iniciar = 1;
						}
					}
					else
					{
						iniciar = 1;
					}

				}while(iniciar == 0);
				PAUSE;
				break;

			case 2:
				printf("Usuario: ");
				getchar();
				fgets(user, 10, stdin);
				fflush(stdin);

				printf("Contrasena: ");
				fgets(pass, 10, stdin);
				fflush(stdin);

				insertarUsuario(usuario, user, pass);
				printf("\nRegistrado");
				PAUSE;
				continue;

			case 3:
				mostrarArbol(usuario, 0);
				getchar();
				PAUSE;
				break;

			default:
				printf("\nopcion no valida");
				PAUSE;
				break;

		}
		if(loggin != 0)
		{
			menuMusica(loggin, listaReproduccion);

		}

	}while(opcion != 0);
}

//Muestra el menu de canciones despues del logueo
void menuMusica(int loggin, ListaReproduccion* listaReproduccion)
{
	int opcion = 0;
	int subOpcion = 0;
	int duracion = 0;
	int idMusic = 0;
	int longitud = 0;
	int idLista = 0;
	int opcionBuscar = 0;
	int idCancion = 0;
	int opcLista = 0;
	int buscar = 0;
	char nombre[30];
	char nombreLista[30];

	GeneroArtista* genero = NULL;
	GeneroArtista* artista = NULL;
	Music* music = NULL;
	Music* musicDuracion = NULL; //para almacenar el nuevo arbol ordenado por tiempo
	

	GeneroArtista* idGenero = NULL;
	GeneroArtista* idArtista = NULL;

	do
	{
		system("clear");
		printf("\n\tBienvenido\n");
		printf("\n1. Ingresar Musica");
		printf("\n2. Mostrar Musica");
		printf("\n3. Mi Musica");
		printf("\n0. Cerrar session");
		printf("\n\nIngrese la opcion: ");
		scanf("%d", &opcion);

		switch(opcion)
		{
			case 0:
				break;

			case 1:
				do
				{
					system("clear");
					printf("\n1. Ingresar nuevo genero");
					printf("\n2. Ingresar nuevo artista");
					printf("\n3. Ingresar nueva cancion");
					printf("\n0. Salir");
					printf("\n\nIngrese la opcion: ");
					scanf("%d", &subOpcion);

					switch(subOpcion)
					{
						case 0:
							break;

						case 1:
							fflush(stdin);
							printf("Nombre: ");
							getchar();
							fgets(nombre, 30, stdin);
							crearGeneroArtista(genero, nombre);
							PAUSE;

							break;

						case 2:
							fflush(stdin);
							printf("Nombre del artista: ");
							getchar();
							fgets(nombre, 30, stdin);
							crearGeneroArtista(artista, nombre);
							PAUSE;
							break;

						case 3:
							fflush(stdin);
							printf("Nombre de la cancion: ");
							getchar();
							fgets(nombre, 30, stdin);
							printf("tiempo de duracion: ");
							scanf("%d", &duracion);
							idGenero = asignarGeneroArtista(genero);
							idArtista = asignarGeneroArtista(artista);
							insertarMusic(music, nombre, duracion, idArtista, idGenero, idContarMusic, NULL);
							break;

						default:
							break;
					}
				}
				while(subOpcion != 0);

				break;

			case 2:
				do
				{
					system("clear");
					printf("\n1. Mostrar musica ordenada por nombre");
					printf("\n2. Mostrar musica ordenada por Duracion");
					printf("\n0. Salir");
					printf("\n\nIngrese la opcion: ");
					scanf("%d", &subOpcion);

					switch(subOpcion)
					{
						case 0:
							break;

						case 1:
							listarMusic(music);
							getchar();
							PAUSE;
							break;

						case 2:
							ordenar(music, musicDuracion);
							listarMusic(musicDuracion);
							getchar();
							PAUSE;
							break;

						case 3:
							break;


						default:
							printf("\nOpcion no valida");
							getchar();
							PAUSE;
							break;
					}
				}
				while(subOpcion != 0);
				
				break;

			case 3:
				do
				{

					fflush(stdin);
					system("clear");
					printf("\n1. Crear lista de reproduccion");
					printf("\n2. Agregar musica");
					printf("\n3. Mostrar lista de reproduccion");
					printf("\n4. Eliminar musica");
					printf("\n5. Editar lista de reproduccion");
					printf("\n0. Salir");
					printf("\n\nIngrese la opcion: ");
					scanf("%d", &opcLista);

					switch(opcLista)
					{
						case 0:
							break;

						case 1:
							fflush(stdin);
							printf("\nIngrese el nombre de la lista: ");
							getchar();
							fgets(nombreLista, 30, stdin);
							insertarLista(listaReproduccion, nombreLista, loggin, id, NULL);
							PAUSE;
							break;

						case 2:
							fflush(stdin);
							listarLista(listaReproduccion, loggin);
							printf("\nIngrese id de lista: ");
							scanf("%d", &idLista);
							printf("\n1.Buscar por nombre");
							printf("\n2.Buscar por genero");
							printf("\n3.Buscar por artista");
							printf("\nOpcion: ");
							scanf("%d", &opcionBuscar);

							switch(opcionBuscar)
							{
								case 1:
									buscar = 0;
									fflush(stdin);
									printf("Cancion: ");
									getchar();
									fgets(nombre, 30, stdin);
									longitud = strlen(nombre)-1;
									buscarMusic(music, nombre, longitud, buscar);
									 
									break;
								case 2:
									buscar = 0;
									fflush(stdin);
									printf("Genero: ");
									getchar();
									fgets(nombre, 30, stdin);
									
									longitud = strlen(nombre)-1;
									printf("\n generoActual: %s -- %d", nombre, longitud);
									buscarMusicGeneroArtista(music, nombre, longitud, 2, buscar);
									
									break;
								case 3:
									buscar = 0;
									fflush(stdin);
									printf("Artista: ");
									getchar();
									fgets(nombre, 30, stdin);
									longitud = strlen(nombre)-1;
									buscarMusicGeneroArtista(music, nombre, longitud, 1, buscar);
									break;
							}
							if(buscar != 0)
							{
								printf("\nIngrese id de la cancion: ");
								scanf("%d", &idCancion);
								ingresarCancion(listaReproduccion, music, idLista, idCancion);
							}
							else
							{
								printf("\nCancion no encontrada");
							}
								
							getchar();
							PAUSE;
							break;
		

						case 3:
							fflush(stdin);
							listarLista(listaReproduccion, loggin);
							printf("\nIngrese id de lista: ");
							scanf("%d", &idLista);
							listarCancionesLista(listaReproduccion, music, idLista);
							getchar();
							PAUSE;
							break;
						case 4:
							do
							{
								system("clear");
								printf("\n1.Eliminar lista de reproduccion");
								printf("\n2.Eliminar Cancion");
								printf("\n3.Vaciar lista");
								printf("\n0.Salir");
								printf("\nOpcion: ");
								scanf("%d", &subOpcion);


								switch(subOpcion)
								{
									case 0:
										break;

									case 1:
										fflush(stdin);
										listarLista(listaReproduccion, loggin);
										printf("\nIngrese id de lista: ");
										scanf("%d", &idLista);
										//El tercer parametro es recibido por referencia, y guardara el enlace principal del arbol,
										//a diferencia del primero que se utiliza para recorrer el arbol y obtener el nodo a eliminar
										eliminar(listaReproduccion, idLista, listaReproduccion);
										getchar();
										PAUSE;
										break;

									case 2:
										listarLista(listaReproduccion, loggin);
										printf("\nIngrese id de lista: ");
										scanf("%d", &idLista);
										listarCancionesLista(listaReproduccion, music, idLista);
										printf("\nIngrese id de la cancion: ");
										scanf("%d", &idCancion);
										eliminarCancionLista(listaReproduccion, idLista, idCancion, 0);
										getchar();
										PAUSE;
										break;

									case 3:
										listarLista(listaReproduccion, loggin);
										printf("\nIngrese id de lista: ");
										scanf("%d", &idLista);
										eliminarCancionLista(listaReproduccion, idLista, idCancion, 1);
										getchar();
										PAUSE;
										break;
								}

							}
							while(subOpcion != 0);
							break;

						case 5:
							fflush(stdin);
							listarLista(listaReproduccion, loggin);
							printf("\nIngrese id de lista: ");
							scanf("%d", &idLista);
							editarLista(listaReproduccion, idLista);
							getchar();
							PAUSE;
					}
				}
				while(opcLista != 0);

				break;

			default:
				printf("\nOpcion no valida");
				PAUSE;
				break;
		}

	}while(opcion != 0);
}