/*
 * Setup camera's DDR on or off,you need input argument value,1 is on,0 is off.
 * If setup successfully,it will return 0;
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
	printf("DDR value = %f\n", *value);
	
	ret = SetQHYCCDParam(camhandle, CONTROL_DDR, *value);
	if(ret == QHYCCD_SUCCESS)
	{
		printf("Set camera DDR successfully.\n");
		*retVal = 0;
	}
	else
	{
		printf("Set camera DDR failed.\n");
		*retVal = -1;
	}
}
