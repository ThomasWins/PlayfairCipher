// Thomas Winslow
// 9/18/24

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CIPHER 100

char * findXY(char * XY, char ** matrix){
    int pos1[2] = {0, 0};
    int pos2[2] = {0, 0};
    int found1 = 0, found2 = 0; // Flags to check if characters are found

    // if plaintext has i, make it j
    if (XY[0] == 'i') XY[0]++;
    if (XY[1] == 'i') XY[1]++;

    // Find position of Char 1
    while (!found1) {
        if (matrix[pos1[0]][pos1[1]] == XY[0]) {
            found1 = 1;
            break;
        }
        pos1[1]++;
        if (pos1[1] == 5){
            pos1[1] = 0;
            pos1[0]++;
        }

        // Prevent out-of-bounds access
        if (pos1[0] >= 5)
        {
            printf("Character %c not found in the matrix.\n", XY[0]);
            return NULL;
        }
    }

    // Find position of Char 2
    while (!found2)
    {
        if (matrix[pos2[0]][pos2[1]] == XY[1])
        {
            found2 = 1;
            break;
        }
        pos2[1]++;
        if (pos2[1] == 5)
        {
            pos2[1] = 0;
            pos2[0]++;
        }

        // Prevent out-of-bounds access
        if (pos2[0] >= 5)
        {
            printf("Character %c not found in the matrix.\n", XY[1]);
            return NULL;
        }
    }

    char * AB = calloc(2, sizeof(char));

    // Same row
    if (pos1[0] == pos2[0]){

        // Both wont happen if I padded correctly...
        if (pos1[1] == 4) pos1[1] = 0;
        else pos1[1]++;

        if (pos2[1] == 4) pos2[1] = 0;
        else pos2[1]++;
        
    }
    // Same col
    else if (pos1[1] == pos2[1]){
        if (pos1[0] == 4) pos1[0] = 0;
        else pos1[0]++;

        if (pos2[0] == 4) pos2[0] = 0;
        else pos2[0]++;
    }
    // Box
    else {
        int tmp = pos1[1];
        pos1[1] = pos2[1];
        pos2[1] = tmp;

    }

    AB[0] = matrix[pos1[0]][pos1[1]];
    AB[1] = matrix[pos2[0]][pos2[1]];
    return AB;
}

char *generateCipher(char *plain, char **matrix)
{
    int len = strlen(plain);

    char *cipher = calloc(MAX_CIPHER, sizeof(char));

    char arr[2];
    int count = 0;
    char *AB;

    for (int i = 0; i < len; i += 2){
        arr[0] = plain[i];
        arr[1] = plain[i + 1];
        // Pad to make even;
        if (arr[1] == '\0') arr[1] = 'x';

        // Pads with 'x' if double letter
        if (arr[0] == arr[1]) {
            arr[1] = (arr[0] == 'x') ? 'q' : 'x';
            i--; // Adjust the index to handle padding correctly
        }

        AB = findXY(arr, matrix);

        // Add cipher to our cipher string
        cipher[count++] = AB[0];
        cipher[count++] = AB[1];

        free(AB); // Free memory allocated by findXY

    }

    cipher[count] = '\0';
    return cipher;
}

char ** generateMatrix(char * key){
    int hash[26] = {0};
    int len = strlen(key);
    int index, x = 0, y = 0;

        // Create Matrix
        char **matrix = malloc(5 * sizeof(char *));
    char *data = malloc(25 * sizeof(char));

    for (int i = 0; i < 5; i++){
        matrix[i] = data + (i * 5);
    }
    // Initialize matrix to \0
    for (int i = 0; i < 25; i++){
        data[i] = '\0';
    }

    // Read in key to matrix without repeats
    for (int i = 0; i < len; i++){
        if (key[i] == 'i') key[i] = 'j'; // Set i to j

        index = (key[i] - 'a');

        hash[index]++;

        if (hash[index] == 1){
            if (y == 5) {
                x++;
                y = 0;
            }

            matrix[x][y++] = key[i];
        }
    }

    hash['i' - 'a']++; // Get rid of i

    // Add rest of chars to matrix
    index = 0;
    while (index < 26){

        if (hash[index] == 0){

            matrix[x][y++] = index + 'a';

            if (y == 5){
                x++;
                y = 0;
            }
        }

        index++;
    }

/*//////////////////////// ERROR CHECK ////////////////////////

        for (int i = 0; i < 5; i++){
            for (int j = 0; j < 5; j++){
                printf("%c ", matrix[i][j]);
            }
            printf("\n");
        }
/////////////////////////////////////////////////////////////*/

    return matrix;
}

void freeMatrix(char ** matrix){
    free(matrix[0]);
    free(matrix);
}

int main(){

    int n;
    scanf("%d", &n);
    
    char ** matrix;
    char * cipher;

    for (int i = 0; i < n; i++){
        char key[50], plaintext[MAX_CIPHER];
        scanf("%s", key);
        scanf("%s", plaintext);

        matrix = generateMatrix(key);
        cipher = generateCipher(plaintext, matrix);

        printf("%s\n", cipher);
    }

    freeMatrix(matrix);
    return 0;
}