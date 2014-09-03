#include <math.h>
#include <windows.h>
#include <winnt.h>
#include "WinDef.h"
#include "mex.h"

#define CHECKARG
#define DATANUMS 512
void mexFunction( int nlhs, mxArray *plhs[],
        int nrhs, const mxArray *prhs[] )
        
{
    BYTE* originalData;
    double *nodeType;
    const mwSize dims[]={DATANUMS,1};
    
    #ifdef CHECKARG
            /* check for proper number of arguments */
            if(nrhs!=2)
                mexErrMsgTxt("Two input required.");
    
    /* input must be a  
    if ( mxIsStruct(prhs[0]) != 1)
        mexErrMsgTxt("Input1 must be a array.");
    */
    /* input must be a row vector */
    if (mxGetM(prhs[0])!=1024)
        mexErrMsgTxt("输入数组长度必须为1024");
    #endif
            
    /* Get Input Data */
    originalData = (BYTE *)mxCalloc(DATANUMS*2,sizeof(UINT8_T));
    originalData = (BYTE *)mxGetData(prhs[0]);
    nodeType = mxGetPr(prhs[1]);
    
    /*  OutPut分配空间 */
    if(*nodeType == 4.0)
    {
        INT16* out;
        out = (INT16*)mxCalloc(DATANUMS,sizeof(INT16_T));
        plhs[0] = mxCreateNumericArray(2,dims,mxINT16_CLASS,mxREAL);
        for(int i = 0; i < DATANUMS; i++)
            out[i] = *((INT16*)(originalData+i*2));
        
        mxSetData(plhs[0],out);
    }
    else if(*nodeType == 100.0)
    {
        UINT16* out;
        out = (UINT16*)mxCalloc(DATANUMS,sizeof(UINT16_T));
        plhs[0] = mxCreateNumericArray(2,dims,mxUINT16_CLASS,mxREAL);
        for(int i = 0; i < DATANUMS; i++)
            out[i] = *((UINT16*)(originalData+i*2));
        
        mxSetData(plhs[0],out);
    }
    
    // sscanf(input_buf, "%16x", mxGetData(plhs[0])); // long hexa
    //mxFree(originalData);
    return;
    
}
