/***************************************************
* Date: April 28, 2018
* Name: Matthew Northey
* Assignment: #3 Unit Test 4 - whoseTurn()
* Note: Much of the structure for this code came
*	from the template made available to us on
*	Canvas. All modifications are my own.
****************************************************/

// Libraries & Header Files
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

// Set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

// Function headers
void assertTrue(char *desc, int expected, int actual);




/****************************************************
*
* main()
*
****************************************************/

int main() {
	// Set up main variables
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int seed = 1000;
	struct gameState G;
	memset(&G, 23, sizeof(struct gameState));   // Clear the game state
	
	// Setup
	printf("------------------------------------------------------------------\n-\n");
	printf("- UNIT TEST 4: whoseTurn()\n-\n");
	printf("------------------------------------------------------------------\n");
		
	// ~~~~~~~~TESTS~~~~~~~~
	// RETURNS CORRECT TURN FOR ALL PLAYERS IN 2-PLAYER GAME
	#if (NOISY_TEST == 1)
		printf("TESTING All Players in 2-Player Game\n");
	#endif
	
	initializeGame(2, k, seed, &G);
	assertTrue("whoseTurn(&G)", 0, whoseTurn(&G));
	
	G.whoseTurn = 1;
	assertTrue("whoseTurn(&G)", 1, whoseTurn(&G));
	
	// RETURNS CORRECT TURN FOR ALL PLAYERS IN 3-PLAYER GAME
	#if (NOISY_TEST == 1)
		printf("TESTING All Players in 3-Player Game\n");
	#endif
	
	initializeGame(3, k, seed, &G);
	assertTrue("whoseTurn(&G)", 0, whoseTurn(&G));
	
	G.whoseTurn = 1;
	assertTrue("whoseTurn(&G)", 1, whoseTurn(&G));
	
	G.whoseTurn = 2;
	assertTrue("whoseTurn(&G)", 2, whoseTurn(&G));
	
	// RETURNS CORRECT TURN FOR ALL PLAYERS IN 4-PLAYER GAME
	#if (NOISY_TEST == 1)
		printf("TESTING All Players in 4-Player Game\n");
	#endif
	
	initializeGame(4, k, seed, &G);
	assertTrue("whoseTurn(&G)", 0, whoseTurn(&G));
	
	G.whoseTurn = 1;
	assertTrue("whoseTurn(&G)", 1, whoseTurn(&G));
	
	G.whoseTurn = 2;
	assertTrue("whoseTurn(&G)", 2, whoseTurn(&G));
	
	G.whoseTurn = 3;
	assertTrue("whoseTurn(&G)", 3, whoseTurn(&G));
	
	// Final message
	printf("\n");
	
    return 0;
}




/****************************************************
*
* assertTrue()
*
****************************************************/

void assertTrue(char *desc, int expected, int actual)
{
	if (expected == actual)
	{
		#if (NOISY_TEST == 1)
			printf("  PASS: %s = %d, Expected = %d\n", desc, actual, expected);
		#endif
	}
	else
	{
		#if (NOISY_TEST == 1)
			printf("! FAIL: %s = %d, Expected = %d\n", desc, actual, expected);
		#endif
	}
}