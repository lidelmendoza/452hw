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
	if(argc != 6){
		fprintf(stderr, "ERROR [%s %s %d]: Input did not provide enough arguments\n",
	 		__FILE__, __FUNCTION__, __LINE__);
			exit(-1);
	}

	// if-else to choose between AES and DES
	if(std::string(argv[1]) == "AES"){
		printf("AES");
		cipher = new AES();
		if(std::string(argv[2]).length() < 32){
			std::cout << "Error: Need a 16-byte key (32 characters)\n";
			exit(-1);
		}
		unsigned char key[33];

		// Temp variable to hold the key argument
		std::string temp = std::string(argv[2]);

		// Read key argument into indices 1-16
		for(int i = 1; i < 32; i++){
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
		cipher->setKey((const unsigned char*)key);
	}else if(std::string(argv[1]) == "DES"){
		printf("DES");
		cipher = new DES();
		cipher->setKey((const unsigned char*)argv[2]);
	}else{
		fprintf(stderr, "NO SUCH ENCRYPTION METHOD\n");
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
	std::cout << "This is the length of the character buffer: " << plainText.length();

	// Padding for AES block
	if(std::string(argv[1]) == "AES"){
		if((plainText.length() - 1) % 16 != 0){
			int pad = 16 - ((plainText.length() - 1) % 16);
			int count = 0;
			while(count < pad){
				plainText += "0";
				count++;
			}
		}
	// Padding for DES block
	}else{
		if((plainText.length() - 1) % 8 != 0){
			int pad = 8 - ((plainText.length() - 1) % 8);
			int count = 0;
			while(count < pad){
				plainText += "0";
				count++;
			}
		}
	}

	// Read blocks from the file and encrypt or decrypt for AES
	if(std::string(argv[1]) == "AES"){
		for(int bufferIndex = 0; bufferIndex < plainText.length() - 1; bufferIndex += 16){
			unsigned char PlainTextBlock[16];
			unsigned char* cipherBlock = new unsigned char[16];
			for(int i = 0; i < 16; i++){
				PlainTextBlock[i] = plainText[i + bufferIndex];
			}
			// Encrypt or decrypt
			if(std::string(argv[3]) == "ENC"){
				cipherBlock = cipher->encrypt((const unsigned char*) PlainTextBlock);
			}else{
				cipherBlock = cipher->decrypt((const unsigned char*) PlainTextBlock);
			}

			// Read either cipher text or plain text to designated file
			std::ofstream outFile;
			outFile.open(std::string(argv[5]), ios::app);
			for(int blockIndex = 0; blockIndex < 16; blockIndex++){
				outFile << cipherBlock[blockIndex];
			}
			outFile.close();
		}
		// Read blocks from the file and encrypt or decrypt for DES
	}else{
		for(int bufferIndex = 0; bufferIndex < plainText.length() - 1; bufferIndex += 8){
			unsigned char PlainTextBlock[8];
			unsigned char* cipherBlock = new unsigned char[8];
			for(int i = 0; i < 8; i++){
				PlainTextBlock[i] = plainText[i + bufferIndex];
			}
			// Encrypt or decrypt
			if(std::string(argv[3]) == "ENC"){
				cipherBlock = cipher->encrypt((const unsigned char*) PlainTextBlock);
			}else{
				cipherBlock = cipher->decrypt((const unsigned char*) PlainTextBlock);
			}

			// Read either cipher text or plain text to designated text
			std::ofstream outFile;
			outFile.open(std::string(argv[5]), ios::app);
			for(int blockIndex = 0; blockIndex < 8; blockIndex++){
				outFile << cipherBlock[blockIndex];
			}
			outFile.close();
		}
	}

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

	return 0;
}
