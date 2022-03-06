// Zarai Huete
// COP 3250, Spring 2019
// NID: za780541

#include <stdio.h>
#include <stdlib.h>
#include "LonelyPartyArray.h"

// Helper Functions
int calculateFragmentNum(LonelyPartyArray *party, int index);
int findCell(LonelyPartyArray *party, int index);
int maxValue(LonelyPartyArray *party);

// Helper Functions
int calculateFragmentNum(LonelyPartyArray *party, int index)
{
  return (index / (party->fragment_length));
}

int calculateCell(LonelyPartyArray *party, int index)
{
  return (index % (party->fragment_length));
}

int maxValue(LonelyPartyArray *party)
{
  return ((party->num_fragments) * (party->fragment_length) - 1);
}

// Required Functions
LonelyPartyArray *createLonelyPartyArray(int num_fragments, int fragment_length)
{
  int i;

  if (num_fragments <= 0 || fragment_length <= 0)
    return NULL;

  else
  {
    // Allocate space for LPA struct
    LPA *party = malloc(sizeof(LPA));

    if (party == NULL)
    {
      free(party);
      return NULL;
    }

    // Initialize non-pointer members
    party->num_fragments = num_fragments;
    party->fragment_length = fragment_length;
    party->num_active_fragments = 0;
    party->size = 0;

    // Allocate space for fragments
    party->fragments = malloc(sizeof(int *) * num_fragments);

    if (party->fragments == NULL)
    {
      free(party->fragments);
      return NULL;
    }

    // Initialize all pointers to NULL
    for (i = 0; i < num_fragments; i++)
      party->fragments[i] = NULL;

    // Allocate space for fragment_sizes
    party->fragment_sizes = malloc(sizeof(int) * num_fragments);

    if (party->fragment_sizes == NULL)
    {
     free(party->fragment_sizes);
     return NULL;
    }

    // Initialize fragment_sizes values to 0
    for (i = 0; i < num_fragments; i++)
      party->fragment_sizes[i] = 0;

    printf("-> A new LonelyPartyArray has emerged from the void.");
    printf(" (capacity: %d", (num_fragments * fragment_length));
    printf(", fragments: %d)\n", num_fragments);

    return party;
    }
  }


LonelyPartyArray *destroyLonelyPartyArray(LonelyPartyArray *party)
{
  int i;
  if (party != NULL)
  {
    // Free fragment_sizes
    free(party->fragment_sizes);

    // Free 2D array
    for (i = 0; i < (party->num_fragments); i++)
    {
      free(party->fragments[i]);
    }

    free(party->fragments);

    // Free structure
    free(party);

    printf("-> The LonelyPartyArray has returned to the void.\n");

    return NULL;
  }
  return NULL;
}

// Optional function
LonelyPartyArray *cloneLonelyPartyArray(LonelyPartyArray *party)
{
  return NULL;
}

int set(LonelyPartyArray *party, int index, int key)
{
  int frag_num, frag_cell, i, max_value;
  int lowest_index, highest_index;

  // Check party is not NULL
  if (party == NULL)
  {
    printf("-> Bloop! NULL pointer detected in set().\n");

    return LPA_FAILURE;
  }
  else
  {
    // Max value of index
    max_value = maxValue(party);

    // Find fragment and cell to enter key
    frag_num = calculateFragmentNum(party,index);
    frag_cell = calculateCell(party,index);

    // Check index
    if (index < 0 || index > max_value)
    {
        printf("-> Bloop! Invalid access in set(). ");
        printf("(index: %d, fragment: %d", index, frag_num);
        printf(", offset: %d)\n", frag_cell);

        return LPA_FAILURE;
    }
    // Check if fragment is NULL
    else if ((party->fragments[frag_num])==NULL)
    {
      // Allocate space for fragment
      party->fragments[frag_num] = malloc(sizeof(int *) * party->fragment_length);

      // Assign unused to cells
      for (i = 0; i < party->fragment_length; i++)
        party->fragments[frag_num][i] = UNUSED;

      // Update active fragments
      party->num_active_fragments++;
      party->fragment_sizes[frag_num]++;

      // Store key
      party->fragments[frag_num][frag_cell] = key;

      // Update Size
      party->size++;

      // Find lowest/hightest index
      lowest_index = frag_num * (party->fragment_length);
      highest_index = ((party->fragment_length) * (frag_num+1)-1);

      printf("-> Spawned fragment %d. ", frag_num);
      printf("(capacity: %d, indices: ", party->fragment_length);
      printf("%d..%d)\n", lowest_index, highest_index);

      return LPA_SUCCESS;
    }
    else if ((party->fragments[frag_num][frag_cell])==UNUSED)
    {
      party->fragments[frag_num][frag_cell] = key;

      // Update Size
      party->size++;

      // Update fragment size
      party->fragment_sizes[frag_num]++;

      return LPA_SUCCESS;
    }
    else
    {
      party->fragments[frag_num][frag_cell] = key;
      return LPA_SUCCESS;
    }
  }

}

