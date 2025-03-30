# Hill-Cipher-Encryption

**Overview**

This project implements the Hill cipher for encrypting alphabetic text using an n * n encryption matrix, where n can range from 2 to 9. The program reads the encryption key and plaintext from two input files specified via command-line arguments, applies the Hill cipher algorithm, and outputs the encrypted text (ciphertext) to the console.

**Features**

* Supports an encryption key matrix size from 2x2 to 9x9.  
* Reads input files via command-line arguments without user prompts.  
* Converts all alphabetic characters to lowercase and ignores non-alphabetic characters.  
* Pads plaintext with the letter 'x' if necessary to match block size.  
* Outputs formatted cipher  

**File Formats**

1. Encryption Key File  

The key file contains:  

* A single integer n (2 ≤ n ≤ 9) on the first line, representing the size of the encryption matrix.  
* n lines containing n integers each, forming the encryption matrix.  

2. Plaintext File  

The plaintext file contains text with alphabetic and non-alphabetic characters. Only alphabetic characters are considered for encryption, and all uppercase letters are converted to lowercase. Non-alphabetic characters are ignored.  

**Output Format**

* Echo the encryption key matrix. 
* Echo the processed plaintext.  
* Output the encrypted ciphertext in rows of 80 characters each.

**How to Run**

1. Compile the program with: gcc -o pa01 pa01.c
2. Execute the program with ./pa01 <Encryption Key File>.txt <Plaintext File>.txt
