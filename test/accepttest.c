#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <getopt.h>
#include "unittest_defs.h"
#include "test_grid.h"


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
  err |= suite_grid(xmldir);

  return err;
}
