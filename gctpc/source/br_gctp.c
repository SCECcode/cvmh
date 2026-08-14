
#ifdef unix
/*  Fortran bridge routine for the UNIX */

void gctp(
double *incoor,		/* input coordinates				*/
long *insys,		/* input projection code			*/
long *inzone,		/* input zone number				*/
double *inparm,		/* input projection parameter array		*/
long *inunit,		/* input units					*/
long *indatum,		/* input datum 					*/
long *ipr,		/* printout flag for error messages. 0=screen, 1=file, 2=both*/
char *efile,		/* error file name				*/
long *jpr,		/* printout flag for projection parameters 0=screen, 1=file, 2 = both*/
char *pfile,		/* error file name				*/
double *outcoor,	/* output coordinates				*/
long *outsys,		/* output projection code			*/
long *outzone,		/* output zone					*/
double *outparm,	/* output projection array			*/
long *outunit,		/* output units					*/
long *outdatum,		/* output datum					*/
char fn27[],		/* file name of NAD 1927 parameter file		*/
char fn83[], 	 	/* file name of NAD 1983 parameter file		*/
long *iflg		/* error flag					*/
);

void gctp_(incoor,insys,inzone,inparm,inunit,indatum,ipr,efile,jpr,pfile,
               outcoor, outsys,outzone,outparm,outunit,fn27,fn83,iflg)

double *incoor;
long *insys;
long *inzone;
double *inparm;
long *inunit;
long *indatum;
long *ipr;        /* printout flag for error messages. 0=yes, 1=no*/
char *efile;
long *jpr;        /* printout flag for projection parameters 0=yes, 1=no*/
char *pfile;
double *outcoor;
long *outsys;
long *outzone;
double *outparm;
long *outunit;
char *fn27;
char *fn83;
long *iflg;

{
long outdatum = 0;

gctp(incoor,insys,inzone,inparm,inunit,indatum,ipr,efile,jpr,pfile,outcoor,
     outsys,outzone,outparm,outunit,&outdatum,fn27,fn83,iflg);

return;
}
#endif
