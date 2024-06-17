/*
 * Check if CFW is connected to camera's 4PIN port,if connected,program will return 0;
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
	
	ret = IsQHYCCDCFWPlugged(camhandle);
	if(ret == QHYCCD_ERROR)
	{
		printf("No CFW is connected to camera.\n");
		*retVal = -1;
	}
	else
	{
		printf("CFW is connected to camera.\n");
		*retVal = 0;
	}
}
