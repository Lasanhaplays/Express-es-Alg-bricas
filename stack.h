/* CABECALHO
   Programa: Converte expressoes infixas para posfixas e calcula o valor da avaliacao
   Arquivo: stack.h
   Autor: lazaro jose Pedrosa dos Reis 
*/

typedef struct				//Struct para info
{
	float value;
}Info;
typedef struct tnode		//Struct para o no
{
	struct tnode *next;
	Info *info;
}Node;
typedef struct				//Struct para a cabeca da pilha
{
	int size;
	Node *first;
}Stack;
Stack *createStack();
Node *createNode();
Info *createInfo(char i);
Info *createInfofloat(float i);
void freeStack(Stack *stack);
bool isEmptyStack(Stack * stack);
void printStack(Stack *stack);
int lengthStack(Stack *stack);
bool push(Stack *stack, Info *inf);
Info *pop(Stack *stack);
int isoperator(char symbol);
int precedence(char symbol);
void InfixToPostfix(Stack *stk, char source[], char target[]);
float evaluatePostfixExp(Stack *stc,char exp[]);
