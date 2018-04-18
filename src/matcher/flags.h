/*
 * flags.h
 *
 *  Created on: Apr 18, 2018
 *      Author: alcabana
 */

#ifndef SRC_FLAGS_H_
#define SRC_FLAGS_H_

#define INIT_BIT				(1<<0)
#define OUTPUT_LINE_BIT			(1<<1)
#define OUTPUT_LINE_NUM_BIT  	(1<<2)
#define VERBOSE_BIT				(1<<3)

#define IS_ACTIVE(flags,bit) 	(flags & bit)

#endif /* SRC_FLAGS_H_ */
