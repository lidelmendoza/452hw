#include <string>
#include "CipherInterface.h"
#include "DES.h"
#include "AES.h"

using namespace std;

int main(int argc,char** argv)
{
	/**
	 * TODO: Replace the code below	with your code which can SWITCH
	 * between DES and AES and encrypt files. DO NOT FORGET TO PAD
	 * THE LAST BLOCK IF NECESSARY.
	 *
	 * NOTE: due to the incomplete skeleton, the code may crash or
	 * misbehave.
	 */
	
	/* Create an instance of the DES cipher */	
	CipherInterface* cipher = NULL;
	if(argc !=  6) {
		fprintf(stderr, "ERROR [%s %s %d]: Input did not provide enough arguments\n",
                __FILE__, __FUNCTION__, __LINE__);
		exit(-1);
	}

	/* Compare if argv[1] is equal to DES if yes create a DES instance */
	if(strcmp((const char*)argv[1],(const char*)"AES") == 0) {
                cipher = new AES; }
	else if(strcmp((const char*)argv[1], (const char*)"DES") == 0) {
		cipher = new DES; 
		fprintf(stderr, "Here!\n");
		}
	//else if(strcmp((const char)argv[1],(const char*)"AES") != NULL) {
		//cipher = new AES; } 
	
	/* Error checks */
	if(!cipher)
	{
		fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",	
		__FILE__, __FUNCTION__, __LINE__);
		exit(-1);
	}

	
	cipher->setKey((const unsigned char*)"0123456789abcdef");		
	
	/* Set the encryption key
	 * A valid key comprises 16 hexidecimal
	 * characters. Below is one example.
	 * Your program should take input from
	 * command line.
	 */
//	cipher->setKey((const unsigned char*)"0123456789abcdef");
	
	/* Perform encryption */
	unsigned char *cipherText = cipher->encrypt((const unsigned char*)"hello world");
	
	fprintf(stderr, "Printing our encrypted plaintext block: %s\n", cipherText);
		
	/* Perform decryption */
	unsigned char *plainText = cipher->decrypt(cipherText);	

	fprintf(stderr, "Printing our original message: %s\n", plainText);

	/*const unsigned char* k = reinterpret_cast<const unsigned char *>( "0123456789abcdef" );
        DES cipher;
        cipher.setKey((unsigned char*)"0123456789abcdef");
        cipher.encrypt((unsigned const char*)"BillyBob");*/
        //bool key = block.setKey(k);
        //        //cout << "This is the key" << key << endl; 
        //                std::cout << "Hello World\n";
        //
        //                        return 0;	
	return 0;
}
