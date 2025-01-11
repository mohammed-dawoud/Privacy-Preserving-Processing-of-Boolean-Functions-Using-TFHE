#include <tfhe/tfhe.h>
#include <tfhe/tfhe_io.h>
#include <stdio.h>
#include <math.h>

int main() {

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
}



