#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include "unittest_defs.h"
#include "test_vx_sub.h"
#include "test_vx_exec.h"
#include "test_vx_lite_exec.h"



int main (int argc, char *argv[])
{
  char *xmldir;
  int err = 0;
  
  if (argc == 2) {  
    xmldir = argv[1];
  } else {
    xmldir = NULL;
  }

  /* Run test suites */
  err |= suite_vx_sub(xmldir);
  err |= suite_vx_exec(xmldir);
  err |= suite_vx_lite_exec(xmldir);

  return err;
}
