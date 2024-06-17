/*
 * Get camera's humidity value,not all QHY268C support this function.
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
	ret = IsQHYCCDControlAvailable(camhandle, CAM_HUMIDITY);
	if(ret == QHYCCD_ERROR)
	{
		printf("Camera don't support humidity function.\n");
		*retVal = -1;
		return;
	}
	
	plhs[1] = mxCreateNumericMatrix(1, 1, mxDOUBLE_CLASS, mxREAL);
	double *value = (double *)mxGetData(plhs[1]);

	*value = GetQHYCCDParam(camhandle, CAM_HUMIDITY);
	printf("Current Humidity : %f\n", *value);
	*retVal = 0;
}
