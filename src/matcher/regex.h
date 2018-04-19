/*
 * regex.h
 *
 *  Created on: Apr 18, 2018
 *      Author: alcabana
 */

#ifndef SRC_MATCHER_REGEX_H_
#define SRC_MATCHER_REGEX_H_

#include <stdlib.h>

#define REGEX_MEM_BUF_BYTES		2048u
#define REGEX_CONDITION_SIZE	32u
#define REGEX_NO				0u
#define REGEX_YES				1u
#define REGEX_BYTE_pBUF			unsigned char*
#define REGEX_BYTE_BUF			unsigned char
#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })
#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

#define PATTERN  							const char *
#define REGEX_ERR_CODE  					unsigned int
#define ESCAPE_CHAR							'\\'
#define OPEN_SINGLE_TOKEN_CHOICES_CHAR		'['
#define CLOSE_SINGLE_TOKEN_CHOICES_CHAR		']'

typedef struct regex_opt{
	const char* pattern;
} REGEX_OPT;

typedef struct regex_err{
	REGEX_ERR_CODE code;
} REGEX_ERR;
typedef REGEX_ERR* REGEX_pERR;

typedef enum {
	SINGLE,
	RANGE,
	ZERO_OR_ONE,
	ZERO_OR_MORE,
	ONE_OR_MORE,
	RANGE_OCCURENCES
	/* TODO add handled condition types here */
} REGEX_CONDITION_TYPE;

typedef struct regex_condition{
	REGEX_CONDITION_TYPE type;
	REGEX_BYTE_BUF payload[REGEX_CONDITION_SIZE];
	unsigned char negated;
} REGEX_CONDITION;

typedef struct regex_edge{
	struct REGEX_STATE* to;
	REGEX_CONDITION condition;
} REGEX_EDGE;
typedef REGEX_EDGE* REGEX_pEDGE;


typedef struct regex_state{
	REGEX_pEDGE* edges;
	size_t nb_edges;
} REGEX_STATE;
typedef REGEX_STATE* REGEX_pSTATE;


typedef struct regex_machine{
	REGEX_pSTATE  start;
	REGEX_BYTE_pBUF membuf;
	size_t bufsize;
	size_t mallocd;
} REGEX_MACHINE;
typedef REGEX_MACHINE* REGEX_pMACHINE;


typedef struct regex_parse_state{

} REGEX_PARSE_STATE;



void regex_init_state_machine(REGEX_pMACHINE machine, PATTERN pattern, int flags, REGEX_pERR err);

REGEX_pSTATE regex_alloc_state(REGEX_pMACHINE machine);

void regex_free_machine(REGEX_pMACHINE machine);

void regex_set_err(REGEX_pERR err, REGEX_ERR_CODE code);

void regex_parse(REGEX_pMACHINE machine, PATTERN pattern, REGEX_pERR err);

REGEX_pSTATE regex_parse_next_token(REGEX_pMACHINE machine, REGEX_pSTATE append_to, PATTERN pattern, size_t* i, REGEX_pERR err);

#endif /* SRC_MATCHER_REGEX_H_ */
