// Gregory Allen

#include "Glowworm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double difficultyRating(void)
{
	return 4;
}

double hoursSpent(void)
{
	return 15;
}

void printGlowworm(int tail, int head, int body, int maxLength, int flag)
{
		// Prints the  Glowworm based on position and length
		// The if-elseif accounts for all of the worms body parts
		for(int i = 0; i <= (maxLength-1); i++)
		{
			if (i == tail) {
				printf("~");
			}
			else if(i > tail && i < body) {
				printf("o");
			}
			else if(tail == (maxLength - 1) && i < body) {
				printf("o");
			}
			else if (i < body && tail > body) {
				printf("o");
			}
			else if(i == body) {
				if(flag == 1)
					printf("O");
				else
					printf("X");
			}
		    else if(i == head) {
				if(flag == 1)
					printf("G");
				else
					printf("x");
			}
			else if(i > tail && tail > body) {
				printf("o");
			}
			else if (i != head && i != tail && i != body && i < head || i < tail) {
				printf(" ");
			}
		}

		printf("\n");

		// Prints Ledge == MaxLength
		for(int i = 0; i < maxLength; i++)
		{
			printf("=");
		}
		printf("\n\n");
}

int main(int argc, char **argv)
{
	int i, wormLength;
	int flagDie = 1;
	int head = 2;
	int body = 1;
	int tail = 0;

	// Prints Full string and calls function for initial Worm
	wormLength = atoi(argv[1]);
	printf("%s\n\n", argv[2]);
	printf("Glowworm appears! Hooray!\n");
	printGlowworm(tail, head, body, wormLength, flagDie);


	// Passes each char of the String argv[2]
	for(i = 0; i < strlen(argv[2]); i++) {
		if(flagDie == 0)
			break;

		// Uses Switch to account for each char case
		switch(argv[2][i]) {
				case 'o': case 'O': case '@':
					// Use if-else to help program decide to chill or to grow 'o'
					if(head != wormLength) {
						head++;
						body++;

						// Keeps Head and Body from falling off Ledge == wormLength
						if(head == wormLength)
							head = 0;
						if(body == wormLength)
							body = 0;

						// Prints little bodies 'o' of Glowworm
						if(head != tail) {
							printf("Glowworm grows:\n");
							printGlowworm(tail, head, body, wormLength, flagDie);
							break;
						}
						else {
							// Worm does not grow if there is no more room on Ledge
							// When chills:if keeps worm the same as before its growth
							printf("Glowworm chills:\n");
							if(head == 0) {
								head = wormLength - 1;
								body = head - 1;
							}
							if(head == tail) {
								head--;
								body--;
							}

							printGlowworm(tail, head, body, wormLength, flagDie);
							break;
						}
					}
					else {
						printf("Glowworm chills:\n");
						printGlowworm(tail, head, body, wormLength, flagDie);
						break;
					}
				case 's': case 'S':
					// if -elseif: keeps worm from shrinking if there is no 'o' bodies
					if(head == wormLength || tail == (body-1)) {
						printf("Glowworm chills:\n");
						printGlowworm(tail, head, body, wormLength, flagDie);
						break;
					}
					else if(body == 0 && head == 1 && tail == (wormLength - 1)) {
						printf("Glowworm chills:\n");
						printGlowworm(tail, head, body, wormLength, flagDie);
						break;
					}
					else {
						// Allows worm head and body to return to right side of ledge
						// when shrinking
						if(head == 0 && body == (wormLength-1))
							head = wormLength;
						if(body == 0 && tail > body)
							body = wormLength;

						head--;
						body--;
					}

					// Prints the shrinked worm
					if(head != wormLength ) {
						printf("Glowworm shrinks:\n");
						printGlowworm(tail, head, body, wormLength, flagDie);
						break;
					}
				case '-': case '=':
					// Worm wiggles Forward by incrementing worm body parts
					printf("Glowworm inches forward:\n");
					head++;
					body++;
					tail++;

					// Makes worm Tranlocational by keeping body parts from falling off
					// the ledge by setting the worm parts == 0 as they reach wormLength
					if(head == wormLength)
						head = 0;
					if(body == wormLength)
						body = 0;
					if(tail == wormLength)
						tail = 0;

					printGlowworm(tail, head, body, wormLength, flagDie);
					break;
				case 'x': case 'X': case '%':
					// Flag used to let program know of approaching Death and to end program
					printf("Glowworm meets its demise. SAD.\n");
					flagDie = 0;
					printGlowworm(tail, head, body, wormLength, flagDie);
					break;
				default:
					// Catches all other possible char characters that are inputed
					printf("Glowworm chills:\n");
					printGlowworm(tail, head, body, wormLength, flagDie);
					break;
		}
	}
	return 0;
}
