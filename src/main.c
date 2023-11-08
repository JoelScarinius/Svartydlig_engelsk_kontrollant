#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Saves the original tal in a buffer
void saveTal(char *tal, char *buffTal)
{
    for (int i = 0, j = 0; i <= strlen(tal); i++)
    {
        buffTal[i] = tal[i];
    }
}
// Sets the end of the word
void setEndOfWord(char *buffTal, int idx, char *end)
{
    for (int i = idx, j = 0; i <= strlen(buffTal); i++)
    {
        if (buffTal[i] == '?' || buffTal[i] == '!' || buffTal[i] == ',' || buffTal[i] == '.' || buffTal[i] == ' ')
        {
            end[j] = buffTal[i];
            j++;
        }
        else if (j > 0)
        {
            break;
        }
    }
}

// Decodes the tal
void decode(char *tal, char *vokabulär[])
{
    int idx = 0;
    char *buffTal = (char *)calloc(strlen(tal), sizeof(char));

    saveTal(tal, buffTal);

    char *encodedWord = strtok(tal, " ?!,.");

    while (encodedWord != NULL)
    {
        char *end = (char *)calloc(strlen(buffTal), sizeof(char));
        char *decodedWord = (char *)calloc(strlen(encodedWord), sizeof(char));
        idx += strlen(encodedWord);
        int i = 0;

        // Checks if the word is in the vokabulär
        while (vokabulär[i] != NULL)
        {
            if (strlen(encodedWord) == strlen(vokabulär[i]))
            {
                int match = 1;
                for (int j = 0; j < strlen(encodedWord); j++)
                {
                    if (encodedWord[j] != '*' && encodedWord[j] != vokabulär[i][j])
                    {
                        match = 0;
                        break;
                    }
                }
                if (match)
                {
                    // Sets the word to the decoded word
                    strcpy(decodedWord, vokabulär[i]);
                    break;
                }
            }
            i++;
        }
        setEndOfWord(buffTal, idx, end);
        printf("%s%s", decodedWord, end);
        encodedWord = strtok(NULL, " ?!,.");
        free(decodedWord);
        free(end);
    }
    free(buffTal);
}

int main()
{
    char tal[] = "***lo w***d!";
    char *vokabulär[] = {"hello", "world"};
    // char tal[] = "b**l, w*ak!";
    // char *vokabulär[] = {"cell", "bell", "week", "weak"};

    decode(tal, vokabulär);

    return 0;
}