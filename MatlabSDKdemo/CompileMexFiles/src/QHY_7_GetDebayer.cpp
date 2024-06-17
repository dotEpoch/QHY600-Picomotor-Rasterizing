/*
 * Get image debayer format for color camera.
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
	ret = IsQHYCCDControlAvailable(camhandle, CAM_IS_COLOR);
	if(ret == QHYCCD_ERROR)
	{
		printf("Camera don't support color function.\n");
		*retVal = -1;
		return;
	}
	
	plhs[1] = mxCreateNumericMatrix(4, 1, mxUINT8_CLASS, mxREAL);
	char *format = (char *)mxGetData(plhs[1]);
	
	ret = IsQHYCCDControlAvailable(camhandle, CAM_COLOR);
	if(ret != QHYCCD_ERROR)
	{		
		if(ret == 1)
		{
			strcat(format, "GBRG");
		}
		else if(ret == 2)
		{
			strcat(format, "GRBG");
		}
		else if(ret == 3)
		{
			strcat(format, "BGGR");
		}
		else if(ret == 4)
		{
			strcat(format, "RGGB");
		}
		else
		{
			printf("Debayer format error.\n");
			*retVal = -1;
			return;
		}
		
		printf("Get debayer format successfully.%s\n", format);
		*retVal = 0;
	}
	else
	{
		printf("Get debayer format failed.\n");
		*retVal = -1;
	}
}
