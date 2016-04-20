#include "ourf.c"
#include "../../hdpmix/hdp.c"

#define HDPIN prhs[0]
#define NUMITER prhs[1]
#define DOCONPARAM prhs[2]
#define DOLIK prhs[3]
#define DODEBUG prhs[4]
#define HDPOUT plhs[0]
#define LIK plhs[1]

void mexFunction( int nlhs, mxArray *plhs[], 
                          int nrhs, const mxArray*prhs[] )
     
{
  int ii, jj, cc, ss;
  unsigned char bEvo;
  mxArray *tmparray, *tmpcell;
  double *tmpdouble;
  HDP *hdp;

  if (nrhs < 4 || nrhs > 6) mexErrMsgTxt("Incorrect number of input arguments.");
  if (!mxIsStruct(HDPIN)) mexErrMsgTxt("HDP structure expected.");
  if (mxGetNumberOfElements(HDPIN)!=1) mexErrMsgTxt("One structure expected.");

  if (nrhs < 6)
	  bEvo = 0;
  else bEvo = *mxGetPr(prhs[5]);

#ifndef NODEBUG
  DEBUG = nrhs==4 ? 0 : *mxGetPr(DODEBUG);
#endif
  srand(0);
  hdp = mxReadHDP(HDPIN, bEvo);

  LIK = mxCreateDoubleMatrix(1, *mxGetPr(NUMITER), mxREAL);

  mxdebug0(1,"Running hdpMultinomial_iterate.\n");
  hdp_iterate(hdp, mxGetPr(LIK), 
	  *mxGetPr(NUMITER), *mxGetPr(DOCONPARAM), *mxGetPr(DOLIK), bEvo);
  mxdebug0(1,"Done hdpMultinomial_iterate.\n");

  HDPOUT = mxDuplicateArray(HDPIN);
  mxWriteHDP(HDPOUT,hdp);
}


