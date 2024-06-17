/*
 * Get one live frame,when call this program,matlab will wait for it until capture successfully.
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
	unsigned char *ImgData;
	unsigned char *ImgDataR;
	unsigned char *ImgDataG;
	unsigned char *ImgDataB;
	void *pImageR = NULL;
	void *pImageG = NULL;
	void *pImageB = NULL;
	
	int length = GetQHYCCDMemLength(camhandle);
	printf("length = %d\n", length);
	if(length > 0)
	{
		ImgData = (unsigned char *)malloc(length);
		memset(ImgData, 0, length);
		ImgDataR = (unsigned char *)malloc(length);
		memset(ImgDataR, 0, length);
		ImgDataG = (unsigned char *)malloc(length);
		memset(ImgDataG, 0, length);
		ImgDataB = (unsigned char *)malloc(length);
		memset(ImgDataB, 0, length);
	}
	else
	{
		printf("Get memory length failed.\n");
		*retVal = -1;
		return;
	}
	
	ret = QHYCCD_ERROR;
	while(ret != QHYCCD_SUCCESS)
	{
		ret = GetQHYCCDLiveFrame(camhandle, w, h, bpp, channels, ImgData);
	}
	
	*retVal = 0;
	int len = (*w) * (*h) * (*bpp) * (*channels) / 8;

	if(8 == *bpp && 1 == *channels)
	{
		printf("Get live frame successfully w = %d h = %d bpp = %d channels = %d\n", *w, *h, *bpp, *channels);

		int x, y;
		for(int j = 0; j < *h; j++)
		{
			for(int i = 0; i < *w; i++)
			{
				x = j * *w + i;
				y = i * *h + j;
				ImgDataR[y] = ImgData[x];
			}
		}

		plhs[5] = mxCreateNumericMatrix(*h,*w,mxUINT8_CLASS,mxREAL);
		pImageR = (uint8_t *)mxGetData(plhs[5]);
		memcpy(pImageR, ImgDataR, (*w)*(*h));
	}
	else if(16 == *bpp && 1 == *channels)
	{
		printf("Get live frame successfully w = %d h = %d bpp = %d channels = %d\n", *w, *h, *bpp, *channels);

		int x, y;
		for(int j = 0; j < *h; j++)
		{
			for(int i = 0; i < *w; i++)
			{
				x = j * *w + i;
				y = i * *h + j;
				ImgDataR[2*y]   = ImgData[2*x];
				ImgDataR[2*y+1] = ImgData[2*x+1];
			}
		}

		plhs[5] = mxCreateNumericMatrix(*h,*w,mxUINT16_CLASS,mxREAL);
		pImageR = (uint16_t *)mxGetData(plhs[5]);
		memcpy(pImageR, ImgDataR, (*w)*(*h)*2);
	}
	else if(8 == *bpp && 3 == *channels)
	{
		printf("Get live frame successfully w = %d h = %d bpp = %d channels = %d\n", *w, *h, *bpp, *channels);

		int x, y;
		for(int j = 0; j < *h; j++)
		{
			for(int i = 0; i < *w; i++)
			{
				x = j * *w + i;
				y = i * *h + j;
				ImgDataR[y] = ImgData[3*x + 0];
				ImgDataG[y] = ImgData[3*x + 1];
				ImgDataB[y] = ImgData[3*x + 2];
			}
		}

		plhs[5] = mxCreateNumericMatrix(*h,*w,mxUINT8_CLASS,mxREAL);
		pImageR = (uint8_t *)mxGetData(plhs[5]);
		memcpy(pImageR, ImgDataR, (*w)*(*h)); 
		plhs[6] = mxCreateNumericMatrix(*h,*w,mxUINT8_CLASS,mxREAL);
		pImageG = (uint8_t *)mxGetData(plhs[6]);
		memcpy(pImageG, ImgDataG, (*w)*(*h)); 
		plhs[7] = mxCreateNumericMatrix(*h,*w,mxUINT8_CLASS,mxREAL);
		pImageB = (uint8_t *)mxGetData(plhs[7]);
		memcpy(pImageB, ImgDataB, (*w)*(*h));
	}
	else
	{
		printf("Get live image error.\n");
		plhs[5] = mxCreateNumericMatrix(1,1,mxUINT8_CLASS,mxREAL);
		pImageR = (uint8_t *)mxGetData(plhs[5]);
		memcpy(pImageR, ImgData, 1);
		plhs[6] = mxCreateNumericMatrix(1,1,mxUINT8_CLASS,mxREAL);
		pImageR = (uint8_t *)mxGetData(plhs[6]);
		memcpy(pImageG, ImgData, 1);
		plhs[7] = mxCreateNumericMatrix(1,1,mxUINT8_CLASS,mxREAL);
		pImageR = (uint8_t *)mxGetData(plhs[7]);
		memcpy(pImageB, ImgData, 1);
		
		*retVal = -1;
	}
	
	free(ImgData);
	free(ImgDataR);
	free(ImgDataG);
	free(ImgDataB);
}
