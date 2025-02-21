#ifndef CVMH_H
#define CVMH_H

/**
 * @file cvmh.h
 * @brief Main header file for CVMH library.
 * @author - SCEC 
 * @version 1.0
 *
 * Delivers CVMH Velocity Model
 *
 */

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <stdarg.h>

#include "vx_sub.h"

// Constants
#ifndef M_PI
	/** Defines pi */
	#define M_PI 3.14159265358979323846
#endif

#define VX_NO_DATA -99999.0
#define CVMH_CONFIG_MAX 1000

// Structures
/** Defines a point (latitude, longitude, and depth) in WGS84 format */
typedef struct cvmh_point_t {
	/** Longitude member of the point */
	double longitude;
	/** Latitude member of the point */
	double latitude;
	/** Depth member of the point */
	double depth;
} cvmh_point_t;

/** Defines the material properties this model will retrieve. */
typedef struct cvmh_properties_t {
	/** P-wave velocity in meters per second */
	double vp;
	/** S-wave velocity in meters per second */
	double vs;
	/** Density in g/m^3 */
	double rho;
        /** NOT USED from basic_property_t */
        double qp;
        /** NOT USED from basic_property_t */
        double qs;
} cvmh_properties_t;

/** The CVMH configuration structure. */
typedef struct cvmh_configuration_t {
	/** The zone of UTM projection */
	int utm_zone;
	/** The model directory */
	char model_dir[1000];
        /** interp */
	int interp;

} cvmh_configuration_t;

/** The model structure which points to available portions of the model. */
typedef struct cvmh_model_t {
	/** A pointer to the Vp data either in memory or disk. Null if does not exist. */
	void *vp;
	/** Vp status: 0 = not found, 1 = found and not in memory, 2 = found and in memory */
	int vp_status;
} cvmh_model_t;

// Constants
/** The version of the model. */
extern const char *cvmh_version_string;

/** The config of the model. */
extern char *cvmh_config_string;
extern int cvmh_config_sz;

// Variables
/** Set to 1 when the model is ready for query. */
extern int cvmh_is_initialized;

/** Location of the binary data files. */
extern char cvmh_data_directory[2000];

/** Configuration parameters. */
extern cvmh_configuration_t *cvmh_configuration;
/** Holds pointers to the velocity model data OR indicates it can be read from file. */
extern cvmh_model_t *cvmh_velocity_model;

/** The height of this model's region, in meters. */
extern double cvmh_total_height_m;
/** The width of this model's region, in meters. */
extern double cvmh_total_width_m;

// UCVM API Required Functions

#ifdef DYNAMIC_LIBRARY

/** Initializes the model */
int model_init(const char *dir, const char *label);
/** Cleans up the model (frees memory, etc.) */
int model_finalize();
/** Returns version information */
int model_version(char *ver, int len);
/** Returns config information */
int model_config(char **config, int *sz);
/** Queries the model */
int model_query(cvmh_point_t *points, cvmh_properties_t *data, int numpts);
/** Setparam */
int model_setparam(int, int, int);

#endif

// CVMH Related Functions

/** Initializes the model */
int cvmh_init(const char *dir, const char *label);
/** Cleans up the model (frees memory, etc.) */
int cvmh_finalize();
/** Returns version information */
int cvmh_version(char *ver, int len);
/** Queries the model */
int cvmh_query(cvmh_point_t *points, cvmh_properties_t *data, int numpts);
/** Setparam*/
int cvmh_setparam(int, int, ...);

// Non-UCVM Helper Functions
/** Reads the configuration file. */
int cvmh_read_configuration(char *file, cvmh_configuration_t *config);
void cvmh_print_error(char *err);
int cvmh_setzmode(char* z);

#endif
