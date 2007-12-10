/*
 *  PWD Shell Command Implmentation
 *
 *  Author: Fernando RUIZ CASAS
 *  Work: fernando.ruiz@ctv.es
 *  Home: correo@fernando-ruiz.com
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.com/license/LICENSE.
 *
 *  $Id$
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <unistd.h>

#include <rtems.h>
#include <rtems/shell.h>
#include "internal.h"

int main_pwd (int argc, char *argv[]) {
  char dir[1024];

  getcwd(dir,1024);
  fprintf(stdout,"%s\n",dir);
  return 0;
}

shell_cmd_t Shell_PWD_Command = {
  "pwd",                                        /* name */
  "pwd          # print work directory",        /* usage */
  "files",                                      /* topic */
  main_pwd  ,                                   /* command */
  NULL,                                         /* alias */
  NULL                                          /* next */
};
