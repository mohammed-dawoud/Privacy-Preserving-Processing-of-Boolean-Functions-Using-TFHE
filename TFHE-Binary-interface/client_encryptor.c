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
#include <tfhe/tfhe.h>
#include <tfhe/tfhe_io.h>
#include <stdio.h>

/* The computational routine */
void client_encryptor(uint16_t center_plaintext1, uint16_t center_plaintext2)
{
    //generate a keyset
    const int minimum_lambda = 110;
    TFheGateBootstrappingParameterSet* params = new_default_gate_bootstrapping_parameters(minimum_lambda);

    //generate a random key
    uint32_t seed[] = { 314, 1592, 657 };
    tfhe_random_generator_setSeed(seed,3);
    TFheGateBootstrappingSecretKeySet* key = new_random_gate_bootstrapping_secret_keyset(params);

    //export the secret key to file for later use
    FILE* secret_key = fopen("secret.key","wb");
    export_tfheGateBootstrappingSecretKeySet_toFile(secret_key, key);
    fclose(secret_key);

    //export the cloud key to a file (for the cloud)
    FILE* cloud_key = fopen("cloud.key","wb");
    export_tfheGateBootstrappingCloudKeySet_toFile(cloud_key, &key->cloud);
    fclose(cloud_key);
   
    //you can put additional instructions here!!
    //...
    FILE* F=fopen("params.txt","w+");
    export_tfheGateBootstrappingParameterSet_toFile(F,params);
    fclose(F);
    
    
    
    //encrypt two centers
    
    //generate encrypt the 16 bits of center1
    //uint16_t center_plaintext1=50;
    //uint16_t center_plaintext1=0b1111;
    //uint16_t center_plaintext2=0b0101;

    



    LweSample* center_ciphertext1 = new_gate_bootstrapping_ciphertext_array(16, params);
    for (int i=0; i<16; i++) {
        bootsSymEncrypt(&center_ciphertext1[i], (center_plaintext1>>i)&1, key);
    }
    
    //generate encrypt the 16 bits of center2
    //int16_t center_plaintext2 = 0b0000000000000101;
    
    LweSample* center_ciphertext2 = new_gate_bootstrapping_ciphertext_array(16, params);
    for (int i=0; i<16; i++) {
        bootsSymEncrypt(&center_ciphertext2[i], (center_plaintext2>>i)&1, key);
    }
    
    
    
    printf("Hi there! Today, I will ask the cloud to do the requested operations\n on two centers of values %d and %d\n",center_plaintext1, center_plaintext2);
    
    
    //export the 2x16 ciphertexts to a file (for the cloud)
    FILE* cloud_data = fopen("cloud.data","wb");
    for (int i=0; i<16; i++) 
        export_gate_bootstrapping_ciphertext_toFile(cloud_data, &center_ciphertext1[i], params);
    for (int i=0; i<16; i++) 
        export_gate_bootstrapping_ciphertext_toFile(cloud_data, &center_ciphertext2[i], params);
    fclose(cloud_data);

    //clean up all pointers
    delete_gate_bootstrapping_ciphertext_array(16, center_ciphertext2);
    delete_gate_bootstrapping_ciphertext_array(16, center_ciphertext1);


    //clean up all pointers
    delete_gate_bootstrapping_secret_keyset(key);
    
    delete_gate_bootstrapping_parameters(params);
    //return 0;

}

/* The gateway function */
void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[])
{
    size_t center1;              /* input scalar */
    size_t center2;               /* 1xN input matrix */
    size_t ncols;                   /* size of matrix */
    size_t outMatrix;              /* output matrix */

    /* check for proper number of arguments */
    if(nrhs!=2) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","Two inputs required.");
    }
    if(nlhs!=0) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","One output required.");
    }
    /* make sure the first input argument is scalar */
    if( !mxIsDouble(prhs[0]) || 
         mxIsComplex(prhs[0]) ||
         mxGetNumberOfElements(prhs[0])!=1 ) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:notScalar","Input multiplier must be a scalar.");
    }
    
    /* make sure the second input argument is type double */
     if( !mxIsDouble(prhs[1]) || 
          mxIsComplex(prhs[1])) {
         mexErrMsgIdAndTxt("MyToolbox:arrayProduct:notDouble","Input matrix must be type double.");
     }
    
    // /* check that number of rows in second input argument is 1 */
    // if(mxGetM(prhs[1])!=1) {
    //     mexErrMsgIdAndTxt("MyToolbox:arrayProduct:notRowVector","Input must be a row vector.");
    // }
    
    /* get the value of the scalar input  */
    center1 = mxGetScalar(prhs[0]);
    center2 = mxGetScalar(prhs[1]);
    /* create a pointer to the real data in the input matrix  */
    // #if MX_HAS_INTERLEAVED_COMPLEX
    // inMatrix = mxGetDoubles(prhs[1]);
    // #else
    // inMatrix = mxGetPr(prhs[1]);
    // #endif

    /* get dimensions of the input matrix */
    ncols = mxGetN(prhs[1]);

    /* create the output matrix */
   // plhs[0] = mxCreateDoubleMatrix(1,(mwSize)ncols,mxREAL);
    //outMatrix=1;
    /* get a pointer to the real data in the output matrix */
    // #if MX_HAS_INTERLEAVED_COMPLEX
    // outMatrix = mxGetScalar(plhs[0]);
    // #else
    // outMatrix = mxGetScalar(plhs[0]);
    // #endif

    /* call the computational routine */
    client_encryptor(center1,center2);
}
