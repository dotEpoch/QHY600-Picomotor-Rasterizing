/*
 * Stop capture single frame,you can call it when is capturing image to cancel or call it after get single frame.
 * I successfully,program will return 0.
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
	ret = CancelQHYCCDExposingAndReadout(camhandle);
	if(ret == QHYCCD_ERROR)
	{
		printf("Stop single mode failed.\n");
		*retVal = -1;
	}
	else
	{
		printf("Stop single mode successfully.\n");
		*retVal = 0;
	}
}
