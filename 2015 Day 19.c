#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RULES 100
#define MAX_CHEM_LEN 1000
#define MAX_MOLECULES 1000

int main() {
    char inputs[MAX_RULES][MAX_CHEM_LEN];
    char products[MAX_RULES][MAX_CHEM_LEN];
    int rulesCount = 0;

    // Read Conversion Table
    printf("Paste Conversion Table Here (end with an empty line):\n");
    while (1) {
        char line[MAX_CHEM_LEN];
        if (!fgets(line, sizeof(line), stdin) || strcmp(line, "\n") == 0) {
            break;
        }
        sscanf(line, "%s => %s", inputs[rulesCount], products[rulesCount]);
        rulesCount++;
    }

    char chemList[MAX_CHEM_LEN];
    printf("Paste Chemical String Here: ");
    fgets(chemList, sizeof(chemList), stdin);
    chemList[strcspn(chemList, "\n")] = 0; // Remove newline character

    char molecules[MAX_MOLECULES][MAX_CHEM_LEN];
    int moleculeCount = 0;

    // Process chemList
    for (int i = 0; i < rulesCount; i++) {
        char *pos = chemList;
        while ((pos = strstr(pos, inputs[i])) != NULL) {
            char newMolecule[MAX_CHEM_LEN];
            strncpy(newMolecule, chemList, pos - chemList);
            newMolecule[pos - chemList] = '\0';
            strcat(newMolecule, products[i]);
            strcat(newMolecule, pos + strlen(inputs[i]));

            // Check for uniqueness
            int isUnique = 1;
            for (int j = 0; j < moleculeCount; j++) {
                if (strcmp(molecules[j], newMolecule) == 0) {
                    isUnique = 0;
                    break;
                }
            }

            if (isUnique) {
                strcpy(molecules[moleculeCount++], newMolecule);
            }

            pos++;
        }
    }

    printf("Number of distinct molecules: %d\n", moleculeCount);

    return 0;
}
