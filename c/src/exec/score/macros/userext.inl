/*  userext.inl
 *
 *  This file contains the macro implementation of the inlined routines
 *  from the User Extension Handler
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

#ifndef __USER_EXTENSIONS_inl
#define __USER_EXTENSIONS_inl

/*PAGE
 *
 *  _User_extensions_Handler_initialization
 *
 */

#define _User_extensions_Handler_initialization( _initial_extensions ) \
  { \
    _Chain_Initialize_empty( &_User_extensions_List ); \
    \
    if ( (_initial_extensions) ) { \
      _User_extensions_Initial.Callouts = *(_initial_extensions); \
      _Chain_Append( \
        &_User_extensions_List, &_User_extensions_Initial.Node ); \
    } \
  }

/*PAGE
 *
 *  _User_extensions_Add_set
 */

#define _User_extensions_Add_set( _the_extension, _extension_table ) \
  do { \
    (_the_extension)->Callouts = *(_extension_table); \
    \
    _Chain_Append( &_User_extensions_List, &(_the_extension)->Node ); \
  } while ( 0 )

/*PAGE
 *
 *  _User_extensions_Add_API_set
 */
 
#define _User_extensions_Add_API_set( _the_extension ) \
  _Chain_Prepend( &_User_extensions_List, &(_the_extension)->Node )
 

/*PAGE
 *
 *  _User_extensions_Remove_set
 */

#define _User_extensions_Remove_set( _the_extension ) \
  _Chain_Extract( &(_the_extension)->Node )

/*PAGE
 *
 *  _User_extensions_Run_list_forward
 *
 *  NOTE:  No parentheses around macro names here to avoid
 *         messing up the name and function call expansion.
 */

#define _User_extensions_Run_list_forward( _name, _arguments ) \
  do { \
    Chain_Node              *the_node; \
    User_extensions_Control *the_extension; \
    \
    for ( the_node = _User_extensions_List.first ; \
          !_Chain_Is_tail( &_User_extensions_List, the_node ) ; \
          the_node = the_node->next ) { \
      the_extension = (User_extensions_Control *) the_node; \
      \
      if ( the_extension->Callouts.## _name != NULL ) \
        (*the_extension->Callouts.## _name) _arguments; \
      \
    } \
    \
  } while ( 0 )

/*PAGE
 *
 *  _User_extensions_Run_list_backward
 *
 *  NOTE:  No parentheses around macro names here to avoid
 *         messing up the name and function call expansion.
 */

#define _User_extensions_Run_list_backward( _name, _arguments ) \
  do { \
    Chain_Node              *the_node; \
    User_extensions_Control *the_extension; \
    \
    for ( the_node = _User_extensions_List.last ; \
          !_Chain_Is_head( &_User_extensions_List, the_node ) ; \
          the_node = the_node->previous ) { \
      the_extension = (User_extensions_Control *) the_node; \
      \
      if ( the_extension->Callouts.## _name != NULL ) \
        (*the_extension->Callouts.## _name) _arguments; \
      \
    } \
    \
  } while ( 0 )

/*PAGE
 *
 *  _User_extensions_Thread_switch
 *
 */

#define _User_extensions_Thread_switch( _executing, _heir ) \
  _User_extensions_Run_list_forward(thread_switch, (_executing, _heir) )

/*PAGE
 *
 *  _User_extensions_Thread_post_switch
 *
 */

#define _User_extensions_Thread_post_switch( _executing ) \
  _User_extensions_Run_list_forward(thread_post_switch, (_executing) )

#endif
/* end of include file */
