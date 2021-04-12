#include <math.h>
#include <stdlib.h>

#define PI 	3.141592653589793238
#define HALF_PI (PI*0.5)
#define TWO_PI 	(PI*2.0)
#define EPSLN	1.0e-10
#define R2D     57.2957795131
/*
#define D2R     0.0174532925199
*/
#define D2R     1.745329251994328e-2
#define S2R	4.848136811095359e-6

#define OK	0
#define ERROR  -1
#define IN_BREAK -2

/* Misc macros
  -----------*/
#define SQUARE(x)       x * x   /* x**2 */
#define CUBE(x)     x * x * x   /* x**3 */
#define QUAD(x) x * x * x * x   /* x**4 */

#define GMAX(A, B)      ((A) > (B) ? (A) : (B)) /* assign2 maximum of a and b */
#define GMIN(A, B)      ((A) < (B) ? (A) : (B)) /* assign2 minimum of a and b */

#define IMOD(A, B)      (A) - (((A) / (B)) * (B)) /* Integer mod function */


/* forward delcaration */
/* cproj.c */
double sign2(double x);

/* report.c */
long init(long ipr,long jpr,char *efile,char *pfile);
void p_error(char *what, char *where);
void close_file();
void ptitle(char *A);
void radius(double A);
void radius2(double A, double B);
void cenlon(double A);
void cenlonmer(double A);
void cenlat(double A);
void origin(double A);
void stanparl(double A,double B);
void stparl1(double A);
void offsetp(double A,double B);
void genrpt(double A,char *S);
void genrpt_long(long A,char *S);
void pblank();

/* untfz.c */
long untfz(long inunit,long outunit,double *factor);

/* sphdz.c */
long sphdz(long isph,double *parm,double *r_major,double *r_minor,double *radius);

/* inv_init.c */
void inv_init(long insys,long inzone,double *inparm,long indatum,char *fn27,char *fn83,long *iflg,long (*inv_trans[])());

/* for_init.c */
void for_init(long outsys,long outzone,double *outparm,long outdatum,char *fn27,char *fn83,long *iflg,long (*for_trans[])());

/* cproj.c */
void sincos(double val,double *sin_val,double *cos_val);
double asinz(double con);
double msfnz(double eccent,double sinphi,double cosphi);
double qsfnz(double eccent,double sinphi,double cosphi);
double phi1z(double eccent,double qs,long *flag);
double phi2z(double eccent,double ts,long *flag);
double phi3z(double ml,double e0,double e1,double e2,double e3,long *flag);
double phi4z(double eccent,double e0,double e1,double e2,double e3,double a,double b,double *c,double *phi);
double pakcz(double pak);
double pakr2dm(double pak);
double tsfnz(double eccent,double phi,double sinphi);
double adjust_lon(double x);
double e0fn(double x);
double e1fn(double x);
double e2fn(double x);
double e3fn(double x);
double e4fn(double x);
double mlfn(double e0,double e1,double e2,double e3,double phi);
long calc_utm_zone(double lon);

/* alberfor.c */
long alberforint(double r_maj,double r_min,double lat1,double lat2,double lon0,double lat0,double false_east,double false_north);
long alberfor(double lon,double lat,double *x,double *y);
/* alberinv.c */
long alberinvint(double r_maj,double r_min,double lat1,double lat2,double lon0,double lat0,double false_east,double false_north);
long alberinv(double x,double y,double *lon,double *lat);

/* alconfor.c */
long alconforint(double r_maj,double r_min,double false_east,double false_north);
long alconfor(double lon,double lat,double *x,double *y);
/* alconinv.c */
long alconinvint(double r_maj,double r_min,double false_east,double false_north);
long alconinv(double x,double y,double *lon,double *lat);

/* azimfor.c */
long azimforint(double r_maj,double center_lon,double center_lat,double false_east,double false_north);
long azimfor(double lon,double  lat,double *x,double *y); 
/* aziminv.c */
long aziminvint(double r_maj,double center_lon,double center_lat,double false_east,double false_north);
long aziminv(double x,double y,double *lon,double *lat);

/* eqconfor.c */
long eqconforint(double r_maj,double r_min,double lat1,double lat2,double center_lon,double center_lat,double false_east,double false_north,long mode);
long eqconfor(double lon,double lat,double *x,double *y);
/* eqconinv.c */
long eqconinvint(double r_maj,double r_min,double lat1,double lat2,double center_lon,double center_lat,double false_east,double false_north,long mode);
long eqconinv(double x,double y,double *lon,double *lat);

