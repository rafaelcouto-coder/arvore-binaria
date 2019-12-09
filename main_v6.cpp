#include <iostream>
#include <locale.h>
#include <stdlib.h>

typedef struct{
	int CPF;
	char nome[50];
}Info;

typedef struct t_no{
	Info *info;
	struct t_no *sae;
	struct t_no *sad;
}Node;

// Inicializa árvore com valor nulo
Node *initializeTree(){
	return NULL;
}

//Retorna informações dos funcionários
Info *createInfo(){
	Info *aux;
	aux = new Info;

	printf("\nInserir: <nome> <CPF>\n");
	scanf("%s %d", &aux->nome, &aux->CPF);
	return aux;
}

/*Verifica dentro da árvore se CPF já existe e 
retorna true caso exista, false caso não exista */
bool existCPF(Node *root, int cpf){	
	if(root != NULL){
		if(root->info->CPF == cpf){
			return true;
		}
		existCPF(root->sae, cpf);
		existCPF(root->sad, cpf);
	}
	return false;
}

Node *insertTree(Node *root, Info *aux){
	
	if(existCPF(root, aux->CPF) == true){
		printf("\nNão serão cadastrados dois CPFs iguais");	
		return root;
	}else{
		if(root == NULL){	
			Node *newElement = new Node;	
			newElement->info = aux;
			newElement->sad = NULL;
			newElement->sae = NULL;
			printf("\nInseriu: %s", newElement->info->nome);
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
}

Node printTree(Node *root){
	if(root != NULL){
		printf("\nFuncionario: %s CPF: %d", root->info->nome, root->info->CPF);
		printTree(root->sae);
		printTree(root->sad);
	}
}

Node *searchNo(Node *root, int cpf){	
	if(root != NULL){
		if(cpf == root->info->CPF){
			printf("\nEncontrou: %s %d", root->info->nome, root->info->CPF);
			return root;
		}else{
			if(cpf > root->info->CPF){
				return searchNo(root->sad, cpf);
			}else{
				return searchNo(root->sae, cpf);
			}
		}
	}
	printf("\nCPF %d não localizado", cpf);
	return NULL;
}

int writeCPF(){
	int cpf;
	printf("Digite CPF: ");
	scanf("%d", &cpf);
	
	return cpf;
}

Node freeTree(Node *root){
	if(root != NULL){
		freeTree(root->sae);
		freeTree(root->sad);
		free(root);
	}
}

Node* minTree(Node *root){
	if(root != NULL){
		Node *aux = root;
		while(aux->sae != NULL){
			aux = aux->sae;
		}
		return aux;
	}
	return NULL;
}

Node* removeNo(Node *root, int cpf){
	if(root != NULL){
		
		if(cpf > root->info->CPF){
			root->sad = removeNo(root->sad, cpf);			
		}
		else if(cpf < root->info->CPF){		
			root->sae = removeNo(root->sae, cpf);
		}
		else{
			//encontrou o elemento a ser removido
			printf("\nRemoveu %s %d", root->info->nome, root->info->CPF);
			//quando não tem nenhum filho
			if(root->sae == NULL && root->sad == NULL){
				free(root);
				return NULL;
			}
			
			//quando tem filho da direita
			else if(root->sae == NULL && root->sad != NULL){
				Node * aux = root->sad;
				free(root);
				return aux;
			}
			
			//quando tem filho a esquerda
			else if(root->sae != NULL && root->sad == NULL){
				Node* aux = root->sae;
				free(root);
				return aux;
				
			//quando tem filho para os dois lados 	
			}else{
				Node* aux = minTree(root->sad);
				Info *infoAux = aux->info;
				
				root = removeNo(root, infoAux->CPF);
				root->info = infoAux;
				return root;
			}
		}
		return root;
	}
	printf("\nCPF %d não localizado", cpf);
	return NULL;
}

void clean(){
	printf("\n\n");
	system("pause");
	system("cls");
}

int main(int argc, char** argv) {
	setlocale(LC_ALL, "Portuguese");
	
	Node *arvoreCPF = initializeTree();
	
	char opc;
	
	do{
		printf("\n\n>MENU \n\nI-> Inserir\nR-> Remover por CPF\nB-> Buscar\nL-> Listar\nS-> Sair\n\nEscolha a operação desejada: ");
		scanf("%c", &opc);	
		switch(opc){
			case 'i':
				arvoreCPF = insertTree(arvoreCPF, createInfo());
				clean();
			break;
			
			case 'l':
				printTree(arvoreCPF);
				clean();				
			break;
			
			case 'r':
				removeNo(arvoreCPF, writeCPF());
				clean();
			break;
			
			case 'b':
				searchNo(arvoreCPF, writeCPF());
				clean();
			break;	
		}
		fflush(stdin);
	}while(opc != 's');

	//printTree(arvoreCPF);
	freeTree(arvoreCPF);
	return 0;
}
