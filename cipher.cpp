#include <string>
#include "CipherInterface.h"
#include "DES.h"
//#include "AES.h"

using namespace std;

int main(int argc, char** argv)
{
	/** 
 	* TODO: Replace the code below with your code wchi can SWITCH
 	* between DES and AES and encrypt files. DO NOT FORGET TO PAD
 	* THE LAST BLOCK IF NECESSARY.
 	*
 	* NOTE: due to the incomplete skeleton, the code may crash or 
 	* misbehave.
 	*/


	/* Create an instance of the DES cipher */
	DES* cipher = NULL;

	/* Error checks */
	if(!cipher) {
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
	cipher->setKey((unsigned char*)"0123456789abcdef");


	/* The plaintext */
	const unsigned char plainText[] = "BillyBob";

	/* Perfomr encryption */
	 cipher->encrypt((const unsigned char*)plainText);
	//fprintf("cipher text: %s\n",cipherText);
	/* Perform encryption */
	//string cipherText = cipher->encrypt("hello world");
	
	/* Perform decryption */
	//cipher->decrypt(cipherText);
	//
	return 0;
}
