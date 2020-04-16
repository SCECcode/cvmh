/** 
    vx_lite - A command line program to extract velocity values
    from CVM-H. Accepts Geographic Coordinates or UTM Zone 11 
    coordinates.

    01/2011: PES: Initial implementation derived from vx.c
    07/2011: PES: Added option for specifying model directory,
                  reorganized options
**/


#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <getopt.h>
#include "params.h"
#include "vx_sub.h"

#define CVMH_LIST_DELIM ","
#define CVMH_MAX_PATH_LEN 100

/* Supported error codes */
typedef enum { CVMH_CODE_SUCCESS = 0,
               CVMH_CODE_ERROR,
               CVMH_CODE_NODATA } cvmh_code_t;

/* Usage function */
void usage() {
  printf("     vx_lite - (c) Harvard University, SCEC\n");
  printf("Extract velocities from a simple GOCAD voxet. Accepts\n");
  printf("geographic coordinates and UTM Zone 11, NAD27 coordinates in\n");
  printf("X Y Z columns. Z is expressed as elevation offset by default.\n\n");
  printf("\tusage: vx_lite [-g] [-s] [-m dir] [-z dep/elev/off] < file.in\n\n");
  printf("\t       or\n");
  printf("\t       vx_lite [-g] [-s] [-m dir] [-z dep/elev/off] -l lon,lat,depth\n\n");
  printf("Flags:\n");
  printf("\t-g disable GTL (default is on).\n");
  printf("\t-s directs use of SCEC 1D background and topo.\n");
  printf("\t-m directory containing model files (default is '.').\n");
  printf("\t-z directs use of dep/elev/off for Z column (default is offset).\n\n");
  printf("\t-l lon,lat,depth.\n\n");
  printf("Output format is:\n");
  printf("\tX Y Z utmX utmY elevX elevY topo mtop base moho hr/lr/cm cellX cellY cellZ tg vp vs rho regionID temp\n\n");
  printf("Version: %s\n\n", VERSION);
  exit (0);
}


/* Parses string list into double array */
int list_parse(const char *lstr, int llen, double *arr, int an)
{
  char *token;
  char *strbuf;
  int i = 0;

  if ((lstr == NULL) || (llen <= 0) || 
      (arr == NULL) || (an <= 0)) {
    return(CVMH_CODE_ERROR);
  }

  strbuf = malloc(llen);
  if (strbuf == NULL) {
    return(CVMH_CODE_ERROR);
  }

  if (snprintf(strbuf, llen, "%s", lstr) > llen) {
    fprintf(stderr, "Warning : String %s truncated to %s\n",
            lstr, strbuf);
  }

  token = strtok(lstr, CVMH_LIST_DELIM);
  while ((token != NULL) && (i < an)) {
    arr[i++] = atof(token);
    token = strtok(NULL, CVMH_LIST_DELIM);
  }

  free(strbuf);
  return(CVMH_CODE_SUCCESS);
}


