#include "DES.h"


bool DES::setKey(const unsigned char* keyArray)
{
	/**
	 * First let's covert the char string
	 * into an integer byte string
	 */


	/* The key error code */
	int keyErrorCode = -1;

	/* A single byte */
	unsigned char singleByte = 0;

	/* The key index */
	int keyIndex = 0;

	/* The DES key index */
	int desKeyIndex = 0;

	/* Go through the entire key character by character */
	while(desKeyIndex != 8)
	{
		/* Convert the key if the character is valid */
		if((this->des_key[desKeyIndex] = twoCharToHexByte(keyArray + keyIndex)) == 'z')
			return false;

		/* Go to the second pair of characters */
		keyIndex += 2;

		/* Increment the index */
		++desKeyIndex;
	}

	fprintf(stdout, "DES KEY: ");

	/* Print the key */
	for(keyIndex = 0; keyIndex < 8; ++keyIndex)
		fprintf(stdout, "%x", this->des_key[keyIndex]);

	fprintf(stdout, "\n");


	/* Set the encryption key */
	if ((keyErrorCode = des_set_key_checked(&des_key, this->key)) != 0)
	{
		fprintf(stderr, "\nkey error %d\n", keyErrorCode);

		return false;
	}

	/* All is well */
	return true;
}

/**
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
unsigned char* DES::encrypt(const unsigned char* plaintext)
{
	// const unsigned char* pstart = plaintext;

        /* An array of two long integers */
        DES_LONG block[2];

        /* Plaintext length */
      //  int plaintextLength = 0;

        /* The cipher text*/
        unsigned char* ciphertext = new unsigned char[9];

        /* Verifies the length of plaintext is 8 */
       // while(plaintext++ != '\0') { ++plaintextLength; }

        /* Continue if length of plaintext is 8 Otherwise exit */
        //if(plaintextLength != 8) {
         //       fprintf(stderr,"\nplaintext length error: %d\n",-1);
         //       return NULL;
        // }

        /* Reset plaintext to be at the beginning */
        //plaintext = pstart;

        /* Print original text */
        fprintf(stderr, "Original text: %s\n", plaintext);

        /* Stuff the first 4 bytes of the plaintext into a long */
        block[0] = ctol((unsigned char*)plaintext);

        /* Stuff the next 4 bytes of the plaintext into a long*/
        block[1] = ctol((unsigned char*)plaintext + 4);


        /* Encrypt the array of 2 longs: block[0] and
 *          * and block[1] will be replaced with the corresponding
 *                   * ciphertext
 *                            */
        des_encrypt1(block, key, ENC);

        memset(ciphertext,0,9);

        /* Convert the first 32 bits of ciphertext from a
 *          * a long integer into a character format
 *                   * (4-char array).
 *                            */
        ltoc(block[0], ciphertext);

        /* Convert the first 32 bits of ciphertext from a
 *          * long integer into a character format
 *                   * (4-char array).
 *                            */
        ltoc(block[1], ciphertext + 4);

        /* Print the cipher text */
        fprintf(stderr, "Cipher text: %s\n", ciphertext);

	return ciphertext;
}

/**
 * Decrypts a string of ciphertext
 * @param ciphertext - the ciphertext
 * @return - the plaintext
 */
unsigned char* DES::decrypt(const unsigned char* ciphertext)
{
	//const unsigned char* pstart = ciphertext;

        /* An array of two long integers */
        DES_LONG block[2];

        /* cipher text length */
        int ciphertextLength = 0;

        /* The plain text*/
        unsigned char* decryptedText = new unsigned char[9];

        /* Verifies the length of cipher text is 8 */
        //while(ciphertext++ != '\0') { ++ciphertextLength; }

        /* Continue if length of cipher text is 8 Otherwise exit */
        /*if(ciphertextLength != 8) {
                fprintf(stderr,"\nplaintext length error: %d\n",-1);
                return NULL;
        }*/

        /* Reset cipher text to be at the beginning */
       // ciphertext = pstart;

        /* Print cipher text */
        fprintf(stderr, "Cipher text: %s\n", ciphertext);

        /* Stuff the first 4 bytes of the cipher text into a long */
        block[0] = ctol((unsigned char*)ciphertext);

        /* Stuff the next 4 bytes of the cipher text into a long*/
        block[1] = ctol((unsigned char*)ciphertext + 4);


        /* Decrypt the cipher text */
        des_encrypt1(block, key, DEC);

        memset(decryptedText,0,9);

        /* Convert the first 32 bits of plaintext from long to char */
        ltoc(block[0], decryptedText);
        ltoc(block[1], decryptedText + 4);

        /* Print the cipher text */
        fprintf(stderr, "Cipher text: %s\n", ciphertext);

        return decryptedText;

}

/**
 * Converts an array of 8 characters
 * (i.e. 4 bytes/32 bits)
 * @param c - the array of 4 characters (i.e. 1-byte per/character
 * @return - the long integer (32 bits) where each byte
 * is equivalent to one of the bytes in a character array
 */
DES_LONG DES::ctol(unsigned char *c)
{
        /* The long integer */
	DES_LONG l;

	l =((DES_LONG)(*((c)++)));
        l = l | (((DES_LONG)(*((c)++)))<<8L);
        l = l | (((DES_LONG)(*((c)++)))<<16L);
        l = l | (((DES_LONG)(*((c)++)))<<24L);
        return l;
};


/**
 * Converts a long integer (4 bytes = 32 bits)
 * into an array of 8 characters.
 * @param l - the long integer to convert
 * @param c - the character array to store the result
 */
void DES::ltoc(DES_LONG l, unsigned char *c)
{
        *((c)++)=(unsigned char)(l&0xff);
        *((c)++)=(unsigned char)(((l)>> 8L)&0xff);
        *((c)++)=(unsigned char)(((l)>>16L)&0xff);
        *((c)++)=(unsigned char)(((l)>>24L)&0xff);
}

/**
 * Converts a character into a hexidecimal integer
 * @param character - the character to convert
 * @return - the converted character, or 'z' on error
 */
unsigned char DES::charToHex(const char& character)
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
unsigned char DES::twoCharToHexByte(const unsigned char* twoChars)
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
