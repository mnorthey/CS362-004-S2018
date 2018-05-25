/***************************************************
* Date: April 28, 2018
* Name: Matthew Northey
* Assignment: #3 Card Test 2 - Smithy
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
void testBaseBehavior();
void testForcedShuffle();
void testOtherPlayers();
void testStates();



/****************************************************
*
* main()
*
****************************************************/

int main() {
	// Setup
	printf("------------------------------------------------------------------\n-\n");
	printf("- CARD TEST 2: Smithy\n-\n");
	printf("------------------------------------------------------------------\n");
		
	// ~~~~~~~~TESTS~~~~~~~~
	testBaseBehavior();
	testForcedShuffle();
	testOtherPlayers();
	testStates();
	
	// Final message
	printf("\n");
	
    return 0;
}




/****************************************************
*
* testBaseBehavior()
*
****************************************************/

void testBaseBehavior()
{
	// Set up main variables
	int i;
	int numPlayers = 4;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int seed = 1000;
	struct gameState G;
	memset(&G, 23, sizeof(struct gameState));   // Clear the game state
	
	#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("TESTING Base Behavior\n");
	#endif
	
	#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("Case: Base Game States\n");
	#endif
	
	// Simulate game
	initializeGame(numPlayers, k, seed, &G);
	gainCard(smithy, &G, 2, 0);
	
	// Save conditions
	int hand_count = G.handCount[0];
	int deck_count = G.deckCount[0];
	int coins = G.coins;
	
	int actions = G.numActions;
	
	// Play smithy
	playCard(5, 0, 0, 0, &G);
	
	// Check that hand size increased by two
	assertTrue("G.handCount[0]", hand_count + 2, G.handCount[0]);

	// Check that coins were added correctly
	for (i = 5; i < G.handCount[0]; i++)
	{
		if (G.hand[0][i] == copper)
		{
			coins += 1;
		}
		else if (G.hand[0][i] == silver)
		{
			coins += 2;
		}
		else if (G.hand[0][i] == gold)
		{
			coins += 3;
		}
	}
	
	assertTrue("G.coins", coins, G.coins);
	
	// Check that deck size decreased by three
	assertTrue("G.deckCount[0]", deck_count - 3, G.deckCount[0] + G.discardCount[0]);
	
	// Check that player actions decreased by one
	assertTrue("G.numActions", actions - 1, G.numActions);
	
	#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("Case: More Cards in Play\n");
	#endif
	
	// Simulate game
	initializeGame(numPlayers, k, seed, &G);
	gainCard(gold, &G, 1, 0);
	gainCard(silver, &G, 1, 0);
	gainCard(copper, &G, 1, 0);
	gainCard(silver, &G, 1, 0);
	gainCard(copper, &G, 1, 0);
	gainCard(mine, &G, 1, 0);
	gainCard(gardens, &G, 1, 0);
	gainCard(feast, &G, 1, 0);
	gainCard(council_room, &G, 1, 0);
	gainCard(estate, &G, 1, 0);
	gainCard(estate, &G, 1, 0);
	gainCard(duchy, &G, 1, 0);
	gainCard(copper, &G, 1, 0);
	gainCard(silver, &G, 1, 0);
	gainCard(copper, &G, 1, 0);
	shuffle(0, &G);
	
	discardCard(0, 0, &G, 0);
	discardCard(1, 0, &G, 0);
	discardCard(2, 0, &G, 0);
	discardCard(3, 0, &G, 0);
	discardCard(4, 0, &G, 0);
	
	drawCard(0, &G);
	drawCard(0, &G);
	drawCard(0, &G);
	drawCard(0, &G);
	drawCard(0, &G);
	
	discardCard(0, 0, &G, 0);
	discardCard(1, 0, &G, 0);
	discardCard(2, 0, &G, 0);
	discardCard(3, 0, &G, 0);
	discardCard(4, 0, &G, 0);
	
	drawCard(0, &G);
	drawCard(0, &G);
	drawCard(0, &G);
	drawCard(0, &G);
	drawCard(0, &G);
	
	gainCard(smithy, &G, 2, 0);
	updateCoins(0, &G, 0);
	
	// Save conditions
	hand_count = G.handCount[0];
	deck_count = G.deckCount[0];
	coins = G.coins;
	
	actions = G.numActions;
	
	// Play smithy
	playCard(5, 0, 0, 0, &G);
	
	// Check that hand size increased by two
	assertTrue("G.handCount[0]", hand_count + 2, G.handCount[0]);

	// Check that coins were added correctly
	for (i = 5; i < G.handCount[0]; i++)
	{
		if (G.hand[0][i] == copper)
		{
			coins += 1;
		}
		else if (G.hand[0][i] == silver)
		{
			coins += 2;
		}
		else if (G.hand[0][i] == gold)
		{
			coins += 3;
		}
	}
	
	assertTrue("G.coins", coins, G.coins);
	
	// Check that deck size decreased by three
	assertTrue("G.deckCount[0]", deck_count - 3, G.deckCount[0] + G.discardCount[0]);
	
	// Check that player actions decreased by one
	assertTrue("G.numActions", actions - 1, G.numActions);
}




