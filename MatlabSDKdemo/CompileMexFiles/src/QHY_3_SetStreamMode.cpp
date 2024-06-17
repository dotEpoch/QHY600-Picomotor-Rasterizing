/*
 * Set camera's stream mode,QHY268 support single and live mode,their setting value is:
 * 0 : Single Mode
 * 1 : Live Mode
 * You need input index value to choose which stream mode you want to setup,
 * and program will return result value,if success,the return value is 0.
 * This is necessary setting.
 */

#include "qhyccd.h"
#include "mex.h"
#include <time.h>
#include <string.h>
#include <windows.h>

void
mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[])
{
	int *retVal;
	char *id;
	qhyccd_handle *camhandle = NULL;
		
	plhs[0] = mxCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
	retVal = (int *)mxGetData(plhs[0]);
	id = (char *)mxGetData(prhs[0]);

	camhandle = OpenQHYCCD(id);
	if(camhandle == NULL)
	{
		printf("Open QHYCCD failed.\n");
		*retVal = -1;
		return;
	}
	
    int ret = QHYCCD_ERROR;
	double *streamMode = (double *)mxGetData(prhs[1]);
	
	printf("streamMode = %f\n", *streamMode);
	
	ret = SetQHYCCDStreamMode(camhandle, (int)(*streamMode));
	if(ret == QHYCCD_SUCCESS)
	{
		*retVal = 0;
		printf("Setup stream mode successfully.\n");
	}
	else
	{
		*retVal = -1;
		printf("Setup stream mode failed.\n");
	}
}
