/* CABECALHO
   Programa: Converte expressoes infixas para posfixas e calcula o valor da avaliacao
   Arquivo: mainStack.c
   Autor: lazaro jose Pedrosa dos Reis 
*/

//Importacao de bibliotecas
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "stack.cpp"

#define SIZE 100

void main()
{
    char infix[SIZE], postfix[SIZE];
    float f;
    printf("\nInsira a expressao infixa: ");
	gets(infix);
    InfixToPostfix(createStack(),infix,postfix);
    printf("\nExpressao posfixa: ");
	puts(postfix);
    f=evaluatePostfixExp(createStack(),postfix);
    printf("\nValor da avaliacao: %.2f \n",f);
   return;
}

