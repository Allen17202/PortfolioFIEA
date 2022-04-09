// Gregory Allen
// COP 3502C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "SneakyRooks.h"

int allTheRooksAreSafe(char **rookStrings, int numRooks, int boardSize)
{
	int i;
	Coordinate *point = malloc(sizeof(Coordinate) * numRooks);
	int *columns = NULL;
	int *rows = NULL;
	int maxCol = 0;
	int maxRow = 0;

	//If string is empty, rook are safe, exit program
	if (rookStrings[0][0] == '\0')
	{
		free (point);
		return 1;
	}

	//Places strings in array into Coordinates and finds max col and row
	for (i = 0; i < numRooks; i++)
	{
		parseCoordinateString(rookStrings[i], &point[i]);

		// Finds Max Column
		if (maxCol < point[i].col)
		{
			maxCol = point[i].col;
		}

		//Finds Max Row
		if (maxRow < point[i].row)
		{
			maxRow = point[i].row;
		}
	}

	columns = calloc(maxCol + 1, sizeof(int));
	rows = calloc(maxRow + 1, sizeof(int));

	//Uses array of coordinates place column and row values into
	//the columns and rows arrays
	for (i = 0; i < numRooks; i++)
	{
		//If there is already a value there, no longer unique and can exit program
		if (columns[point[i].col] == 0)
		{
			columns[point[i].col] = point[i].col;
		}
		else
		{
			free (point);
			free (columns);
			free (rows);
			return 0;
		}

		//Checks for values in the row, if not equal to 0 then exit program
		if (rows[point[i].row] == 0)
		{
			rows[point[i].row] = point[i].row;
		}
		else
		{
			free (point);
			free (columns);
			free (rows);
			return 0;
		}
	}

	//Free memory, No collisions occured so rooks must be safe
	free (point);
	free (columns);
	free (rows);
	return 1;
	}

//Power function for Parsing through String
int math(char c, int base, int exp)
{
	//Loop to get base to the power of exp
	int count = 1;
	for (int i = 0; i < exp - 1; i++)
	{
		count *= base;
	}

	//For the case of c being a digit, so Base = 10
	if (isdigit(c) != 0)
	{
		return atoi(&c) * count;
	}

	//For the case of c being a letter
	return (c - 'a' + 1) * count;
}


void parseCoordinateString(char *rookString, Coordinate *rookCoordinate)
{
	int i;
	int length = strlen(rookString);
	int count = 0;
	int stringCount = 0;
	int digiCount = 0;
	int altCounter = 0;

	//Transverse through string until digit is encountered
	for (i = 0; i < length; i++)
	{
		//Letter check to add to count
		if (isalpha(rookString[i]))
		{
			count++;
		}

		//Digit check to stop loop
		if (isdigit(rookString[i]))
		{
			digiCount = length - count;
			break;
		}
	}

	//Transverse through string to get numerical equivilant of col and rows
	for (i = 0; i < length; i++)
	{
		//Computes integer version of the string representing columns
		if (isalpha(rookString[i]) != 0)
		{
			stringCount += math(rookString[i], 26 ,count);
			count--;
		}

		//Once digit is encountered, computes int of string for rows
		if (isdigit(rookString[i]) != 0)
		{
			altCounter += math(rookString[i], 10, digiCount);
			digiCount--;
		}
	}

	//Puts collected data into Coordinate
	rookCoordinate->col = stringCount;
	rookCoordinate->row = altCounter;
}

double difficultyRating(void)
{
	return 4;
}

double hoursSpent(void)
{
	return 12;
}
