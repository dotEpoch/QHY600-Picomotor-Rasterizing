/*
 * Get one single frame,when call this program,matlab will wait for it until it capture successfully.
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
	plhs[1] = mxCreateNumericMatrix(1, 1, mxUINT32_CLASS, mxREAL);
	uint32_t *w = (uint32_t *)mxGetData(plhs[1]);
	plhs[2] = mxCreateNumericMatrix(1, 1, mxUINT32_CLASS, mxREAL);
	uint32_t *h = (uint32_t *)mxGetData(plhs[2]);
	plhs[3] = mxCreateNumericMatrix(1, 1, mxUINT32_CLASS, mxREAL);
	uint32_t *bpp = (uint32_t *)mxGetData(plhs[3]);
	plhs[4] = mxCreateNumericMatrix(1, 1, mxUINT32_CLASS, mxREAL);
	uint32_t *channels = (uint32_t *)mxGetData(plhs[4]);
	
	uint32_t imgW, imgH, imgBpp, imgChannels;
	unsigned char *ImgData;
	unsigned char *convertData;
	
	int length = GetQHYCCDMemLength(camhandle);
	if(length > 0)
	{
		ImgData = (unsigned char *)malloc(length);
		memset(ImgData, 0, length);
		convertData = (unsigned char *)malloc(length);
		memset(convertData, 0, length);
	}
	else
	{
		printf("Get memory length failed.\n");
		*retVal = -1;
		return;
	}
	
	ret = GetQHYCCDSingleFrame(camhandle, w, h, bpp, channels, ImgData);
	if(ret == QHYCCD_ERROR)
	{
		printf("Get single frame failed.\n");
		*retVal = -1;
		*w = 0;
		*h = 0;
		*bpp = 0;
		*channels = 0;
		plhs[5] = mxCreateNumericMatrix(1,1,mxUINT8_CLASS,mxREAL);
		uint8_t *pImage = (uint8_t *)mxGetData(plhs[5]);
		memcpy(pImage, ImgData, 1);
		return;
	}
	else
	{
		*retVal = 0;
		
		if(16 == *bpp && 1 == *channels)
		{
			printf("Get single frame successfully.\n");
			
			int x, y;
			for(int j = 0; j < *h; j++)
			{
				for(int i = 0; i < *w; i++)
				{
					x = j * *w + i;
					y = i * *h + j;
					convertData[2*y]   = ImgData[2*x];
					convertData[2*y+1] = ImgData[2*x+1];
				}
			}
			
			plhs[5] = mxCreateNumericMatrix(*h,*w,mxUINT16_CLASS,mxREAL);
			uint16_t *pImage = (uint16_t *)mxGetData(plhs[5]);
			memcpy(pImage, convertData, (*w)*(*h)*2);
		}
		else
		{
			printf("Get single image error.\n");

			plhs[5] = mxCreateNumericMatrix(1,1,mxUINT8_CLASS,mxREAL);
			uint16_t *pImage = (uint16_t *)mxGetData(plhs[5]);
			memcpy(pImage, ImgData, 1); 
			*retVal = -1;
		}
		
		free(ImgData);
		free(convertData);
	}
}
