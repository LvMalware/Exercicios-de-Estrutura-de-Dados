/*
  Solucao para o "problema de Josefo" usando listas.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Vou implementar uma lista duplamente ligada, circular e com nó-cabeça (mas daria pra fazer com uma lista simples)
typedef struct soldier {
	unsigned ID; //Soldados não tem nome. Eles têm número de identificação. (O nó-cabeça terá o número 0)
	struct soldier *next; //Soldado a direita
	struct soldier *prev; //Soldado a esquerda
} Soldier;

typedef enum {false, true} bool; //Define o tipo booleano

Soldier* new_commander();
Soldier* new_soldier(unsigned ID);
Soldier* random_Soldier(Soldier *commander, unsigned *count);
Soldier* choose_soldier(Soldier *commander, unsigned *count);

bool remove_soldier(Soldier *c, Soldier *s);
bool create_amy(Soldier *commander, unsigned count);
bool add_soldier(Soldier *commander, Soldier *s);

void randomize();
void show_army(Soldier *commander);

int main(){
	randomize();
	Soldier *snow = new_commander(); //Esse é (Jon Snow) o nó-cabeça da lista
	unsigned contingent;
	printf("\n[+] Quantidade de soldados: ");
	scanf("%u", &contingent);
	create_amy(snow, contingent);
	//show_army(snow); //Teste
	printf("\n---------------------------------\n\n[*] O ultimo soldado e o 0%d. Ele vai pedir ajuda.\n", choose_soldier(snow, &contingent)->ID);
	//show_army(snow); //Teste
	return 0;
}
void randomize(){ //Reinicia o "contador" de numeros aleatorios da stdlib (Sem isso os numeros se repetem a cada execução)
	srand(time(NULL));
}
unsigned random_number(unsigned max){ //Retorna um numero pseudo-aleatorio entre 0 e max-1
	return rand() % max;
}
void show_army(Soldier *commander){ //Exibe a lista de soldados
	Soldier *s = commander->next;
	while (s != commander){
		printf("0%u, ", s->ID);
		s = s->next;
	}
	printf("\b\n");
}
Soldier *choose_soldier(Soldier *commander, unsigned *count){ //Escolhe o soldado que vai pedir ajuda
	//Esse processo pode ser ainda mais rápido removendo-se todos as instâncias de printf  ... mas vou deixar aqui pra que seja possivel ver o que está acontecendo
	while (*count > 1){
		Soldier *choosen = random_Soldier(commander, count);
		printf("[+] O soldado 0%u foi sorteado.\n", choosen->ID);
		unsigned M = random_number(*count * 5); //Vou escolher numeros pseudo-aleatorios entre 0 e 5 vezes a quantidade de soldados
		printf("[+] Contando %u soldados apartir dele...\n", M);
		unsigned i;
		for (i=0; i < (M % *count); i++)
			choosen = choosen->prev; //Sentido horário ...
		if (choosen == commander)
			choosen = commander->prev;
		if (remove_soldier(commander, choosen)){
			free(choosen);
			(*count)--;
			printf("[+] Restam %u soldados...\n", *count);
		}
	}
	return commander->next;
}
Soldier *new_commander(){ //Inicializa uma novo exercito
	Soldier *c = (Soldier *) malloc(sizeof(Soldier));
	if (!c){
		printf("[!] ERRO AO INICIALIZAR EXERCITO: O comandante desertou!");
		return c;
	}
	c->next = c->prev = c;
	c->ID = 0;
	return c;
}
Soldier* new_soldier(unsigned ID){ //Cria/inicializa um novo item para a lista
	Soldier *s = (Soldier *) malloc (sizeof(Soldier));
	if (!s)
		printf("[!] ERRO AO INICIALIZAR SOLDADO: Soldado dispensado por excesso de contingente."); 
	else
		s->ID = ID;
	return s;
}
bool add_soldier(Soldier *commander, Soldier *s){ //Insere um soldado no circulo
	if (!commander)
		commander = new_commander(); //Inicializa a lista, caso ela ainda não o tenha sido
	s->prev = commander->prev;
	s->next = commander;
	commander->prev->next = s;
	commander->prev = s;
	return true;
}
Soldier *random_Soldier(Soldier *commander, unsigned *count){ //Sortea um soldado apatir do qual serao contados os M soldados...
	Soldier *s = commander->next;
	unsigned pos = random_number(*count) % *count; //Posição do soldado sorteado.
	unsigned i;
	for (i=0; i<pos; i++)
		s = s->next;
	return s;
}
bool remove_soldier(Soldier *c, Soldier *s){ //Remove um soldado do circulo
	if (s==c) //O comandante fica!
		return true; //Retorna verdadeiro mesmo sem remover o item. Retornar falso (nesse exercicio especificamente) significa que o item é o ultimo da lista
	if (s->prev == s->next) //Se o proximo for igual ao anterior, significa que este é o ultimo soldado (isto é, o ultimo soldado válido, já que o outro é o nó-cabeça)
		return false;
	else
		printf("[+] O soldado 0%u vai pra guerra!\n", s->ID);
	s->next->prev = s->prev;
	s->prev->next = s->next;
	return true;
}
bool create_amy(Soldier *commander, unsigned count){ //Adiciona os soldados no circulo
	unsigned i;
	for (i=0; i<count; i++){
		add_soldier(commander, new_soldier(i+1));
	}
	return true;
}
