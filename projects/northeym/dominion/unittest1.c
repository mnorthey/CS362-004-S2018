/***************************************************
* Date: April 26, 2018
* Name: Matthew Northey
* Assignment: #3 Unit Test 1 - initializeGame()
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
void testNumPlayers();
void testKingdomCards();
void testStartingConditions();
void assertTrue(char *desc, int expected, int actual);

int main() {
	// Setup
	printf("------------------------------------------------------------------\n-\n");
	printf("- UNIT TEST 1: initializeGame()\n-\n");
	printf("------------------------------------------------------------------\n");
		
	// Test numPlayers
	testNumPlayers();
	testKingdomCards();
	testStartingConditions();
	
	// Final message
	printf("\n");
	
    return 0;
}




/****************************************************
*
* testNumPlayers()
*
****************************************************/

void testNumPlayers()
{
	// Set up main variables
	int i, r, numPlayers;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int seed = 1000;
	struct gameState G;
	memset(&G, 23, sizeof(struct gameState));   // Clear the game state
	
	// Initial output
	#if (NOISY_TEST == 1)
		printf("TESTING Number of Players Validation\n");
	#endif
		
	// ~~~~~~~~TESTS~~~~~~~~
	// ACCEPTABLE VALUES (2-4)
	#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("Case: In Range\n");
	#endif
	
	for (i = 2; i <= 4; i++)
	{
		#if (NOISY_TEST == 1)
			printf("numPlayers: %d\n", i);
		#endif
		
		r = initializeGame(i, k, seed, &G);
		assertTrue("r", 0, r);
		assertTrue("G.numPlayers", i, G.numPlayers);
	}
	
	// NEGATIVES
	#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("Case: Negatives\n");
	#endif
	
	for (i = 1; i <= 10; i++)
	{
		numPlayers = i * -1;
		
		#if (NOISY_TEST == 1)
			printf("numPlayers: %d\n", numPlayers);
		#endif
		
		r = initializeGame(numPlayers, k, seed, &G);
		assertTrue("r", -1, r);
	}
	
	// ZERO
	#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("Case: Zero\n");
	#endif
	
	numPlayers = 0;
	
	#if (NOISY_TEST == 1)
		printf("numPlayers: %d\n", numPlayers);
	#endif
		
	r = initializeGame(numPlayers, k, seed, &G);
	assertTrue("r", -1, r);
	
	// ONE PLAYER (BENEATH LOWER LIMIT)
	#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("Case: Too Small\n");
	#endif
	
	numPlayers = 1;
	
	#if (NOISY_TEST == 1)
		printf("numPlayers: %d\n", numPlayers);
	#endif
		
	r = initializeGame(numPlayers, k, seed, &G);
	assertTrue("r", -1, r);
	
	// EXCEEDS UPPER LIMIT
	#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("Case: Too Large\n");
	#endif
	
	for (i = 5; i <= 15; i++)
	{
		#if (NOISY_TEST == 1)
			printf("numPlayers: %d\n", i);
		#endif
		
		r = initializeGame(i, k, seed, &G);
		assertTrue("r", -1, r);
	}
	
	return;
}




/****************************************************
*
* testKingdomCards()
*
****************************************************/

