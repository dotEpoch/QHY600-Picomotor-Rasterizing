/*
 * Setup camera's gamma,its range is 0 ~ 2,sep is 0.1,if don't setup,default value is 1.0.
 * If setup successfully,it will 0.
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
	double *value = (double *)mxGetData(prhs[1]);
	
	ret = SetQHYCCDParam(camhandle, CONTROL_GAMMA, *value);
	if(ret == QHYCCD_SUCCESS)
	{
		printf("Set camera gamma successfully.\n");
		*retVal = 0;
	}
	else
	{
		printf("Set camera gamma failed.\n");
		*retVal = -1;
	}
}