void process_one(vx_entry_t *entry,int json) {
    /* In case we got anything like degrees */
    if ((entry->coor[0]<360.) && (fabs(entry->coor[1])<90)) {
	entry->coor_type = VX_COORD_GEO;
    } else {
	entry->coor_type = VX_COORD_UTM;
    }

    /* Query the point */
    vx_getcoord(entry);

    /*** Prevent all to obvious bad coordinates from being displayed */
    if (entry->coor[1]<10000000) {
	/* AP: Let's provide the computed UTM coordinates as well */
        if(!json) {
	  printf("%14.6f %15.6f %9.2f ", 
	       entry->coor[0], entry->coor[1], entry->coor[2]);
	  printf("%10.2f %11.2f ", entry->coor_utm[0], entry->coor_utm[1]);
  	
	  printf("%10.2f %11.2f ", entry->elev_cell[0], entry->elev_cell[1]);
	  printf("%9.2f ", entry->topo);
	  printf("%9.2f ", entry->mtop);
	  printf("%9.2f ", entry->base);
	  printf("%9.2f ", entry->moho);
	  printf("%s %10.2f %11.2f %9.2f ", VX_SRC_NAMES[entry->data_src], 
	       entry->vel_cell[0], entry->vel_cell[1], entry->vel_cell[2]);
	  printf("%9.2f %9.2f %9.2f ", entry->provenance, entry->vp, entry->vs);
	  printf("%9.2f ", entry->rho);
  	  printf("%0.0f ", entry->regionID);
  	  printf("%0.4f\n", entry->temp_median);
//	  printf("regionID=%lf\n", entry->regionID);
//	  printf("temp_median=%lf\n", entry->temp_median);
          } else {  // concat a json like string..
	      printf("{\"X\":%.4f,\"Y\":%.4f,\"Z\":%.2f,", 
	           entry->coor[0], entry->coor[1], entry->coor[2]);
	      printf("\"utmX\":%.2f,\"utmY\":%.2f,", entry->coor_utm[0], entry->coor_utm[1]);
	      printf("\"elevX\":%.2f,\"elevY\":%.2f,", entry->elev_cell[0], entry->elev_cell[1]);
	      printf("\"topo\":%.2f,", entry->topo);
	      printf("\"mtop\":%.2f,", entry->mtop);
	      printf("\"base\":%.2f,", entry->base);
	      printf("\"moho\":%.2f,", entry->moho);
	      printf("\"src\":\"%s\",\"cellX\":%.2f,\"cellY\":%.2f,\"cellZ\":%.2f,", VX_SRC_NAMES[entry->data_src], 
	           entry->vel_cell[0], entry->vel_cell[1], entry->vel_cell[2]);
	      printf("\"tg\":%.2f,\"vp\":%.2f,\"vs\":%.2f,", entry->provenance, entry->vp, entry->vs);
	      printf("\"rho\":%.2f,", entry->rho);
	      printf("\"regionID\":%.0f,\"temp\":%.2f}\n",entry->regionID,entry->temp_median);
       }
    }
}



extern char *optarg;
extern int optind, opterr, optopt;


int main (int argc, char *argv[])
{
  vx_entry_t entry;
  char modeldir[CMLEN];
  vx_zmode_t zmode;
  int use_gtl = True;
  int use_scec = False;
  int use_infile = True;
  int opt;
  double lvals[3];
  
  zmode = VX_ZMODE_ELEVOFF;
  strcpy(modeldir, ".");

  /* Parse options */
  while ((opt = getopt(argc, argv, "gm:sz:hl:")) != -1) {
    switch (opt) {
    case 'g':
      use_gtl = False;
      break;
    case 'm':
      strcpy(modeldir, optarg);
      break;
    case 's':
      use_scec = True;
      break;
    case 'l':
      if (list_parse(optarg, CVMH_MAX_PATH_LEN,
                     lvals, 3) != CVMH_CODE_SUCCESS) {
        fprintf(stderr, "Invalid -l lon,lat,depth: %s.\n", optarg);
        usage();
        exit(1);
      }
      use_infile = False;
      break;
    case 'z':
      if (strcasecmp(optarg, "dep") == 0) {
	zmode = VX_ZMODE_DEPTH;
      } else if (strcasecmp(optarg, "elev") == 0) {
	zmode = VX_ZMODE_ELEV;
      } else if (strcasecmp(optarg, "off") == 0) {
	zmode = VX_ZMODE_ELEVOFF;
      } else {
	fprintf(stderr, "Invalid coord type %s", optarg);
	usage();
	exit(0);
      }
      break;
    case 'h':
      usage();
      exit(0);
      break;
    default: /* '?' */
      usage();
      exit(1);
    }
  }

  /* Perform setup */
  if (vx_setup(modeldir) != 0) {
    fprintf(stderr, "Failed to init vx\n");
    exit(1);
  }

  /* Register SCEC 1D background model */
  if (use_scec) {
    vx_register_scec();
  }

  /* Set GTL */
  vx_setgtl(use_gtl);

  /* Set zmode */
  vx_setzmode(zmode);

  /* now let's start with searching .... */
  if(use_infile) {
    while (!feof(stdin)) {    
      if (fscanf(stdin,"%lf %lf %lf",
	         &entry.coor[0],&entry.coor[1],&entry.coor[2]) == 3) {
          process_one(&entry,0);
      }
    }
    } else { // just 1 set
      entry.coor[0]=lvals[1];
      entry.coor[1]=lvals[0];
      entry.coor[2]=lvals[2];
      process_one(&entry,1);
  }

  /* Perform cleanup */
  vx_cleanup();

  return(CVMH_CODE_SUCCESS);
}
