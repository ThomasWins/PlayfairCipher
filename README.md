# PlayfairCipher
The Playfair cipher is a manual symmetric encryption technique that encrypts pairs of letters (digraphs) using a 5x5 grid of letters based on a keyword. The keyword is used to fill the grid, omitting duplicate letters, and the remaining spaces are filled with the rest of the alphabet. Typically, 'I' and 'J' are combined in the same cell to fit into the 5x5 grid. In this case I is replaced with the single letter J.

# Input
       %d = n (however many ciphers you want to encrypt)
       
       %s = key 
       %s = Plaintext 
       ...

# Notes
Copying and pasting more than 3 Playfair samples simultaneously causes the ciphers to overlap the inputting code. Putting 1 in at a time fixes this problem. (Still works inputting any n)

This Code works to encrypt any message you give it up to 100 characters. Change MAX_CIPHER to however long you want your cipher to be.
