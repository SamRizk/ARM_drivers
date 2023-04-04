/*
 * SCHED.h
 *
 *  Created on: Mar 18, 2023
 *      Author: samir
 */

#ifndef SCHED_H_
#define SCHED_H_

#include "Std_types.h"
#include "Bit_math.h"

#include "SCHED_CFG.h"
#include "APP.h"

/*====================================================================================================*/
/******************************************* Macros ***************************************************/
/*====================================================================================================*/
#define TICK_T                         2

/********************************************** END ****************************************************/
/*====================================================================================================*/

/*====================================================================================================*/
/******************************************* Types ****************************************************/
/*====================================================================================================*/
typedef void (*runnableCbf_t) (void);
typedef struct
{
	runnable_name_t name;
    u32 period;
    runnableCbf_t cbf;
    u32 startDelay;
}taskInfo_t;

/********************************************** END ****************************************************/
/*====================================================================================================*/
extern const  taskInfo_t TaskInfo[NUM_OF_Runnables];


/*===================================================================================================*/
/************************************************ APIs ***********************************************/
/*===================================================================================================*/ 


/****************************************************************************************/
/*                       SCHED_init  function                                           */
/****************************************************************************************/
/*  Description: used to  intialize the schedelr                                        */
/* 	input:       void                                                                   */
/* 	return:      void                                                                   */
/****************************************************************************************/

void SCHED_init(void);



/****************************************************************************************/
/*                       SCHED_init  function                                           */
/****************************************************************************************/
/*  Description: used to  start the schedelr                                            */
/* 	input:       void                                                                   */
/* 	return:      void                                                                   */
/****************************************************************************************/

void SCHED_start (void);

/********************************************** END ****************************************************/
/*====================================================================================================*/




#endif /* SCHED_H_ */
