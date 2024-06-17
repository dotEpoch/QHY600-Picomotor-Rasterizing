/*
 * Get image overscan area,program will return start posiion and size.
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
	plhs[1] = mxCreateNumericMatrix(1, 1, mxUINT32_CLASS, mxREAL);
	uint32_t *x = (uint32_t *)mxGetData(plhs[1]);
	plhs[2] = mxCreateNumericMatrix(1, 1, mxUINT32_CLASS, mxREAL);
	uint32_t *y = (uint32_t *)mxGetData(plhs[2]);
	plhs[3] = mxCreateNumericMatrix(1, 1, mxUINT32_CLASS, mxREAL);
	uint32_t *sizex = (uint32_t *)mxGetData(plhs[3]);
	plhs[4] = mxCreateNumericMatrix(1, 1, mxUINT32_CLASS, mxREAL);
	uint32_t *sizey = (uint32_t *)mxGetData(plhs[4]);
		
	ret = GetQHYCCDOverScanArea(camhandle, x, y, sizex, sizey);
	if(ret == QHYCCD_ERROR)
	{
		printf("Get camera overscan area failed.\n");
		*retVal = -1;
	}
	else
	{
		printf("Get camera overscan area successfully.\n");
		*retVal = 0;
	}
}
