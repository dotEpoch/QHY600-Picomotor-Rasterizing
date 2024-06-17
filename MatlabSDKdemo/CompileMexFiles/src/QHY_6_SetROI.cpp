/*
 * Set ROI for camera,when setup,you need make sure the value of start position add ROI size is shorter than original image size.
 * You need input start position and ROI size.If setup successfully,program will return 0.
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
	uint32_t imagew, imageh, bpp;
	double chipw, chiph, pixelw, pixelh;
/*	
	ret = GetQHYCCDChipInfo(camhandle, &chipw, &chiph, &imagew, &imageh, &pixelw, &pixelh, &bpp);
	if(ret == QHYCCD_ERROR)
	{
		printf("Get camera chip info failed.\n");
		*retVal = -1;
		return;
	}
*/
	double *x = (double *)mxGetData(prhs[1]);
	double *y = (double *)mxGetData(prhs[2]);
	double *sizex = (double *)mxGetData(prhs[3]);
	double *sizey = (double *)mxGetData(prhs[4]);
	
	printf("x = %f y = %f sizex = %f sizey = %f\n", *x, *y, *sizex, *sizey);
/*	
	if((int)*x + (int)*sizex > imagew || (int)*y + (int)*sizey > imageh)
	{
		printf("ROI parameters error.\n");
		*retVal = -1;
		return;
	}
*/
	ret = SetQHYCCDResolution(camhandle, (int)(*x), (int)(*y), (int)(*sizex), (int)(*sizey));
	if(ret == QHYCCD_SUCCESS)
	{
		printf("Set camera ROI successfully***********.\n");
		*retVal = 0;
	}
	else
	{
		printf("Set camera ROI failed.\n");
		*retVal = -1;
	}
}
