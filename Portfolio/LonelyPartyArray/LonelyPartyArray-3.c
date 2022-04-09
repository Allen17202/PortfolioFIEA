// Gregory Allen

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LonelyPartyArray.h"

LonelyPartyArray *createLonelyPartyArray(int num_fragments, int fragment_length)
{
	int i = 0;
	LPA *new = malloc(sizeof(LPA));

	// Check to see if malloc was successful
	if (new == NULL)
	{
		return NULL;
	}

	new->num_fragments = num_fragments;
	new->fragment_length = fragment_length;

	// Check if num fragments and their length is initialized
	if (new->num_fragments <= 0 || new->fragment_length <= 0)
	{
		return NULL;
	}

	new->num_active_fragments = 0;
	new->size = 0;
	new->fragments = malloc(sizeof(int *) * num_fragments);

	// Check if malloc fails, deallocates memory
	if (new->fragments == NULL)
	{
		free(new);
		return NULL;
	}

	new->fragment_sizes = malloc(sizeof(int) * num_fragments);

	// Check if malloc fails, deallocates memory
	if (new->fragment_sizes == NULL)
	{
		free(new->fragments);
		free(new);
		return NULL;
	}

	while (i < num_fragments)
	{
		new->fragments[i] = NULL;
		new->fragment_sizes[i] = 0;
		i++;
	}

	printf("-> A new LonelyPartyArray has emerged from the void. (capacity: %d, fragments: %d)\n",
					num_fragments * fragment_length, num_fragments);

	return new;
}

LonelyPartyArray *cloneLonelyPartyArray(LonelyPartyArray *party)
{
	int i = 0, j = 0;
	LPA *clone = malloc(sizeof(LPA));

	if (party == NULL)
	{
		return NULL;
	}

	clone->num_fragments = party->num_fragments;
	clone->fragment_length = party->fragment_length;

	// Check if num fragments and their length is initialized
	if (clone->num_fragments <= 0 || clone->fragment_length <= 0)
	{
		return NULL;
	}

	clone->num_active_fragments = party->num_active_fragments;
	clone->size = party->size;
	clone->fragments = malloc(sizeof(int *) * clone->num_fragments);


	// Check if malloc fails, deallocates memory
	if (clone->fragments == NULL)
	{
		free(clone);
		return NULL;
	}

	clone->fragment_sizes = malloc(sizeof(int) * clone->num_fragments);

	// Check if malloc fails, deallocates memory
	if (clone->fragment_sizes == NULL)
	{
		free(clone->fragments);
		free(clone);
		return NULL;
	}

	while (i < clone->num_fragments)
	{
		if (party->fragments[i] != NULL)
		{
			clone->fragments[i] = malloc(sizeof(int) * clone->fragment_length);
			// Copies data over from party to clone
			while (j < clone->fragment_length)
			{
				if (party->fragments[i][j] != UNUSED)
				{
					clone->fragments[i][j] = party->fragments[i][j];
				}
				else
				{
					clone->fragments[i][j] = UNUSED;
				}
				j++;
			}
			j = 0;
		}
		i++;
	}

	printf("-> Successfully cloned the LonelyPartyArray. (capacity: %d, fragments: %d)\n",
					clone->num_fragments * clone->fragment_length, clone->num_fragments);

	return clone;
}

LonelyPartyArray *destroyLonelyPartyArray(LonelyPartyArray *party)
{
	int i = 0;

	// Avoids seg fault if party is null, deallocates memory otherwise
	if (party == NULL)
	{
		return NULL;
	}
	else
	{
		// Work from the inside to the outside freeing memory
		while (i < party->num_fragments)
		{
			free(party->fragments[i]);
			i++;
		}
		free(party->fragments);
		free(party->fragment_sizes);
		free(party);
		printf("-> The LonelyPartyArray has returned to the void.\n");
		return NULL;
 	}
}