int get(LonelyPartyArray *party, int index)
{
  int frag_num, frag_cell, max_value;

  if (party == NULL)
  {
    printf("-> Bloop! NULL pointer detected in get().\n");
    return LPA_FAILURE;
  }
 else
 {
   max_value = maxValue(party);
   frag_num = calculateFragmentNum(party,index);
   frag_cell = calculateCell(party,index);

   if (index < 0 || index > max_value)
     {
       printf("-> Bloop! Invalid access in get(). ");
       printf("(index: %d, fragment: %d", index, frag_num);
       printf(", offset: %d)\n", frag_cell);

       return LPA_FAILURE;
     }
   else if((party->fragments[frag_num])==NULL)
     return UNUSED;
   else if (party->fragments[frag_num][frag_cell] != UNUSED)
     return (party->fragments[frag_num][frag_cell]);
 }
}

int delete(LonelyPartyArray *party, int index)
{
  int frag_num, frag_cell, max_value, i;
  int lowest_index, highest_index;

  if (party == NULL)
  {
    printf("-> Bloop! NULL pointer detected in delete().\n");
    return LPA_FAILURE;
  }
  else
  {
  max_value = maxValue(party);
  frag_num = calculateFragmentNum(party,index);
  frag_cell = calculateCell(party,index);

  if (index < 0 || index > max_value)
  {
     printf("-> Bloop! Invalid access in delete(). ");
     printf("(index: %d, fragment: %d", index, frag_num);
     printf(", offset: %d)\n", frag_cell);

     return LPA_FAILURE;
   }
   else if ((party->fragments[frag_num])== NULL)
   {
     return LPA_FAILURE;
   }
   else if((party->fragments[frag_num][frag_cell]) == UNUSED)
   {
     return LPA_FAILURE;
   }
   else if ((party->fragments[frag_num][frag_cell]) != UNUSED)
   {
    // Set to unused
    party->fragments[frag_num][frag_cell] = UNUSED;

    party->size--;

    party->fragment_sizes[frag_num]--;


      if (party->fragment_sizes[frag_num] == 0)
      {

        // Deallocate array
        free(party->fragments[frag_num]);

        // Set point in the strcut's fragments array to NULL
        party->fragments[frag_num] = NULL;

        // Update struct's num_active_fragments
        party->num_active_fragments--;

        lowest_index = frag_num * (party->fragment_length);
        highest_index = ((party->fragment_length) * (frag_num+1)-1);

        printf("-> Deallocated fragment %d. ", frag_num);
        printf("(capacity: %d, indices: ", party->fragment_length);
        printf("%d..%d)\n", lowest_index, highest_index);
      }
    return LPA_SUCCESS;
  }
 }
}

int containsKey(LonelyPartyArray *party, int key)
{
  int i, j;

  if (party == NULL)
    return 0;
  else
  {
    for (i = 0; i < (party->num_fragments); i++)
    {
      for (j = 0; j < (party->fragment_length); j++)
      {
        if (party->fragments[i] != NULL)
        {
          if (party->fragments[i][j] == key)
            return 1;
        }
      }
    }
  }
}

