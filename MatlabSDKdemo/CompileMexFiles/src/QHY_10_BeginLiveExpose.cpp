/*
 * Start live mode expose,if run successfully,camera will produce image data continuously.
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
	ret = BeginQHYCCDLive(camhandle);
	if(ret == QHYCCD_ERROR)
	{
		printf("Begin live expose failed.\n");
		*retVal = -1;
	}
	else
	{
		printf("Begin live expose successfully.\n");
		*retVal = 0;
	}
}
