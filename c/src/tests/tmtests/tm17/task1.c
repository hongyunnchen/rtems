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

rtems_unsigned32 Task_count;
rtems_task_priority Task_priority;

rtems_task First_task(
  rtems_task_argument argument
);

rtems_task Middle_tasks(
  rtems_task_argument argument
);

rtems_task Last_task(
  rtems_task_argument argument
);

rtems_task Init(
  rtems_task_argument argument
)
{
  rtems_task_entry  task_entry;
  rtems_unsigned32  index;
  rtems_status_code status;

  Print_Warning();

  puts( "\n\n*** TIME TEST 17 ***" );

  Task_priority = 254;

  for( index = 0; index <= OPERATION_COUNT ; index++ ) {
    status = rtems_task_create(
      rtems_build_name( 'T', 'I', 'M', 'E' ),
      Task_priority,
      1024,
      RTEMS_DEFAULT_MODES,
      RTEMS_DEFAULT_ATTRIBUTES,
      &Task_id[ index ]
    );
    directive_failed( status, "rtems_task_create loop" );

    if ( index == OPERATION_COUNT ) task_entry = Last_task;
    else if ( index == 0 )          task_entry = First_task;
    else                            task_entry = Middle_tasks;

    status = rtems_task_start( Task_id[ index ], task_entry, 0 );
    directive_failed( status, "rtems_task_start loop" );
  }

  Task_count = 1;
  status = rtems_task_delete( RTEMS_SELF );
  directive_failed( status, "rtems_task_delete of RTEMS_SELF" );
}

rtems_task First_task(
  rtems_task_argument argument
)
{
  rtems_task_priority previous_priority;

  Timer_initialize();

  Task_priority--;
  Task_count++;

  (void) rtems_task_set_priority(
           Task_id[ Task_count ],
           Task_priority,
           &previous_priority
         );
}

rtems_task Middle_tasks(
  rtems_task_argument argument
)
{
  rtems_task_priority previous_priority;

  Task_priority--;
  Task_count++;

  (void) rtems_task_set_priority(
           Task_id[ Task_count ],
           Task_priority,
           &previous_priority
         );
}

rtems_task Last_task(
  rtems_task_argument argument
)
{
  rtems_unsigned32 index;

  end_time = Read_timer();

  Timer_initialize();
    for ( index=1 ; index <= OPERATION_COUNT ; index++ )
      (void) Empty_function();
  overhead = Read_timer();

  put_time(
    "rtems_task_set_priority (preemptive)",
    end_time,
    OPERATION_COUNT,
    overhead,
    CALLING_OVERHEAD_TASK_SET_PRIORITY
  );

  puts( "*** END OF TEST 17 ***" );
  exit( 0 );
}
