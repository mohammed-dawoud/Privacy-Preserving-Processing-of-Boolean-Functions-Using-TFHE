#include <tfhe/tfhe.h>
#include <tfhe/tfhe_io.h>
#include <stdio.h>


void encrypt(uint16_t center_plaintext1, uint16_t center_plaintext2) {
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
    
    
    
    printf("Hi there! Today, I will ask the cloud to xor %d and %d\n",center_plaintext1, center_plaintext2);
    
    
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
    }
    int main(uint16_t center_plaintext1, uint16_t center_plaintext2)
    { 
        printf("please enter the first number\n");
    scanf("%hu", &center_plaintext1);
    
    printf("please enter the second number\n");
    scanf("%hu", &center_plaintext2);
    encrypt(center_plaintext1,center_plaintext2);
    }
