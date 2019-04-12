#include "AES.h"

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
	unsigned char keyAfterByte[16];
	for(int i = 1; i < 17; i++){
		keyAfterByte[i - 1] = keyArray[i];
		fprintf(stderr, "%c\n", keyAfterByte[i - 1]);
	}

	if (keyArray[0] == 0){
		if (!AES_set_encrypt_key((const unsigned char*)keyAfterByte, 128, &aes_key)){
			aes_key = (AES_KEY)keyAfterByte;
		}
	}else{
		if (!AES_set_decrypt_key((const unsigned char*)keyAfterByte, 128, &aes_key)){
			aes_key = keyAfterByte;
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
	//
	unsigned char* enc_in = new unsigned char*[], enc_out;
	enc_in = new unsigned char[sizeof(plainText)];
	for(int i = 0; i < sizeof(plainText) - 1; i++){
		enc_in[i] = plainText[i];
	}

	AES_ecb_encrypt(enc_in, enc_out, &aes_key, AES_ENCRYPT);

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
	unsigned char* dec_in, dec_out;
	dec_in = new unsigned char[sizeof(cipherText)];
	for(int i = 0; i < sizeof(cipherText) - 1; i++){
		dec_in[i] = cipherText[i];
	}
	AES_ecb_encrypt(dec_in, dec_out, &aes_key, AES_DECRYPT);

	return dec_out;
}