int set(LonelyPartyArray *party, int index, int key)
{
	int i = 0, dart, board;

	// Null Check
	if (party == NULL)
	{
		printf("-> Bloop! NULL pointer detected in set().\n");
		return LPA_FAILURE;
	}

	// Dart = Number of Darts(Fragments) at the LPA Party
	// Board = where the dart hits the board(Location)
	dart = index / party->fragment_length;
	board = index % party->fragment_length;

	// Invaid Index Check
	if (index < 0 || index > ((party->num_fragments * party->fragment_length) - 1))
	{
		printf("-> Bloop! Invalid access in set(). (index: %d, fragment: %d, offset: %d)\n", index, dart, board);
		return LPA_FAILURE;
	}

	// Fragment Check and Creation
	if (party->fragments[dart] == NULL)
	{
		party->fragments[dart] = malloc(sizeof(int) * party->fragment_length);

		while (i < party->fragment_length)
		{
			if(i == board)
			{
				party->fragments[dart][i] = key;
				party->num_active_fragments++;
			}
			else
			{
				party->fragments[dart][i] = UNUSED;
			}
			i++;
		}
		party->size++;
		party->fragment_sizes[dart]++;
		printf("-> Spawned fragment %d. (capacity: %d, indices: %d..%d)\n", dart, party->fragment_length, dart * party->fragment_length, ((dart+1) * party->fragment_length) - 1);
	}

	// Check to see if dart hits the board at the correct Location
	// Puts key into that Location otherwise
	if (party->fragments[dart][board] != key)
	{
		if (party->fragments[dart][board] == UNUSED)
		{
			party->size++;
			party->fragment_sizes[dart]++;
		}
		party->fragments[dart][board] = key;
	}
	return LPA_SUCCESS;
}

int get(LonelyPartyArray *party, int index)
{
	int dart, board;

	// Null check on Party
	if (party == NULL)
	{
		printf("-> Bloop! NULL pointer detected in get().\n");
		return LPA_FAILURE;
	}

	// Dart = Number of Darts(Fragments) at the LPA Party
	// Board = where the dart hits the board(Location)
	dart = index / party->fragment_length;
	board = index % party->fragment_length;

	// Check for Invalid Index
	if (index < 0 || index > (party->num_fragments * party->fragment_length - 1))
	{
		printf("-> Bloop! Invalid access in get(). (index: %d, fragment: %d, offset: %d)\n", index, dart, board);
		return LPA_FAILURE;
	}

	// Returns whatever is in the fragments array
	if (party->fragments[dart] != NULL)
	{
		return party->fragments[dart][board];
	}
	else
	{
		return UNUSED;
	}
}

int delete(LonelyPartyArray *party, int index)
{
	int dart, board;

	// Null Party Check
	if (party == NULL)
	{
		printf("-> Bloop! NULL pointer detected in delete().\n");
		return LPA_FAILURE;
	}

	// Dart = Number of Darts(Fragments) at the LPA Party
	// Board = where the dart hits the board(Location)
	dart = index / party->fragment_length;
	board = index % party->fragment_length;

	// Valid index Check
	if (index < 0 || index > ((party->num_fragments * party->fragment_length) - 1))
	{
		printf("-> Bloop! Invalid access in delete(). (index: %d, fragment: %d, offset: %d)\n", index, dart, board);
		return LPA_FAILURE;
	}

	if (party->fragments[dart] == NULL || party->fragments[dart][board] == UNUSED)
	{
		return LPA_FAILURE;
	}

	// Deletion where index is pointing, Checks if location is being used
	if (party->fragments[dart][board] != UNUSED)
	{
		party->fragments[dart][board] = UNUSED;
		party->size--;
		party->fragment_sizes[dart]--;
		if (party->fragment_sizes[dart] == 0)
		{
			free(party->fragments[dart]);
			party->fragments[dart] = NULL;
			party->num_active_fragments--;
			printf("-> Deallocated fragment %d. (capacity: %d, indices: %d..%d)\n", dart, party->fragment_length, dart * party->fragment_length, ((dart+1) * party->fragment_length)-1);
		}
	}
	return LPA_SUCCESS;
}