/* equifor.c */
long equiforint(double r_maj,double center_lon,double lat1,double false_east,double false_north); 
long equifor(double lon,double lat,double *x,double *y);
/* equiinv.c */
long equiinvint(double r_maj,double center_lon,double lat1,double false_east,double false_north); 
long equiinv(double x,double y,double *lon,double *lat);

/* gnomfor.c */
long gnomforint(double r,double center_long,double center_lat,double false_east,double false_north);
long gnomfor(double lon,double lat,double *x,double *y);
/* gnominv.c */
long gnominvint(double r,double center_long,double center_lat,double false_east,double false_north);
long gnominv(double x,double y,double *lon,double *lat);

/* goodfor.c */
long goodforint(double r);
long goodfor(double lon,double lat,double *x,double *y);
/* goodinv.c */
long goodinvint(double r);
long goodinv(double x,double y,double *lon,double *lat);

/* gvnspfor.c */
long gvnspforint(double r,double h,double center_long,double center_lat,double false_east,double false_north);
long gvnspfor(double lon,double lat,double *x,double *y);
/* gvnspinv.c */
long gvnspinvint(double r,double h,double center_long,double center_lat,double false_east,double false_north);
long gvnspinv(double x,double y,double *lon,double *lat);

/* hamfor.c */
long hamforint(double r,double center_long,double false_east,double false_north);
long hamfor(double lon,double lat,double *x,double *y);
/* haminv.c */
long haminvint(double r,double center_long,double false_east,double false_north);
long haminv(double x,double y,double *lon,double *lat);

/* imolwfor.c */
long imolwforint(double r);
long imolwfor(double lon,double lat,double *x,double *y);
/* imolwinv.c */
long imolwinvint(double r);
long imolwinv(double x,double y,double *lon,double *lat);

/* for_init.c  */
void for_init(long outsys,long outzone,double *outparm,long outdatum,char *fn27,char *fn83,long *iflg,long (*for_trans[])());
/* inv_init.c */
void inv_init(long insys,long inzone,double *inparm,long indatum,char *fn27,char *fn83,long *iflg,long (*inv_trans[])());

/* lamazfor.c */
long lamazforint(double r,double center_long,double center_lat,double false_east,double false_north); 
long lamazfor(double lon,double lat,double *x,double *y);
/* lamazinv.c */
long lamazinvint(double r,double center_long,double center_lat,double false_east,double false_north);
long lamazinv(double x,double  y,double *lon,double *lat);

/* lamccfor.c */
long lamccforint(double r_maj,double r_min,double lat1,double lat2,double c_lon,double c_lat,double false_east,double false_north);
long lamccfor(double lon,double lat,double *x,double *y);
/* lamccinv.c */
long lamccinvint(double r_maj,double r_min,double lat1,double lat2,double c_lon,double c_lat,double false_east,double false_north);
long lamccinv(double x,double y,double *lon,double *lat);

/* merfor.c */
long merforint(double r_maj,double r_min,double center_lon,double center_lat,double false_east,double false_north); 
long merfor(double lon,double lat,double *x,double *y);
/* merinv.c */
long merinvint(double r_maj,double r_min,double center_lon,double center_lat,double false_east,double false_north); 
long merinv(double x,double y,double *lon,double *lat);

/* millfor.c */
long millforint(double r,double center_long,double false_east,double false_north); 
long millfor(double lon,double lat,double *x,double *y);
/* millinv.c */
long millinvint(double r,double center_long,double false_east,double false_north);
long millinv(double x,double y,double *lon,double *lat);

/* molwfor.c */
long molwforint(double r,double center_long,double false_east,double false_north);
long molwfor(double lon,double lat,double *x,double *y);
/* molwinv.c */
long molwinvint(double r,double center_long,double false_east,double false_north); 
long molwinv(double x,double y,double *lon,double *lat);

/* obleqfor.c */
long obleqforint(double r,double center_long,double center_lat,double shape_m,double shape_n,double angle,double false_east,double false_north);
long obleqfor(double lon,double lat,double *x,double *y);
/* obleqinv.c */
long obleqinvint(double r,double center_long,double center_lat,double shape_m,double shape_n,double angle,double false_east,double false_north);
long obleqinv(double x,double y,double *lon,double *lat);

/* omerfor.c */
long omerforint(double r_maj,double r_min,double scale_fact,double azimuth,double lon_orig,double lat_orig,double false_east, double false_north,double lon1,double lat1,double lon2,double lat2,long mode);
long omerfor(double lon,double lat,double *x,double *y);
/* omerinv.c */
long omerinvint(double r_maj,double r_min,double scale_fact,double azimuth,double lon_orig,double lat_orig,double false_east,double false_north,double lon1,double lat1,double lon2,double lat2,long mode);
long omerinv(double x,double y,double *lon,double *lat);

