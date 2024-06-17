/*
 * Setup camera's image format,this include color and bits setting,this setting is necessary.
 * The RAW8 is 8 bits MONO mode,the RAW16 is 16 bits MONO mode,the RGB24 is 8 bits COLOR mode.
 * Normally single mode can only support RAW16 mode,live mode can support all three modes.
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
	plhs[0] = mxCreateNumericMatrix(1, 1, mxINT32_CLASS, mxREAL);
	int *retVal = (int *)mxGetData(plhs[0]);
	char *id = (char *)mxGetData(prhs[0]);

	qhyccd_handle *camhandle = OpenQHYCCD(id);
	if(camhandle == NULL)
	{
		printf("Open QHYCCD failed.\n");
		*retVal = -1;
		return;
	}
	
    int ret = QHYCCD_ERROR;
	char *format = mxArrayToString(prhs[1]);
	printf("format = %s\n", format);
	
	if(strstr(format, "RAW8") != NULL)
	{
		printf("Setup to RAW8\n");
		
		ret = SetQHYCCDDebayerOnOff(camhandle, false);
		if(ret == QHYCCD_ERROR)
		{
			printf("Setup debayer failed.\n");
			*retVal = -1;
			return;
		}
		ret = SetQHYCCDParam(camhandle, CONTROL_TRANSFERBIT, 8);
		if(ret == QHYCCD_ERROR)
		{
			printf("Setup bits failed.\n");
			*retVal = -1;
			return;
		}
	}
	else if(strstr(format, "RAW16") != NULL)
	{
		printf("Setup to RAW16\n");
		
		ret = SetQHYCCDDebayerOnOff(camhandle, false);
		if(ret == QHYCCD_ERROR)
		{
			printf("Setup debayer failed.\n");
			*retVal = -1;
			return;
		}
		ret = SetQHYCCDParam(camhandle, CONTROL_TRANSFERBIT, 16);
		if(ret == QHYCCD_ERROR)
		{
			printf("Setup bits failed.\n");
			*retVal = -1;
			return;
		}
	}
	else if(strstr(format, "RGB24") != NULL)
	{
		printf("Setup to RGB24\n");
		ret = IsQHYCCDControlAvailable(camhandle, CAM_IS_COLOR);
		if(ret == QHYCCD_SUCCESS)
		{
			ret = SetQHYCCDDebayerOnOff(camhandle, true);
			if(ret == QHYCCD_ERROR)
			{
				printf("Setup debayer failed.\n");
				*retVal = -1;
				return;
			}
		}
		else
		{
			printf("This camera don't support color mode.\n");
			ret = SetQHYCCDDebayerOnOff(camhandle, false);
			if(ret == QHYCCD_ERROR)
			{
				printf("Setup debayer failed.\n");
				*retVal = -1;
				return;
			}
		}
		ret = SetQHYCCDParam(camhandle, CONTROL_TRANSFERBIT, 8);
		if(ret == QHYCCD_ERROR)
		{
			printf("Setup bits failed.\n");
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
	
	printf("Setup format successfully.\n");
	*retVal = 0;
}
