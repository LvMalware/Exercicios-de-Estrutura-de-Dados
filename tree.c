#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
	int value; //Conteudo do no
	struct node *left; //No menor
	struct node *right; //No maior
} Node;
typedef struct {
	Node *root; //No raiz da arvore
	unsigned size; //Guardar o numero de nos da arvore pode ser util em algumas aplicacoes (embora nesse exercicio o numero vai ser 50 mesmo...)
} Tree;

Tree *new_tree();

int random_number(int max);

void show_tree(Tree* t);
void insert_value(Tree *t, Node *n, int value);

int main(){
	srand(time(NULL)); //Reinicia o "contador" de numeros aleatorios
	Tree *t = new_tree(); //Inicializa a arvore
	int i;
	for (i=0; i<50; i++)
		insert_value(t, t->root, random_number(616 + i)); //Insere os elementos da arvore
	show_tree(t); //Exibe a arvore na tela
	return 0;
}
int random_number(int max){ //Essa funcao (baseada no metodo congruencial) tenta gerar numeros aleatorios sem repeticao (funcionou na maioria dos meus testes...)
	static int seed = 27; //Valor inicial da semente aleatoria
	seed = seed + rand()%max; //Diferente do metodo congruencial normal, aqui eu faco uma soma com a semente pra redefinir o intervalo
	return seed % max; //O resto da divisao garante que os numeros estarao dentro do intervalo especificado
}
Tree *new_tree(){ //Inicializa a arvore
	Tree *t = (Tree*)malloc(sizeof(Tree));
	if (!t){
		printf("Erro ao criar árvore.");
	} else {
		t->size = 0;
	}
	return t;
}
void insert_value(Tree *t, Node *n, int value){ //Insere um no na arvore
	if (!t->root){//Caso esteja vazia, o primeiro no e adicionado
		t->root = (Node*) malloc(sizeof(Node));
		t->root->value = value;
		t->size ++;
	} else if (value > n->value){ //Verifica se o valor e maior que o no atual
		if (!n->right){ //Verifica se o no atual e vazio
			n->right = (Node*) malloc(sizeof(Node));
			n->right->value = value;
			t->size++; //Incrementa o tamanho da arvore
		} else
			insert_value(t, n->right, value);
	} else { //Se o valor for menor que o no atual
		if (!n->left){
			n->left = (Node*) malloc(sizeof(Node));
			n->left->value = value;
			t->size++;
		} else
			insert_value(t, n->left, value);
	}
}
void show_node(Node *n){ //Exibe um no recursivamente, de forma que aparecam ordenados
	if (!n) return ;
	show_node(n->left);
	printf("%d ", n->value);
	show_node(n->right);
}
void show_tree(Tree* t){ //Exibe a arvore inteira
	show_node(t->root);
	printf("\n");
}