/* orthfor.c */
long orthforint(double r_maj,double center_lon,double center_lat,double false_east,double false_north); 
long orthfor(double lon,double lat,double *x,double *y);
/* orthinv.c */
long orthinvint(double r_maj,double center_lon,double center_lat,double false_east,double false_north); 
long orthinv(double x,double y,double *lon,double *lat);

/* polyfor.c */
long polyforint(double r_maj,double r_min,double center_lon,double center_lat,double false_east,double false_north); 
long polyfor(double lon,double lat,double *x,double *y);
/* polyinv.c */
long polyinvint(double r_maj,double r_min,double center_lon,double center_lat,double false_east,double false_north); 
long polyinv(double x,double y,double *lon,double *lat);

/* psfor.c */
long psforint(double r_maj,double r_min,double c_lon,double c_lat,double false_east,double false_north); 
long psfor(double lon,double lat,double *x,double *y);
/* psinv.c */
long psinvint(double r_maj,double r_min,double c_lon,double c_lat,double false_east,double false_north);
long psinv(double x,double y,double *lon,double *lat);

/* robfor.c */
long robforint(double r,double center_long,double false_east,double false_north); 
long robfor(double lon,double lat,double *x,double *y);
/* robinv.c */
long robinvint(double r,double center_long,double false_east,double false_north); 
long robinv(double x,double y,double *lon,double *lat);

/* sinfor.c */
long sinforint(double r,double center_long,double false_east,double false_north);
long sinfor(double lon,double lat,double *x,double *y);
/* sininv.c */
long sininvint(double r,double center_long,double false_east,double false_north);
long sininv(double x,double y,double *lon,double *lat);

/* somfor.c */
long somforint(double r_major,double r_minor,long satnum,long path,double alf_in,double lon,double false_east,double false_north,double time,long start1,long flag);
long somfor(double lon,double lat,double *y,double *x);
/* sominv.c */
long sominvint(double r_major,double r_minor,long satnum,long path,double alf_in,double lon,double false_east,double false_north,double time,long start1,long flag);
long sominv(double y,double x,double *lon,double *lat);

/* sterfor.c */
long sterforint(double r_maj,double center_lon,double center_lat,double false_east,double false_north);
long sterfor(double lon,double lat,double *x,double *y);
/* sterinv.c */
long sterinvint(double r_maj,double center_lon,double center_lat,double false_east,double false_north);
long sterinv(double x,double y,double *lon,double *lat);

/* stplnfor.c */
long stplnforint(long zone,long sphere,char *fn27,char *fn83);
long stplnfor(double lon,double lat,double *x,double *y);
/* stplninv.c */
long stplninvint(long zone,long sphere,char *fn27,char *fn83);
long stplninv(double x,double y,double *lon,double *lat);

/* tmfor.c */
long tmforint(double r_maj,double r_min,double scale_fact,double center_lon,double center_lat,double false_east,double false_north);
long tmfor(double lon,double lat,double *x,double *y);
/* tminv.c */
long tminvint(double r_maj,double r_min,double scale_fact,double center_lon,double center_lat,double false_east,double false_north);
long tminv(double x,double y,double *lon,double *lat);

/* utmfor.c */
long utmforint(double r_maj,double r_min,double scale_fact,long zone);
long utmfor(double lon,double lat,double *x,double *y);
/* utminv.c */
long utminvint(double r_maj,double r_min,double scale_fact,long zone);
long utminv(double x,double y,double *lon,double *lat);

/* vandgfor.c */
long vandgforint(double r,double center_long,double false_east,double false_north); 
long vandgfor(double lon,double lat,double *x,double *y);
/* vandginv.c */
long vandginvint(double r,double center_long,double false_east,double false_north);
long vandginv(double x,double y,double *lon,double *lat);

/* wivfor.c */
long wivforint(double r,double center_long,double false_east,double false_north); 
long wivfor(double lon,double lat,double *x,double *y);
/* wivinv.c */
long wivinvint(double r,double center_long,double false_east,double false_north); 
long wivinv(double x,double y,double *lon,double *lat);

/* wviifor.c  */
long wviiforint(double r,double center_long,double false_east,double false_north); 
long wviifor(double lon,double lat,double *x,double *y);
/* wviiinv.c */
long wviiinvint(double r,double center_long,double false_east,double false_north);
long wviiinv(double x,double y,double *lon,double *lat);
