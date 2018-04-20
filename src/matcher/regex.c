/*
 * regex.c
 *
 *  Created on: Apr 18, 2018
 *      Author: alcabana
 */
#include <string.h>
#include <ctype.h>
#include "regex.h"

static REGEX_STATE START_STATE_TEMPLATE = {
	.edges = NULL,
	.nb_edges  = 0,
};

void* regex_alloc(REGEX_pMACHINE machine, size_t size){
	void* ret;

	if(!size) return NULL;

	if(!machine->membuf || size + machine->mallocd > machine->bufsize){
		/* realloc */
		size_t newbufsize = max(2*(machine->bufsize+size),REGEX_MEM_BUF_BYTES);
		void* tmp = machine->membuf;
		machine->membuf = malloc(newbufsize);
		memcpy(machine->membuf,tmp,machine->mallocd);
		machine->bufsize = newbufsize;
		free(tmp);
	}
	ret = &machine->membuf[machine->mallocd];
	machine->mallocd += size;
	return ret;
}

void regex_free(REGEX_pMACHINE machine, void* ptr){
	(void*)ptr;
}

void regex_init_state_machine(REGEX_pMACHINE machine, PATTERN pattern, int flags, REGEX_pERR err){

	/* Init */
	machine->bufsize = 0;
	machine->mallocd = 0;
	machine->membuf  = NULL;
	machine->start = regex_alloc_state(machine);
	memcpy(machine->start, &START_STATE_TEMPLATE, sizeof(REGEX_STATE));

	regex_parse(machine, pattern, err);
}

REGEX_pSTATE regex_alloc_state(REGEX_pMACHINE machine){
	REGEX_pSTATE ret;

	ret = regex_alloc(machine, sizeof(REGEX_STATE));
	ret->edges = NULL;
	ret->nb_edges = 0;
	return ret;
}

REGEX_pEDGE regex_alloc_edge(REGEX_pMACHINE machine){
	REGEX_pEDGE ret;

	ret = regex_alloc(machine, sizeof(REGEX_EDGE));
	return ret;
}

/* skynet beware, regex machina comin */
void regex_free_machine(REGEX_pMACHINE machine){
	free(machine->membuf);
}

void regex_parse(REGEX_pMACHINE machine, PATTERN pattern, REGEX_pERR err) {
	size_t ptrn_size, i;
	REGEX_pSTATE tail;

	/* pattern is empty? */
	ptrn_size = strlen(pattern);
	if(ptrn_size == 0) regex_set_err(err, 0);
	/* TODO case when pattern is a single ascii char, performance to be gained here*/

	tail = machine->start;
	i = 0;
	do{
		/* There should always be a single state of "return" for a token, even embedded ones*/
		REGEX_pSTATE token_tail = regex_parse_next_token(machine, tail, pattern, &i, err);
		tail = token_tail;
	} while(i < ptrn_size);
	return;
}

void regex_set_err(REGEX_pERR err, REGEX_ERR_CODE code){
	err->code = code;
}

REGEX_pSTATE regex_parse_next_token(REGEX_pMACHINE machine, REGEX_pSTATE append_to, PATTERN pattern, size_t* i, REGEX_pERR err){
	char cur;
	REGEX_pSTATE newtail;

	cur = pattern[*i];

	/* Separate cases */
	if(isalpha(cur))
		newtail = regex_handle_char(machine, append_to, pattern, i, err);
	else if(cur == BACKSLASH)
		newtail = regex_handle_escaped_char(machine, append_to, pattern, i, err);
	else if(cur == OPEN_BRACKET)
		newtail = regex_handle_brackets(machine, append_to, pattern, i, err);

	return newtail;
}

REGEX_pSTATE regex_handle_char(REGEX_pMACHINE machine, REGEX_pSTATE append_to, PATTERN pattern, size_t* i, REGEX_pERR err){
	REGEX_pEDGE nedge;
	REGEX_pSTATE nstate;

	nedge  = regex_alloc_edge(machine);
	nstate = regex_alloc_state(machine);

	nedge->condition = regex_get_quantifier_condition(pattern, i);
	nedge->to = (struct REGEX_STATE*)nstate;

	append_to->edges    = (REGEX_pEDGE*)nedge;
	append_to->nb_edges = 1;

	return nstate;
}

REGEX_pSTATE regex_handle_escaped_char(REGEX_pMACHINE machine, REGEX_pSTATE append_to, PATTERN pattern, size_t* i, REGEX_pERR err){
	REGEX_pEDGE edge;

}

REGEX_pSTATE regex_handle_brackets(REGEX_pMACHINE machine, REGEX_pSTATE append_to, PATTERN pattern, size_t* i, REGEX_pERR err){

}

REGEX_CONDITION regex_get_quantifier_condition(PATTERN pattern, size_t* i){
	REGEX_CONDITION c;
	char next, current;
	current = pattern[*(i)];
	next 	= pattern[*(i)+1];

	c.negated    = REGEX_NO;
	c.payload[0] = current; //the letter itself

	switch(next) {
	case('\0'): c.type = SINGLE; break;
	case(STAR): c.type = ZERO_OR_MORE; break;
	case(ADD_SIGN): c.type = ONE_OR_MORE; break;
	case(INT_MARK): c.type = ZERO_OR_ONE; break;
	case(OPEN_BRACE):
		/* Get ranged quantifier*/
				//TODO
	default: c.type = SINGLE; break;
	}
	return c;
}
