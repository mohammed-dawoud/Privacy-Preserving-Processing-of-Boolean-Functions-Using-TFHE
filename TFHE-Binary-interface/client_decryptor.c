/*==========================================================
 * client_encryptor.c - example in MATLAB External Interfaces
 *
 * Multiplies an input scalar (multiplier) 
 * times a 1xN matrix (inMatrix)
 * and outputs a 1xN matrix (outMatrix)
 *
 * The calling syntax is:
 *
 *		outMatrix = arrayProduct(multiplier, inMatrix)
 *
 * This is a MEX-file for MATLAB.
 * Copyright 2007-2012 The MathWorks, Inc.
 *
 *========================================================*/

#include "mex.h"
#include "matrix.h"
#include <tfhe/tfhe.h>
#include <tfhe/tfhe_io.h>
#include <stdio.h>
#include <math.h>


/* The computational routine */
uint16_t client_decryptor()
{
        //reads the cloud key from file
    FILE* secret_key = fopen("secret.key","rb");
    TFheGateBootstrappingSecretKeySet* key = new_tfheGateBootstrappingSecretKeySet_fromFile(secret_key);
    fclose(secret_key);
 
    //if necessary, the params are inside the key
    const TFheGateBootstrappingParameterSet* params = key->params;

    //read the 16 ciphertexts of the result
    LweSample* client_answer = new_gate_bootstrapping_ciphertext_array(16, params);

    //import the 32 ciphertexts from the answer file
    FILE* answer_data = fopen("answer.data","rb");
    for (int i=0; i<16; i++) 
        import_gate_bootstrapping_ciphertext_fromFile(answer_data, &client_answer[i], params);
    fclose(answer_data);

    //decrypt and rebuild the 16-bit plaintext answer
    uint16_t int_answer = 0;
    for (int i=0; i<16; i++) {
        int ai = bootsSymDecrypt(&client_answer[i], key);
        int_answer |= (ai<<i);
    }
/*    uint16_t int_answer[16] = {1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768};
    uint16_t decimal_answer=0;
    for (int i=0; i<16; i++) {
        int ai = bootsSymDecrypt(&client_answer[i], key);
        //if (ai==1)
        printf("%dth%d\n",i,ai);
        decimal_answer += ai*int_answer[i];
        
    }
*/    
    /*int16_t decimal_result=0;
    for (int i=0; i<16; i++) {
    decimal_result+=int_answer[i]*{pow(2,i)}
    }*/
    
    printf("And the result is: %d\n",int_answer);
    printf("I hope you remember what was the question!\n");

    //clean up all pointers
    delete_gate_bootstrapping_ciphertext_array(16, client_answer);
    delete_gate_bootstrapping_secret_keyset(key);
    return int_answer;

}

/* The gateway function */
void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[])
{
    double *result;              /* input scalar */
    // size_t center2;               /* 1xN input matrix */
     size_t ncols=1;                   /* size of matrix */
    // size_t outMatrix;              /* output matrix */

    /* check for proper number of arguments */
    if(nrhs!=0) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","Two inputs required.");
    }
    if(nlhs!=1) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","One output required.");
    }
    // /* make sure the first input argument is scalar */
    // if( !mxIsDouble(prhs[0]) || 
    //      mxIsComplex(prhs[0]) ||
    //      mxGetNumberOfElements(prhs[0])!=1 ) {
    //     mexErrMsgIdAndTxt("MyToolbox:arrayProduct:notScalar","Input multiplier must be a scalar.");
    // }
    
    // /* make sure the second input argument is type double */
    // if( !mxIsDouble(prhs[1]) || 
    //      mxIsComplex(prhs[1])) {
    //     mexErrMsgIdAndTxt("MyToolbox:arrayProduct:notDouble","Input matrix must be type double.");
    // }
    // 
    // /* check that number of rows in second input argument is 1 */
    // if(mxGetM(prhs[1])!=1) {
    //     mexErrMsgIdAndTxt("MyToolbox:arrayProduct:notRowVector","Input must be a row vector.");
    // }
    
    /* get the value of the scalar input  */
    // center1 = mxGetScalar(prhs[0]);
    // center2 = mxGetScalar(prhs[1]);
    /* create a pointer to the real data in the input matrix  */
    // #if MX_HAS_INTERLEAVED_COMPLEX
    // inMatrix = mxGetDoubles(prhs[1]);
    // #else
    // inMatrix = mxGetPr(prhs[1]);
    // #endif

    /* get dimensions of the input matrix */
    // ncols = mxGetN(prhs[1]);

    /* create the output matrix */
    plhs[0] = mxCreateDoubleMatrix(1,(mwSize)ncols,mxREAL);

    /* get a pointer to the real data in the output matrix */
    #if MX_HAS_INTERLEAVED_COMPLEX
    result = mxGetscalar(plhs[0]);
    #else
    result = mxGetPr(plhs[0]);
    #endif

    /* call the computational routine */
    *result =client_decryptor();

}    
