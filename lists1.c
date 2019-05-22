#include <stdio.h>
#include <stdlib.h>

#define size 15

typedef struct {
	int key;
	int value;
} Item;

enum bool {false, true};

enum bool is_sorted(Item *list, int sz, int ord); //ord: ordem; 1 para crescente, ord <> 1 para decrescente
enum bool copy_list(Item *l1, Item *l2);
enum bool copy_list_u(Item *l1, Item *l2);
enum bool copy_inverted(Item *l1, Item *l2);
enum bool invert_list(Item *list);
enum bool join_lists(Item *l1, Item *l2, Item *l3);
int remove_from_list(Item *list, int value);
void show_list(Item *list, int sz);

int main(void){
	Item l1[size], l2[size], l3[size*2]; //Listas (estáticas)
	int i;
	for (i = 0; i<size; i++){
		l1[i].key = i;
		l1[i].value = i+1;
	}
	
	//Testes...

	l1[1].value = 3;
	show_list(l1, size);
	copy_list_u(l1, l2);
	show_list(l2, size);

	//

	for (i = 0; i<size; i++){
		l2[i].key = 15+i;
		l2[i].value = i+20;
	}
	
	//Testes...

	remove_from_list(l2, 34);
	l2[14].value = 0; //Redefine o valor da posicao 14 (só pra testar)
	show_list(l2, size);
	join_lists(l1, l2, l3);
	show_list(l3, size*2);
	if (is_sorted(l2, size, 1))
		printf("Lista ordenada\n");
	else
		printf("Lista nao ordenada\n");
	//
	
	return 0;
}

void show_list(Item *list, int sz){ //Exibe os valores da lista
	int i;
	for (i = 0; i<sz; i++){
		printf("%d ", list[i].value);
	}
	puts("");
}

enum bool is_sorted(Item *list, int sz, int ord){ //Verifica se list esta ordenado de acordo com ord
	int i;
	Item last = list[0];
	if (ord == 1){
		for (i = 1; i < sz; i++){
			if (list[i].value < last.value){
				return false;
			}
			last = list[i];
		}
		return true;
	}

	for (i = 1; i < sz; i++){
		if (list[i].value > last.value){
			return false;
		}
			last = list[i];
	}
	return true;
}

enum bool copy_list(Item *l1, Item *l2){ //Copia l1 em l2
	int i;
	for (i = 0; i<size; i++){
		l2[i] = l1[i];
	}
	return true;
}

enum bool copy_list_u(Item *l1, Item *l2){ //Copia l1 em l2 sem repetir valores
	int i, j, k = 0;
	for (i = 0; i<size; i++){
		enum bool add = true;
		for (j = 0; j<i; j++){
			if (l2[j].value == l1[i].value){
				add = false;
				break;
			}
		}
		if (add){
			l2[k] = l1[i];
			l2[k].key = k;
			k++;
		}
	}
	return true;
}

enum bool copy_inverted(Item *l1, Item *l2){ //Copia o inverso de l1 em l2
	int i, j = size-1;
	for (i = 0; i < size; i++){
		l2[j] = l1[i];
		l2[j].key = j;
		j--;
	}
	return true;
}

enum bool invert_list(Item *list){ //Inverte list
	int i, j=size-1;
	for (i = 0; i < size/2; i++){
		Item x = list[i];
		x.key = j;
		list[i] = list[j];
		list[i].key = i;
		list[j] = x;
		j--;
	}
	return true;
}
enum bool insert_at(Item *list, int sz, Item item, int index){ //Insere um item na posicao especificada
	if (index>=sz)
		return false;
	if (index == sz - 1){
		list[index] = item;
		list[index].key = index;
		return true;
	}
	int i;
	for (i = sz - 1; i>index; i--){
		list[i] = list[i-1];
		list[i].key  = i - 1;
	}
	list[index] = item;
	list[index].key = index;
	return true;
}

enum bool join_lists(Item *l1, Item *l2, Item *l3){ //Junta l1 a l2 em l3 (de forma ordenada)
	int i, j, k;
	for (i = 0; i < size; i++){
		l3[i] = l1[i];
		l3[i].key = i;
	}
	k = 15;
	for (i = 0; i < size; i++){
		int index = k+i;
		for (j = 0; j < k; j++){
			if (l3[j].value > l2[i].value){
				index = j;
				break;
			}
		}
		insert_at(l3, 30, l2[i], index);
	}
	return true;
}

enum bool remove_at(Item *list, int index){ //Remove o item na posicao especificada
	if (index>=size)
		return false;
	int i=index;
	for (i = index; i<size; i++){
		list[i] = list[i+1];
		list[i].key = i;
	}
	return true;
}

int remove_from_list(Item *list, int value){ //Remove da lista todas as ocorrencias de um valor especificado
	int i, rem = 0;
	for (i = 0; i<size; i++){
	/*
	Eu ia usar busca binária (a lista já estaria ordenada mesmo...), mas se o valor aparecesse mais de uma vez,
	só seria removida a primeira ocorrência (a menos que eu repetisse até que nenhuma outra ocorrencia fosse encontrada).
	*/
		if (list[i].value == value){
			remove_at(list, i);
			rem ++;
		}
	}
	return rem; //Retorna o numero de ocorrencias do valor
}
