/***************************************************
* Date: April 27, 2018
* Name: Matthew Northey
* Assignment: #3 Unit Test 3 - shuffle()
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
void testCounts();
void testComps();
void testStates();
void testShuffle();
void testInvalid();
void assertTrue(char *desc, int expected, int actual);




/****************************************************
*
* main()
*
****************************************************/

int main() {
	// Setup
	printf("------------------------------------------------------------------\n-\n");
	printf("- UNIT TEST 3: shuffle()\n-\n");
	printf("------------------------------------------------------------------\n");
		
	// ~~~~~~~~TESTS~~~~~~~~
	testCounts();
	testComps();
	testStates();
	testShuffle();
	testInvalid();
	
	// Final message
	printf("\n");
	
    return 0;
}




/****************************************************
*
* testCounts()
*
****************************************************/

void testCounts()
{
	// Set up main variables
	int i;
	int numPlayers = 4;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int seed = 1000;
	struct gameState G;
	memset(&G, 23, sizeof(struct gameState));   // Clear the game state
	
	// DECK SIZES REMAINS THE SAME
		#if (NOISY_TEST == 1)
			printf("TESTING Deck, Hand, and Discard Sizes\n");
		#endif
		
		#if (NOISY_TEST == 1)
			printf("------------------------------------------------------------------\n");
			printf("Case: Shuffle After Initial Setup\n");
		#endif
		
			// Simulate game
			initializeGame(numPlayers, k, seed, &G);
		
			// Save sizes
			int deck_counts[4];
			int hand_counts[4];
			int discard_counts[4];
			
			for (i = 0; i < 4; i++)
			{
				deck_counts[i] = G.deckCount[i];
				hand_counts[i] = G.handCount[i];
				discard_counts[i] = G.discardCount[i];
			}
			
			// Shuffle
			shuffle(1, &G);
			
			// Test new values for any changes
			for (i = 0; i < 4; i++)
			{
				if (deck_counts[i] == G.deckCount[i])
				{
					#if (NOISY_TEST == 1)
						printf("  PASS: G.deckCount[%d] = %d, Expected = %d\n", i, G.deckCount[i], deck_counts[i]);
					#endif
				}
				else
				{
					#if (NOISY_TEST == 1)
						printf("! FAIL: G.deckCount[%d] = %d, Expected = %d\n", i, G.deckCount[i], deck_counts[i]);
					#endif
				}
				
				if (hand_counts[i] == G.handCount[i])
				{
					#if (NOISY_TEST == 1)
						printf("  PASS: G.handCount[%d] = %d, Expected = %d\n", i, G.handCount[i], hand_counts[i]);
					#endif
				}
				else
				{
					#if (NOISY_TEST == 1)
						printf("! FAIL: G.handCount[%d] = %d, Expected = %d\n", i, G.handCount[i], hand_counts[i]);
					#endif
				}
				
				if (discard_counts[i] == G.discardCount[i])
				{
					#if (NOISY_TEST == 1)
						printf("  PASS: G.discardCount[%d] = %d, Expected = %d\n", i, G.discardCount[i], discard_counts[i]);
					#endif
				}
				else
				{
					#if (NOISY_TEST == 1)
						printf("! FAIL: G.discardCount[%d] = %d, Expected = %d\n", i, G.discardCount[i], discard_counts[i]);
					#endif
				}
			}
			
		#if (NOISY_TEST == 1)
			printf("------------------------------------------------------------------\n");
			printf("Case: Shuffle With Different Deck Sizes\n");
		#endif
		
			// Simulate game
			initializeGame(numPlayers, k, seed, &G);
			gainCard(copper, &G, 1, 0);
			gainCard(copper, &G, 1, 0);
			gainCard(adventurer, &G, 1, 0);
			gainCard(council_room, &G, 1, 0);
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
		
			// Save sizes
			for (i = 0; i < 4; i++)
			{
				deck_counts[i] = G.deckCount[i];
				hand_counts[i] = G.handCount[i];
				discard_counts[i] = G.discardCount[i];
			}
			
			// Shuffle
			shuffle(1, &G);
			
			// Test new values for any changes
			for (i = 0; i < 4; i++)
			{
				if (deck_counts[i] == G.deckCount[i])
				{
					#if (NOISY_TEST == 1)
						printf("  PASS: G.deckCount[%d] = %d, Expected = %d\n", i, G.deckCount[i], deck_counts[i]);
					#endif
				}
				else
				{
					#if (NOISY_TEST == 1)
						printf("! FAIL: G.deckCount[%d] = %d, Expected = %d\n", i, G.deckCount[i], deck_counts[i]);
					#endif
				}
				
				if (hand_counts[i] == G.handCount[i])
				{
					#if (NOISY_TEST == 1)
						printf("  PASS: G.handCount[%d] = %d, Expected = %d\n", i, G.handCount[i], hand_counts[i]);
					#endif
				}
				else
				{
					#if (NOISY_TEST == 1)
						printf("! FAIL: G.handCount[%d] = %d, Expected = %d\n", i, G.handCount[i], hand_counts[i]);
					#endif
				}
				
				if (discard_counts[i] == G.discardCount[i])
				{
					#if (NOISY_TEST == 1)
						printf("  PASS: G.discardCount[%d] = %d, Expected = %d\n", i, G.discardCount[i], discard_counts[i]);
					#endif
				}
				else
				{
					#if (NOISY_TEST == 1)
						printf("! FAIL: G.discardCount[%d] = %d, Expected = %d\n", i, G.discardCount[i], discard_counts[i]);
					#endif
				}
			}
			
		#if (NOISY_TEST == 1)
			printf("------------------------------------------------------------------\n");
			printf("Case: Shuffle With Different Hand Sizes\n");
		#endif
		
			// Simulate game
			initializeGame(numPlayers, k, seed, &G);
			gainCard(copper, &G, 2, 0);
			gainCard(copper, &G, 2, 0);
			gainCard(adventurer, &G, 2, 0);
			gainCard(council_room, &G, 2, 0);
			gainCard(silver, &G, 2, 1);
			gainCard(gold, &G, 2, 1);
			gainCard(gardens, &G, 2, 1);
			gainCard(feast, &G, 2, 2);
			gainCard(baron, &G, 2, 2);
			gainCard(smithy, &G, 2, 3);
			gainCard(estate, &G, 2, 3);
			gainCard(duchy, &G, 2, 3);
			gainCard(remodel, &G, 2, 3);
			gainCard(village, &G, 2, 3);
			gainCard(baron, &G, 2, 3);
			gainCard(copper, &G, 2, 3);
			gainCard(copper, &G, 2, 3);
		
			// Save sizes
			for (i = 0; i < 4; i++)
			{
				deck_counts[i] = G.deckCount[i];
				hand_counts[i] = G.handCount[i];
				discard_counts[i] = G.discardCount[i];
			}
			
			// Shuffle
			shuffle(1, &G);
			
			// Test new values for any changes
			for (i = 0; i < 4; i++)
			{
				if (deck_counts[i] == G.deckCount[i])
				{
					#if (NOISY_TEST == 1)
						printf("  PASS: G.deckCount[%d] = %d, Expected = %d\n", i, G.deckCount[i], deck_counts[i]);
					#endif
				}
				else
				{
					#if (NOISY_TEST == 1)
						printf("! FAIL: G.deckCount[%d] = %d, Expected = %d\n", i, G.deckCount[i], deck_counts[i]);
					#endif
				}
				
				if (hand_counts[i] == G.handCount[i])
				{
					#if (NOISY_TEST == 1)
						printf("  PASS: G.handCount[%d] = %d, Expected = %d\n", i, G.handCount[i], hand_counts[i]);
					#endif
				}
				else
				{
					#if (NOISY_TEST == 1)
						printf("! FAIL: G.handCount[%d] = %d, Expected = %d\n", i, G.handCount[i], hand_counts[i]);
					#endif
				}
				
				if (discard_counts[i] == G.discardCount[i])
				{
					#if (NOISY_TEST == 1)
						printf("  PASS: G.discardCount[%d] = %d, Expected = %d\n", i, G.discardCount[i], discard_counts[i]);
					#endif
				}
				else
				{
					#if (NOISY_TEST == 1)
						printf("! FAIL: G.discardCount[%d] = %d, Expected = %d\n", i, G.discardCount[i], discard_counts[i]);
					#endif
				}
			}
			
		#if (NOISY_TEST == 1)
			printf("------------------------------------------------------------------\n");
			printf("Case: Shuffle With Different Discard Sizes\n");
		#endif
		
			// Simulate game
			initializeGame(numPlayers, k, seed, &G);
			gainCard(copper, &G, 0, 0);
			gainCard(copper, &G, 0, 0);
			gainCard(adventurer, &G, 0, 0);
			gainCard(council_room, &G, 0, 0);
			gainCard(silver, &G, 0, 1);
			gainCard(gold, &G, 0, 1);
			gainCard(gardens, &G, 0, 1);
			gainCard(feast, &G, 0, 2);
			gainCard(baron, &G, 0, 2);
			gainCard(smithy, &G, 0, 3);
			gainCard(estate, &G, 0, 3);
			gainCard(duchy, &G, 0, 3);
			gainCard(remodel, &G, 0, 3);
			gainCard(village, &G, 0, 3);
			gainCard(baron, &G, 0, 3);
			gainCard(copper, &G, 0, 3);
			gainCard(copper, &G, 0, 3);
		
			// Save sizes
			for (i = 0; i < 4; i++)
			{
				deck_counts[i] = G.deckCount[i];
				hand_counts[i] = G.handCount[i];
				discard_counts[i] = G.discardCount[i];
			}
			
			// Shuffle
			shuffle(1, &G);
			
			// Test new values for any changes
			for (i = 0; i < 4; i++)
			{
				if (deck_counts[i] == G.deckCount[i])
				{
					#if (NOISY_TEST == 1)
						printf("  PASS: G.deckCount[%d] = %d, Expected = %d\n", i, G.deckCount[i], deck_counts[i]);
					#endif
				}
				else
				{
					#if (NOISY_TEST == 1)
						printf("! FAIL: G.deckCount[%d] = %d, Expected = %d\n", i, G.deckCount[i], deck_counts[i]);
					#endif
				}
				
				if (hand_counts[i] == G.handCount[i])
				{
					#if (NOISY_TEST == 1)
						printf("  PASS: G.handCount[%d] = %d, Expected = %d\n", i, G.handCount[i], hand_counts[i]);
					#endif
				}
				else
				{
					#if (NOISY_TEST == 1)
						printf("! FAIL: G.handCount[%d] = %d, Expected = %d\n", i, G.handCount[i], hand_counts[i]);
					#endif
				}
				
				if (discard_counts[i] == G.discardCount[i])
				{
					#if (NOISY_TEST == 1)
						printf("  PASS: G.discardCount[%d] = %d, Expected = %d\n", i, G.discardCount[i], discard_counts[i]);
					#endif
				}
				else
				{
					#if (NOISY_TEST == 1)
						printf("! FAIL: G.discardCount[%d] = %d, Expected = %d\n", i, G.discardCount[i], discard_counts[i]);
					#endif
				}
			}
			
		#if (NOISY_TEST == 1)
			printf("------------------------------------------------------------------\n");
			printf("Case: Shuffle With Different Deck, Hand, and Discard Sizes\n");
		#endif
		
			// Simulate game
			initializeGame(numPlayers, k, seed, &G);
			gainCard(copper, &G, 1, 0);
			gainCard(copper, &G, 1, 0);
			gainCard(adventurer, &G, 1, 0);
			gainCard(council_room, &G, 1, 0);
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
			gainCard(smithy, &G, 0, 0);
			gainCard(estate, &G, 0, 0);
			gainCard(duchy, &G, 0, 0);
			gainCard(remodel, &G, 0, 0);
			gainCard(village, &G, 0, 0);
			gainCard(baron, &G, 0, 0);
			gainCard(copper, &G, 0, 0);
			gainCard(copper, &G, 0, 0);
			gainCard(copper, &G, 2, 3);
			gainCard(copper, &G, 2, 3);
			gainCard(adventurer, &G, 2, 3);
			gainCard(council_room, &G, 2, 3);
			gainCard(silver, &G, 2, 0);
			gainCard(gold, &G, 2, 0);
			gainCard(gardens, &G, 2, 0);
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
		
			// Save sizes
			for (i = 0; i < 4; i++)
			{
				deck_counts[i] = G.deckCount[i];
				hand_counts[i] = G.handCount[i];
				discard_counts[i] = G.discardCount[i];
			}
			
			// Shuffle
			shuffle(1, &G);
			
			// Test new values for any changes
			for (i = 0; i < 4; i++)
			{
				if (deck_counts[i] == G.deckCount[i])
				{
					#if (NOISY_TEST == 1)
						printf("  PASS: G.deckCount[%d] = %d, Expected = %d\n", i, G.deckCount[i], deck_counts[i]);
					#endif
				}
				else
				{
					#if (NOISY_TEST == 1)
						printf("! FAIL: G.deckCount[%d] = %d, Expected = %d\n", i, G.deckCount[i], deck_counts[i]);
					#endif
				}
				
				if (hand_counts[i] == G.handCount[i])
				{
					#if (NOISY_TEST == 1)
						printf("  PASS: G.handCount[%d] = %d, Expected = %d\n", i, G.handCount[i], hand_counts[i]);
					#endif
				}
				else
				{
					#if (NOISY_TEST == 1)
						printf("! FAIL: G.handCount[%d] = %d, Expected = %d\n", i, G.handCount[i], hand_counts[i]);
					#endif
				}
				
				if (discard_counts[i] == G.discardCount[i])
				{
					#if (NOISY_TEST == 1)
						printf("  PASS: G.discardCount[%d] = %d, Expected = %d\n", i, G.discardCount[i], discard_counts[i]);
					#endif
				}
				else
				{
					#if (NOISY_TEST == 1)
						printf("! FAIL: G.discardCount[%d] = %d, Expected = %d\n", i, G.discardCount[i], discard_counts[i]);
					#endif
				}
			}
}




