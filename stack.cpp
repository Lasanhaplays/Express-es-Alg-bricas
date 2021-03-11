/* CABECALHO
   Programa: Converte expressoes infixas para posfixas e calcula o valor da avaliacao
   Arquivo: stack.c
   Autor: lazaro jose Pedrosa dos Reis 
*/

//Importacao de bibliotecas
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "stack.h"

Stack *createStack() //Funcao que cria a caveca da pilha
{
    Stack *ptr;
    if(ptr=(Stack *)malloc(sizeof(Stack))){
        ptr->size=0;
        ptr->first=NULL;
        return ptr;
    }
    return NULL;
}
Node *createNode() //Funcao que cria o no
{
    Node *ptr;
    if(ptr=(Node *)malloc(sizeof(Node))){
        ptr->info=NULL;
        ptr->next=NULL;
        return ptr;
    }
    return NULL;
}
Info *createInfo(char i) //Funcao que cria a info tipo char
{
    Info *ptr;
    if(ptr=(Info *)malloc(sizeof(Info))){
        ptr->value=i;
        return ptr;
    }
    return NULL;
}
Info *createInfofloat(float i) //Funcao que cria a info tipo float
{
    Info *ptr;
    if(ptr=(Info *)malloc(sizeof(Info))){
        ptr->value=i;
        return ptr;
    }
    return NULL;
}
void freeStack(Stack *stack) //Funcao que limpa a pilha
{
    Node *ptr;
    if (!stack) return;
    while(stack->first)
    {
        ptr=stack->first->next;
        free(stack->first->info);
        free(stack->first);
        stack->first=ptr;
    }
    free(stack);
}
bool isEmptyStack(Stack * stack) //Funcao que verifica se a pilha esta vazia
{
    return (!stack || stack->size==0);
}
void printStack(Stack *stack) //Funcao que printa a pilha
{
    Node *ptr;
    if(isEmptyStack(stack)) return;
    printf("\n TOP[ ");
    ptr=stack->first;
    while(ptr != NULL)
    {
      printf("(%d) ",ptr->info->value);
      ptr = ptr->next;
    }
	printf(" ]BOTTOM");
}
int lengthStack(Stack *stack) //Funcao que verifica o tamanho da pilha
{
	if (!stack) return -1;
	return stack->size;
}
bool push(Stack *stack, Info *inf) //Funccao que insere no primeiro lugar da pilha
{
	Node *ptr;
    if(!stack || !(ptr=createNode())) return false;
    ptr->info=inf;
    ptr->next=stack->first;
    stack->first=ptr;
    stack->size++;
    return true;
}
Info *pop(Stack *stack) //Funcao que retira o primeiro no da pilha e retorna a info desse no
{
	Node *ptr;
  	Info *inf;
	if (isEmptyStack(stack)) return NULL;
	ptr=stack->first;
	stack->first=ptr->next;
  	inf=ptr->info;
  	free(ptr);
  	stack->size--;
  	return inf;
}
int isoperator(char symbol) //Funcao que verifica se o caractere e um operador
{
	if(symbol == '%' || symbol == '*' || symbol == '/' || symbol == '+' || symbol =='-')
	{
		return 1;
	}
	else
	{
	return 0;
	}
}
int precedence(char symbol) //Funcao que retorna a prioridade do operador
{
    if(symbol == '*' || symbol == '/' || symbol == '%')
	{
		return(2);
	}
	else if(symbol == '+' || symbol == '-')
	{
		return(1);
	}
	else
	{
		return(0);
	}
}
void InfixToPostfix(Stack *stk,char source[], char target[]) //Funcao que converte a expressao infixa para posfixa
{
    char s,t;
    int i,j;
    Info *r,*u;

    i=0;
    j=0;
    strcat(source,")");
    push(stk,createInfo('('));
    s=source[i];

    while(s != '\0')
    {
        if (s =='(')
        {
            push(stk,createInfo(s));
        }
        else if (isdigit(s) || isalpha(s))
        {
            target[j]=s;
            j++;
        }
        else if (s ==')')
        {
            r=pop(stk);
            t=r->value;
			while(t != '(')
			{
				target[j] = t;
				j++;
				u=pop(stk);
				t=u->value;
			}
        }
        else if (isoperator(s)==1)
        {
            r=pop(stk);
            t=r->value;
            while (isoperator(t)==1 && precedence(t) >= precedence(s))
            {
                target[j]=t;
                j++;
                u=pop(stk);
                t=u->value;
            }
            push(stk,createInfo(t));
            push(stk,createInfo(s));
        }
        else
		{
			printf("\n Expressao invalida\n");
            getchar();
			exit(1);
		}
		i++;
		s=source[i];
    }
    target[j] = '\0';
}
float evaluatePostfixExp(Stack *stc,char exp[]) //Funcao que calcula o valor da avaliacao de uma expressao posfixa
{
    char a;                             //a= char retirado da string exp
    int i,nc,fa,fb,ri;                  //i = contador || nc = char convertido em int || fa e fb= float convertido em int || ri = resultado do modulo entre dois inteiros
    Info *t,*u;                         //ponteiros para info retirada da pilha
    float f,nf,p,s,rf;                  //f = float para retornar o valor do avaliacao || nf = int convertido em float || p e s = primeiro e segundo float retirado da pilha || rf = resultado entre p e s

    i=0;
    strcat(exp,")");
    a=exp[i];

    while(a != ')')
    {
        if (isdigit(a))                 //Analisa se o char e um numero
        {
            nc=(a-'0');
            nf=(float)nc;
            push(stc,createInfofloat(nf));
        }
        else if (isoperator(a)==1)      //Analisa se o char e um operador
        {
            t=pop(stc);                 //Retira o primeiro valor da pilha
            u=pop(stc);                 //Retira o segundo valor da pilha
            s=t->value;                 //Retira o char de dentro da info
            p=u->value;                 //Retira o char de dentro da info

            //Verifica qual operacao fazer, calcula e insere na pilha novamente
            if(a == '%')
            {
                fa=(int)p;              //Conversao de float para int para conseguir calcular o modulo
                fb=(int)s;
                ri=(fa%fb);             //calculo do modulo
                rf=(float)ri;           //Conversao de int para float para inserir novamente na pilha
                push(stc,createInfofloat(rf));
            }
            if(a == '*')
            {
                rf=(p*s);
                push(stc,createInfofloat(rf));
            }
            if(a == '/')
            {
                rf=(p/s);
                push(stc,createInfofloat(rf));
            }
            if(a == '+')
            {
                rf=(p+s);
                push(stc,createInfofloat(rf));
            }
            if(a =='-')
            {
                rf=(p-s);
                push(stc,createInfofloat(rf));
            }
        }
		i++;
		a=exp[i];
    }
    t=pop(stc);             //retira o .info da pilha
    f=t->value;             //retirar o valor da pilha
    return f;               //retorna o valor da avaliacao
}
