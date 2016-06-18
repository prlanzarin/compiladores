/*
 * hashtable.h
 * ALUNOS:
 * MARCOS HENRIQUE BACKES
 * PAULO RENATO LANZARIN
 */

#ifndef SEMANTIC
#define SEMANTIC

#include "hashtable.h"
#include "ast.h"

#define FOREACH_ERROR(ERROR)					\
    ERROR(SEM_REDECLARED, "ID %s REDECLARED")	\
    ERROR(SEM_UNDECLARED, "ID %s UNDECLARED")	\
    ERROR(SEM_USAGE, "ID %s WRONG USAGE")		\
    ERROR(SEM_USAGE_NOF_ARGS, "WRONG NUMBER OF ARGUMENTS TO FUNCTION %s") \
    ERROR(SEM_TYPE, "WRONG TYPE")       		\
    ERROR(SEM_TYPE_EXPECTED_NUMBER, "OPERAND OF WRONG TYPE. EXPECTED int, char or real") \
    ERROR(SEM_TYPE_EXPECTED_BOOL, "OPERAND OF WRONG TYPE. EXPECTED bool") \
    ERROR(SEM_TYPE_ATTR_TYPE, "ATTR TYPE DOES NOT MATCH") \
    ERROR(SEM_TYPE_INCOMPATIBLE_OPS, "OPERANDS OF INCOMPATIBLE TYPES") \
    ERROR(SEM_TYPE_INDEX, "INDEX TO %s OF WRONG TYPE. EXPECTED int OR char") \
    ERROR(SEM_TYPE_INCOMPATIBLE_RETURN, "RETURN TYPE DOES NOT MATCH") \
    ERROR(SEM_TYPE_INCOMPATIBLE_ARGS, "ARGUMENT TYPES OF %s MATCH WITH FUNCTION DEFINITION ") \
    ERROR(SEM_TYPE_EXPECTED_SCALAR, "INPUT EXPECTS SCALAR VALUES") \
    ERROR(SEM_TYPE_OUTPUT, "OUTPUT EXPECTS string, real, int OR char") 


#define GENERATE_ERROR_ENUM(ENUM, STRING) ENUM,
#define GENERATE_ERROR_STRING(ENUM, STRING) STRING,

enum sem_error {
    FOREACH_ERROR(GENERATE_ERROR_ENUM)
};

int semCheck(AST_NODE*);
void semCheckDeclaration(AST_NODE  *node);
void semCheckUndeclared(HASH_NODE **hash);
void semCheckUsage(AST_NODE *node);
void semCheckTypes(AST_NODE *node);

void semError(int error, int line, char *msg);

#endif