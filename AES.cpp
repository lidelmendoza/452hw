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
	unsigned char keyAfterByte = new unsigned char[16];

	for(int i = 1; i < 17; i++){
		keyAfterByte[i - 1] = keyArray[i];
	}

	std::cout << "size of key without byte: " << sizeof(keyAfterByte) << "\n";

	if (keyArray[0] == 0){
		if (AES_set_encrypt_key(keyAfterByte, 128, &aes_enc_key) != 0){
			printf("Key set to enc\n");
			std::cout << "size of key after encrypt: " << sizeof(&aes_enc_key) << "\n";
		}
	}else{
		if (AES_set_decrypt_key(keyAfterByte, 128, &aes_dec_key) != 0){
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
	std::cout << "size of plain text before encrypt: " << sizeof(plainText) << "\n";
	unsigned char enc_in[16];
	unsigned char* enc_out = new unsigned char[16];

	memset(enc_in, 0, 16);
	memset(enc_out, 0, 16);

	/*
	std::cout << "size of ENC_IN: " << sizeof(enc_in) << "\n";
	for(int i = 0; i < 16; i++){
		enc_in[i] = plainText[i];
	}
*/
	AES_ecb_encrypt(plainText, enc_in, &aes_enc_key, AES_ENCRYPT);
	std::cout << "size of ENC_OUT after encrypt: " << sizeof(enc_out) << "\n";
	for(int i = 0; i < 16; i++){
		enc_out[i] = enc_in[i];
		std::cout << enc_out[i] << "\n";
	}

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
	unsigned char dec_in[16];
	unsigned char* dec_out = new unsigned char[16];

	memset(dec_in, 0, 16);
	memset(dec_out, 0, 16);

	// std::cout << &aes_key;
	AES_ecb_encrypt(cipherText, dec_in, &aes_dec_key, AES_DECRYPT);

	for(int i = 0; 16; i++){
		dec_out[i] = cipherText[i];
		// std::cout << dec_in[i];
	}
	return dec_out;
}