/****************************************************
*
* testForcedShuffle()
*
****************************************************/

void testForcedShuffle()
{
	// Set up main variables
	int i;
	int numPlayers = 4;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int seed = 1000;
	struct gameState G;
	memset(&G, 23, sizeof(struct gameState));   // Clear the game state
	
	#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("TESTING Forced Shuffle\n");
	#endif
	
	#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("Case: Base Game States\n");
	#endif
	
	// Simulate game
	initializeGame(numPlayers, k, seed, &G);
	gainCard(silver, &G, 0, 0);
	gainCard(copper, &G, 0, 0);
	gainCard(mine, &G, 0, 0);
	gainCard(gardens, &G, 0, 0);
	gainCard(feast, &G, 0, 0);
	
	discardCard(0, 0, &G, 0);
	discardCard(1, 0, &G, 0);
	discardCard(2, 0, &G, 0);
	discardCard(3, 0, &G, 0);
	discardCard(4, 0, &G, 0);
	
	drawCard(0, &G);
	drawCard(0, &G);
	drawCard(0, &G);
	drawCard(0, &G);
	drawCard(0, &G);
	
	gainCard(smithy, &G, 2, 0);
	updateCoins(0, &G, 0);
	
	// Save conditions
	int hand_count = G.handCount[0];
	int non_hand_count = G.deckCount[0] + G.discardCount[0];
	int coins = G.coins;
	
	int actions = G.numActions;
	
	// Play smithy
	playCard(5, 0, 0, 0, &G);
	
	// Check that hand size increased by two
	assertTrue("G.handCount[0]", hand_count + 2, G.handCount[0]);

	// Check that coins were added correctly
	for (i = 5; i < G.handCount[0]; i++)
	{
		if (G.hand[0][i] == copper)
		{
			coins += 1;
		}
		else if (G.hand[0][i] == silver)
		{
			coins += 2;
		}
		else if (G.hand[0][i] == gold)
		{
			coins += 3;
		}
	}
	
	assertTrue("G.coins", coins, G.coins);
	
	// Check that deck + discard size decreased by three
	assertTrue("G.deckCount[0] + G.discardCount[0]", non_hand_count - 3, G.deckCount[0] + G.discardCount[0]);
	
	// Check that player actions decreased by one
	assertTrue("G.numActions", actions - 1, G.numActions);
	
	#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("Case: More Cards in Play\n");
	#endif
	
	// Simulate game
	initializeGame(numPlayers, k, seed, &G);
	gainCard(gold, &G, 0, 0);
	gainCard(silver, &G, 0, 0);
	gainCard(copper, &G, 0, 0);
	gainCard(silver, &G, 0, 0);
	gainCard(copper, &G, 0, 0);
	gainCard(mine, &G, 0, 0);
	gainCard(gardens, &G, 0, 0);
	gainCard(feast, &G, 0, 0);
	gainCard(council_room, &G, 0, 0);
	gainCard(estate, &G, 0, 0);
	gainCard(estate, &G, 0, 0);
	gainCard(duchy, &G, 0, 0);
	gainCard(copper, &G, 0, 0);
	gainCard(silver, &G, 0, 0);
	gainCard(copper, &G, 0, 0);
	
	discardCard(0, 0, &G, 0);
	discardCard(1, 0, &G, 0);
	discardCard(2, 0, &G, 0);
	discardCard(3, 0, &G, 0);
	discardCard(4, 0, &G, 0);
	
	drawCard(0, &G);
	drawCard(0, &G);
	drawCard(0, &G);
	drawCard(0, &G);
	drawCard(0, &G);
	
	gainCard(smithy, &G, 2, 0);
	updateCoins(0, &G, 0);
	
	// Save conditions
	hand_count = G.handCount[0];
	non_hand_count = G.deckCount[0] + G.discardCount[0];
	coins = G.coins;
	
	actions = G.numActions;
	
	// Play smithy
	playCard(5, 0, 0, 0, &G);
	
	// Check that hand size increased by two
	assertTrue("G.handCount[0]", hand_count + 2, G.handCount[0]);

	// Check that coins were added correctly
	for (i = 5; i < G.handCount[0]; i++)
	{
		if (G.hand[0][i] == copper)
		{
			coins += 1;
		}
		else if (G.hand[0][i] == silver)
		{
			coins += 2;
		}
		else if (G.hand[0][i] == gold)
		{
			coins += 3;
		}
	}
	
	assertTrue("G.coins", coins, G.coins);
	
	// Check that deck + discard size decreased by three
	assertTrue("G.deckCount[0] + G.discardCount[0]", non_hand_count - 3, G.deckCount[0] + G.discardCount[0]);
	
	// Check that player actions decreased by one
	assertTrue("G.numActions", actions - 1, G.numActions);
}




