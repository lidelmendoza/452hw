#include <string>
#include "CipherInterface.h"
#include "DES.h"
#include "AES.h"

using namespace std;

int main(int argc, char** argv)
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
	if(argc ==  6) {
		fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",
                __FILE__, __FUNCTION__, __LINE__);
		exit(-1);
	}
	/* Compare if argv[1] is equal to DES if yes create a DES instance */
	if(strcmp((const char)argv[1],(const char*)"AES") == 0) {
                cipher = new AES; }
	else if(strcmp((const char*)argv[1], (const char*)"DES") == 0) {
		cipher = new DES; }
	//else if(strcmp((const char)argv[1],(const char*)"AES") != NULL) {
		cipher = new AES; } 

	cipher->setKey((const unsigned char*)"0123456789abcdef");		
	/* Error checks */
	if(!cipher)
	{
		fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",	
		__FILE__, __FUNCTION__, __LINE__);
		exit(-1);
	}
	
	/* Set the encryption key
	 * A valid key comprises 16 hexidecimal
	 * characters. Below is one example.
	 * Your program should take input from
	 * command line.
	 */
//	cipher->setKey((const unsigned char*)"0123456789abcdef");
	
	/* Perform encryption */
	cipher->encrypt((const unsigned char*)"hello world");
	
	/* Perform decryption */
	//cipher->decrypt(cipherText);	

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
