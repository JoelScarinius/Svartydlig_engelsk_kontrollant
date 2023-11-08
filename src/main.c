#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void saveTal(char *tal, char *buffTal)
{
    for (int i = 0, j = 0; i <= strlen(tal); i++)
    {
        buffTal[i] = tal[i];
    }
}

void setEndOfWord(char *buffTal, char *specialCharacters, int idx, char *end)
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

void decrypt(char *tal, char *vokabulär[])
{
    int idx = 0;
    char *buffTal = (char *)calloc(strlen(tal), sizeof(char));

    saveTal(tal, buffTal);

    char *specialCharacters = strtok(tal, " ?!,.");

    while (specialCharacters != NULL)
    {
        idx += strlen(specialCharacters);
        char *end = (char *)calloc(strlen(buffTal), sizeof(char));
        int i = 0;
        while (vokabulär[i] != NULL)
        {
            if (strlen(specialCharacters) == strlen(vokabulär[i]))
            {
                int matchning = 1;
                for (int j = 0; j < strlen(specialCharacters); j++)
                {
                    if (specialCharacters[j] != '*' && specialCharacters[j] != vokabulär[i][j])
                    {
                        matchning = 0;
                        break;
                    }
                }
                if (matchning)
                {
                    strcpy(specialCharacters, vokabulär[i]);
                    break;
                }
            }
            i++;
        }
        setEndOfWord(buffTal, specialCharacters, idx, end);
        printf("%s%s", specialCharacters, end);
        specialCharacters = strtok(NULL, " ?!,.");
    }
}

int main()
{
    char tal[] = "***lo w***d!";
    char *vokabulär[] = {"hello", "world"};
    // char tal[] = "b**l, w*ak!";
    // char *vokabulär[] = {"cell", "bell", "week", "weak"};

    decrypt(tal, vokabulär);

    return 0;
}