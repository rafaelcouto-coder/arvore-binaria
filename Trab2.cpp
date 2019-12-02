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

Node freeTree(Node *root){
	if(root != NULL){
		freeTree(root->sae);
		freeTree(root->sad);
		free(root);
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
				insertTree(arvoreCPF, createInfo());
				fflush(stdin);
			break;
			case 'L':
				printTree(arvoreCPF);
				fflush(stdin);				
			break;
			case 'B':
			
			break;
			case 'R':
			
			break;
			
		}
	}while(opc != 's');

	printTree(arvoreCPF);
	freeTree(arvoreCPF);
	return 0;
}
