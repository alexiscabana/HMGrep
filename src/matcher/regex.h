/*
 * regex.h
 *
 *  Created on: Apr 18, 2018
 *      Author: alcabana
 */

#ifndef SRC_MATCHER_REGEX_H_
#define SRC_MATCHER_REGEX_H_

#include <stdio.h>

/*
 * Represents an error object
 * */
typedef struct match_err{
	unsigned int code;
} MATCHER_ERR;


typedef struct match_result{
	unsigned int code;
} MATCHER_RESULT;
/*
 * This options struct concerns the pattern and how the state machine should react and interpret things
 * */
typedef struct regex_opt{
	const char* pattern;
} REGEX_OPT;

/*
 * Represents a matcher object
 * */
typedef struct matcher{
	REGEX_OPT* 	opts;
	unsigned int flags;
} MATCHER;

void matcher_init(MATCHER* m, REGEX_OPT* opts, MATCHER_ERR* e);

void match_against_str(MATCHER m, char* source_str, MATCHER_RESULT* res, MATCHER_ERR* e);

void match_against_stream(MATCHER m, FILE* stream, MATCHER_RESULT* res, MATCHER_ERR* e);

#endif /* SRC_MATCHER_REGEX_H_ */