int containsKey(LonelyPartyArray *party, int key)
{
	int i = 0, j = 0;

	// Null Party Check
	if (party == NULL)
	{
		return 0;
	}

	while (i < party->num_fragments)
	{
		//Checks if fragment is null if not then goes within fragment
		if (party->fragments[i] != NULL)
		{
			while (j < party->fragment_length)
			{
				//Checks if key is in that fragment if not then continues
				if (party->fragments[i][j] == key)
				{
					return 1;
				}
				j++;
			}
		}
		i++;
	}
	return 0;
}

int isSet(LonelyPartyArray *party, int index)
{
	int dart, board;

	// Null Party Check
	if (party == NULL)
	{
		return 0;
	}

	// Dart = Number of Darts(Fragments) at the LPA Party
	// Board = where the dart hits the board(Location)
	dart = index / party->fragment_length;
	board = index % party->fragment_length;

	// Valid index Check
	if (index < 0 || index > ((party->num_fragments * party->fragment_length) - 1))
	{
		return 0;
	}

	//Checks if value is there
	if (party->fragments[dart] == NULL || party->fragments[dart][board] == UNUSED)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int printIfValid(LonelyPartyArray *party, int index)
{
	int dart, board;

	//Null Party Check
	if (party == NULL)
	{
		return LPA_FAILURE;
	}

	// Dart = fragments
	// Board = location
	dart = index / party->fragment_length;
	board = index % party->fragment_length;

	// Valid index check
	if (index < 0 || index > party->fragment_length * party->num_fragments - 1)
	{
    return LPA_FAILURE;
	}

	// Checks if fragment is even being used
	if (party->fragments[dart] == NULL)
	{
		return LPA_FAILURE;
	}

	// Returns value stored at index or fails
  if (party->fragments[dart][board] != UNUSED)
	{
		printf("%d\n", party->fragments[dart][board]);
		return LPA_SUCCESS;
	}
	else
	{
		return LPA_FAILURE;
	}
}

LonelyPartyArray *resetLonelyPartyArray(LonelyPartyArray *party)
{
	int i = 0;

	// Null Check Party
	if (party == NULL)
	{
		printf("“-> Bloop! NULL pointer detected in resetLonelyPartyArray()");
		return party;
	}

	// Resets fragments
	while (i < party->num_fragments)
	{
		while (party->fragment_sizes[i] > 0)
		{
			free(party->fragments[i]);
			party->fragments[i] = NULL;
			party->fragment_sizes[i] = 0;
		}
		i++;
	}
	party->size = 0;
	party->num_active_fragments = 0;
	printf("-> The LonelyPartyArray has returned to its nascent state. (capacity: %d, fragments: %d)\n", party->fragment_length * party->num_fragments, party->num_fragments);
	return party;
}

int getSize(LonelyPartyArray *party)
{
	// Returns size
	if (party != NULL)
	{
		return party->size;
	}
	else
	{
		return -1;
	}
}

int getCapacity(LonelyPartyArray *party)
{
	// Capacity of LPA
	if (party != NULL)
	{
		return party->num_fragments * party->fragment_length;
	}
	else
	{
		return -1;
	}
}

int getAllocatedCellCount(LonelyPartyArray *party)
{
	// Max Number of Elements without any new fragments
	if (party != NULL)
	{
		return party->num_active_fragments * party->fragment_length;
	}
	else
	{
		return -1;
	}
}

long long unsigned int getArraySizeInBytes(LonelyPartyArray *party)
{
	// Size of standard array
	if (party != NULL)
	{
		return (long long unsigned int)(sizeof(int) * (party->num_fragments * party->fragment_length));
	}
	else
	{
		return 0;
	}
}

long long unsigned int getCurrentSizeInBytes(LonelyPartyArray *party)
{
	// Number of bytes taken up by LPA
	if (party != NULL)
	{
		return (long long unsigned int)(sizeof(LPA*) + sizeof(LPA) + (sizeof(int *) * party->num_fragments) +
			(sizeof(int) * party->num_fragments) + (sizeof(int) * party->num_active_fragments * party->fragment_length));
	}
	else
	{
		return 0;
	}
}

double difficultyRating(void)
{
	return 4.5;
}

double hoursSpent(void)
{
	return 25;
}