/****************************************************
*
* testComps()
*
****************************************************/

void testComps()
{
	// Set up main variables
	int i, j;
	int numPlayers = 4;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int seed = 1000;
	struct gameState G;
	memset(&G, 23, sizeof(struct gameState));   // Clear the game state
	
	// COMPOSITION REMAINS THE SAME
	#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("TESTING Deck, Hand, and Discard Composition\n");
	#endif

	#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("Case: Shuffle After Initial Setup\n");
	#endif

	// Simulate game
	initializeGame(numPlayers, k, seed, &G);

	// Save compositions
	int deck_comp[4][MAX_DECK];
	int hand_comp[4][MAX_HAND];
	int discard_comp[4][MAX_DECK];
	
	for (i = 0; i < 4; i++)
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
	
	// Shuffle
	shuffle(0, &G);
	
	// Test first player composition for any changes to composition, but not order
	int deck_flag = 0;
	int hand_flag = 0;
	int discard_flag = 0;
	
	for (i = 0; i < G.deckCount[0]; i++)
	{
		for (j = 0; j < G.deckCount[0]; j++)
		{
			// Matching card found
			if (G.deck[0][i] == deck_comp[0][j])
			{
				deck_comp[0][j] = -1;
				break;
			}
			// Matching card not found
			else if (j == G.deckCount[0] - 1)
			{
				deck_flag = 1;
			}
		}
	}
	
	for (i = 0; i < G.discardCount[0]; i++)
	{
		for (j = 0; j < G.discardCount[0]; j++)
		{
			// Matching card found
			if (G.discard[0][i] == discard_comp[0][j])
			{
				discard_comp[0][j] = -1;
				break;
			}
			// Matching card not found
			else if (j == G.discardCount[0] - 1)
			{
				discard_flag = 1;
			}
		}
	}
	
	for (i = 0; i < G.handCount[0]; i++)
	{
		for (j = 0; j < G.handCount[0]; j++)
		{
			// Matching card found
			if (G.hand[0][i] == hand_comp[0][j])
			{
				hand_comp[0][j] = -1;
				break;
			}
			// Matching card not found
			else if (j == G.handCount[0] - 1)
			{
				hand_flag = 1;
			}
		}
	}
	
	if (deck_flag == 0)
	{
		#if (NOISY_TEST == 1)
			printf("  PASS: P0 Deck Change = 0, Expected = 0\n");
		#endif
	}
	else
	{
		#if (NOISY_TEST == 1)
			printf("! FAIL: P0 Deck Change = 1, Expected = 0\n");
		#endif
	}
		
	if (discard_flag == 0)
	{
		#if (NOISY_TEST == 1)
			printf("  PASS: P0 Discard Change = 0, Expected = 0\n");
		#endif
	}
	else
	{
		#if (NOISY_TEST == 1)
			printf("! FAIL: P0 Discard Change = 1, Expected = 0\n");
		#endif
	}
		
	if (hand_flag == 0)
	{
		#if (NOISY_TEST == 1)
			printf("  PASS: P0 Hand Change = 0, Expected = 0\n");
		#endif
	}
	else
	{
		#if (NOISY_TEST == 1)
			printf("! FAIL: P0 Hand Change = 1, Expected = 0\n");
		#endif
	}
	
	// Test new non-current player compositions for any changes to composition or order
	for (i = 1; i < 4; i++)
	{
		deck_flag = 0;
		hand_flag = 0;
		discard_flag = 0;
		
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
		printf("Case: Shuffle With Different Deck Compositions\n");
	#endif

	// Simulate game
	initializeGame(numPlayers, k, seed, &G);
	gainCard(copper, &G, 1, 0);
	gainCard(copper, &G, 1, 0);
	gainCard(adventurer, &G, 1, 0);
	gainCard(council_room, &G, 1, 0);
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
	
	// Save compositions
	for (i = 0; i < 4; i++)
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
	
	// Shuffle
	shuffle(0, &G);
	
	// Test first player composition for any changes to composition, but not order
	deck_flag = 0;
	hand_flag = 0;
	discard_flag = 0;
	
	for (i = 0; i < G.deckCount[0]; i++)
	{
		for (j = 0; j < G.deckCount[0]; j++)
		{
			// Matching card found
			if (G.deck[0][i] == deck_comp[0][j])
			{
				deck_comp[0][j] = -1;
				break;
			}
			// Matching card not found
			else if (j == G.deckCount[0] - 1)
			{
				deck_flag = 1;
			}
		}
	}
	
	for (i = 0; i < G.discardCount[0]; i++)
	{
		for (j = 0; j < G.discardCount[0]; j++)
		{
			// Matching card found
			if (G.discard[0][i] == discard_comp[0][j])
			{
				discard_comp[0][j] = -1;
				break;
			}
			// Matching card not found
			else if (j == G.discardCount[0] - 1)
			{
				discard_flag = 1;
			}
		}
	}
	
	for (i = 0; i < G.handCount[0]; i++)
	{
		for (j = 0; j < G.handCount[0]; j++)
		{
			// Matching card found
			if (G.hand[0][i] == hand_comp[0][j])
			{
				hand_comp[0][j] = -1;
				break;
			}
			// Matching card not found
			else if (j == G.handCount[0] - 1)
			{
				hand_flag = 1;
			}
		}
	}
	
	if (deck_flag == 0)
	{
		#if (NOISY_TEST == 1)
			printf("  PASS: P0 Deck Change = 0, Expected = 0\n");
		#endif
	}
	else
	{
		#if (NOISY_TEST == 1)
			printf("! FAIL: P0 Deck Change = 1, Expected = 0\n");
		#endif
	}
		
	if (discard_flag == 0)
	{
		#if (NOISY_TEST == 1)
			printf("  PASS: P0 Discard Change = 0, Expected = 0\n");
		#endif
	}
	else
	{
		#if (NOISY_TEST == 1)
			printf("! FAIL: P0 Discard Change = 1, Expected = 0\n");
		#endif
	}
		
	if (hand_flag == 0)
	{
		#if (NOISY_TEST == 1)
			printf("  PASS: P0 Hand Change = 0, Expected = 0\n");
		#endif
	}
	else
	{
		#if (NOISY_TEST == 1)
			printf("! FAIL: P0 Hand Change = 1, Expected = 0\n");
		#endif
	}
	
	// Test new non-current player compositions for any changes to composition or order
	for (i = 1; i < 4; i++)
	{
		deck_flag = 0;
		hand_flag = 0;
		discard_flag = 0;
		
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
		printf("Case: Shuffle With Different Hand Compositions\n");
	#endif

	// Simulate game
	initializeGame(numPlayers, k, seed, &G);
	gainCard(copper, &G, 2, 0);
	gainCard(copper, &G, 2, 0);
	gainCard(adventurer, &G, 2, 0);
	gainCard(council_room, &G, 2, 0);
	gainCard(silver, &G, 2, 1);
	gainCard(gold, &G, 2, 1);
	gainCard(gardens, &G, 2, 1);
	gainCard(feast, &G, 2, 2);
	gainCard(baron, &G, 2, 2);
	gainCard(smithy, &G, 2, 3);
	gainCard(estate, &G, 2, 3);
	gainCard(duchy, &G, 2, 3);
	gainCard(remodel, &G, 2, 3);
	gainCard(village, &G, 2, 3);
	gainCard(baron, &G, 2, 3);
	gainCard(copper, &G, 2, 3);
	gainCard(copper, &G, 2, 3);
	
	// Save compositions
	for (i = 0; i < 4; i++)
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
	
	// Shuffle
	shuffle(0, &G);
	
	// Test first player composition for any changes to composition, but not order
	deck_flag = 0;
	hand_flag = 0;
	discard_flag = 0;
	
	for (i = 0; i < G.deckCount[0]; i++)
	{
		for (j = 0; j < G.deckCount[0]; j++)
		{
			// Matching card found
			if (G.deck[0][i] == deck_comp[0][j])
			{
				deck_comp[0][j] = -1;
				break;
			}
			// Matching card not found
			else if (j == G.deckCount[0] - 1)
			{
				deck_flag = 1;
			}
		}
	}
	
	for (i = 0; i < G.discardCount[0]; i++)
	{
		for (j = 0; j < G.discardCount[0]; j++)
		{
			// Matching card found
			if (G.discard[0][i] == discard_comp[0][j])
			{
				discard_comp[0][j] = -1;
				break;
			}
			// Matching card not found
			else if (j == G.discardCount[0] - 1)
			{
				discard_flag = 1;
			}
		}
	}
	
	for (i = 0; i < G.handCount[0]; i++)
	{
		for (j = 0; j < G.handCount[0]; j++)
		{
			// Matching card found
			if (G.hand[0][i] == hand_comp[0][j])
			{
				hand_comp[0][j] = -1;
				break;
			}
			// Matching card not found
			else if (j == G.handCount[0] - 1)
			{
				hand_flag = 1;
			}
		}
	}
	
	if (deck_flag == 0)
	{
		#if (NOISY_TEST == 1)
			printf("  PASS: P0 Deck Change = 0, Expected = 0\n");
		#endif
	}
	else
	{
		#if (NOISY_TEST == 1)
			printf("! FAIL: P0 Deck Change = 1, Expected = 0\n");
		#endif
	}
		
	if (discard_flag == 0)
	{
		#if (NOISY_TEST == 1)
			printf("  PASS: P0 Discard Change = 0, Expected = 0\n");
		#endif
	}
	else
	{
		#if (NOISY_TEST == 1)
			printf("! FAIL: P0 Discard Change = 1, Expected = 0\n");
		#endif
	}
		
	if (hand_flag == 0)
	{
		#if (NOISY_TEST == 1)
			printf("  PASS: P0 Hand Change = 0, Expected = 0\n");
		#endif
	}
	else
	{
		#if (NOISY_TEST == 1)
			printf("! FAIL: P0 Hand Change = 1, Expected = 0\n");
		#endif
	}
	
	// Test new non-current player compositions for any changes to composition or order
	for (i = 1; i < 4; i++)
	{
		deck_flag = 0;
		hand_flag = 0;
		discard_flag = 0;
		
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
		printf("Case: Shuffle With Different Discard Compositions\n");
	#endif

	// Simulate game
	initializeGame(numPlayers, k, seed, &G);
	gainCard(copper, &G, 0, 0);
	gainCard(copper, &G, 0, 0);
	gainCard(adventurer, &G, 0, 0);
	gainCard(council_room, &G, 0, 0);
	gainCard(silver, &G, 0, 1);
	gainCard(gold, &G, 0, 1);
	gainCard(gardens, &G, 0, 1);
	gainCard(feast, &G, 0, 2);
	gainCard(baron, &G, 0, 2);
	gainCard(smithy, &G, 0, 3);
	gainCard(estate, &G, 0, 3);
	gainCard(duchy, &G, 0, 3);
	gainCard(remodel, &G, 0, 3);
	gainCard(village, &G, 0, 3);
	gainCard(baron, &G, 0, 3);
	gainCard(copper, &G, 0, 3);
	gainCard(copper, &G, 0, 3);
	
	// Save compositions
	for (i = 0; i < 4; i++)
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
	
	// Shuffle
	shuffle(0, &G);
	
	// Test first player composition for any changes to composition, but not order
	deck_flag = 0;
	hand_flag = 0;
	discard_flag = 0;
	
	for (i = 0; i < G.deckCount[0]; i++)
	{
		for (j = 0; j < G.deckCount[0]; j++)
		{
			// Matching card found
			if (G.deck[0][i] == deck_comp[0][j])
			{
				deck_comp[0][j] = -1;
				break;
			}
			// Matching card not found
			else if (j == G.deckCount[0] - 1)
			{
				deck_flag = 1;
			}
		}
	}
	
	for (i = 0; i < G.discardCount[0]; i++)
	{
		for (j = 0; j < G.discardCount[0]; j++)
		{
			// Matching card found
			if (G.discard[0][i] == discard_comp[0][j])
			{
				discard_comp[0][j] = -1;
				break;
			}
			// Matching card not found
			else if (j == G.discardCount[0] - 1)
			{
				discard_flag = 1;
			}
		}
	}
	
	for (i = 0; i < G.handCount[0]; i++)
	{
		for (j = 0; j < G.handCount[0]; j++)
		{
			// Matching card found
			if (G.hand[0][i] == hand_comp[0][j])
			{
				hand_comp[0][j] = -1;
				break;
			}
			// Matching card not found
			else if (j == G.handCount[0] - 1)
			{
				hand_flag = 1;
			}
		}
	}
	
	if (deck_flag == 0)
	{
		#if (NOISY_TEST == 1)
			printf("  PASS: P0 Deck Change = 0, Expected = 0\n");
		#endif
	}
	else
	{
		#if (NOISY_TEST == 1)
			printf("! FAIL: P0 Deck Change = 1, Expected = 0\n");
		#endif
	}
		
	if (discard_flag == 0)
	{
		#if (NOISY_TEST == 1)
			printf("  PASS: P0 Discard Change = 0, Expected = 0\n");
		#endif
	}
	else
	{
		#if (NOISY_TEST == 1)
			printf("! FAIL: P0 Discard Change = 1, Expected = 0\n");
		#endif
	}
		
	if (hand_flag == 0)
	{
		#if (NOISY_TEST == 1)
			printf("  PASS: P0 Hand Change = 0, Expected = 0\n");
		#endif
	}
	else
	{
		#if (NOISY_TEST == 1)
			printf("! FAIL: P0 Hand Change = 1, Expected = 0\n");
		#endif
	}
	
	// Test new non-current player compositions for any changes to composition or order
	for (i = 1; i < 4; i++)
	{
		deck_flag = 0;
		hand_flag = 0;
		discard_flag = 0;
		
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
		printf("Case: Shuffle With Different Deck, Hand, and Discard Compositions\n");
	#endif

	// Simulate game
	initializeGame(numPlayers, k, seed, &G);
	gainCard(copper, &G, 1, 0);
	gainCard(copper, &G, 1, 0);
	gainCard(adventurer, &G, 1, 0);
	gainCard(council_room, &G, 1, 0);
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
	gainCard(smithy, &G, 0, 0);
	gainCard(estate, &G, 0, 0);
	gainCard(duchy, &G, 0, 0);
	gainCard(remodel, &G, 0, 0);
	gainCard(village, &G, 0, 0);
	gainCard(baron, &G, 0, 0);
	gainCard(copper, &G, 0, 0);
	gainCard(copper, &G, 0, 0);
	gainCard(copper, &G, 2, 3);
	gainCard(copper, &G, 2, 3);
	gainCard(adventurer, &G, 2, 3);
	gainCard(council_room, &G, 2, 3);
	gainCard(silver, &G, 2, 0);
	gainCard(gold, &G, 2, 0);
	gainCard(gardens, &G, 2, 0);
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
	
	// Save compositions
	for (i = 0; i < 4; i++)
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
	
	// Shuffle
	shuffle(0, &G);
	
	// Test first player composition for any changes to composition, but not order
	deck_flag = 0;
	hand_flag = 0;
	discard_flag = 0;
	
	for (i = 0; i < G.deckCount[0]; i++)
	{
		for (j = 0; j < G.deckCount[0]; j++)
		{
			// Matching card found
			if (G.deck[0][i] == deck_comp[0][j])
			{
				deck_comp[0][j] = -1;
				break;
			}
			// Matching card not found
			else if (j == G.deckCount[0] - 1)
			{
				deck_flag = 1;
			}
		}
	}
	
	for (i = 0; i < G.discardCount[0]; i++)
	{
		for (j = 0; j < G.discardCount[0]; j++)
		{
			// Matching card found
			if (G.discard[0][i] == discard_comp[0][j])
			{
				discard_comp[0][j] = -1;
				break;
			}
			// Matching card not found
			else if (j == G.discardCount[0] - 1)
			{
				discard_flag = 1;
			}
		}
	}
	
	for (i = 0; i < G.handCount[0]; i++)
	{
		for (j = 0; j < G.handCount[0]; j++)
		{
			// Matching card found
			if (G.hand[0][i] == hand_comp[0][j])
			{
				hand_comp[0][j] = -1;
				break;
			}
			// Matching card not found
			else if (j == G.handCount[0] - 1)
			{
				hand_flag = 1;
			}
		}
	}
	
	if (deck_flag == 0)
	{
		#if (NOISY_TEST == 1)
			printf("  PASS: P0 Deck Change = 0, Expected = 0\n");
		#endif
	}
	else
	{
		#if (NOISY_TEST == 1)
			printf("! FAIL: P0 Deck Change = 1, Expected = 0\n");
		#endif
	}
		
	if (discard_flag == 0)
	{
		#if (NOISY_TEST == 1)
			printf("  PASS: P0 Discard Change = 0, Expected = 0\n");
		#endif
	}
	else
	{
		#if (NOISY_TEST == 1)
			printf("! FAIL: P0 Discard Change = 1, Expected = 0\n");
		#endif
	}
		
	if (hand_flag == 0)
	{
		#if (NOISY_TEST == 1)
			printf("  PASS: P0 Hand Change = 0, Expected = 0\n");
		#endif
	}
	else
	{
		#if (NOISY_TEST == 1)
			printf("! FAIL: P0 Hand Change = 1, Expected = 0\n");
		#endif
	}
	
	// Test new non-current player compositions for any changes to composition or order
	for (i = 1; i < 4; i++)
	{
		deck_flag = 0;
		hand_flag = 0;
		discard_flag = 0;
		
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
		printf("Case: Shuffle After Initial Setup\n");
	#endif
		
	// Simulate game
	initializeGame(numPlayers, k, seed, &G);

	// Save states
	int num_players = G.numPlayers;
	int supply_count[treasure_map+1];
	int embargo_tokens[treasure_map+1];
	int outpost_played = G.outpostPlayed;
	int outpost_turn = G.outpostTurn;
	int whose_turn = G.whoseTurn;
	int phase = G.phase;
	int num_actions = G.numActions;
	int coins = G.coins;
	int num_buys = G.numBuys;
	int played_cards[MAX_DECK];
	int played_card_count = G.playedCardCount;
	
	for (i = 0; i < treasure_map + 1; i++)
	{
		supply_count[i] = G.supplyCount[i];
		embargo_tokens[i] = G.embargoTokens[i];
	}
	
	for (i = 0; i < MAX_DECK; i++)
	{
		played_cards[i] = G.playedCards[i];
	}

	// Shuffle
	shuffle(0, &G);
	
	// Test states
	assertTrue("G.numPlayers", num_players, G.numPlayers);
	assertTrue("G.outpostPlayed", outpost_played, G.outpostPlayed);
	assertTrue("G.outpostTurn", outpost_turn, G.outpostTurn);
	assertTrue("G.whoseTurn", whose_turn, G.whoseTurn);
	assertTrue("G.phase", phase, G.phase);
	assertTrue("G.numActions", num_actions, G.numActions);
	assertTrue("G.coins", coins, G.coins);
	assertTrue("G.numBuys", num_buys, G.numBuys);
	assertTrue("G.playedCardCount", played_card_count, G.playedCardCount);

	int supply_count_change = 0;
	int embargo_token_change = 0;
	int played_card_change = 0;
	
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
	
	for (i = 0; i < MAX_DECK; i++)
	{
		if (played_cards[i] != G.playedCards[i])
		{
			played_card_change = 1;
		}
	}
	
	assertTrue("G.supplyCount[]", 0, supply_count_change);
	assertTrue("G.embargoTokens[]", 0, embargo_token_change);
	assertTrue("G.playedCards[]", 0, played_card_change);
	
	#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("Case: Shuffle With Alternate Game States\n");
	#endif
		
	// Simulate game
	initializeGame(3, k, seed, &G);
	
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
	G.phase = 1;
	G.numActions = 3;
	G.coins = 2;
	G.numBuys = 2;
	
	G.playedCards[0] = 2;
	G.playedCards[3] = 1;
	G.playedCards[5] = 5;
	G.playedCards[6] = 4;
	
	G.playedCardCount = 12;

	// Save states
	num_players = G.numPlayers;
	outpost_played = G.outpostPlayed;
	outpost_turn = G.outpostTurn;
	whose_turn = G.whoseTurn;
	phase = G.phase;
	num_actions = G.numActions;
	coins = G.coins;
	num_buys = G.numBuys;
	played_card_count = G.playedCardCount;
	
	for (i = 0; i < treasure_map + 1; i++)
	{
		supply_count[i] = G.supplyCount[i];
		embargo_tokens[i] = G.embargoTokens[i];
	}
	
	for (i = 0; i < MAX_DECK; i++)
	{
		played_cards[i] = G.playedCards[i];
	}

	// Shuffle
	shuffle(0, &G);
	
	// Test states
	assertTrue("G.numPlayers", num_players, G.numPlayers);
	assertTrue("G.outpostPlayed", outpost_played, G.outpostPlayed);
	assertTrue("G.outpostTurn", outpost_turn, G.outpostTurn);
	assertTrue("G.whoseTurn", whose_turn, G.whoseTurn);
	assertTrue("G.phase", phase, G.phase);
	assertTrue("G.numActions", num_actions, G.numActions);
	assertTrue("G.coins", coins, G.coins);
	assertTrue("G.numBuys", num_buys, G.numBuys);
	assertTrue("G.playedCardCount", played_card_count, G.playedCardCount);

	supply_count_change = 0;
	embargo_token_change = 0;
	played_card_change = 0;
	
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
	
	for (i = 0; i < MAX_DECK; i++)
	{
		if (played_cards[i] != G.playedCards[i])
		{
			played_card_change = 1;
		}
	}
	
	assertTrue("G.supplyCount[]", 0, supply_count_change);
	assertTrue("G.embargoTokens[]", 0, embargo_token_change);
	assertTrue("G.playedCards[]", 0, played_card_change);
}




/****************************************************
*
* testShuffle()
*
****************************************************/

void testShuffle()
{
	// Set up main variables
	int i;
	int numPlayers = 4;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int seed1 = 1000;
	int seed2 = 2500;
	int seed3 = 5000;
	struct gameState G1, G2, G3;
	memset(&G1, 23, sizeof(struct gameState));   // Clear the game state
	memset(&G2, 23, sizeof(struct gameState));   // Clear the game state
	memset(&G3, 23, sizeof(struct gameState));   // Clear the game state
	
	#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("TESTING Deck Properly Shuffled\n");
	#endif
	
	#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("Case: Shuffle After Initial Setup\n");
	#endif
		
	// Simulate three games to ensure no "fluke" same-order shuffle
	int cards_shuffled = 0;
	initializeGame(numPlayers, k, seed1, &G1);
	initializeGame(numPlayers, k, seed2, &G2);
	initializeGame(numPlayers, k, seed3, &G3);

	// Save deck orders
	int deck_order1[MAX_DECK];
	int deck_order2[MAX_DECK];
	int deck_order3[MAX_DECK];
	for (i = 0; i < MAX_DECK; i++)
	{
		deck_order1[i] = G1.deck[0][i];
	}
	
	for (i = 0; i < MAX_DECK; i++)
	{
		deck_order2[i] = G2.deck[0][i];
	}
	
	for (i = 0; i < MAX_DECK; i++)
	{
		deck_order3[i] = G3.deck[0][i];
	}

	// Shuffle
	shuffle(0, &G1);
	shuffle(0, &G2);
	shuffle(0, &G3);
	
	// Test shuffle
	for (i = 0; i < MAX_DECK; i++)
	{
		if (deck_order1[i] != G1.deck[0][i])
		{
			cards_shuffled = 1;
			break;
		}
		else if (deck_order2[i] != G2.deck[0][i])
		{
			cards_shuffled = 1;
			break;
		}
		else if (deck_order3[i] != G3.deck[0][i])
		{
			cards_shuffled = 1;
			break;
		}
	}
	
	// Assert shuffle occurred
	assertTrue("Shuffled", 1, cards_shuffled);
	
		#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("Case: Shuffle With Different Deck Composition\n");
	#endif
		
	// Simulate three games to ensure no "fluke" same-order shuffle
	cards_shuffled = 0;
	initializeGame(numPlayers, k, seed1, &G1);
	initializeGame(numPlayers, k, seed2, &G2);
	initializeGame(numPlayers, k, seed3, &G3);
	
	gainCard(copper, &G1, 1, 0);
	gainCard(copper, &G1, 1, 0);
	gainCard(adventurer, &G1, 1, 0);
	gainCard(council_room, &G1, 1, 0);
	gainCard(silver, &G1, 1, 0);
	gainCard(gold, &G1, 1, 0);
	gainCard(gardens, &G1, 1, 0);
	gainCard(feast, &G1, 1, 0);
	gainCard(baron, &G1, 1, 0);
	gainCard(smithy, &G1, 1, 0);
	
	gainCard(copper, &G2, 1, 0);
	gainCard(copper, &G2, 1, 0);
	gainCard(adventurer, &G2, 1, 0);
	gainCard(council_room, &G2, 1, 0);
	gainCard(silver, &G2, 1, 0);
	gainCard(gold, &G2, 1, 0);
	gainCard(gardens, &G2, 1, 0);
	gainCard(feast, &G2, 1, 0);
	gainCard(baron, &G2, 1, 0);
	gainCard(smithy, &G2, 1, 0);
	
	gainCard(copper, &G3, 1, 0);
	gainCard(copper, &G3, 1, 0);
	gainCard(adventurer, &G3, 1, 0);
	gainCard(council_room, &G3, 1, 0);
	gainCard(silver, &G3, 1, 0);
	gainCard(gold, &G3, 1, 0);
	gainCard(gardens, &G3, 1, 0);
	gainCard(feast, &G3, 1, 0);
	gainCard(baron, &G3, 1, 0);
	gainCard(smithy, &G3, 1, 0);

	// Save deck orders
	for (i = 0; i < MAX_DECK; i++)
	{
		deck_order1[i] = G1.deck[0][i];
	}
	
	for (i = 0; i < MAX_DECK; i++)
	{
		deck_order2[i] = G2.deck[0][i];
	}
	
	for (i = 0; i < MAX_DECK; i++)
	{
		deck_order3[i] = G3.deck[0][i];
	}

	// Shuffle
	shuffle(0, &G1);
	shuffle(0, &G2);
	shuffle(0, &G3);
	
	// Test shuffle
	for (i = 0; i < MAX_DECK; i++)
	{
		if (deck_order1[i] != G1.deck[0][i])
		{
			cards_shuffled = 1;
			break;
		}
		else if (deck_order2[i] != G2.deck[0][i])
		{
			cards_shuffled = 1;
			break;
		}
		else if (deck_order3[i] != G3.deck[0][i])
		{
			cards_shuffled = 1;
			break;
		}
	}
	
	// Assert shuffle occurred
	assertTrue("Shuffled", 1, cards_shuffled);
	
}




/****************************************************
*
* testInvalid()
*
****************************************************/

void testInvalid()
{
	// Set up main variables
	int i, s;
	int numPlayers = 3;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int seed = 1000;
	struct gameState G;
	memset(&G, 23, sizeof(struct gameState));   // Clear the game state
	
	#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("TESTING Invalid Inputs\n");
	#endif
	
	#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("Case: Player Doesn't Exist\n");
	#endif
		
	// Simulate game
	initializeGame(numPlayers, k, seed, &G);
	
	
	/****************************************************************
	* Note: Code not executed. Bug found that crashes program.
	* 	Hard-coded to highlight problem.
	****************************************************************/
	
	// Shuffle
	s = 0;
	//s = shuffle(3, &G);
	assertTrue("Return", -1, s);
	
	//s = shuffle(4, &G);
	assertTrue("Return", -1, s);
	
	//s = shuffle(-1, &G);
	assertTrue("Return", -1, s);
	
	// RETURNS ERROR IF PLAYER DOESN'T HAVE A DECK
	#if (NOISY_TEST == 1)
		printf("------------------------------------------------------------------\n");
		printf("Case: Player Doesn't Have Deck\n");
	#endif
		
	// Simulate game
	initializeGame(numPlayers, k, seed, &G);
	
	G.deckCount[0] = 0;
	for (i = 0; i < G.deckCount[0]; i++)
	{
		G.deck[0][i] = -1;
	}
	
	
	// Shuffle
	s = shuffle(0, &G);
	assertTrue("Return", -1, s);
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