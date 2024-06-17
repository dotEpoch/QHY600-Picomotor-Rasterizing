/*
 * Init camera's parameters setting,if run successfully,program will return 0.
 * This step is necessary.
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
	
	ret = InitQHYCCD(camhandle);
	if(ret == QHYCCD_SUCCESS)
	{
		*retVal = 0;
		printf("Init camera's parameters successfully.\n");
	}
	else
	{
		*retVal = -1;
		printf("Init camera's parameters failed.\n");
	}
}
