/*
 * Setup camera's expose time,you need input expose time,its unit is us,for example,
 * if you want set up 1s expose time,the setting value is 1*1000*1000.
 * If setup successfully,it will return 0.
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
	
	ret = SetQHYCCDParam(camhandle, CONTROL_EXPOSURE, *value);
	if(ret == QHYCCD_SUCCESS)
	{
		printf("Set camera expose time successfully.\n");
		*retVal = 0;
	}
	else
	{
		printf("Set camera expose time failed.\n");
		*retVal = -1;
	}
}