int isSet(LonelyPartyArray *party, int index)
{
  int max_value, frag_num, frag_cell;

  if (party == NULL)
    return 0;
  else
  {
    max_value = maxValue(party);
    frag_num = calculateFragmentNum(party, index);
    frag_cell = calculateCell(party, index);

    if (index < 0 || index > max_value)
      return 0;
    else if ((party->fragments[frag_num]) == NULL)
      return 0;
    else if ((party->fragments[frag_num][frag_cell]) == UNUSED)
      return 0;
    else if ((party->fragments[frag_num][frag_cell]) != UNUSED)
      return 1;
  }

}

int printIfValid(LonelyPartyArray *party, int index)
{
  int frag_num, frag_cell, max_value;


  if (party == NULL)
    return LPA_FAILURE;
  else
  {
    max_value = maxValue(party);
    frag_num = calculateFragmentNum(party,index);
    frag_cell = calculateCell(party,index);

    if (index < 0 || index > max_value)
      return LPA_FAILURE;
    else if((party->fragments[frag_num]) == NULL)
      return LPA_FAILURE;
   else if((party->fragments[frag_num][frag_cell]) == UNUSED)
      return LPA_FAILURE;
   else if ((party->fragments[frag_num][frag_cell]) != UNUSED)
   {
    printf("%d\n",(party->fragments[frag_num][frag_cell]));
    return LPA_SUCCESS;
   }
 }
}

LonelyPartyArray *resetLonelyPartyArray(LonelyPartyArray *party)
{
  int i, capacity;

  if (party == NULL)
  {
    printf("-> Bloop! NULL pointer detected in resetLonelyPartyArray().");
    return party;
  }
  else
  {
    // Deallocate any array fragments that are active
    for (i = 0; i < (party->num_fragments); i++)
    {
      if (party->fragments[i] != NULL)
        free(party->fragments[i]);
    }
    // Reset all values in the struct's fragments array
    for (i = 0; i < (party->num_fragments); i++)
    {
      if (party->fragments[i] != NULL)
        party->fragments[i] = NULL;
    }
    // Reset all values in the struct's fragment_sizes array
    for (i = 0; i < (party->num_fragments); i++)
    {
      if (party->fragment_sizes[i] != 0)
        party->fragment_sizes[i] = 0;
    }
    // Reset size and num_active_fragments
    party->size = 0;
    party->num_active_fragments = 0;

    capacity = (party->num_fragments) * (party->fragment_length);

    printf("-> The LonelyPartyArray has returned to its nascent state. ");
    printf("(capacity: %d, ", capacity);
    printf("fragments: %d)\n", party->num_fragments);

    return party;
  }
}

int getSize(LonelyPartyArray *party)
{
  if (party== NULL)
    return -1;
  else
    return (party->size);
}

int getCapacity(LonelyPartyArray *party)
{
  if (party== NULL)
    return -1;
  else
    return (party->num_fragments) * (party->fragment_length);
}

int getAllocatedCellCount(LonelyPartyArray *party)
{
  if (party== NULL)
    return -1;
  else
    return (party->num_active_fragments)*(party->fragment_length);
}

long long unsigned int getArraySizeInBytes(LonelyPartyArray *party)
{
  if (party== NULL)
    return 0;
  else
    return ((long long unsigned int)(sizeof(int))*(party->num_fragments)
            *(party->fragment_length));
}

long long unsigned int getCurrentSizeInBytes(LonelyPartyArray *party)
{
  int bytLPAPtr, bytLPA, bytFrag;
  long long unsigned int bytFragSize, bytActiveFrag;

  if (party== NULL)
    return 0;
  else
  {
    bytLPAPtr = sizeof(party);
    bytLPA = (long long unsigned int)sizeof(LPA);
    bytFrag = (long long unsigned int)sizeof(int *) * (party->num_fragments);
    bytFragSize = (long long unsigned int)sizeof(int)
                   *(party->num_fragments);
    bytActiveFrag = (party->fragment_length) * (long long unsigned int)sizeof(int)
                    * (party->num_active_fragments);

    return (bytLPAPtr + bytLPA + bytFrag + bytFragSize + bytActiveFrag);
  }

}

double difficultyRating(void)
{
  return 4.0;
}

double hoursSpent(void)
{
    return 15.0;
}
