#include "AES.h"
#include <iostream>
/**
 * Sets the key to use
 * @param key - the first byte of this represents whether
 * to encrypt or decrypt. 00 means encrypt and any other
 * value to decrypt. Then come the bytes of the 128-bit key
 * (should be 16 of them).
 *  @return - True if the key is valid and False otherwise
 */
bool AES::setKey(const unsigned char* keyArray) {


	//TODO: AES implementation of openssl cares about whether
	//you are encrypting or decryting when setting the key.
	//That is, when encrypting you use function AES_set_encrypt_key(...)
	//and when decrypting AES_set_decrypt_key(...).
	//
	//One way to solve this problem is to pass in a 17 byte key, where
	//the first byte is used to indicate whether we are encrypting or
	//decrypting. E.g., if the first byte is 0, then ise AES_set_encrypt_key(...).
	//Otherwise, use AES_set_decrypt_key(...).  The rest of the bytes in the
	//array indicate the 16 bytes of the 128-bit AES key.
	//
	//Both functions return 0 on success and other values of faliure.
	//For documentation, please see https://boringssl.googlesource.com/boringssl/+/2623/include/openssl/aes.h
	//and aes.cpp example provided witht the assignment.
	printf("Made it to setkey\n");
	unsigned char keyAfterByte[32];
	unsigned char aes_key[16];
	int AESKeyIndex = 0;
	int keyIndex = 0;
	// Read actual key
	for(int i = 1; i < 33; i++){
		keyAfterByte[i - 1] = keyArray[i];
	}

	// Convert AES key into hexidecimal
	while(AESKeyIndex != 16){
		if(aes_key[AESKeyIndex] = twoCharToHexByte(keyAfterByte + keyIndex) == 'z'){
			return false;
		}
		keyIndex += 2;
		++AESKeyIndex;
	}

	std::cout << "\nThis is in the set key:\n";
	for(int i = 0; i < 16; i++){
		std::cout << aes_key[i];
	}
	std::cout << "\n\n";
	// Sets key to either encrypt or decrypt mode
	if (keyArray[0] == 0){
		if (AES_set_encrypt_key(aes_key, 128, &AESKey) != 0){
			printf("Key set to enc\n");
		}
	}else{
		if (AES_set_decrypt_key(aes_key, 128, &AESKey) != 0){
			printf("Key set to dec");
		}
	}

	return false;
}

/**
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */

unsigned char * AES::encrypt(const unsigned char * plainText) {
	//TODO: 1. Dynamically allocate a block to store the ciphertext.
	// 2. Use AES_ecb_encrypt(...) to encrypt the text (please see the URL in setKey(...)
	// and the aes.cpp example provided
	// 3. return the pointer to the ciphertext

	printf("Made it to encrypt\n");
	unsigned char* enc_out = new unsigned char[16];

	memset(enc_out, 0, 16);

	/*
	std::cout << "size of ENC_IN: " << sizeof(enc_in) << "\n";
	for(int i = 0; i < 16; i++){
		enc_in[i] = plainText[i];
	}
*/
	AES_ecb_encrypt(plainText, enc_out, &AESKey, AES_ENCRYPT);

	printf("Exiting encrypt\n");
	return enc_out;
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */
unsigned char* AES::decrypt(const unsigned char* cipherText) {

	//TODO: 1. Dynamically allocate a block to store the plaintext.
	// 2. Use AES_ecb_encrypt(...) to decrypt the text (please see the URL in setKey(...)
	//  and the aes.cpp example provided.
	//  3. Return the pointer tot he plaintext
	unsigned char* dec_out = new unsigned char[16];

	memset(dec_out, 0, 16);

	// std::cout << &aes_key;
	AES_ecb_encrypt(cipherText, dec_out, &AESKey, AES_DECRYPT);

	return dec_out;
}

// Functions to convert AES key to hex
/**
 * Converts a character into a hexidecimal integer
 * @param character - the character to convert
 * @return - the converted character, or 'z' on error
 */
unsigned char AES::charToHex(const char& character)
{
	/* Is the first digit 0-9 ? */
	if(character >= '0' && character <= '9')
		/* Convert the character to hex */
		return character - '0';
	/* It the first digit a letter 'a' - 'f'? */
	else if(character >= 'a' && character <= 'f')
		/* Conver the cgaracter to hex */
		return (character - 97) + 10;
	/* Invalid character */
	else return 'z';
}

/**
 * Converts two characters into a hex integers
 * and then inserts the integers into the higher
 * and lower bits of the byte
 * @param twoChars - two charcters representing the
 * the hexidecimal nibbles of the byte.
 * @param twoChars - the two characters
 * @return - the byte containing having the
 * valud of two characters e.g. string "ab"
 * becomes hexidecimal integer 0xab.
 */
unsigned char AES::twoCharToHexByte(const unsigned char* twoChars)
{
	/* The byte */
	unsigned char singleByte;

	/* The second character */
	unsigned char secondChar;

	/* Convert the first character */
	if((singleByte = charToHex(twoChars[0])) == 'z')
	{
		/* Invalid digit */
		return 'z';
	}

	/* Move the newly inserted nibble from the
	 * lower to upper nibble.
	 */
	singleByte = (singleByte << 4);

	/* Conver the second character */
	if((secondChar = charToHex(twoChars[1])) == 'z')
		return 'z';

	/* Insert the second value into the lower nibble */
	singleByte |= secondChar;

	return singleByte;
}
