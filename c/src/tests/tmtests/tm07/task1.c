/*
 *
 *  COPYRIGHT (c) 1989, 1990, 1991, 1992, 1993, 1994.
 *  On-Line Applications Research Corporation (OAR).
 *  All rights assigned to U.S. Government, 1994.
 *
 *  This material may be reproduced by or for the U.S. Government pursuant
 *  to the copyright license under the clause at DFARS 252.227-7013.  This
 *  notice must appear in all copies of this file and its derivatives.
 *
 *  $Id$
 */

#define TEST_INIT
#include "system.h"

rtems_id Task_id[OPERATION_COUNT+1], task_index;

rtems_task High_task(
  rtems_task_argument argument
);

rtems_task Middle_tasks(
  rtems_task_argument argument
);

rtems_task Low_task(
  rtems_task_argument argument
);

void test_init();

rtems_task Init(
  rtems_task_argument argument
)
{
  rtems_status_code status;

  Print_Warning();

  puts( "\n\n*** TIME TEST 7 ***" );

  test_init();

  status = rtems_task_delete( RTEMS_SELF );
  directive_failed( status, "rtems_task_delete of RTEMS_SELF" );
}

void test_init()
{
  rtems_status_code   status;
  rtems_task_priority priority;
  rtems_task_entry    task_entry;
  rtems_unsigned32    index;

  priority = 250;

  for( index=0 ; index <= OPERATION_COUNT ; index++ ) {
    status = rtems_task_create(
      rtems_build_name( 'T', 'I', 'M', 'E' ),
      priority,
      1024,
      RTEMS_DEFAULT_MODES,
      RTEMS_DEFAULT_ATTRIBUTES,
      &Task_id[index]
    );
    directive_failed( status, "rtems_task_create" );
    priority--;

    if      ( index == 0 )               task_entry = Low_task;
    else if ( index == OPERATION_COUNT ) task_entry = High_task;
    else                                 task_entry = Middle_tasks;

    status = rtems_task_start( Task_id[index], task_entry, 0 );
    directive_failed( status, "rtems_task_start" );
  }
}

rtems_task High_task(
  rtems_task_argument argument
)
{
  if ( argument != 0 ) {
    end_time = Read_timer();

    put_time(
      "rtems_task_restart suspended/preempt",
      end_time,
      OPERATION_COUNT,
      0,
      CALLING_OVERHEAD_TASK_RESTART
    );
  } else
    (void) rtems_task_suspend( RTEMS_SELF );

  puts( "*** END OF TEST 7 ***" );
  exit( 0 );
}

rtems_task Middle_tasks(
  rtems_task_argument argument
)
{
  task_index++;

  if ( argument != 0 )
    (void) rtems_task_restart( Task_id[ task_index ], 0xffffffff );
  else
    (void) rtems_task_suspend( RTEMS_SELF );
}

rtems_task Low_task(
  rtems_task_argument argument
)
{
  task_index = 1;

  Timer_initialize();
  (void) rtems_task_restart( Task_id[ task_index ], 0xffffffff );
}
