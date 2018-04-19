/*
 * regex.h
 *
 *  Created on: Apr 18, 2018
 *      Author: alcabana
 */

#ifndef SRC_MATCHER_MATCHER_H_
#define SRC_MATCHER_MATCHER_H_

#include <stdio.h>
#include "regex.h"

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
 * Represents a matcher object
 * */
typedef struct matcher{
	REGEX_MACHINE machine;
	unsigned int flags;
} MATCHER;

void matcher_init(MATCHER* m, const char* ptrn, int flags, MATCHER_ERR* e);

void match_against_str(MATCHER m, char* source_str, MATCHER_RESULT* res, MATCHER_ERR* e);

void match_against_stream(MATCHER m, FILE* stream, MATCHER_RESULT* res, MATCHER_ERR* e);

#endif /* SRC_MATCHER_MATCHER_H_ */
