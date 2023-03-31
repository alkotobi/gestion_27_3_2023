#pragma once
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif
    //todo: reset ARRAY_MIN_SIZE
#define ARRAY_MIN_SIZE 250
#define INT_PRINT_SIZE 5
#define DOUBLE_PRINT_SIZE 10
#define STRING_PRINT_SIZE 20
#define DEBUG 1
typedef enum {
    CString,
    Double,
    Int,
    Big_int,
    Null,
} mntypes ;

//typedef  enum mnlogic_op mnlogic_op_enum  ;
enum mnlogic_op { AND, OR, AND_NOT,OR_NOT   };
//typedef  enum mncomp_op mncomp_op_enum  ;
enum mncomp_op {EQ , GREAT, LESS , GR_OR_EQ , LES_OR_EQ ,LIKE};
typedef unsigned long int TLint ;
typedef void* mnvar;
typedef char** mnstrhld;
typedef void** mnptrhld ;
typedef void (*mnfree_fnc)(mnptrhld) ;
typedef mnvar (*mnf_var_var)(mnvar);
typedef void(*mnf_void_ptrhld)(mnptrhld) ;
typedef char (*mnf_char_var_var)(void*,void*);
/*typedef char(*TFCharVarVar)(TVar,TVar) ;
typedef void(*TFVoidPtrHld)(TPtrHld) ;
typedef TVar(*TFVarVoid)(void) ;
typedef void(*TFVoidVarVar)(TVar,TVar) ;
typedef TLint(*TFLintVar)(TVar) ;
typedef TVar(*TFVarVarLint)(TVar,TLint) ;
typedef void(*TFVoidVar)(TVar) ;
typedef TLint(*TFLintVarVar)(TVar,TVar) ;*/
void mnassert(void* ptr);
void* mnalloc(size_t size);
void mnfree(void* ptr);
void mnfree_v1(mnptrhld ptr_hld);
void* mnrealloc(void* ptr,size_t new_size);
void* mncalloc(size_t count,size_t size);
void mnfree_v0(void** ptr_hld);

#ifdef __cplusplus
}
#endif
