/*
 * Search QHY camera,if found and open successfully,it will return camera's ID.
 * In this code,it will return ID.
 */
 
#include "qhyccd.h"
#include "mex.h"
#include <time.h>
#include <string.h>
#include <windows.h>

void
mexFunction(int nlhs,mxArray *plhs[],int nrhs,const mxArray *prhs[])
{
	int ret = QHYCCD_ERROR;
	int num = 0;
    qhyccd_handle *camhandle = NULL;
	
	plhs[0] = mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
	int *retVal  = (int *)mxGetData(plhs[0]);
	plhs[1] = mxCreateNumericMatrix(32,1,mxUINT8_CLASS,mxREAL);
	char *id = (char *)mxGetData(plhs[1]);
	
	ret = InitQHYCCDResource();
    if(ret == QHYCCD_SUCCESS)
    {
        printf("Init SDK successfully.\n");
    }
    else
    {
        printf("Init SDK failed.\n");
		*retVal = -1;
		return;
    }

    num = ScanQHYCCD();
    if(num > 0)
    {
        printf("Yes!Found QHYCCD,the num is %d.\n", num);
    }
    else
    {
        printf("Not Found QHYCCD,please check the usblink or the power.\n");
		*retVal = -1;
		return;
    }

    for(int i = 0;i < num;i++)
    {
        ret = GetQHYCCDId(i,id);
        if(ret == QHYCCD_SUCCESS)
        {
            printf("Connected to the first camera from the list,id is %s.\n", id);
	
            camhandle = OpenQHYCCD(id);
			if(camhandle != NULL)
			{
				printf("Open QHYCCD successfully.\n");
			}
			else
			{
				printf("Open QHYCCD failed.\n");
				*id = NULL;
				*retVal = -1;
				return;
			}

            break;
        }
		else
		{
			printf("Get camera ID failed.\n");
			*retVal = -1;
			return;
		}
    }
}
