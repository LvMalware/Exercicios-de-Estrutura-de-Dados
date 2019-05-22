#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} bool; //Implementa o tipo bool (booleano)
typedef unsigned long u64; //Numero inteiro (sem sinal) de 64 bits

typedef struct item {
	int value;
	struct item *next; //Próximo item da lista
	struct item *prev; //Item anterior (caso exista)
} Item;

typedef struct {
	Item *first; //Primeiro item da lista
	Item *last; //Ultimo item da lista
	u64 length; //Tamanho da lista
} List;

List* new_list(void);

Item* new_item(int value);
Item* seq_search(List *l, int value);
Item* bin_search(List *l, int value, u64 s, u64 e);

bool is_empty(List *l);
bool reverse_list(List *l);
bool add_item(List *l, Item *it);
bool is_sorted(List *l, int ord);
bool contains(List *l, int value);
bool add_sorted(List *l, Item *it);
bool copy_list(List *l1, List *l2);
bool remove_item(List *l, Item *it);
bool copy_list_u(List *l1, List *l2);
bool copy_list_r(List *l1, List *l2);
bool eliminate_value(List *l, int value);
bool join_lists(List *l1, List *l2, List *l3);

void show_list(List *l);

int main(void){ 
	//TESTES

	List *l1 = new_list();
	List *l2 = new_list();
	List *l3 = new_list();
	int i;
	for (i=10; i<20; i++){
		add_item(l1, new_item(i + 1));
	}

	for (i=0; i<10; i++){
		add_item(l2, new_item(i + 1));
	}

	show_list(l1);
	show_list(l2);

	join_lists(l1, l2, l3);
	show_list(l3);

	add_sorted(l3, new_item(2));
	show_list(l3);

	eliminate_value(l3, 2);
	show_list(l3);

	return 0;
}

List* new_list(void){ //Cria/inicializa uma nova lista
	List *l = (List *) malloc (sizeof(List));
	if (!l)
		printf("Erro ao criar lista!\n");
	else
		l->length = 0;
	return l;
}

Item* new_item(int value){ //Cria um novo item com o valor especificado
	Item *it = malloc(sizeof(Item));
	it->value = value;
	return it;
}

bool copy_list(List *l1, List *l2){ //Copia cada item de uma lista para outra
	if (!l2 || !l1){
		printf("Erro ao copiar lista.\n");
		return false;
	}
	Item *last = l1->first;
	while (last){
		add_sorted(l2, new_item(last->value));
		last = last->next;
	}
	return true;
}

bool copy_list_u(List *l1, List *l2){ //Copia os items de uma lista para outra sem repetir valores
	if (!l1 || !l2){
		printf("Opa! As listas devem ser criadas antes de copiar!\n");
		return false;
	}
	Item *last = l1->first;
	while (last){
		if (!contains(l2, last->value)){		
			add_item(l2, new_item(last->value));
		}
		last = last->next;
	}
	return true;
}
bool copy_list_r(List *l1, List *l2){ //Copia o inverso de l1 em l2
	if (!l1 || !l2 || is_empty(l1)){
		printf("Erro ao inverter lista!\n");
		return false;
	}
	Item *f  = l1->last;
	while (f){
		add_item(l2, new_item(f->value));
		f  = f->prev;
	}
	return true;
}
bool reverse_list(List *l){ //Inverte uma lista
	if (!l || is_empty(l)){
		printf("Erro ao inverter lista!\n");
		return false;
	}
	Item *nx = l->first;
	l->first = l->last;
	l->last = nx;
	Item *ax;
	while (nx){
		ax = nx;
		nx = nx->next;
		ax->next = ax->prev;
		ax->prev = nx;
	}
	return true;
}
bool join_lists(List *l1, List *l2, List *l3){ //Junta as duas listas em uma terceira
	if (!l1 || !l2 || !l3){
		printf("Erro ao intercalar listas!\n");
		return false;
	}
	Item *nx = l1->first;
	while (nx){
		add_sorted(l3, new_item(nx->value));
		nx = nx->next;
	}
	nx = l2->first;
	while (nx){
		add_sorted(l3, new_item(nx->value));
		nx = nx->next;
	}
	return true;
}
bool eliminate_value(List *l, int value){ //Elimina um dado valor da lista
	if (!l || is_empty(l)){
		printf("Nao e possivel remover um valor de uma lista vazia.\n");
		return false;
	}
	while (contains(l, value)){
		remove_item(l, bin_search(l, value, 0, l->length));
	}
	return true;
}

