#ifndef __AS_H__
#define __AS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include <brandon/vvector.h>
#include <brandon/tok.h>

typedef enum AsmSyntax_enum
{
    AsmSyntax_patt,
    AsmSyntax_lccc
} AsmSyntax;

typedef struct AsmSettings_str
{
    AsmSyntax syntax;
} AsmSettings;



typedef struct Source_str
{
    char * name;    // where this came from
    char * raw;     // raw code

    int numLines;   // number of lines
    char ** lines;  // array of lines

    Tokenizer * tok;    // tokenizer for the source
} Source;
void Source_ctor( Source * thiz, const char * src, const char * name );
void Source_dtor( Source * thiz );

typedef struct Program_str
{
    VVector(Symbol) * localSymbols;     // symbols declared in this unit
    VVector(Symbol) * externalSymbols;  // symbols that are
    VVector(Symbol) * exportSymbols;
    VVector(Symbol) * code;
} Program;

typedef struct Symbol_str
{
    int external;
    int32_t offset;
} Symbol;

typedef enum ParseError_enum
{
    ParseError_Okay,
    ParseError_InvalidOpcode,
    ParseError_SymbolMultiplyDeclare,
    ParseError_OtherError
} ParseError;

typedef enum AsmOp_enum
{
    // original operations
    AsmOp_add,
    AsmOp_and,
    AsmOp_not,
    AsmOp_br,
    AsmOp_nop,
    AsmOp_jmp,
    AsmOp_jsr,
    AsmOp_jsrr,
    AsmOp_ret,
    AsmOp_ld,
    AsmOp_ldr,
    AsmOp_ldi,
    AsmOp_st,
    AsmOp_str,
    AsmOp_sti,
    AsmOp_trap,
    AsmOp_rti,
    // original pseudo-ops
    AsmOp_orig,
    AsmOp_blkw,
    AsmOp_fill,
    AsmOp_stringz,

    // new operations
    AsmOp_mov,
    AsmOp_or,
    AsmOp_neg,
    AsmOp_push,
    AsmOp_pop,
    // new pseudo-ops
    AsmOp_stringp,
    AsmOp_define,
    AsmOp_section,
    AsmOp_export,
    AsmOp_import,

    //
    AsmOp_invalid
} AsmOp;

typedef enum AsmOpClass_enum
{
    AsmOpClass_Concrete,    // linkable; creates data
    AsmOpClass_Meta,        // doesn't create data
} AsmOpClass;

typedef struct AsmOpProp_str
{
    const char * match; // pattern to match
    AsmOp op;           // resulting op
    AsmOpClass cls;     // class of operation
} AsmOpProp;

#ifdef __cplusplus
}
#endif

#endif//__AS_H__
