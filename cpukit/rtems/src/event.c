/*
 *  Event Manager
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

#include <rtems/system.h>
#include <rtems/rtems/status.h>
#include <rtems/rtems/event.h>
#include <rtems/core/isr.h>
#include <rtems/core/object.h>
#include <rtems/rtems/options.h>
#include <rtems/core/states.h>
#include <rtems/core/thread.h>
#include <rtems/rtems/tasks.h>

/*PAGE
 *
 *  rtems_event_send
 *
 *  This directive allows a thread send an event set to another thread.
 *
 *  Input parameters:
 *    id    - thread id
 *    event - event set
 *
 *  Output parameters:
 *    RTEMS_SUCCESSFUL - if successful
 *    error code - if unsuccessful
 */

rtems_status_code rtems_event_send(
  Objects_Id         id,
  rtems_event_set event_in
)
{
  register Thread_Control *the_thread;
  Objects_Locations        location;
  RTEMS_API_Control       *api;

  the_thread = _Thread_Get( id, &location );
  switch ( location ) {
    case OBJECTS_ERROR:
      return RTEMS_INVALID_ID;
    case OBJECTS_REMOTE:
      return(
        _Event_MP_Send_request_packet(
          EVENT_MP_SEND_REQUEST,
          id,
          event_in
        )
      );
    case OBJECTS_LOCAL:
      api = the_thread->API_Extensions[ THREAD_API_RTEMS ];
      _Event_sets_Post( event_in, &api->pending_events );
      _Event_Surrender( the_thread );
      _Thread_Enable_dispatch();
      return RTEMS_SUCCESSFUL;
  }

  return RTEMS_INTERNAL_ERROR;   /* unreached - only to remove warnings */
}

/*PAGE
 *
 *  rtems_event_receive
 *
 *  This directive allows a thread to receive a set of events.
 *
 *  Input parameters:
 *    event_in   - input event condition
 *    option_set - options
 *    ticks      - number of ticks to wait (0 means wait forever)
 *    event_out  - pointer to output event set
 *
 *  Output parameters:
 *    event out         - event set
 *    RTEMS_SUCCESSFUL - if successful
 *    error code        - if unsuccessful
 */

rtems_status_code rtems_event_receive(
  rtems_event_set  event_in,
  rtems_option     option_set,
  rtems_interval   ticks,
  rtems_event_set *event_out
)
{
  RTEMS_API_Control       *api;

  api = _Thread_Executing->API_Extensions[ THREAD_API_RTEMS ];

  if ( _Event_sets_Is_empty( event_in ) ) {
    *event_out = api->pending_events;
    return RTEMS_SUCCESSFUL;
  }

  _Thread_Disable_dispatch();
  _Event_Seize( event_in, option_set, ticks, event_out );
  _Thread_Enable_dispatch();
  return( _Thread_Executing->Wait.return_code );
}