Item* seq_search(List *l, int value){ //Busca sequencial. Usado apenas se a lista nao estiver ordenada (nem vou usar)
	if (!l || is_empty(l))
		return NULL;
	Item *last = l->first;
	do {
		if (last->value == value)
			return last;
		last = last->next;
	} while (last);
	return NULL;
}

Item* get_by_index(List *l, u64 index){ //Retorna um item dado seu indice, ou NULL caso nao exista (usado pra pesquisa binaria)
	if (is_empty(l)){
		printf("Erro ao encontrar item. A lista esta vazia!\n");
		return NULL;
	}
	Item *last = l->first;
	u64 i;
	for (i=0; i<index; i++){
		last = last->next;
	}
	return last;
}
Item* bin_search(List *l, int value, u64 s, u64 e){//Busca binaria. Usada apenas se a lista estiver ordenada. s -- Inicio; e -- tamanho/fim
	u64 mid = (s + e)/2;
	Item *central = get_by_index(l, mid);
	if (central->value == value)
		return central;
	else if (s == e-1 || s==e)
		return NULL;
	if (central->value < value)
		return bin_search(l, value, mid, e);
	return bin_search(l, value, s, mid);
}
bool contains(List *l, int value){ //Verifica se a lista contem um dado valor (considera a lista ordenada)
	if (!l || is_empty(l))
		return false;
	if ((l->last->value < value) || (l->first->value > value))
		return false;
	Item *found = bin_search(l, value, 0, l->length);
	return (found !=NULL);
}
void show_list(List *l){ //Mostra a lista
	printf("Mostrando %lu items: \n", l->length);
	Item *last = l->first;
	do {
		printf("%d ", last->value);
		last = last->next;
	} while (last);
	puts("");
}
bool is_empty(List *l){ //Retorna true se a lista estiver vazia
	if (!l->first)
		return true;
	return false;
}
bool add_item(List *l, Item *it) { //Adiciona um item ao final da lista
	if (!l){
		printf("Erro ao adicionar item na lista!\n");
		return false;
	}
	if (is_empty(l)){
		it->prev = NULL;
		l->first = it;
	} else {
		it->prev = l->last;
		(l->last)->next = it;
		it->next = NULL;
	}
	l->last = it;
	l->length ++;
	return true;
}
bool add_sorted(List *l, Item *it) { //Adiciona um item na lista de forma ordenada (crescente)
	if (!l){
		printf("Erro ao adicionar item na lista!\n");
		return false;
	}
	if (is_empty(l)){
		l->first = l->last = it;
	} else if (l->length == 1){
		if (l->first->value <= it->value){
			it->prev = l->first;
			l->first->next = it;
			l->last = it;
		} else {
			it->prev = NULL;
			it->next = l->first;
			l->last = l->first;
			l->first = it;
		}
	} else {
		Item *before = l->first;
		if (before->value >= it->value){
			before->prev = it;
			it->prev = NULL;
			it->next = before;
			l->first = it;
		} else {
			u64 i;
			for (i=1; i < l->length; i++){
				if ((before->next)->value >= it->value){
					it->next = before->next;
					before->next->prev = it;
					it->prev = before;
					before->next = it;
					break;
				} else {
					before = before->next;
				}
			}
			if (!it->next){
				it->prev = l->last;
				l->last->next = it;
				l->last = it;
			}
		}
	}
	l->length++;
	return true;
}
bool is_sorted(List *l, int ord){ //ord: ordem -- ord==1 para crescente, ord!=1 para decrescente (Nesse exercicio especificamente, todas as listas sao consideradas ordenadas de forma crescente)
	if (is_empty(l)){
		printf("Erro ao verificar ordenação da lista!\n");
		return false;
	}
	Item *last = l->first;
	u64 i;
	if (ord==1){
		for (i=0; i<l->length; i++){
			if (last->next->value >= last->value){
				last = last->next;
			} else {
				return false;
			}
		}
	} else {
		for (i=0; i<l->length; i++){
			if (last->next->value <= last->value){
				last = last->next;
			} else {
				return false;
			}
		}
	}
	return true;
}
bool remove_item(List *l, Item *it){ //Remove um item da lista
	if (is_empty(l)){
		printf("Erro ao remover item!\n");
		return false;
	}
	Item *before = it->prev;
	if (it == l->first){
		l->first = it->next;
		l->first->prev = NULL;
		free(it);
	} else if (it == l->last){
		l->last = before;
		l->last->next = NULL;
		free(it);
	} else {
		it->next->prev = before;
		before->next = it->next;
		free(it);
	}
	l->length --;
	return true;
}
