/*
  loop through an array of strings and print the last string in the array that is a 
  duplicate of any other string in the array
*/

#include "DupeyDupe.h"
#include <stdio.h>
#include <string.h>

double difficultyRating(void);
double hoursSpent(void);

int main(int argc, char **argv)
{
  int i, j, duplicateFlag = 0, dupeFlag = 0;

    for (i = (argc - 1); i > 0; i--)
    {
      if (duplicateFlag == 1)
        break;
      else
      {
        for (j = (i - 1); j > 0; j--)
        {
          if (duplicateFlag == 1)
            break;
          else
          {
            if (strcmp (argv[i], argv[j]) == 0)
            {
              printf("%s\n", argv[i]);
              duplicateFlag = 1;
            }
          }
        }
      }
    }

    for (i = (argc - 1); i > 0; i--)
    {
      if (dupeFlag == 1)
        break;
      else
      {
        for (j = (i - 1); j > 0; j--)
        {
          if (dupeFlag == 1)
            break;
          else
          {
            if (strcmp(argv[i], "dupe") == 0 && strcmp(argv[j], "dupe") == 0)
            {
              if (i - 1 == j)
              {
                printf("dupe dupe!\n");
                dupeFlag = 1;
              }
            }
          }
        }
      }
    }

    if (duplicateFlag == 0)
       printf("no dupey dupe :(\n");

return 0;
}


double difficultyRating(void)
{
  return 3.0;
}

double hoursSpent(void)
{
  return 4.5;
}
