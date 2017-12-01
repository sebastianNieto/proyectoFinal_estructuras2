#define RESERVAR_GENERO_ARTISTA (GeneroArtista *)malloc(sizeof(GeneroArtista))

struct GeneroArtista
{
	int id;
	char nombre[30];
	GeneroArtista *siguiente, *anterior;
};

void crearGeneroArtista(GeneroArtista *&lista, char generoArtista[])
{

	GeneroArtista *nuevoNodo = RESERVAR_GENERO_ARTISTA;
	strcpy(nuevoNodo->nombre, generoArtista);

	if(lista == NULL)
	{
		lista = nuevoNodo;
		nuevoNodo->siguiente = nuevoNodo;
		nuevoNodo->anterior = nuevoNodo;
		nuevoNodo->id = 1;
	}
	else
	{
		nuevoNodo->siguiente = lista;
		nuevoNodo->anterior = lista->anterior;
		nuevoNodo->id = lista->anterior->id+1;
		lista->anterior->siguiente = nuevoNodo;
		lista->anterior = nuevoNodo;
	}
}

void mostrarGeneroArtista(GeneroArtista* lista)
{
	GeneroArtista* aux = lista;
	printf("\nId\tNombre\n");
	do
	{
		printf("\n%d\t%s", aux->id, aux->nombre);
		aux = aux->siguiente;
	}
	while(aux != lista);
}

GeneroArtista* asignarGeneroArtista(GeneroArtista* lista)
{
	int id = 0;

	GeneroArtista* aux = lista;
	system("clear");
	printf("Eliga el id correspondiente: ");
	mostrarGeneroArtista(lista);
	printf("\nId: : ");
	scanf("%d", &id);

	for(int i = 1; i < id; i++)
	{
		aux = aux->siguiente;
	}

	return aux;

}