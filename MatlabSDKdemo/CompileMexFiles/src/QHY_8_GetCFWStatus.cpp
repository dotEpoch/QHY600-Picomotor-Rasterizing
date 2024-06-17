/*
 * Get CFW's current position,you can use this to check if CFW is arrived to target position. 
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
	ret = IsQHYCCDControlAvailable(camhandle, CONTROL_CFWPORT);
	if(ret == QHYCCD_ERROR)
	{
		printf("Camera don't support CFW control function.\n");
		*retVal = -1;
		return;
	}
	
	plhs[1] = mxCreateNumericMatrix(1, 1, mxUINT8_CLASS, mxREAL);
	char *status = (char *)mxGetData(plhs[1]);
	
	ret = GetQHYCCDParam(camhandle, CONTROL_CFWPORT);
	if(ret == QHYCCD_ERROR)
	{
		printf("Get CFW status failed.\n");
		*retVal = -1;
	}
	else
	{
		printf("Get CFW status successfully.\n");
		*retVal = 0;
	}
}
