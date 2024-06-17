/*
 * Setup green balance for camera,normally this parameter can only be setup for live mode,
 * the value bigger,the image greener.QHY268's setting range is 10 - 30,step is 1.
 * If setup successfully,program will return 0.
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
	
	ret = SetQHYCCDParam(camhandle, CONTROL_WBG, *value);
	if(ret == QHYCCD_SUCCESS)
	{
		printf("Set camera green balance successfully.\n");
		*retVal = 0;
	}
	else
	{
		printf("Set camera green balance failed.\n");
		*retVal = -1;
	}
}
