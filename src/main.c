/*
 ============================================================================
 Name        : HMgrep.c
 Author      : Alexis Cabana-Loriaux
 Version     : 1.0
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "argparse/argparse.h"
#include "matcher/flags.h"
#include "matcher/regex.h"



#define PATH_MAX_CHAR			256u
#define REGEX_MAX_CHAR			256u

static const char *const usage[] = {
    "test_argparse [options] [[--] args]",
    "test_argparse [options]",
    NULL,
};

int main(int argc, const char **argv) {
    char path[PATH_MAX_CHAR];
    char regex[REGEX_MAX_CHAR];
    memset(path,0,PATH_MAX_CHAR);
    memset(regex,0,REGEX_MAX_CHAR);
    int flags = 0;
    MATCHER m;
    REGEX_OPT opts;
    MATCHER_ERR err;
    MATCHER_RESULT res;
    FILE* fp = NULL;

    struct argparse_option options[] = {
        OPT_HELP(),
        OPT_GROUP("Basic options"),
        OPT_STRING('p', "path", &path, "file to match. if empty, will match against stdin"),
		OPT_STRING('r', "regex", &regex, "regex to match against"),
        OPT_GROUP("Flag options"),
		OPT_BIT('v', "verbose", &flags, "", NULL, VERBOSE_BIT),
		OPT_BIT('l', "", &flags, "if a match should output the whole line (until a carriage return)", NULL, OUTPUT_LINE_BIT),
		OPT_BIT('n', "", &flags, "if a match should output the line number",NULL, OUTPUT_LINE_NUM_BIT),
        //OPT_BIT(0, "write", &perms, "write perm", NULL, PERM_WRITE),
        //OPT_BIT(0, "exec", &perms, "exec perm", NULL, PERM_EXEC),
        OPT_END(),
    };

    struct argparse argparse;
    argparse_init(&argparse, options, usage, 0);
    argparse_describe(&argparse, "\nA brief description of what the program does and how it works.", "\nAdditional description of the program after the description of the arguments.");

    if(argc < 2) {
    	/* No options given */
    	argparse_help_cb(&argparse,NULL);
    }

    argc = argparse_parse(&argparse, argc, argv);

    /* Setup Matcher object*/
    if (path  != NULL)  fp = fopen(path,"r");
    if (regex != NULL)  opts.pattern = regex;

    matcher_init(&m, &opts, &err);
    if(err.code)  printf("Could not initialize matcher, code %u\n", err.code);

    /* Find results */
    match_against_str(m, "hey what is up my dude\n", &res, &err);


	return EXIT_SUCCESS;
}
