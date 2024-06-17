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
	qhyccd_handle *camhandle = NULL;

	plhs[0] = mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
	int *retVal  = (int *)mxGetData(plhs[0]);
	plhs[1] = mxCreateNumericMatrix(500, 1, mxINT8_CLASS, mxREAL);
	char *readModeName   = (char *)mxGetData(plhs[1]);
	plhs[2] = mxCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
	int *readModeNum   = (int *)mxGetData(plhs[1]);
	char *id = (char *)mxGetData(prhs[0]);
	
	printf("id = %s\n", id);
	
	camhandle = OpenQHYCCD(id);
	if(camhandle == NULL)
	{
		printf("Open QHYCCD failed.\n");
		*retVal = -1;
		return;
	}

	int ret = QHYCCD_ERROR;
	ret = GetQHYCCDNumberOfReadModes(camhandle, (uint32_t *)readModeNum);
	if(ret == QHYCCD_ERROR)
	{
		printf("Get read mode number failed.\n");
		*retVal = -1;
		return;
	}
	
	char name[40] = {0};
	char index[2] = {0};
	for(int i = 0; i < *readModeNum; i ++)
	{
		ret = GetQHYCCDReadModeName(camhandle, i, name);
		if(ret == QHYCCD_SUCCESS)
		{
			itoa(i, index, 10);
			strcat(readModeName, "ReadMode ");
			strcat(readModeName, index);
			strcat(readModeName, ":");
			strcat(readModeName, name);
			if(i < *readModeNum - 1)
				strcat(readModeName, " | ");
		}
	}
	
	printf("ReadMode : %s\n", readModeName);
}
