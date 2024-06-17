/*
 * Set camera cooler off,you don't need input other parameters except camID,and if setup successfully,it will return 0.
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
	
	ret = SetQHYCCDParam(camhandle, CONTROL_MANULPWM, 0.0);
	if(ret == QHYCCD_SUCCESS)
	{
		printf("Set cooler OFF successfully.\n");
		*retVal = 0;
	}
	else
	{
		printf("Set cooler OFF failed.\n");
		*retVal = -1;
	}
}
