/*
 * regex
 *
 *  Created on: Apr 18, 2018
 *      Author: alcabana
 */
#include "matcher.h"
#include "regex.h"

void matcher_init(MATCHER* m, const char* ptrn, int flags, MATCHER_ERR* e) {
	REGEX_ERR err;
	regex_init_state_machine(&m->machine, ptrn, flags, &err);
}

void match_against_str(MATCHER m, char* source_str, MATCHER_RESULT* res, MATCHER_ERR* e) {

}

void match_against_stream(MATCHER m, FILE* stream, MATCHER_RESULT* res, MATCHER_ERR* e) {

}
