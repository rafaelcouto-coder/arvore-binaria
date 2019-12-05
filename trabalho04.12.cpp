#include <iostream>
#include <locale.h>
#include <stdlib.h>

typedef struct{
	int CPF;
	char nome[50];
	char profissao[30];
}Info;

typedef struct t_no{
	Info *info;
	struct t_no *sae;
	struct t_no *sad;
	struct t_no *atual = NULL;
	struct t_no *ant = NULL;
}Node;

Node *initializeTree(){
	return NULL;
}

Info *createInfo(){
	Info *aux;
	aux = new Info;

	printf("<nome>;<CPF>;<profissão>\n");
	scanf("%s %d %s", &aux->nome, &aux->CPF, &aux->profissao);
	return aux;
}

Node *insertTree(Node *root, Info *aux){
		
	if(root == NULL){	
		Node *newElement = new Node;	
		newElement->info = aux;
		newElement->sad = NULL;
		newElement->sae = NULL;
		return newElement;
	}else{
		if(aux->CPF > root->info->CPF){
			root->sad = insertTree(root->sad, aux);
		}else{
			root->sae = insertTree(root->sae, aux);
		}
	}
	return root;
}

Node printTree(Node *root){
	if(root != NULL){
		printf("%s ", root->info->nome);
		printf("%d ", root->info->CPF);
		printf("%s ", root->info->profissao);
		printTree(root->sae);
		printTree(root->sad);
	}
}

Node searchTree(Node *root, int searchCpf){
	
	if(root != NULL){
		if(searchCpf == root->info->CPF){
			printf("%s ", root->info->nome);
			printf("%d ", root->info->CPF);
			printf("%s ", root->info->profissao);
		}
		searchTree(root->sae, searchCpf);
		searchTree(root->sad, searchCpf);
	}
}

Node freeTree(Node *root){
	if(root != NULL){
		freeTree(root->sae);
		freeTree(root->sad);
		free(root);
	}
}

struct Node* remove(struct Node *atual){
	struct Node *aux1, *aux2;
	if(atual->sae == NULL){			//Caso n tenha nada na esquerda, significa q só tem 1 filho
		aux2 = atual->sad;
		free(atual);
		return aux2;
	}
	aux1= atual;
	aux2 = atual->sae;
	
	while(aux2->sad != NULL){		//Procura o mais a direita na sub arvore da esquerda
		aux1 = aux2;
		aux2= aux2->sad;
	}
	
	if(aux1 != atual){		//Nesse IF ele vai copiar o da mais longe da direita na sub arvore da esquerda no local onde o nó vai ser removido.
		aux1->sad = aux2->sae;
		aux2->esq = atual->sae
	}
	aux2->sad = atual->sad;
	free(atual);
	return aux2;
}

int removeInfo(Node *root, int removecpf, Node atual){
	if(root == NULL){return 0;}					//Caso a árvore seja vazia ele já sai
	*atual = *root;
	while(atual != NULL){
		if(removecpf == atual){			//CASO o valor seja igual a algum nó com certeza vai achar o nó a ser removido(onde ele está).
			if(atual == *Info->CPF){
				*root = remover(atual);
			}else{
				if(ant->sad == atual){
					ant->sad = remove(atual);		//Recebe o NOVO atual	
				}else{
					ant->sae= remove(atual);		//-----
				}
			}
			return 1;
		}
		ant = atual;
		if(removecpf > atual->info){
			atual = atual->sad;
		}else{
			atual = atual->sae; 			
		}
	}
}


int main(int argc, char** argv) {
	setlocale(LC_ALL, "Portuguese");
	char opc;
	Node *arvoreCPF = initializeTree();
	do{
		printf("\n>MENU:\n\nI->Inserir\nR->Remover por CPF\nB->Buscar\nL->Listar\nS->Sair\nEscolha a operação desejada: ");
		scanf("%c", &opc);	
		switch(opc){
			case 'I':
				arvoreCPF = insertTree(arvoreCPF, createInfo());
				fflush(stdin);
			break;
			
			case 'L':
				printTree(arvoreCPF);
				fflush(stdin);				
			break;
			
			case 'B':
				int searchCpf;
				printf("Digite CPF: ");
				scanf("%d", &searchCpf);
				searchTree(arvoreCPF, searchCpf);
			break;
			
			case 'R':
				int removecpf();
			break;
			
		}
	}while(opc != 'S');

	printTree(arvoreCPF);
	freeTree(arvoreCPF);
	return 0;
}
