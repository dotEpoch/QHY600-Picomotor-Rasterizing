/*
 * Set camera's read mode,QHY268 have four read modes,their names and index values are:
 * 0 : PhotoGraphic DSO
 * 1 : High Gain Mode
 * 2 : Extend Fullwell
 * 3 : Extend Fullwell 2CMS
 * You need input index value to choose which read mode you want to setup,
 * and program will return result value,if success,the return value is 0.
 * If you don't setup this,the default is PhotoGraphic DSO mode.
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

	plhs[0] = mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
	retVal  = (int *)mxGetData(plhs[0]);
	id      = (char *)mxGetData(prhs[0]);
	
	printf("id = %s\n", id);
	
	camhandle = OpenQHYCCD(id);
	if(camhandle == NULL)
	{
		printf("Open QHYCCD failed.\n");
		*retVal = -1;
		return;
	}

	int ret = QHYCCD_ERROR;
	double *readMode = (double *)mxGetData(prhs[1]);
	
	printf("readMode = %f\n", *readMode);
	
	ret = SetQHYCCDReadMode(camhandle, (int)(*readMode));
	if(ret == QHYCCD_SUCCESS)
	{
		*retVal = 0;
		printf("Setup read mode successfully.\n");
	}
	else
	{
		*retVal = -1;
		printf("Setup read mode failed.\n");
	}
}
