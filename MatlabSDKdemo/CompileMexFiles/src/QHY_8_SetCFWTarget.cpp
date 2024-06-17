/*
 * Set CFW's target position,you need input target position,char '0' is target position 1,and char '1' is target position 2...
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
	
	char *pos = (char *)mxGetData(prhs[1]);
	ret = SetQHYCCDParam(camhandle, CONTROL_CFWPORT, (int)(*pos));
	if(ret == QHYCCD_ERROR)
	{
		printf("Set CFW target position failed.\n");
		*retVal = -1;
	}
	else
	{
		printf("Set CFW target position successfully.\n");
		*retVal = 0;
	}
}
