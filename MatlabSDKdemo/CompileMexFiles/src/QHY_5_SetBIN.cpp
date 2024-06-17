/*
 * Setup camera's BIN mode,QHY268C support 1X1 2X2 3X3 and 4X4,this setting is necessary.
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
	uint32_t imagew, imageh, bpp;
	double chipw, chiph, pixelw, pixelh;
	
	ret = GetQHYCCDChipInfo(camhandle, &chipw, &chiph, &imagew, &imageh, &pixelw, &pixelh, &bpp);
	if(ret == QHYCCD_ERROR)
	{
		printf("Get camera chip info failed.\n");
		*retVal = -1;
		return;
	}
	
	char *bin = mxArrayToString(prhs[1]);
	printf("bin = %s\n", bin);
	if(strstr(bin, "1X1") != NULL)
	{
		ret = SetQHYCCDBinMode(camhandle, 1, 1);
		if(ret == QHYCCD_ERROR)
		{
			printf("Set bin mode failed.\n");
			*retVal = -1;
			return;
		}
		ret = SetQHYCCDResolution(camhandle, 0, 0, imagew / 1, imageh / 1);
		if(ret == QHYCCD_ERROR)
		{
			printf("Set resolution failed.\n");
			*retVal = -1;
			return;
		}
	}
	else if(strstr(bin, "2X2") != NULL)
	{
		ret = SetQHYCCDBinMode(camhandle, 2, 2);
		if(ret == QHYCCD_ERROR)
		{
			printf("Set bin mode failed.\n");
			*retVal = -1;
			return;
		}
		ret = SetQHYCCDResolution(camhandle, 0, 0, imagew / 2, imageh / 2);
		if(ret == QHYCCD_ERROR)
		{
			printf("Set resolution failed.\n");
			*retVal = -1;
			return;
		}
	}
	else if(strstr(bin, "3X3") != NULL)
	{
		ret = SetQHYCCDBinMode(camhandle, 3, 3);
		if(ret == QHYCCD_ERROR)
		{
			printf("Set bin mode failed.\n");
			*retVal = -1;
			return;
		}
		ret = SetQHYCCDResolution(camhandle, 0, 0, imagew / 3, imageh / 3);
		if(ret == QHYCCD_ERROR)
		{
			printf("Set resolution failed.\n");
			*retVal = -1;
			return;
		}
	}
	else if(strstr(bin, "4X4") != NULL)
	{
		ret = SetQHYCCDBinMode(camhandle, 4, 4);
		if(ret == QHYCCD_ERROR)
		{
			printf("Set bin mode failed.\n");
			*retVal = -1;
			return;
		}
		ret = SetQHYCCDResolution(camhandle, 0, 0, imagew / 4, imageh / 4);
		if(ret == QHYCCD_ERROR)
		{
			printf("Set resolution failed.\n");
			*retVal = -1;
			return;
		}
	}
	else
	{
		printf("Input error.\n");
		*retVal = -1;
		return;
	}
	
	printf("Setup bin successfully.\n");
	*retVal = 0;
}
