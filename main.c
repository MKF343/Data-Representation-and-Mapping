#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "convert.h"

int main() {
    //Open the file
	FILE* file = fopen("a2_test.txt", "r");
    //Check if file opened successfully
	if (file == NULL) {
		printf("Error: Could not open file\n");
		return 1;
	}
	char line[256];
    int test_num = 1;
    int numPassed = 0;
    //read the file line by line
    while (fgets(line, sizeof(line), file) != NULL) {
        //Skip comment lines and blanks
        if (line[0] == '#' || line[0] == '\n') {
            continue;
        }
        //Direct Mapping Functions (String Input)
        if (strstr(line, "oct_to_bin")) {
            char expectedStr[100];
            char actualStr[100];
            char inputStr[100];

            sscanf(line, "%*s %s %s", inputStr, expectedStr);

            oct_to_bin(inputStr,actualStr);

            if (strcmp(actualStr, expectedStr) == 0) {
                printf("Test %d: oct_to_bin(\"%s\") -> Expected: \"%s\", Got: \"%s\" [PASS]\n",test_num, inputStr, expectedStr, actualStr);
                numPassed++;
            }
            else {
                printf("Test %d: oct_to_bin(\"%s\") -> Expected: \"%s\", Got: \"%s\" [FAIL]\n", test_num, inputStr, expectedStr, actualStr);
            }

        }
        else if (strstr(line, "oct_to_hex")) {
            char expectedStr[100];
            char actualStr[100];
            char inputStr[100];

            sscanf(line, "%*s %s %s", inputStr, expectedStr);

            oct_to_hex(inputStr, actualStr);

            if (strcmp(actualStr, expectedStr) == 0) {
                printf("Test %d: oct_to_hex(\"%s\") -> Expected: \"%s\", Got: \"%s\" [PASS]\n", test_num, inputStr, expectedStr, actualStr);
				numPassed++;
            }
            else {
                printf("Test %d: oct_to_hex(\"%s\") -> Expected: \"%s\", Got: \"%s\" [FAIL]\n", test_num, inputStr, expectedStr, actualStr);
            }

        }
        else if (strstr(line, "hex_to_bin")) {
            char expectedStr[100];
            char actualStr[100];
            char inputStr[100];

            sscanf(line, "%*s %s %s", inputStr, expectedStr);

            hex_to_bin(inputStr, actualStr);

            if (strcmp(actualStr, expectedStr) == 0) {
                printf("Test %d: hex_to_bin(\"%s\") -> Expected: \"%s\", Got: \"%s\" [PASS]\n", test_num, inputStr, expectedStr, actualStr);
                numPassed++;
            }
            else {
                printf("Test %d: hex_to_bin(\"%s\") -> Expected: \"%s\", Got: \"%s\" [FAIL]\n", test_num, inputStr, expectedStr, actualStr);
            }

        }
        //Signed Representation Functions (Integer Input)
        else if (strstr(line, "to_sign_magnitude")) {
            char inputNumStr[20];
            char expectedStr[100];
            char actualStr[100];

            sscanf(line, "%*s %s %s", inputNumStr, expectedStr);

            int32_t num = atoi(inputNumStr); //Convert string input to int

            to_sign_magnitude(num, actualStr);

            if (strcmp(actualStr, expectedStr) == 0) {
                printf("Test %d: to_sign_magnitude(%d) -> Expected: \"%s\", Got: \"%s\" [PASS]\n", test_num, num, expectedStr, actualStr);
                numPassed++;
            }
            else {
                printf("Test %d: to_sign_magnitude(%d) -> Expected: \"%s\", Got: \"%s\" [FAIL]\n", test_num, num, expectedStr, actualStr);
            }

        }
        else if (strstr(line, "to_ones_complement")) {
            char inputNumStr[20];
            char expectedStr[100];
            char actualStr[100];

            sscanf(line, "%*s %s %s", inputNumStr, expectedStr);

            int32_t num = atoi(inputNumStr);//Convert string input to int

            to_ones_complement(num, actualStr);
            
            if (strcmp(actualStr, expectedStr) == 0) {
                printf("Test %d: to_ones_complement(%d) -> Expected: \"%s\", Got: \"%s\" [PASS]\n", test_num, num, expectedStr, actualStr);
                numPassed++;
            }
            else {
                printf("Test %d: to_ones_complement(%d) -> Expected: \"%s\", Got: \"%s\" [FAIL]\n", test_num, num, expectedStr, actualStr);
            }

        }
        else if (strstr(line, "to_twos_complement")) {
            char inputNumStr[20];
            char expectedStr[100];
            char actualStr[100];

            sscanf(line, "%*s %s %s", inputNumStr, expectedStr);

            int32_t num = atoi(inputNumStr);//Convert string input to int

            to_twos_complement(num, actualStr);

            if (strcmp(actualStr, expectedStr) == 0) {
                printf("Test %d: to_twos_complement(%d) -> Expected: \"%s\", Got: \"%s\" [PASS]\n", test_num, num, expectedStr, actualStr);
                numPassed++;
            }
            else {
                printf("Test %d: to_twos_complement(%d) -> Expected: \"%s\", Got: \"%s\" [FAIL]\n", test_num, num, expectedStr, actualStr);
            }

        }
        //increment test number
        test_num++;
    }
    printf("Summary: %d/%d tests passed\n", numPassed, test_num - 1);
    //close file when finished
	fclose(file);
	return 0;
}
