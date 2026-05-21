/* ============================================================
    Mini Project: Text Pattern Search System using KMP Algorithm
    Algorithm   : Knuth-Morris-Pratt (KMP) Algorithm
    Author      : [Student Name]  |  USN: [USN]
    Date        : [DD-MM-YYYY]
    Description : Searches a pattern efficiently inside a text
   ============================================================ */

/* --- Include necessary header files --- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* --- Constants and Macro Definitions --- */

#define MAX_TEXT 1000
#define MAX_PATTERN 100

/* ============================================================
    Module / Function 1: computeLPS
    Purpose : Computes the Longest Prefix Suffix (LPS) array
    Input   : pattern[] - pattern string
              m - length of pattern
              lps[] - array to store LPS values
    Output  : Stores LPS values in lps array
   ============================================================ */

void computeLPS(char pattern[], int m, int lps[]) {

    int len = 0;

    lps[0] = 0;

    int i = 1;

    while (i < m) {

        if (pattern[i] == pattern[len]) {

            len++;
            lps[i] = len;
            i++;
        }

        else {

            if (len != 0) {

                /* Move to previous longest prefix suffix */
                len = lps[len - 1];
            }

            else {

                lps[i] = 0;
                i++;
            }
        }
    }
}

/* ============================================================
    Module / Function 2: KMPSearch
    Purpose : Searches pattern inside the text using KMP
    Input   : text[] - main text string
              pattern[] - pattern string to search
    Output  : Displays positions where pattern is found
   ============================================================ */

void KMPSearch(char text[], char pattern[]) {

    int n = strlen(text);
    int m = strlen(pattern);
if (m == 0) {
    printf("Pattern cannot be empty.\n");
    return;
}
    int lps[m];

    /* Generate LPS array */
    computeLPS(pattern, m, lps);

    int i = 0;
    int j = 0;

    int found = 0;

    while (i < n) {

        /* If characters match, move both indices */
        if (pattern[j] == text[i]) {

            i++;
            j++;
        }

        /* Full pattern matched */
        if (j == m) {

            printf("Pattern found at position %d\n", i - j);

            found = 1;

            /* Continue searching for next occurrence */
            j = lps[j - 1];
        }

        else if (i < n && pattern[j] != text[i]) {

            if (j != 0) {

                /* Use LPS to skip unnecessary comparisons */
                j = lps[j - 1];
            }

            else {

                i++;
            }
        }
    }

    if (!found) {

        printf("Pattern not found in the text.\n");
    }
}

/* ============================================================
    Module / Function 3: main
    Purpose : Reads input and starts pattern searching
    Input   : User entered text and pattern
    Output  : Displays search results
   ============================================================ */

int main() {

    char text[MAX_TEXT];
    char pattern[MAX_PATTERN];

    printf("====================================\n");
    printf(" TEXT PATTERN SEARCH SYSTEM - KMP\n");
    printf("====================================\n\n");

    printf("Enter the text:\n");
    fgets(text, sizeof(text), stdin);

    text[strcspn(text, "\n")] = '\0';

    printf("Enter the pattern to search: ");
    fgets(pattern, sizeof(pattern), stdin);

    pattern[strcspn(pattern, "\n")] = '\0';

    printf("\nSearching...\n\n");

    KMPSearch(text, pattern);

    return 0;
}