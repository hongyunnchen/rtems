/*  Preempt_task
 *
 *  This routine serves as a test task.  It verifies the task manager.
 *
 *  Input parameters:
 *    argument - task argument
 *
 *  Output parameters:  NONE
 *
 *  COPYRIGHT (c) 1989, 1990, 1991, 1992, 1993, 1994.
 *  On-Line Applications Research Corporation (OAR).
 *  All rights assigned to U.S. Government, 1994.
 *
 *  This material may be reproduced by or for the U.S. Government pursuant
 *  to the copyright license under the clause at DFARS 252.227-7013.  This
 *  notice must appear in all copies of this file and its derivatives.
 *
 *  preempt.c,v 1.2 1995/05/31 17:06:51 joel Exp
 */

#include "system.h"

rtems_task Preempt_task(
  rtems_task_argument argument
)
{
  rtems_status_code status;

  puts( "PREEMPT - rtems_task_delete - deleting self" );
  status = rtems_task_delete( RTEMS_SELF );
  directive_failed( status, "rtems_task_delete of RTEMS_PREEMPT" );
}