void testKingdomCards()
{
	// Set up main variables
	int r;
	int numPlayers = 3;
	int seed = 1000;
	struct gameState G;
	memset(&G, 23, sizeof(struct gameState));   // Clear the game state
	
	// Initial output
	#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("TESTING Kingdom Card Validation\n");
	#endif
	
	// ~~~~~~~~TESTS~~~~~~~~
	// BASE CARD COUNTS
	#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("Case: Base Card Counts\n");
	#endif
	
		// Two Players
		#if (NOISY_TEST == 1)
			printf("Two Players\n");
		#endif
			
		int k1[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
		r = initializeGame(2, k1, seed, &G);
		
		assertTrue("G.supplyCount[curse]", 10, G.supplyCount[curse]);
		assertTrue("G.supplyCount[estate]", 8, G.supplyCount[estate]);
		assertTrue("G.supplyCount[duchy]", 8, G.supplyCount[duchy]);
		assertTrue("G.supplyCount[province]", 8, G.supplyCount[province]);
		assertTrue("G.supplyCount[copper]", 60 - (7 * 2), G.supplyCount[copper]);
		assertTrue("G.supplyCount[silver]", 40, G.supplyCount[silver]);
		assertTrue("G.supplyCount[gold]", 30, G.supplyCount[gold]);
		
		// Three Players
		#if (NOISY_TEST == 1)
			printf("Three Players\n");
		#endif
			
		r = initializeGame(3, k1, seed, &G);
		
		assertTrue("G.supplyCount[curse]", 20, G.supplyCount[curse]);
		assertTrue("G.supplyCount[estate]", 12, G.supplyCount[estate]);
		assertTrue("G.supplyCount[duchy]", 12, G.supplyCount[duchy]);
		assertTrue("G.supplyCount[province]", 12, G.supplyCount[province]);
		assertTrue("G.supplyCount[copper]", 60 - (7 * 3), G.supplyCount[copper]);
		assertTrue("G.supplyCount[silver]", 40, G.supplyCount[silver]);
		assertTrue("G.supplyCount[gold]", 30, G.supplyCount[gold]);
		
		// Four Players
		#if (NOISY_TEST == 1)
			printf("Four Players\n");
		#endif
			
		r = initializeGame(4, k1, seed, &G);
		
		assertTrue("G.supplyCount[curse]", 30, G.supplyCount[curse]);
		assertTrue("G.supplyCount[estate]", 12, G.supplyCount[estate]);
		assertTrue("G.supplyCount[duchy]", 12, G.supplyCount[duchy]);
		assertTrue("G.supplyCount[province]", 12, G.supplyCount[province]);
		assertTrue("G.supplyCount[copper]", 60 - (7 * 4), G.supplyCount[copper]);
		assertTrue("G.supplyCount[silver]", 40, G.supplyCount[silver]);
		assertTrue("G.supplyCount[gold]", 30, G.supplyCount[gold]);
	
	// ACCEPTABLE CARD COMBINATIONS
	#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("Case: Acceptable Combinations\n");
	#endif
	
		// First test
		#if (NOISY_TEST == 1)
			printf("kingdomCards: {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall}\n");
		#endif

		r = initializeGame(numPlayers, k1, seed, &G);
		
		assertTrue("r", 0, r);
		assertTrue("G.supplyCount[adventurer]", 10, G.supplyCount[adventurer]);
		assertTrue("G.supplyCount[council_room]", 10, G.supplyCount[council_room]);
		assertTrue("G.supplyCount[feast]", 10, G.supplyCount[feast]);
		assertTrue("G.supplyCount[gardens]", 12, G.supplyCount[gardens]);
		assertTrue("G.supplyCount[mine]", 10, G.supplyCount[mine]);
		assertTrue("G.supplyCount[remodel]", 10, G.supplyCount[remodel]);
		assertTrue("G.supplyCount[smithy]", 10, G.supplyCount[smithy]);
		assertTrue("G.supplyCount[village]", 10, G.supplyCount[village]);
		assertTrue("G.supplyCount[baron]", 10, G.supplyCount[baron]);
		assertTrue("G.supplyCount[great_hall]", 12, G.supplyCount[great_hall]);
		assertTrue("G.supplyCount[minion]", -1, G.supplyCount[minion]);
		assertTrue("G.supplyCount[steward]", -1, G.supplyCount[steward]);
		assertTrue("G.supplyCount[tribute]", -1, G.supplyCount[tribute]);
		assertTrue("G.supplyCount[ambassador]", -1, G.supplyCount[ambassador]);
		assertTrue("G.supplyCount[cutpurse]", -1, G.supplyCount[cutpurse]);
		assertTrue("G.supplyCount[embargo]", -1, G.supplyCount[embargo]);
		assertTrue("G.supplyCount[outpost]", -1, G.supplyCount[outpost]);
		assertTrue("G.supplyCount[salvager]", -1, G.supplyCount[salvager]);
		assertTrue("G.supplyCount[sea_hag]", -1, G.supplyCount[sea_hag]);
		assertTrue("G.supplyCount[treasure_map]", -1, G.supplyCount[treasure_map]);
		
		// Second test
		#if (NOISY_TEST == 1)
			printf("kingdomCards: {salvager, baron, treasure_map, outpost, great_hall, mine, feast, sea_hag, minion, village}\n");
		#endif
		
		int k2[10] = {salvager, baron, treasure_map, outpost, great_hall, mine, feast, sea_hag, minion, village};
		r = initializeGame(numPlayers, k2, seed, &G);
		
		assertTrue("r", 0, r);
		assertTrue("G.supplyCount[adventurer]", -1, G.supplyCount[adventurer]);
		assertTrue("G.supplyCount[council_room]", -1, G.supplyCount[council_room]);
		assertTrue("G.supplyCount[feast]", 10, G.supplyCount[feast]);
		assertTrue("G.supplyCount[gardens]", -1, G.supplyCount[gardens]);
		assertTrue("G.supplyCount[mine]", 10, G.supplyCount[mine]);
		assertTrue("G.supplyCount[remodel]", -1, G.supplyCount[remodel]);
		assertTrue("G.supplyCount[smithy]", -1, G.supplyCount[smithy]);
		assertTrue("G.supplyCount[village]", 10, G.supplyCount[village]);
		assertTrue("G.supplyCount[baron]", 10, G.supplyCount[baron]);
		assertTrue("G.supplyCount[great_hall]", 12, G.supplyCount[great_hall]);
		assertTrue("G.supplyCount[minion]", 10, G.supplyCount[minion]);
		assertTrue("G.supplyCount[steward]", -1, G.supplyCount[steward]);
		assertTrue("G.supplyCount[tribute]", -1, G.supplyCount[tribute]);
		assertTrue("G.supplyCount[ambassador]", -1, G.supplyCount[ambassador]);
		assertTrue("G.supplyCount[cutpurse]", -1, G.supplyCount[cutpurse]);
		assertTrue("G.supplyCount[embargo]", -1, G.supplyCount[embargo]);
		assertTrue("G.supplyCount[outpost]", 10, G.supplyCount[outpost]);
		assertTrue("G.supplyCount[salvager]", 10, G.supplyCount[salvager]);
		assertTrue("G.supplyCount[sea_hag]", 10, G.supplyCount[sea_hag]);
		assertTrue("G.supplyCount[treasure_map]", 10, G.supplyCount[treasure_map]);
		
		// Third test
		#if (NOISY_TEST == 1)
			printf("kingdomCards: {embargo, gardens, cutpurse, ambassador, council_room, steward, tribute, village, treasure_map, adventurer}\n");
		#endif
		
		int k3[10] = {embargo, gardens, cutpurse, ambassador, council_room, steward, tribute, village, treasure_map, adventurer};
		r = initializeGame(numPlayers, k3, seed, &G);
		
		assertTrue("r", 0, r);
		assertTrue("G.supplyCount[adventurer]", 10, G.supplyCount[adventurer]);
		assertTrue("G.supplyCount[council_room]", 10, G.supplyCount[council_room]);
		assertTrue("G.supplyCount[feast]", -1, G.supplyCount[feast]);
		assertTrue("G.supplyCount[gardens]", 12, G.supplyCount[gardens]);
		assertTrue("G.supplyCount[mine]", -1, G.supplyCount[mine]);
		assertTrue("G.supplyCount[remodel]", -1, G.supplyCount[remodel]);
		assertTrue("G.supplyCount[smithy]", -1, G.supplyCount[smithy]);
		assertTrue("G.supplyCount[village]", 10, G.supplyCount[village]);
		assertTrue("G.supplyCount[baron]", -1, G.supplyCount[baron]);
		assertTrue("G.supplyCount[great_hall]", -1, G.supplyCount[great_hall]);
		assertTrue("G.supplyCount[minion]", -1, G.supplyCount[minion]);
		assertTrue("G.supplyCount[steward]", 10, G.supplyCount[steward]);
		assertTrue("G.supplyCount[tribute]", 10, G.supplyCount[tribute]);
		assertTrue("G.supplyCount[ambassador]", 10, G.supplyCount[ambassador]);
		assertTrue("G.supplyCount[cutpurse]", 10, G.supplyCount[cutpurse]);
		assertTrue("G.supplyCount[embargo]", 10, G.supplyCount[embargo]);
		assertTrue("G.supplyCount[outpost]", -1, G.supplyCount[outpost]);
		assertTrue("G.supplyCount[salvager]", -1, G.supplyCount[salvager]);
		assertTrue("G.supplyCount[sea_hag]", -1, G.supplyCount[sea_hag]);
		assertTrue("G.supplyCount[treasure_map]", 10, G.supplyCount[treasure_map]);
	
	// VICTORY CARDS WITH VARIABLE COUNT
	#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("Case: Cards with Variable Counts\n");
	#endif
	
		// Two Players
		#if (NOISY_TEST == 1)
			printf("Two Players\n");
		#endif
			
		r = initializeGame(2, k1, seed, &G);
		
		assertTrue("G.supplyCount[great_hall]", 8, G.supplyCount[great_hall]);
		assertTrue("G.supplyCount[gardens]", 8, G.supplyCount[gardens]);
		
		// Three Players
		#if (NOISY_TEST == 1)
			printf("Three Players\n");
		#endif
			
		r = initializeGame(3, k1, seed, &G);
		
		assertTrue("G.supplyCount[great_hall]", 12, G.supplyCount[great_hall]);
		assertTrue("G.supplyCount[gardens]", 12, G.supplyCount[gardens]);
		
		// Four Players
		#if (NOISY_TEST == 1)
			printf("Four Players\n");
		#endif
			
		r = initializeGame(4, k1, seed, &G);
		
		assertTrue("G.supplyCount[great_hall]", 12, G.supplyCount[great_hall]);
		assertTrue("G.supplyCount[gardens]", 12, G.supplyCount[gardens]);
	
	// REPEATED CARDS
	#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("Case: Repeated Cards\n");
	#endif
	
		// First test
		#if (NOISY_TEST == 1)
			printf("kingdomCards: {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, adventurer}\n");
		#endif
		
		int k4[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, adventurer};
		r = initializeGame(numPlayers, k4, seed, &G);
		
		assertTrue("r", -1, r);
		
		// Second test
		#if (NOISY_TEST == 1)
			printf("kingdomCards: {sea_hag, baron, treasure_map, outpost, great_hall, mine, feast, sea_hag, minion, sea_hag}\n");
		#endif
		
		int k5[10] = {sea_hag, baron, treasure_map, outpost, great_hall, mine, feast, sea_hag, minion, sea_hag};
		r = initializeGame(numPlayers, k5, seed, &G);
		
		assertTrue("r", -1, r);
		
		// Third test
		#if (NOISY_TEST == 1)
			printf("kingdomCards: {embargo, gardens, cutpurse, ambassador, treasure_map, steward, tribute, village, treasure_map, adventurer}\n");
		#endif
		
		int k6[10] = {embargo, gardens, cutpurse, ambassador, treasure_map, steward, tribute, village, treasure_map, adventurer};
		r = initializeGame(numPlayers, k6, seed, &G);
		
		assertTrue("r", -1, r);
		
		// Fourth test
		#if (NOISY_TEST == 1)
			printf("kingdomCards: {remodel, smithy, smithy, smithy, smithy, remodel, ambassador, cutpurse, cutpurse, cutpurse}\n");
		#endif
		
		int k7[10] = {remodel, smithy, smithy, smithy, smithy, remodel, ambassador, cutpurse, cutpurse, cutpurse};
		r = initializeGame(numPlayers, k7, seed, &G);
		
		assertTrue("r", -1, r);
		
		// Fifth test
		#if (NOISY_TEST == 1)
			printf("kingdomCards: {baron, baron, baron, baron, baron, baron, baron, baron, baron, baron}\n");
		#endif
		
		int k8[10] = {baron, baron, baron, baron, baron, baron, baron, baron, baron, baron};
		r = initializeGame(numPlayers, k8, seed, &G);
		
		assertTrue("r", -1, r);

	// TOO MANY CARDS
	#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("Case: Too Many Cards\n");
	#endif
		
		// First test
		#if (NOISY_TEST == 1)
			printf("Number Cards: 11\n");
		#endif
		
		int k9[11] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion};
		r = initializeGame(numPlayers, k9, seed, &G);
		
		assertTrue("r", -1, r);
		
		// Second test
		#if (NOISY_TEST == 1)
			printf("Number Cards: 12\n");
		#endif
		
		int k10[12] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward};
		r = initializeGame(numPlayers, k10, seed, &G);
		
		assertTrue("r", -1, r);
		
		// Third test
		#if (NOISY_TEST == 1)
			printf("Number Cards: 15\n");
		#endif
		
		int k11[15] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse};
		r = initializeGame(numPlayers, k11, seed, &G);
		
		assertTrue("r", -1, r);
		
		// Fourth test
		#if (NOISY_TEST == 1)
			printf("Number Cards: 18\n");
		#endif
		
		int k12[18] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse, embargo, outpost, salvager};
		r = initializeGame(numPlayers, k12, seed, &G);
		
		assertTrue("r", -1, r);
		
		// Fifth test
		#if (NOISY_TEST == 1)
			printf("Number Cards: 20\n");
		#endif
		
		int k13[20] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward, tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map};
		r = initializeGame(numPlayers, k13, seed, &G);
		
		assertTrue("r", -1, r);
	
	// TOO FEW CARDS
	#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("Case: Too Few Cards\n");
	#endif
	
		// First test
		#if (NOISY_TEST == 1)
			printf("Number Cards: 0\n");
		#endif
		
		int k14[0] = {};
		r = initializeGame(numPlayers, k14, seed, &G);
		
		assertTrue("r", -1, r);
		
		// Second test
		#if (NOISY_TEST == 1)
			printf("Number Cards: 1\n");
		#endif
		
		int k15[1] = {adventurer};
		r = initializeGame(numPlayers, k15, seed, &G);
		
		assertTrue("r", -1, r);
		
		// Third test
		#if (NOISY_TEST == 1)
			printf("Number Cards: 5\n");
		#endif
		
		int k16[5] = {adventurer, council_room, feast, gardens, mine};
		r = initializeGame(numPlayers, k16, seed, &G);
		
		assertTrue("r", -1, r);
		
		// Fourth test
		#if (NOISY_TEST == 1)
			printf("Number Cards: 8\n");
		#endif
		
		int k17[8] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village};
		r = initializeGame(numPlayers, k17, seed, &G);
		
		assertTrue("r", -1, r);
		
		// Fifth test
		#if (NOISY_TEST == 1)
			printf("Number Cards: 9\n");
		#endif
		
		int k18[9] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron};
		r = initializeGame(numPlayers, k18, seed, &G);
		
		assertTrue("r", -1, r);	
	
	// AUTOMATICALLY INCLUDED CARDS
	#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("Case: Restricted Cards\n");
	#endif
	
		// Curse test
		#if (NOISY_TEST == 1)
			printf("Restricted Card: curse\n");
		#endif
		
		int k19[10] = {curse, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
		r = initializeGame(numPlayers, k19, seed, &G);
		
		assertTrue("r", -1, r);	
	
		// Estate test
		#if (NOISY_TEST == 1)
			printf("Restricted Card: estate\n");
		#endif
		
		int k20[10] = {estate, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
		r = initializeGame(numPlayers, k20, seed, &G);
		
		assertTrue("r", -1, r);	
		
		// Duchy test
		#if (NOISY_TEST == 1)
			printf("Restricted Card: duchy\n");
		#endif
		
		int k21[10] = {duchy, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
		r = initializeGame(numPlayers, k21, seed, &G);
		
		assertTrue("r", -1, r);	
		
		// Province test
		#if (NOISY_TEST == 1)
			printf("Restricted Card: province\n");
		#endif
		
		int k22[10] = {province, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
		r = initializeGame(numPlayers, k22, seed, &G);
		
		assertTrue("r", -1, r);	
		
		// Copper test
		#if (NOISY_TEST == 1)
			printf("Restricted Card: copper\n");
		#endif
		
		int k23[10] = {copper, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
		r = initializeGame(numPlayers, k23, seed, &G);
		
		assertTrue("r", -1, r);	
		
		// Silver test
		#if (NOISY_TEST == 1)
			printf("Restricted Card: silver\n");
		#endif
		
		int k24[10] = {silver, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
		r = initializeGame(numPlayers, k24, seed, &G);
		
		assertTrue("r", -1, r);	
		
		// Gold test
		#if (NOISY_TEST == 1)
			printf("Restricted Card: gold\n");
		#endif
		
		int k25[10] = {gold, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
		r = initializeGame(numPlayers, k25, seed, &G);
		
		assertTrue("r", -1, r);	
	
	return;
}




/****************************************************
*
* testPlayerDecks()
*
****************************************************/

void testStartingConditions()
{
	// Set up main variables
	int i, copper1, copper2, copper3, copper4, estate1, estate2, estate3, estate4;
	int numPlayers = 4;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int seed1 = 1000;
	int seed2 = 10000;
	int seed3 = 700;
	int seed4 = 5;
	int seed5 = 153;
	struct gameState G;
	memset(&G, 23, sizeof(struct gameState));   // Clear the game state
	
	// Initial output
	#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("TESTING Starting Conditions\n");
	#endif
	
	// STARTING DECK COUNTS ARE CORRECT
	#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("Case: Starting Deck Counts\n");
	#endif
	
		// Test 1
		#if (NOISY_TEST == 1)
			printf("Simulation 1\n");
		#endif
		
		initializeGame(numPlayers, k, seed1, &G);
		
		assertTrue("G.deckCount[0]", 5, G.deckCount[0]);	
		assertTrue("G.deckCount[1]", 10, G.deckCount[1]);
		assertTrue("G.deckCount[2]", 10, G.deckCount[2]);
		assertTrue("G.deckCount[3]", 10, G.deckCount[3]);
		
		assertTrue("G.discardCount[0]", 0, G.discardCount[0]);	
		assertTrue("G.discardCount[1]", 0, G.discardCount[1]);
		assertTrue("G.discardCount[2]", 0, G.discardCount[2]);
		assertTrue("G.discardCount[3]", 0, G.discardCount[3]);
		
		// Test 2
		#if (NOISY_TEST == 1)
			printf("Simulation 2\n");
		#endif
		
		memset(&G, 23, sizeof(struct gameState));   // Clear the game state
		initializeGame(numPlayers, k, seed2, &G);
		
		assertTrue("G.discardCount[0]", 0, G.discardCount[0]);	
		assertTrue("G.discardCount[1]", 0, G.discardCount[1]);
		assertTrue("G.discardCount[2]", 0, G.discardCount[2]);
		assertTrue("G.discardCount[3]", 0, G.discardCount[3]);
		
		// Test 3
		#if (NOISY_TEST == 1)
			printf("Simulation 3\n");
		#endif
		
		memset(&G, 23, sizeof(struct gameState));   // Clear the game state
		initializeGame(numPlayers, k, seed3, &G);
		
		assertTrue("G.discardCount[0]", 0, G.discardCount[0]);	
		assertTrue("G.discardCount[1]", 0, G.discardCount[1]);
		assertTrue("G.discardCount[2]", 0, G.discardCount[2]);
		assertTrue("G.discardCount[3]", 0, G.discardCount[3]);
	
	// STARTING DECK COMPOSITIONS ARE CORRECT
	#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("Case: Starting Deck Composition\n");
	#endif
	
		// Test
		#if (NOISY_TEST == 1)
			printf("Each Card Copper or Estate\n");
		#endif
		
		memset(&G, 23, sizeof(struct gameState));   // Clear the game state
		initializeGame(numPlayers, k, seed1, &G);
		
		copper1 = 0;
		copper2 = 0;
		copper3 = 0;
		copper4 = 0;
		estate1 = 0;
		estate2 = 0;
		estate3 = 0;
		estate4 = 0;
		
		int suspicious = 1;
		
		for (i = 0; i < 10; i++)
		{
			// Player 1
			if (i < 5)
			{
				if (G.deck[0][i] == copper)
				{
					#if (NOISY_TEST == 1)
						printf("  PASS: G.deck[0][%d] = copper, Expected = copper or estate\n", i);
					#endif
					
					copper1++;
				}
				else if (G.deck[0][i] == estate)
				{
					#if (NOISY_TEST == 1)
						printf("  PASS: G.deck[0][%d] = estate, Expected = copper or estate\n", i);
					#endif
					
					estate1++;
				}
				else
				{
					#if (NOISY_TEST == 1)
						printf("! FAIL: G.deck[0][%d] = %d, Expected = copper or estate\n", G.deck[0][i], i);
					#endif
				}
			}
			else
			{
				if (G.hand[0][i-5] == copper)
				{
					#if (NOISY_TEST == 1)
						printf("  PASS: G.hand[0][%d] = copper, Expected = copper or estate\n", i-5);
					#endif
					
					copper1++;
				}
				else if (G.hand[0][i-5] == estate)
				{
					#if (NOISY_TEST == 1)
						printf("  PASS: G.hand[0][%d] = estate, Expected = copper or estate\n", i-5);
					#endif
					
					estate1++;
				}
				else
				{
					#if (NOISY_TEST == 1)
						printf("! FAIL: G.hand[0][%d] = %d, Expected = copper or estate\n", G.deck[0][i-5], i-5);
					#endif
				}
			}
			
			// Player 2
			if (G.deck[1][i] == copper)
			{
				#if (NOISY_TEST == 1)
					printf("  PASS: G.deck[1][%d] = copper, Expected = copper or estate\n", i);
				#endif
				
				copper2++;
			}
			else if (G.deck[1][i] == estate)
			{
				#if (NOISY_TEST == 1)
					printf("  PASS: G.deck[1][%d] = estate, Expected = copper or estate\n", i);
				#endif
				
				estate2++;
			}
			else
			{
				#if (NOISY_TEST == 1)
					printf("! FAIL: G.deck[1][%d] = %d, Expected = copper or estate\n", G.deck[1][i], i);
				#endif
			}
			
			// Player 3
			if (G.deck[2][i] == copper)
			{
				#if (NOISY_TEST == 1)
					printf("  PASS: G.deck[2][%d] = copper, Expected = copper or estate\n", i);
				#endif
				
				copper3++;
			}
			else if (G.deck[2][i] == estate)
			{
				#if (NOISY_TEST == 1)
					printf("  PASS: G.deck[2][%d] = estate, Expected = copper or estate\n", i);
				#endif
				
				estate3++;
			}
			else
			{
				#if (NOISY_TEST == 1)
					printf("! FAIL: G.deck[2][%d] = %d, Expected = copper or estate\n", G.deck[2][i], i);
				#endif
			}
			
			// Player 4
			if (G.deck[3][i] == copper)
			{
				#if (NOISY_TEST == 1)
					printf("  PASS: G.deck[3][%d] = copper, Expected = copper or estate\n", i);
				#endif
				
				copper4++;
			}
			else if (G.deck[3][i] == estate)
			{
				#if (NOISY_TEST == 1)
					printf("  PASS: G.deck[3][%d] = estate, Expected = copper or estate\n", i);
				#endif
				
				estate4++;
			}
			else
			{
				#if (NOISY_TEST == 1)
					printf("! FAIL: G.deck[3][%d] = %d, Expected = copper or estate\n", G.deck[3][i], i);
				#endif
			}
			
			if (i < 5 && (G.deck[0][i] != G.deck[1][i] || G.deck[0][i] != G.deck[2][i] || G.deck[0][i] != G.deck[3][i]))
			{
				suspicious = 0;
			}
			else if (G.deck[1][i] != G.deck[2][i] || G.deck[1][i] != G.deck[3][i])
			{
				suspicious = 0;
			}
		}
	
	#if (NOISY_TEST == 1)
		printf("Copper Counts\n");
	#endif
		
		assertTrue("P1 Copper", 7, copper1);
		assertTrue("P2 Copper", 7, copper2);
		assertTrue("P3 Copper", 7, copper3);
		assertTrue("P4 Copper", 7, copper4);
		
	#if (NOISY_TEST == 1)
		printf("Estate Counts\n");
	#endif
		
		assertTrue("P1 Estates", 3, estate1);
		assertTrue("P2 Estates", 3, estate2);
		assertTrue("P3 Estates", 3, estate3);
		assertTrue("P4 Estates", 3, estate4);
		
	#if (NOISY_TEST == 1)
		printf("Deck Order\n");
	#endif
	
		assertTrue("Same Deck Order", 0, suspicious);
		
	// STARTING HANDS ARE CORRECT
	#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("Case: Starting Hands\n");
	#endif
	
		// Test 1
		#if (NOISY_TEST == 1)
			printf("Simulation 1\n");
		#endif
		
		struct gameState G1, G2, G3, G4, G5;
		
		memset(&G1, 23, sizeof(struct gameState));   // Clear the game state
		initializeGame(numPlayers, k, seed1, &G1);
		assertTrue("G1.handCount[0]", 5, G1.handCount[0]);	
		assertTrue("G1.handCount[1]", 0, G1.handCount[1]);
		assertTrue("G1.handCount[2]", 0, G1.handCount[2]);
		assertTrue("G1.handCount[3]", 0, G1.handCount[3]);
		
		// Test 2
		#if (NOISY_TEST == 1)
			printf("Simulation 2\n");
		#endif
		
		memset(&G2, 23, sizeof(struct gameState));   // Clear the game state
		initializeGame(numPlayers, k, seed2, &G2);
		assertTrue("G2.handCount[0]", 5, G2.handCount[0]);	
		assertTrue("G2.handCount[1]", 0, G2.handCount[1]);
		assertTrue("G2.handCount[2]", 0, G2.handCount[2]);
		assertTrue("G2.handCount[3]", 0, G2.handCount[3]);
		
		// Test 3
		#if (NOISY_TEST == 1)
			printf("Simulation 3\n");
		#endif
		
		memset(&G3, 23, sizeof(struct gameState));   // Clear the game state
		initializeGame(numPlayers, k, seed3, &G3);
		assertTrue("G3.handCount[0]", 5, G3.handCount[0]);	
		assertTrue("G3.handCount[1]", 0, G3.handCount[1]);
		assertTrue("G3.handCount[2]", 0, G3.handCount[2]);
		assertTrue("G3.handCount[3]", 0, G3.handCount[3]);
		
		// Test 4
		#if (NOISY_TEST == 1)
			printf("Simulation 4\n");
		#endif
		
		memset(&G4, 23, sizeof(struct gameState));   // Clear the game state
		initializeGame(numPlayers, k, seed4, &G4);
		assertTrue("G4.handCount[0]", 5, G4.handCount[0]);	
		assertTrue("G4.handCount[1]", 0, G4.handCount[1]);
		assertTrue("G4.handCount[2]", 0, G4.handCount[2]);
		assertTrue("G4.handCount[3]", 0, G4.handCount[3]);
		
		// Test 5
		#if (NOISY_TEST == 1)
			printf("Simulation 5\n");
		#endif
		
		memset(&G5, 23, sizeof(struct gameState));   // Clear the game state
		initializeGame(numPlayers, k, seed5, &G5);
		assertTrue("G5.handCount[0]", 5, G5.handCount[0]);	
		assertTrue("G5.handCount[1]", 0, G5.handCount[1]);
		assertTrue("G5.handCount[2]", 0, G5.handCount[2]);
		assertTrue("G5.handCount[3]", 0, G5.handCount[3]);
		
		// Hand Order Test
		#if (NOISY_TEST == 1)
			printf("Hand Order\n");
		#endif
		
		suspicious = 1;
		for (i = 0; i < 5; i++)
		{
			if (G1.hand[0][i] != G2.hand[0][i] || G1.hand[0][i] != G3.hand[0][i] || G1.hand[0][i] != G4.hand[0][i] || G1.hand[0][i] != G5.hand[0][i])
			{
				suspicious = 0;
			}
		}
		
		assertTrue("Same Hand Order", 0, suspicious);
		
	// STARTING EMBARGO TOKENS ARE AT ZERO
	#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("Case: Starting Embargo Tokens\n");
	#endif
	
		// Simulation
		#if (NOISY_TEST == 1)
			printf("Simulation\n");
		#endif
		
		initializeGame(numPlayers, k, seed1, &G);
		
		for (i = 0; i <= treasure_map; i++)
		{
			if (G.embargoTokens[i] == 0)
			{
				#if (NOISY_TEST == 1)
					printf("  PASS: G.embargoTokens[%d] = 0, Expected = 0\n", i);
				#endif
			}
			else
			{
				#if (NOISY_TEST == 1)
					printf("! FAIL: G.embargoTokens[%d] = %d, Expected = 0\n", i, G.embargoTokens[i]);
				#endif
			}

		}
		
	// OTHER STARTING CONDITIONS ARE CORRECT
	#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("Case: Other Starting Conditions\n");
	#endif
	
		// Test 1
		#if (NOISY_TEST == 1)
			printf("Simulation 1\n");
		#endif
		
		initializeGame(numPlayers, k, seed1, &G);
		
		assertTrue("G.outpostPlayed", 0, G.outpostPlayed);	
		assertTrue("G.phase", 0, G.phase);	
		assertTrue("G.numActions", 1, G.numActions);	
		assertTrue("G.numBuys", 1, G.numBuys);	
		assertTrue("G.playedCardCount", 0, G.playedCardCount);	
		assertTrue("G.whoseTurn", 0, G.whoseTurn);	
		
		// Test 2
		#if (NOISY_TEST == 1)
			printf("Simulation 2\n");
		#endif
		
		initializeGame(numPlayers, k, seed2, &G);
		
		assertTrue("G.outpostPlayed", 0, G.outpostPlayed);	
		assertTrue("G.phase", 0, G.phase);	
		assertTrue("G.numActions", 1, G.numActions);	
		assertTrue("G.numBuys", 1, G.numBuys);	
		assertTrue("G.playedCardCount", 0, G.playedCardCount);	
		assertTrue("G.whoseTurn", 0, G.whoseTurn);	
		
		// Test 3
		#if (NOISY_TEST == 1)
			printf("Simulation 3\n");
		#endif
		
		initializeGame(numPlayers, k, seed3, &G);
		
		assertTrue("G.outpostPlayed", 0, G.outpostPlayed);	
		assertTrue("G.phase", 0, G.phase);	
		assertTrue("G.numActions", 1, G.numActions);	
		assertTrue("G.numBuys", 1, G.numBuys);	
		assertTrue("G.playedCardCount", 0, G.playedCardCount);	
		assertTrue("G.whoseTurn", 0, G.whoseTurn);	
	
	return;
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























