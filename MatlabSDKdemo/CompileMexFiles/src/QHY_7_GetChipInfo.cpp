/*
 * Get camera's chip information,include chip size,pixel size,image size and current image bits.
 */
 
#include "qhyccd.h"
#include "mex.h"
#include <time.h>
#include <string.h>
#include <windows.h>

void
mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[])
{
    qhyccd_handle *camhandle = NULL;
		
	plhs[0] = mxCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
	int *retVal = (int *)mxGetData(plhs[0]);
	char *id = (char *)mxGetData(prhs[0]);

	camhandle = OpenQHYCCD(id);
	if(camhandle == NULL)
	{
		printf("Open QHYCCD failed.\n");
		*retVal = -1;
		return;
	}
	
    int ret = QHYCCD_ERROR;
	uint32_t bpp;
	
	plhs[1] = mxCreateNumericMatrix(1, 1, mxDOUBLE_CLASS, mxREAL);
	double *chipw = (double *)mxGetData(plhs[1]);
	plhs[2] = mxCreateNumericMatrix(1, 1, mxDOUBLE_CLASS, mxREAL);
	double *chiph = (double *)mxGetData(plhs[2]);
	plhs[3] = mxCreateNumericMatrix(1, 1, mxUINT32_CLASS, mxREAL);
	uint32_t *imagew = (uint32_t *)mxGetData(plhs[3]);
	plhs[4] = mxCreateNumericMatrix(1, 1, mxUINT32_CLASS, mxREAL);
	uint32_t *imageh = (uint32_t *)mxGetData(plhs[4]);
	plhs[5] = mxCreateNumericMatrix(1, 1, mxDOUBLE_CLASS, mxREAL);
	double *pixelw = (double *)mxGetData(plhs[5]);
	plhs[6] = mxCreateNumericMatrix(1, 1, mxDOUBLE_CLASS, mxREAL);
	double *pixelh = (double *)mxGetData(plhs[6]);
	
	ret = GetQHYCCDChipInfo(camhandle, chipw, chiph, imagew, imageh, pixelw, pixelh, &bpp);
	if(ret == QHYCCD_ERROR)
	{
		printf("Get camera chip info failed.\n");
		*retVal = -1;
	}
	else
	{
		printf("Get camera chip info successfully.\n");
		*retVal = 0;
	}
}
