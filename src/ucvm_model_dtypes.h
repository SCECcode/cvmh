#ifndef UCVM_MODEL_DTYPES_H
#define UCVM_MODEL_DTYPES_H

// from ucvm's src/ucvm/ucvm_dtypes.h
/* Supported error codes  */
typedef enum { UCVM_CODE_SUCCESS = 0,
               UCVM_CODE_ERROR = 1,
               UCVM_CODE_NODATA = 2,
               UCVM_CODE_DATAGAP =3 } ucvm_code_t;

/* Special source model/ifunc flags */
#define UCVM_SOURCE_NONE -1
#define UCVM_SOURCE_CRUST -2
#define UCVM_SOURCE_GTL -3

/* Supported domains for query points. Used internally by UCVM */
typedef enum { UCVM_DOMAIN_NONE = 0,
               UCVM_DOMAIN_GTL = 1,
               UCVM_DOMAIN_INTERP = 2,
               UCVM_DOMAIN_CRUST = 3} ucvm_domain_t;

typedef enum { UCVM_PARAM_QUERY_MODE = 1,
               UCVM_PARAM_IFUNC_ZRANGE = 2,
               UCVM_PARAM_MODEL_CONF = 3 } ucvm_param_t;

/* Supported coordinate query modes */
typedef enum { UCVM_COORD_GEO_DEPTH = 0,
               UCVM_COORD_GEO_ELEV = 1} ucvm_ctype_t;

/* Supported model parameters. Used internally by UCVM
UCVM_MODEL_PARAM_FORCE_DEPTH_ABOVE_SURF : Force elevation points to be
  treated as offset relative to regional model surface when it is
  above the ucvm dem surface. Removes discontinuities between model
  surface and GTL.
*/
typedef enum { UCVM_MODEL_PARAM_MODEL_CONF = 3,
	       UCVM_MODEL_PARAM_FORCE_DEPTH_ABOVE_SURF = 4 } ucvm_mparam_t;

#endif