/****************************************************
*
* testOtherPlayers()
*
****************************************************/

void testOtherPlayers()
{
	// Set up main variables
	int i, j;
	int numPlayers = 4;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int seed = 1000;
	struct gameState G;
	memset(&G, 23, sizeof(struct gameState));   // Clear the game state
	
	#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("TESTING Other Player Pile Counts and Composition\n");
	#endif
	
	#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("Case: Base Game States\n");
	#endif
		
	// Simulate game
	initializeGame(numPlayers, k, seed, &G);
	gainCard(smithy, &G, 2, 0);
	gainCard(gold, &G, 1, 0);
	gainCard(silver, &G, 1, 0);
	gainCard(copper, &G, 1, 0);
	gainCard(silver, &G, 1, 0);
	gainCard(copper, &G, 1, 0);
	shuffle(0, &G);

	// Save counts
	int hand_count[3], deck_count[3], discard_count[3];
	
	for (i = 1; i < 4; i++)
	{
		hand_count[i] = G.handCount[i];
		deck_count[i] = G.deckCount[i];
		discard_count[i] = G.discardCount[i];
	}
	
	// Save compositions
	int deck_comp[4][MAX_DECK];
	int hand_comp[4][MAX_HAND];
	int discard_comp[4][MAX_DECK];
	
	for (i = 1; i < 4; i++)
	{
		for (j = 0; j < MAX_DECK; j++)
		{
			deck_comp[i][j] = G.deck[i][j];
			discard_comp[i][j] = G.discard[i][j];
		}
		
		for (j = 0; j < MAX_HAND; j++)
		{
			hand_comp[i][j] = G.hand[i][j];
		}
	}

	// Play smithy
	playCard(5, 0, 0, 0, &G);
	
	// Test counts
	for (i = 1; i < 4; i++)
	{
		if (deck_count[i] == G.deckCount[i])
		{
			#if (NOISY_TEST == 1)
				printf("  PASS: G.deckCount[%d] = %d, Expected = %d\n", i, G.deckCount[i], deck_count[i]);
			#endif
		}
		else
		{
			#if (NOISY_TEST == 1)
				printf("! FAIL: G.deckCount[%d] = %d, Expected = %d\n", i, G.deckCount[i], deck_count[i]);
			#endif
		}
		
		if (hand_count[i] == G.handCount[i])
		{
			#if (NOISY_TEST == 1)
				printf("  PASS: G.handCount[%d] = %d, Expected = %d\n", i, G.handCount[i], hand_count[i]);
			#endif
		}
		else
		{
			#if (NOISY_TEST == 1)
				printf("! FAIL: G.handCount[%d] = %d, Expected = %d\n", i, G.handCount[i], hand_count[i]);
			#endif
		}
		
		if (discard_count[i] == G.discardCount[i])
		{
			#if (NOISY_TEST == 1)
				printf("  PASS: G.discardCount[%d] = %d, Expected = %d\n", i, G.discardCount[i], discard_count[i]);
			#endif
		}
		else
		{
			#if (NOISY_TEST == 1)
				printf("! FAIL: G.discardCount[%d] = %d, Expected = %d\n", i, G.discardCount[i], discard_count[i]);
			#endif
		}
	}
	
	// Test compositions for any changes to composition or order
	int deck_flag = 0;
	int hand_flag = 0;
	int discard_flag = 0;
	for (i = 1; i < 4; i++)
	{
		for (j = 0; j < G.deckCount[i]; j++)
		{
			if (G.deck[i][j] != deck_comp[i][j])
			{
				deck_flag = 1;
			}
		}
		
		for (j = 0; j < G.discardCount[i]; j++)
		{
			if (G.discard[i][j] != discard_comp[i][j])
			{
				discard_flag = 1;
			}
		}
		
		for (j = 0; j < G.handCount[i]; j++)
		{
			if (G.hand[i][j] != hand_comp[i][j])
			{
				hand_flag = 1;
			}
		}
		
		if (deck_flag == 0)
		{
			#if (NOISY_TEST == 1)
				printf("  PASS: P%d Deck Change = 0, Expected = 0\n", i);
			#endif
		}
		else
		{
			#if (NOISY_TEST == 1)
				printf("! FAIL: P%d Deck Change = 1, Expected = 0\n", i);
			#endif
		}
		
		if (discard_flag == 0)
		{
			#if (NOISY_TEST == 1)
				printf("  PASS: P%d Discard Change = 0, Expected = 0\n", i);
			#endif
		}
		else
		{
			#if (NOISY_TEST == 1)
				printf("! FAIL: P%d Discard Change = 1, Expected = 0\n", i);
			#endif
		}
		
		if (hand_flag == 0)
		{
			#if (NOISY_TEST == 1)
				printf("  PASS: P%d Hand Change = 0, Expected = 0\n", i);
			#endif
		}
		else
		{
			#if (NOISY_TEST == 1)
				printf("! FAIL: P%d Hand Change = 1, Expected = 0\n", i);
			#endif
		}
	}
	
	#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("Case: Different Deck Compositions\n");
	#endif
		
	// Simulate game
	initializeGame(numPlayers, k, seed, &G);
	gainCard(smithy, &G, 2, 0);
	gainCard(gold, &G, 1, 0);
	gainCard(silver, &G, 1, 0);
	gainCard(copper, &G, 1, 0);
	gainCard(silver, &G, 1, 0);
	gainCard(copper, &G, 1, 0);
	shuffle(0, &G);
	
	gainCard(silver, &G, 1, 1);
	gainCard(gold, &G, 1, 1);
	gainCard(gardens, &G, 1, 1);
	gainCard(feast, &G, 1, 2);
	gainCard(baron, &G, 1, 2);
	gainCard(smithy, &G, 1, 3);
	gainCard(estate, &G, 1, 3);
	gainCard(duchy, &G, 1, 3);
	gainCard(remodel, &G, 1, 3);
	gainCard(village, &G, 1, 3);
	gainCard(baron, &G, 1, 3);
	gainCard(copper, &G, 1, 3);
	gainCard(copper, &G, 1, 3);
	gainCard(copper, &G, 0, 1);
	gainCard(copper, &G, 0, 1);
	gainCard(adventurer, &G, 0, 1);
	gainCard(council_room, &G, 0, 1);
	gainCard(silver, &G, 0, 2);
	gainCard(gold, &G, 0, 2);
	gainCard(gardens, &G, 0, 2);
	gainCard(feast, &G, 0, 3);
	gainCard(baron, &G, 0, 3);
	gainCard(copper, &G, 2, 3);
	gainCard(copper, &G, 2, 3);
	gainCard(adventurer, &G, 2, 3);
	gainCard(council_room, &G, 2, 3);
	gainCard(feast, &G, 2, 1);
	gainCard(baron, &G, 2, 1);
	gainCard(smithy, &G, 2, 2);
	gainCard(estate, &G, 2, 2);
	gainCard(duchy, &G, 2, 2);
	gainCard(remodel, &G, 2, 2);
	gainCard(village, &G, 2, 2);
	gainCard(baron, &G, 2, 2);
	gainCard(copper, &G, 2, 2);
	gainCard(copper, &G, 2, 2);

	// Save counts
	for (i = 1; i < 4; i++)
	{
		hand_count[i] = G.handCount[i];
		deck_count[i] = G.deckCount[i];
		discard_count[i] = G.discardCount[i];
	}
	
	// Save compositions
	for (i = 1; i < 4; i++)
	{
		for (j = 0; j < MAX_DECK; j++)
		{
			deck_comp[i][j] = G.deck[i][j];
			discard_comp[i][j] = G.discard[i][j];
		}
		
		for (j = 0; j < MAX_HAND; j++)
		{
			hand_comp[i][j] = G.hand[i][j];
		}
	}

	// Play smithy
	playCard(5, 0, 0, 0, &G);
	
	// Test counts
	for (i = 1; i < 4; i++)
	{
		if (deck_count[i] == G.deckCount[i])
		{
			#if (NOISY_TEST == 1)
				printf("  PASS: G.deckCount[%d] = %d, Expected = %d\n", i, G.deckCount[i], deck_count[i]);
			#endif
		}
		else
		{
			#if (NOISY_TEST == 1)
				printf("! FAIL: G.deckCount[%d] = %d, Expected = %d\n", i, G.deckCount[i], deck_count[i]);
			#endif
		}
		
		if (hand_count[i] == G.handCount[i])
		{
			#if (NOISY_TEST == 1)
				printf("  PASS: G.handCount[%d] = %d, Expected = %d\n", i, G.handCount[i], hand_count[i]);
			#endif
		}
		else
		{
			#if (NOISY_TEST == 1)
				printf("! FAIL: G.handCount[%d] = %d, Expected = %d\n", i, G.handCount[i], hand_count[i]);
			#endif
		}
		
		if (discard_count[i] == G.discardCount[i])
		{
			#if (NOISY_TEST == 1)
				printf("  PASS: G.discardCount[%d] = %d, Expected = %d\n", i, G.discardCount[i], discard_count[i]);
			#endif
		}
		else
		{
			#if (NOISY_TEST == 1)
				printf("! FAIL: G.discardCount[%d] = %d, Expected = %d\n", i, G.discardCount[i], discard_count[i]);
			#endif
		}
	}
	
	// Test compositions for any changes to composition or order
	deck_flag = 0;
	hand_flag = 0;
	discard_flag = 0;
	for (i = 1; i < 4; i++)
	{
		for (j = 0; j < G.deckCount[i]; j++)
		{
			if (G.deck[i][j] != deck_comp[i][j])
			{
				deck_flag = 1;
			}
		}
		
		for (j = 0; j < G.discardCount[i]; j++)
		{
			if (G.discard[i][j] != discard_comp[i][j])
			{
				discard_flag = 1;
			}
		}
		
		for (j = 0; j < G.handCount[i]; j++)
		{
			if (G.hand[i][j] != hand_comp[i][j])
			{
				hand_flag = 1;
			}
		}
		
		if (deck_flag == 0)
		{
			#if (NOISY_TEST == 1)
				printf("  PASS: P%d Deck Change = 0, Expected = 0\n", i);
			#endif
		}
		else
		{
			#if (NOISY_TEST == 1)
				printf("! FAIL: P%d Deck Change = 1, Expected = 0\n", i);
			#endif
		}
		
		if (discard_flag == 0)
		{
			#if (NOISY_TEST == 1)
				printf("  PASS: P%d Discard Change = 0, Expected = 0\n", i);
			#endif
		}
		else
		{
			#if (NOISY_TEST == 1)
				printf("! FAIL: P%d Discard Change = 1, Expected = 0\n", i);
			#endif
		}
		
		if (hand_flag == 0)
		{
			#if (NOISY_TEST == 1)
				printf("  PASS: P%d Hand Change = 0, Expected = 0\n", i);
			#endif
		}
		else
		{
			#if (NOISY_TEST == 1)
				printf("! FAIL: P%d Hand Change = 1, Expected = 0\n", i);
			#endif
		}
	}
}




