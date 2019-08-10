#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vx_sub.h"

/* VX no data value */
#define VX_NO_DATA -99999.0

  /* Init vx */
//(vx_setup(conf->config) != 0)

/* Register SCEC 1D background model */
//vx_register_scec();
/* Disable background model */
//vx_register_bkg(NULL);

/* Query CVM-H */
int main()
{
  vx_entry_t entry;
  float vx_surf;
  vx_zmode_t zmode;

  zmode = VX_ZMODE_ELEVOFF;
/*
  zmode = VX_ZMODE_DEPTH;
 or zmode = VX_ZMODE_ELEV;
  */

  vx_setup("../model");

  vx_setgtl(1);
  /* Set vx query mode */
  vx_setzmode(zmode);

  /* Set query by geo coordinates */
  entry.coor_type = VX_COORD_GEO;
//  entry.coor_type = VX_COORD_UTM;

  vx_getsurface(&(entry.coor[0]), entry.coor_type, &vx_surf);
  fprintf(stderr,"vx_surf is %lf\n", vx_surf); 

/*
   if (vx_surf - VX_NO_DATA < 0.01) {
     entry.coor[2] = Z;
   } else {
     entry.coor[2] = vx_surf - Z;
   }
*/

   /* Setup point to query */
   entry.coor[0] = -120.7712;
   entry.coor[1] = 31.0403;
   entry.coor[2] = -100000.0;
// result should be 1, and 1316.400024

   vx_getcoord(&entry);

if (entry.data_src != VX_SRC_NR) {
   if (entry.vp > 0.0) {
     fprintf(stderr,"Vp is..%lf\n", entry.vp);
   }
   if (entry.vs > 0.0) {
     fprintf(stderr,"Vs is..%lf\n", entry.vs);
   }
   if (entry.rho > 0.0) {
     fprintf(stderr,"Rho is..%lf\n", entry.rho);
   }
 } else {
   fprintf(stderr,"XXX datasource is VX_SRC_NR\n");
 }

  return 1;
}
