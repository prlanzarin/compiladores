/*
 * tac.c
 * ALUNOS:
 * MARCOS HENRIQUE BACKES
 * PAULO RENATO LANZARIN
 * >>>>>>>>> CODE SPONSORED BY THE ORDER OF THE LABLE <<<<<<<<<<
 */

#include "tac.h"
#include <stdlib.h>
#include <stdarg.h>


const char* _tacString[] = {
    FOREACH_TAC(GENERATE_TAC_STRING)
};

TAC *tacUnaryOp(int type, TAC **code);

TAC *tacBinOp(int type, TAC **code);

TAC *tacCreate(int type, HASH_NODE *res, HASH_NODE *op1, HASH_NODE *op2) {
    TAC *newTac; 

    if(!(newTac = (TAC *) malloc(sizeof(TAC)))) {
        fprintf(stderr, "ERROR [TAC]: out of memory!\n"); 
	exit(-1); // abort
    }

    newTac->type = type;
    newTac->res = res;
    newTac->op1 = op1;
    newTac->op2 = op2;
    newTac->prev = newTac->next = NULL;

    return newTac;
}

TAC *tacJoin(int nofTacs, TAC **tacs) {
    int i;
    TAC *tmp = tacs[nofTacs-1];

    for(i = nofTacs - 1; i > 0; i--) {
	if(!tmp) {
	    tmp = tacs[i-1];
	    continue;
	}

	if(!tacs[i-1])
	    continue;

	while(tmp->prev) 
	    tmp = tmp->prev;

	tmp->prev = tacs[i-1];
	tacs[i-1]->next = tmp; // already doing half reversing

	tmp = tacs[i-1];
    }
    
    return tmp;
}

TAC *tacReverse(TAC *tac) {
    TAC *tmp = tac;

    if(!tac)
	return NULL;

    while(tmp->prev) 
	tmp = tmp->prev;

    return tmp;
}

TAC *generateCode(AST_NODE *node) {
    TAC *code[node->size];    
    int i;

    for(i = 0; i < node->size; i++)
	if(!node->children[i])
	    code[i] = NULL;
	else
	    code[i] = generateCode(node->children[i]); 

    switch(node->type) {
	case AST_LIT:
	case AST_VAR:
	    return tacCreate(TAC_SYMBOL, node->symbol, NULL, NULL);
	case AST_FUNCALL:
	    return NULL;
        case AST_ARRACCESS:
	    return NULL;
	case AST_LPAR:
	    return NULL;
	case AST_ATTR:
            return NULL;
        case AST_ATTRARR:
            return NULL;
        case AST_OUTPUT:
            return NULL;
	case AST_INPUT:
	    return NULL;
        case AST_IF:
            return NULL;
        case AST_IFTE:
            return NULL;
        case AST_WHILE:
            return NULL;
        case AST_RETURN:
            return NULL;
	// UNARY
        case AST_NOT:
            return tacUnaryOp(TAC_NOT, code);
	// BINARY
        case AST_LE:
	    return tacBinOp(TAC_LE, code);
        case AST_GE:
	    return tacBinOp(TAC_GE, code);
        case AST_EQ:
	    return tacBinOp(TAC_EQ, code);
        case AST_NE:
	    return tacBinOp(TAC_NE, code);
        case AST_AND:
	    return tacBinOp(TAC_AND, code);
        case AST_OR:
	    return tacBinOp(TAC_OR, code);
        case AST_LESS:
	    return tacBinOp(TAC_LESS, code);
        case AST_GREATER:
	    return tacBinOp(TAC_GREATER, code);
        case AST_ADD:
	    return tacBinOp(TAC_ADD, code);
        case AST_SUB:
	    return tacBinOp(TAC_SUB, code);
        case AST_MUL:
	    return tacBinOp(TAC_MUL, code);
        case AST_DIV:
	    return tacBinOp(TAC_DIV, code);
        default:
	    tacJoin(node->size, code);
    }

    return NULL;
}

TAC *tacBinOp(int type, TAC **code) {
    TAC *tmp[3];
    tmp[0] = code[0];
    tmp[1] = code[1];
    tmp[2] = tacCreate(type, makeTemp(), tmp[0]?tmp[0]->res:NULL, tmp[1]?tmp[1]->res:NULL);
    return tacJoin(3, tmp);
}

TAC *tacUnaryOp(int type, TAC **code) {
    TAC *tmp[2];
    tmp[0] = code[0];
    tmp[1] = tacCreate(type, makeTemp(), tmp[0]?tmp[0]->res:NULL, NULL);
    return tacJoin(2, tmp);
}

