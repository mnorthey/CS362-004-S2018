/***************************************************
* Date: April 28, 2018
* Name: Matthew Northey
* Assignment: #3 Card Test 4 - Sea Hag
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
void testStates();
void printDeck(int player, struct gameState *G);



/****************************************************
*
* main()
*
****************************************************/

int main() {
	// Setup
	printf("------------------------------------------------------------------\n-\n");
	printf("- CARD TEST 4: Sea Hag\n-\n");
	printf("------------------------------------------------------------------\n");
		
	// ~~~~~~~~TESTS~~~~~~~~
	testBaseBehavior();
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
	int i, j;
	int numPlayers = 4;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, sea_hag};
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
	gainCard(sea_hag, &G, 2, 0);
	
	// Other players draw up
	for (i = 1; i < 4; i++)
	{
		drawCard(i, &G);
		drawCard(i, &G);
		drawCard(i, &G);
		drawCard(i, &G);
		drawCard(i, &G);
	}
	
	// Save P1 states
	int p1_hand_count = G.handCount[0];
	int p1_deck_count = G.deckCount[0];
	int p1_discard_count = G.discardCount[0];
	int coins = G.coins;
	int actions = G.numActions;

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
	
	// Play sea hag
	playCard(5, 0, 0, 0, &G);
	
	// Test P1 states
	assertTrue("G.handCount[0]", p1_hand_count, G.handCount[0]);
	assertTrue("G.coins", coins, G.coins);
	assertTrue("G.deckCount[0]", p1_deck_count, G.deckCount[0]);
	assertTrue("G.discardCount[0]", p1_discard_count, G.discardCount[0]);
	assertTrue("G.numActions", actions - 1, G.numActions);
	
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
		
		if (discard_count[i] + 1 == G.discardCount[i])
		{
			#if (NOISY_TEST == 1)
				printf("  PASS: G.discardCount[%d] = %d, Expected = %d\n", i, G.discardCount[i], discard_count[i] + 1);
			#endif
		}
		else
		{
			#if (NOISY_TEST == 1)
				printf("! FAIL: G.discardCount[%d] = %d, Expected = %d\n", i, G.discardCount[i], discard_count[i] + 1);
			#endif
		}
	}
	
	// Test compositions for changes to composition or order
	int deck_flag = 0;
	int hand_flag = 0;
	int discard_flag = 0;
	for (i = 1; i < 4; i++)
	{
		for (j = 0; j < G.deckCount[i]; j++)
		{
			if (j == 0)
			{
				if (G.deck[i][j] != curse)
				{
					deck_flag = 1;
				}
			}
			else if (G.deck[i][j] != deck_comp[i][j])
			{
				deck_flag = 1;
			}
		}
		
		for (j = 0; j < G.discardCount[i] - 1; j++)
		{
			if (discard_count[i] + 1 != G.discardCount[i])
			{
				discard_flag = 1;
			}
			
			
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
				printf("  PASS: P%d Deck + Curse, Otherwise Unchanged = 0, Expected = 0\n", i);
			#endif
		}
		else
		{
			#if (NOISY_TEST == 1)
				printf("! FAIL: P%d Deck + Curse, Otherwise Unchanged = 1, Expected = 0\n", i);
			#endif
		}
		
		if (discard_flag == 0)
		{
			#if (NOISY_TEST == 1)
				printf("  PASS: P%d Discard + 1, Otherwise Unchanged = 0, Expected = 0\n", i);
			#endif
		}
		else
		{
			#if (NOISY_TEST == 1)
				printf("! FAIL: P%d Discard + 1, Otherwise Unchanged = 1, Expected = 0\n", i);
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
	gainCard(sea_hag, &G, 2, 0);
	
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
	
	// Other players draw up
	for (i = 1; i < 4; i++)
	{
		drawCard(i, &G);
		drawCard(i, &G);
		drawCard(i, &G);
		drawCard(i, &G);
		drawCard(i, &G);
	}
	
	// Save P1 states
	p1_hand_count = G.handCount[0];
	p1_deck_count = G.deckCount[0];
	p1_discard_count = G.discardCount[0];
	coins = G.coins;
	actions = G.numActions;

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
	
	// Play sea hag
	playCard(5, 0, 0, 0, &G);
	
	// Test P1 states
	assertTrue("G.handCount[0]", p1_hand_count, G.handCount[0]);
	assertTrue("G.coins", coins, G.coins);
	assertTrue("G.deckCount[0]", p1_deck_count, G.deckCount[0]);
	assertTrue("G.discardCount[0]", p1_discard_count, G.discardCount[0]);
	assertTrue("G.numActions", actions - 1, G.numActions);
	
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
		
		if (discard_count[i] + 1 == G.discardCount[i])
		{
			#if (NOISY_TEST == 1)
				printf("  PASS: G.discardCount[%d] = %d, Expected = %d\n", i, G.discardCount[i], discard_count[i] + 1);
			#endif
		}
		else
		{
			#if (NOISY_TEST == 1)
				printf("! FAIL: G.discardCount[%d] = %d, Expected = %d\n", i, G.discardCount[i], discard_count[i] + 1);
			#endif
		}
	}
	
	// Test compositions for changes to composition or order
	deck_flag = 0;
	hand_flag = 0;
	discard_flag = 0;
	for (i = 1; i < 4; i++)
	{
		for (j = 0; j < G.deckCount[i]; j++)
		{
			if (j == 0)
			{
				if (G.deck[i][j] != curse)
				{
					deck_flag = 1;
				}
			}
			else if (G.deck[i][j] != deck_comp[i][j])
			{
				deck_flag = 1;
			}
		}
		
		for (j = 0; j < G.discardCount[i] - 1; j++)
		{
			if (discard_count[i] + 1 != G.discardCount[i])
			{
				discard_flag = 1;
			}
			
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
				printf("  PASS: P%d Deck + Curse, Otherwise Unchanged = 0, Expected = 0\n", i);
			#endif
		}
		else
		{
			#if (NOISY_TEST == 1)
				printf("! FAIL: P%d Deck + Curse, Otherwise Unchanged = 1, Expected = 0\n", i);
			#endif
		}
		
		if (discard_flag == 0)
		{
			#if (NOISY_TEST == 1)
				printf("  PASS: P%d Discard + 1, Otherwise Unchanged = 0, Expected = 0\n", i);
			#endif
		}
		else
		{
			#if (NOISY_TEST == 1)
				printf("! FAIL: P%d Discard + 1, Otherwise Unchanged = 1, Expected = 0\n", i);
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
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, sea_hag};
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
	gainCard(sea_hag, &G, 2, 0);
	
	// Other players draw up
	for (i = 1; i < 4; i++)
	{
		drawCard(i, &G);
		drawCard(i, &G);
		drawCard(i, &G);
		drawCard(i, &G);
		drawCard(i, &G);
	}

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
	
	// Play sea hag
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
	gainCard(sea_hag, &G, 2, 0);
	
	// Other players draw up
	for (i = 1; i < 4; i++)
	{
		drawCard(i, &G);
		drawCard(i, &G);
		drawCard(i, &G);
		drawCard(i, &G);
		drawCard(i, &G);
	}
	
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
	
	// Play sea hag
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




/****************************************************
*
* printDeck()
*
****************************************************/

void printDeck(int player, struct gameState *G)
{
	int i;
	
	for (i = 0; i < G->deckCount[player]; i++)
	{
		if (G->deck[player][i] == copper)
		{
			printf(" copper,");
		}
		else if (G->deck[player][i] == silver)
		{
			printf(" silver,");
		}
		else if (G->deck[player][i] == gold)
		{
			printf(" gold,");
		}
		else if (G->deck[player][i] == curse)
		{
			printf(" curse,");
		}
		else if (G->deck[player][i] == estate)
		{
			printf(" estate,");
		}
		else if (G->deck[player][i] == duchy)
		{
			printf(" duchy,");
		}
		else if (G->deck[player][i] == province)
		{
			printf(" province,");
		}
		else if (G->deck[player][i] == adventurer)
		{
			printf(" adventurer,");
		}
		else if (G->deck[player][i] == council_room)
		{
			printf(" council_room,");
		}
		else if (G->deck[player][i] == feast)
		{
			printf(" feast,");
		}
		else if (G->deck[player][i] == gardens)
		{
			printf(" gardens,");
		}
		else if (G->deck[player][i] == mine)
		{
			printf(" mine,");
		}
		else if (G->deck[player][i] == remodel)
		{
			printf(" remodel,");
		}
		else if (G->deck[player][i] == smithy)
		{
			printf(" smithy,");
		}
		else if (G->deck[player][i] == village)
		{
			printf(" village,");
		}
		else if (G->deck[player][i] == baron)
		{
			printf(" baron,");
		}
		else if (G->deck[player][i] == great_hall)
		{
			printf(" great_hall,");
		}
		else if (G->deck[player][i] == minion)
		{
			printf(" minion,");
		}
		else if (G->deck[player][i] == steward)
		{
			printf(" steward,");
		}
		else if (G->deck[player][i] == tribute)
		{
			printf(" tribute,");
		}
		else if (G->deck[player][i] == ambassador)
		{
			printf(" ambassador,");
		}
		else if (G->deck[player][i] == cutpurse)
		{
			printf(" cutpurse,");
		}
		else if (G->deck[player][i] == embargo)
		{
			printf(" embargo,");
		}
		else if (G->deck[player][i] == outpost)
		{
			printf(" outpost,");
		}
		else if (G->deck[player][i] == salvager)
		{
			printf(" salvager,");
		}
		else if (G->deck[player][i] == sea_hag)
		{
			printf(" sea_hag,");
		}
		else if (G->deck[player][i] == treasure_map)
		{
			printf(" treasure_map,");
		}
		else
		{
			printf(" CARD_NOT_FOUND,");
		}
	}
	
	printf("\n");
}