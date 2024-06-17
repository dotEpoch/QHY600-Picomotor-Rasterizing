/*
 * Setup camera cooler's target temperature,after you setup temperature,cooler will work on Auto mode,
 * it will auto adjust PWM to maintain at target temperature.
 * You need input the target temperature,and its setup range is -50 ~ 50,step is 0.5,and its real cooling range
 * is lower thanenvironment temperature 35 degree,if you control camera capture short expose time image,camera
 * will generate more heat,its cooling rang will become lower than environment temperature 30 degree.
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
	
	ret = SetQHYCCDParam(camhandle, CONTROL_COOLER, *value);
	if(ret == QHYCCD_SUCCESS)
	{
		printf("Set target temperature successfully.\n");
		*retVal = 0;
	}
	else
	{
		printf("Set target temperature failed.\n");
		*retVal = -1;
	}
}
