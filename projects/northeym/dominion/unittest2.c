/***************************************************
* Date: April 26, 2018
* Name: Matthew Northey
* Assignment: #3 Unit Test 2 - getCost()
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
	int numPlayers = 4;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int seed = 1000;
	struct gameState G;
	memset(&G, 23, sizeof(struct gameState));   // Clear the game state
	
	// Setup
	printf("------------------------------------------------------------------\n-\n");
	printf("- UNIT TEST 2: getCost()\n-\n");
	printf("------------------------------------------------------------------\n");
		
	// ~~~~~~~~TESTS~~~~~~~~
	initializeGame(numPlayers, k, seed, &G);
	
	// RETURNS CORRECT COST FOR ALL CARDS BY NAME
	#if (NOISY_TEST == 1)
		printf("TESTING Cards by Name\n");
	#endif
	
	assertTrue("getCost(curse)", 0, getCost(curse));
	assertTrue("getCost(estate)", 2, getCost(estate));
	assertTrue("getCost(duchy)", 5, getCost(duchy));
	assertTrue("getCost(province)", 8, getCost(province));
	assertTrue("getCost(copper)", 0, getCost(copper));
	assertTrue("getCost(silver)", 3, getCost(silver));
	assertTrue("getCost(gold)", 6, getCost(gold));
	assertTrue("getCost(adventurer)", 6, getCost(adventurer));
	assertTrue("getCost(council_room)", 5, getCost(council_room));
	assertTrue("getCost(feast)", 4, getCost(feast));
	assertTrue("getCost(gardens)", 4, getCost(gardens));
	assertTrue("getCost(mine)", 5, getCost(mine));
	assertTrue("getCost(remodel)", 4, getCost(remodel));
	assertTrue("getCost(smithy)", 4, getCost(smithy));
	assertTrue("getCost(village)", 3, getCost(village));
	assertTrue("getCost(baron)", 4, getCost(baron));
	assertTrue("getCost(great_hall)", 3, getCost(great_hall));
	assertTrue("getCost(minion)", 5, getCost(minion));
	assertTrue("getCost(steward)", 3, getCost(steward));
	assertTrue("getCost(tribute)", 5, getCost(tribute));
	assertTrue("getCost(ambassador)", 3, getCost(ambassador));
	assertTrue("getCost(cutpurse)", 4, getCost(cutpurse));
	assertTrue("getCost(embargo)", 2, getCost(embargo));
	assertTrue("getCost(outpost)", 5, getCost(outpost));
	assertTrue("getCost(salvager)", 4, getCost(salvager));
	assertTrue("getCost(sea_hag)", 4, getCost(sea_hag));
	assertTrue("getCost(treasure_map)", 4, getCost(treasure_map));
		
	// RETURNS CORRECT COST FOR ALL CARDS BY VALUE
	#if (NOISY_TEST == 1)
		printf("TESTING Cards by Value\n");
	#endif
	
	assertTrue("getCost(0)", 0, getCost(0));
	assertTrue("getCost(1)", 2, getCost(1));
	assertTrue("getCost(2)", 5, getCost(2));
	assertTrue("getCost(3)", 8, getCost(3));
	assertTrue("getCost(4)", 0, getCost(4));
	assertTrue("getCost(5)", 3, getCost(5));
	assertTrue("getCost(6)", 6, getCost(6));
	assertTrue("getCost(7)", 6, getCost(7));
	assertTrue("getCost(8)", 5, getCost(8));
	assertTrue("getCost(9)", 4, getCost(9));
	assertTrue("getCost(10)", 4, getCost(10));
	assertTrue("getCost(11)", 5, getCost(11));
	assertTrue("getCost(12)", 4, getCost(12));
	assertTrue("getCost(13)", 4, getCost(13));
	assertTrue("getCost(14)", 3, getCost(14));
	assertTrue("getCost(15)", 4, getCost(15));
	assertTrue("getCost(16)", 3, getCost(16));
	assertTrue("getCost(17)", 5, getCost(17));
	assertTrue("getCost(18)", 3, getCost(18));
	assertTrue("getCost(19)", 5, getCost(19));
	assertTrue("getCost(20)", 3, getCost(20));
	assertTrue("getCost(21)", 4, getCost(21));
	assertTrue("getCost(22)", 2, getCost(22));
	assertTrue("getCost(23)", 5, getCost(23));
	assertTrue("getCost(24)", 4, getCost(24));
	assertTrue("getCost(25)", 4, getCost(25));
	assertTrue("getCost(26)", 4, getCost(26));
		

	// RETURNS ERROR FOR INVALID INPUTS
	#if (NOISY_TEST == 1)
		printf("TESTING Invalid Inputs\n");
	#endif
	
	assertTrue("getCost(-1)", -1, getCost(-1));
	assertTrue("getCost(-5)", -1, getCost(-5));
	assertTrue("getCost(-10)", -1, getCost(-10));
	assertTrue("getCost(27)", -1, getCost(27));
	assertTrue("getCost(30)", -1, getCost(30));
	assertTrue("getCost(33)", -1, getCost(33));
	assertTrue("getCost(3.123)", -1, getCost(3.123));
	assertTrue("getCost(7.912)", -1, getCost(7.912));
	assertTrue("getCost(13.333)", -1, getCost(13.333));

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