#include <string>
#include "CipherInterface.h"
#include "DES.h"
#include "AES.h"
#include <fstream>
#include <sstream>
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


	/* Create an instance of the Cipher Interface */
	CipherInterface* cipher = NULL;

	// if-else to choose between AES and DES
	if(std::string(argv[1]) == "AES"){
		printf("AES");
		cipher = new AES();
	}else if(std::string(argv[1]) == "DES"){
		printf("DES");
		//DES des;
		//cipher = &des;
	}else{
		fprintf(stderr, "NO SUCH ENCRYPTION METHOD\n");
		exit(-1);
	}

	// Temp variable to hold the key argument
	std::string temp = std::string(argv[2]);

	// Create key variable
	unsigned char* key = new unsigned char;

	// Read key argument into indices 1-16
	for(int i = 1; i < 17; i++){
		key[i] = temp[i - 1];
	}

	// if-else to determine whether to encrypt or decrypt
	if(std::string(argv[3]) == "ENC"){
		printf("%s\n", "ENC\n");
		key[0] = 0;

	}else if (std::string(argv[3]) == "DEC"){
		printf("DEC");
		key[0] = 1;
	}else{
		printf("Error");
		exit(-1);
	}

	// Read file into buffer
	// https://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
	std::ifstream file(argv[4]);
	std::stringstream characterBuffer;
	characterBuffer << file.rdbuf();
	file.close();

	// string to hold original message
	string plainText = characterBuffer.str();

	// unsigned char to hold cipherText
	// cipher text isnt an unsgined char * and the encrypt method requires that as an assigned
	string cipherText = "";

	unsigned char* cipherBlock = new unsigned char[16];
	memset(cipherBlock, 0, 16);

	std::cout << "This is the key: ";
	for(int i = 1; i < 17; i++){
		std::cout << key[i];
	}


	std::cout << "\nThis is the size of the key: " << sizeof(key) << "\n";

	if (!cipher->setKey((unsigned char*)key)){
		/* The plaintext */
		int posInPlainText = 0;
		string block = plainText.substr(posInPlainText, posInPlainText +  16);

		}
char hex[16];
		for(int i = 0; i < 16; i++){
			if(block[i] >= '0' && block[i] <= '9'){
				hex[i] = (char)block[i] - '0';
			}else if(block[i] >= 'a' && block[i] <= 'f'){
				hex[i] = (char)(block[i] - 97) + 10;
			}else{
				hex[i] = 'z';
			}
		/*
		unsigned char* currentBlock = new unsigned char[16];
		memset(currentBlock, 0, 16);

		// Change characters into hex bytes
		std::cout << "These are the hex values: ";
		for(int i = 0; i < 16; i++){
			if(block[i] >= '0' && block[i] <= '9'){
				currentBlock[i] = (unsigned char*)(block[i] - '0');
			}else if(block[i] >= 'a' && block[i] <= 'f'){
				currentBlock[i] = (unsigned char*)((block[i] - 97) + 10);
			}else{
				currentBlock[i] = (unsigned char*)'z';
			}
			std::cout << currentBlock[i] << " ";
		}
		*/
		/* Perform encryption */
		if (key[0] == 0){
			std::cout << "size of cipher text before encrypt: " << sizeof(cipherText) << "\n";
			//cipherBlock = cipher->encrypt((const unsigned char*)currentBlock);
		}else{
			// cipherBlock = cipher->decrypt((const unsigned char*)currentBlock);
		}
	}
	std::cout << "Made it out" << "\n";

	std::cout << "Key before: " << key[0] << "\n";
	key[0] = 1;
	std::cout << "this is the key: " << key[0] << "\n";
	/*
	if (cipher->setKey((unsigned char*)key)){
		unsigned char* decryptedText;

		decryptedText = cipher->decrypt((const unsigned char*)cipherText);
	}
	//std::cout << decryptedText;
*/
	/* Error checks
	if(!cipher) {
		fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",
		__FILE__, __FUNCTION__, __LINE__);
		exit(-1);
	}
	*/
	/* Set the encryption key
 	 * A valid key comprises 16 hexidecimal
 	 * characters. Below is one example.
 	 * Your program should take input from
 	 * command line.
 	 */


	//fprintf("cipher text: %s\n",cipherText);
	/* Perform encryption */
	//string cipherText = cipher->encrypt("hello world");

	/* Perform decryption */
	//cipher->decrypt(cipherText);
	//
	return 0;
}