/****************************************************
*
* testStates()
*
****************************************************/

void testStates()
{
	// Set up main variables
	int i;
	int numPlayers = 4;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int seed = 1000;
	struct gameState G;
	memset(&G, 23, sizeof(struct gameState));   // Clear the game state
	
	#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("TESTING Game States\n");
	#endif
	
	#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("Case: Base Game States\n");
	#endif
		
	// Simulate game
	initializeGame(numPlayers, k, seed, &G);
	gainCard(smithy, &G, 2, 0);
	gainCard(gold, &G, 1, 0);
	gainCard(silver, &G, 1, 0);
	gainCard(copper, &G, 1, 0);
	gainCard(silver, &G, 1, 0);
	gainCard(copper, &G, 1, 0);
	shuffle(0, &G);

	// Save states
	int num_players = G.numPlayers;
	int supply_count[treasure_map+1];
	int embargo_tokens[treasure_map+1];
	int outpost_played = G.outpostPlayed;
	int outpost_turn = G.outpostTurn;
	int whose_turn = G.whoseTurn;
	int phase = G.phase;
	int num_buys = G.numBuys;
	
	for (i = 0; i < treasure_map + 1; i++)
	{
		supply_count[i] = G.supplyCount[i];
		embargo_tokens[i] = G.embargoTokens[i];
	}
	
	// Play smithy
	playCard(5, 0, 0, 0, &G);

	// Test states
	assertTrue("G.numPlayers", num_players, G.numPlayers);
	assertTrue("G.outpostPlayed", outpost_played, G.outpostPlayed);
	assertTrue("G.outpostTurn", outpost_turn, G.outpostTurn);
	assertTrue("G.whoseTurn", whose_turn, G.whoseTurn);
	assertTrue("G.phase", phase, G.phase);
	assertTrue("G.numBuys", num_buys, G.numBuys);

	int supply_count_change = 0;
	int embargo_token_change = 0;
	
	for (i = 0; i < treasure_map + 1; i++)
	{
		if (supply_count[i] != G.supplyCount[i])
		{
			supply_count_change = 1;
		}
		
		if (embargo_tokens[i] != G.embargoTokens[i])
		{
			embargo_token_change = 1;
		}
		
	}
	
	assertTrue("G.supplyCount[]", 0, supply_count_change);
	assertTrue("G.embargoTokens[]", 0, embargo_token_change);
	
	#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("Case: Alternative Game States\n");
	#endif
		
	// Simulate game
	initializeGame(numPlayers, k, seed, &G);
	gainCard(smithy, &G, 2, 0);
	gainCard(gold, &G, 1, 0);
	gainCard(silver, &G, 1, 0);
	gainCard(copper, &G, 1, 0);
	gainCard(silver, &G, 1, 0);
	gainCard(copper, &G, 1, 0);
	shuffle(0, &G);
	
	G.supplyCount[0] -= 2;
	G.supplyCount[2] -= 3;
	G.supplyCount[3] -= 1;
	G.supplyCount[5] -= 4;
	
	G.embargoTokens[1] += 1;
	G.embargoTokens[2] += 2;
	G.embargoTokens[3] += 1;
	G.embargoTokens[4] += 3;
	
	G.outpostPlayed = 1;
	G.outpostTurn = 1;
	G.whoseTurn = 2;
	G.numBuys = 2;
	
	G.playedCards[0] = adventurer;
	
	G.playedCardCount = 1;
	
	// Save states
	num_players = G.numPlayers;
	outpost_played = G.outpostPlayed;
	outpost_turn = G.outpostTurn;
	whose_turn = G.whoseTurn;
	phase = G.phase;
	num_buys = G.numBuys;
	
	for (i = 0; i < treasure_map + 1; i++)
	{
		supply_count[i] = G.supplyCount[i];
		embargo_tokens[i] = G.embargoTokens[i];
	}

	// Play smithy
	playCard(5, 0, 0, 0, &G);
	
	// Test states
	assertTrue("G.numPlayers", num_players, G.numPlayers);
	assertTrue("G.outpostPlayed", outpost_played, G.outpostPlayed);
	assertTrue("G.outpostTurn", outpost_turn, G.outpostTurn);
	assertTrue("G.whoseTurn", whose_turn, G.whoseTurn);
	assertTrue("G.phase", phase, G.phase);
	assertTrue("G.numBuys", num_buys, G.numBuys);

	supply_count_change = 0;
	embargo_token_change = 0;

	for (i = 0; i < treasure_map + 1; i++)
	{
		if (supply_count[i] != G.supplyCount[i])
		{
			supply_count_change = 1;
		}
		
		if (embargo_tokens[i] != G.embargoTokens[i])
		{
			embargo_token_change = 1;
		}
		
	}
	
	assertTrue("G.supplyCount[]", 0, supply_count_change);
	assertTrue("G.embargoTokens[]", 0, embargo_token_change);
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