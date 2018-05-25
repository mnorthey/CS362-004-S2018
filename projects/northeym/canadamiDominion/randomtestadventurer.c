/***************************************************
* Date: May 13, 2018
* Name: Matthew Northey
* Assignment: #4 Random Test Adventurer
* Note: Some of the structure for this code came
*	from the lectures made available to us on
*	Canvas. All modifications are my own.
****************************************************/

// Libraries & Header Files
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <time.h>

// Set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int testAdventurer(int p, int pos, struct gameState *post);
void listCards(int *arr, int size);

/****************************************************
*
* main()
*
****************************************************/

int main() {
	// Output file header
	printf("------------------------------------------------------------------\n-\n");
	printf("- RANDOM TEST SET 0: Adventurer\n-\n");
	printf("------------------------------------------------------------------\n");

#if (NOISY_TEST == 1)
	// Variable setup
	int i, n, p;

	struct gameState G;

	SelectStream(2);
	PutSeed(3);

	printf("RANDOM TESTS\n");
	time_t start, end;
	double elapsed;
	start = time(NULL);
	for (n = 0; n < 2000; n++)
	{
		end = time(NULL);
		elapsed = difftime(end, start);

		if (elapsed > 300)
			return 0;

		for (i = 0; i < sizeof(struct gameState); i++)
		{
			((char*)&G)[i] = floor(Random() * 256);
		}

		// Set players
		G.numPlayers = floor(Random() * 3) + 2;
		p = floor(Random() * G.numPlayers);
		G.whoseTurn = p;

		// Set critical states
		G.phase = 0;
		while (G.numActions < 1)
		{
			G.numActions = floor(Random() * 256);
		}

		// Set counts
		for (i = 0; i < G.numPlayers; i++)
		{
			do
			{
				G.handCount[i] = floor(Random() * MAX_HAND) - 10;
			} while (G.handCount[i] < 0);

			do
			{
				G.deckCount[i] = floor(Random() * MAX_DECK);
				G.discardCount[i] = floor(Random() * MAX_DECK);
			} while ((G.deckCount[i] + G.discardCount[i]) > MAX_DECK);
			

			// Fill deck, discard, hand with random cards
			int j;
			for (j = 0; j < G.deckCount[i]; j++)
			{
				G.deck[i][j] = floor(Random() * treasure_map);
			}

			for (j = 0; j < G.discardCount[i]; j++)
			{
				G.discard[i][j] = floor(Random() * treasure_map);
			}

			for (j = 0; j < G.handCount[i]; j++)
			{
				G.hand[i][j] = floor(Random() * treasure_map);
			}


		}

		// Add adventurer to hand
		int pos = floor(Random() * G.handCount[p]);
		G.hand[p][pos] = adventurer;

		// Update coins
		updateCoins(p, &G, 0);

		//printf("Run %d\n", n);
		testAdventurer(p, pos, &G);
	}
#endif

	// Final message
	printf("\n");

	return 0;
}





/****************************************************
*
* testAdventurer()
*
****************************************************/

int testAdventurer(int p, int pos, struct gameState *post)
{
	// Run simulation
	int i;
	int ret = 0;
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));

	//printf("Pre-Hand(%d): ", pre.handCount[p]);
	//listCards(pre.hand[p], pre.handCount[p]);

	int r = playCard(pos, 0, 0, 0, post);

	//printf("Post-Hand(%d): ", post->handCount[p]);
	//listCards(post->hand[p], post->handCount[p]);

	// Count number of treasures
	int numTreasures = 0;
	for (i = 0; i < pre.deckCount[p]; i++)
	{
		if (pre.deck[p][i] == copper || pre.deck[p][i] == silver || pre.deck[p][i] == gold)
		{
			numTreasures++;

			if (numTreasures == 2)
				break;
		}
	}

	if (numTreasures != 2)
	{
		for (i = 0; i < pre.discardCount[p]; i++)
		{
			if (pre.discard[p][i] == copper || pre.discard[p][i] == silver || pre.discard[p][i] == gold)
			{
				numTreasures++;

				if (numTreasures == 2)
					break;
			}
		}
	}

	// Check unchanged game states
	if (pre.numPlayers != post->numPlayers)
	{
		printf("ERROR: Change in numPlayers.\n");
		ret = -1;
	}

	if (memcmp(&pre.supplyCount, post->supplyCount, sizeof(post->supplyCount)) != 0)
	{
		printf("ERROR: Change in supplyCount.\n");
		ret = -1;
	}

	if (memcmp(&pre.embargoTokens, post->embargoTokens, sizeof(post->embargoTokens)) != 0)
	{
		printf("ERROR: Change in embargoTokens.\n");
		ret = -1;
	}

	if (pre.outpostPlayed != post->outpostPlayed)
	{
		printf("ERROR: Change in outpostPlayed.\n");
		ret = -1;
	}

	if (pre.outpostTurn != post->outpostTurn)
	{
		printf("ERROR: Change in outpostTurn.\n");
		ret = -1;
	}

	if (pre.whoseTurn != post->whoseTurn)
	{
		printf("ERROR: Change in whoseTurn.\n");
		ret = -1;
	}

	if (pre.phase != post->phase)
	{
		printf("ERROR: Change in phase.\n");
		ret = -1;
	}

	if (pre.numBuys != post->numBuys)
	{
		printf("ERROR: Change in numBuys.\n");
		ret = -1;
	}

	if (memcmp(&pre.playedCards, post->playedCards, sizeof(post->playedCards)) != 0)
	{
		printf("ERROR: Change in playedCards.\n");
		ret = -1;
	}

	if (pre.playedCardCount != post->playedCardCount)
	{
		printf("ERROR: Change in playedCardCount.\n");
		ret = -1;
	}

	for (i = 0; i < pre.numPlayers; i++)
	{
		if (i == p)
			continue;

		if (memcmp(&pre.deck[i], post->deck[i], sizeof(post->deck[i])) != 0)
		{
			printf("ERROR: Change in player %d deck.\n", i);
			ret = -1;
		}

		if (pre.deckCount[i] != post->deckCount[i])
		{
			printf("ERROR: Change in player %d deck count.\n", i);
			ret = -1;
		}

		if (memcmp(&pre.discard[i], post->discard[i], sizeof(post->discard[i])) != 0)
		{
			printf("ERROR: Change in player %d discard.\n", i);
			ret = -1;
		}

		if (pre.discardCount[i] != post->discardCount[i])
		{
			printf("ERROR: Change in player %d discard count.\n", i);
			ret = -1;
		}

		if (memcmp(&pre.hand[i], post->hand[i], sizeof(post->hand[i])) != 0)
		{
			printf("ERROR: Change in player %d hand.\n", i);
			ret = -1;
		}

		if (pre.handCount[i] != post->handCount[i])
		{
			printf("ERROR: Change in player %d hand count.\n", i);
			ret = -1;
		}
	}

	// Check changed game states
	pre.numActions--;
	if (pre.numActions != post->numActions)
	{
		printf("ERROR: numActions not decreased correctly.\n");
		ret = -1;
	}

	if (numTreasures == 2)	// At least two treasures in deck + discard
	{
		// Hand increased by two
		if (pre.handCount[p] + 2 != post->handCount[p])
		{
			printf("ERROR: Player hand count increased incorrectly.\n     Expected: %d + 2 = %d. Actual: %d + %d = %d.\n",
				pre.handCount[p], pre.handCount[p] + 2, pre.handCount[p], post->handCount[p] - pre.handCount[p],
				post->handCount[p]);
			ret = -1;
		}

		// Two new cards both treasures and coins increased correctly
		int coinsAdded = 0;
		if (post->hand[p][post->handCount[p] - 2] == copper)
		{
			coinsAdded++;
		}
		else if (post->hand[p][post->handCount[p] - 2] == silver)
		{
			coinsAdded += 2;
		}
		else if (post->hand[p][post->handCount[p] - 2] == gold)
		{
			coinsAdded += 3;
		}
		else
		{
			printf("ERROR: First treasure card added incorrectly.\n");
			ret = -1;
		}

		if (post->hand[p][post->handCount[p] - 1] == copper)
		{
			coinsAdded++;
		}
		else if (post->hand[p][post->handCount[p] - 1] == silver)
		{
			coinsAdded += 2;
		}
		else if (post->hand[p][post->handCount[p] - 1] == gold)
		{
			coinsAdded += 3;
		}
		else
		{
			printf("ERROR: Second treasure card added incorrectly.\n");
			ret = -1;
		}

		if (pre.coins + coinsAdded != post->coins)
		{
			printf("ERROR: Coins added to state incorrectly.\n     Expected: %d + %d = %d. Actual: %d + %d = %d.\n",
				pre.coins, coinsAdded, pre.coins + coinsAdded, pre.coins, post->coins - pre.coins, post->coins);
			ret = -1;
		}

		// Deck + discard count decreased by two
		if (pre.deckCount[p] + pre.discardCount[p] - 2 != post->deckCount[p] + post->discardCount[p])
		{
			printf("ERROR: Deck + discard decreased incorrectly.\n     Expected: %d. Actual: %d.\n",
				pre.deckCount[p] + pre.discardCount[p] - 2, post->deckCount[p] + post->discardCount[p]);
			ret = -1;
		}

	}
	else if (numTreasures == 1)	// One treasure in deck + discard
	{
		// Hand increased by one
		if (pre.handCount[p] + 1 != post->handCount[p])
		{
			printf("ERROR: Player hand count increased incorrectly.\n     Expected: %d + 1 = %d. Actual: %d + %d = %d.\n",
				pre.handCount[p], pre.handCount[p] + 1, pre.handCount[p], post->handCount[p] - pre.handCount[p],
				post->handCount[p]);
			ret = -1;
		}

		// New card treasures and coins increased correctly
		int coinsAdded;
		if (post->hand[p][post->handCount[p] - 1] == copper)
		{
			coinsAdded = 1;
		}
		else if (post->hand[p][post->handCount[p] - 1] == silver)
		{
			coinsAdded = 2;
		}
		else if (post->hand[p][post->handCount[p] - 1] == gold)
		{
			coinsAdded = 3;
		}
		else
		{
			printf("ERROR: Single treasure card added incorrectly.\n");
			ret = -1;
		}

		if (pre.coins + coinsAdded != post->coins)
		{
			printf("ERROR: Coins added to state incorrectly.\n     Expected: %d + %d = %d. Actual: %d + %d = %d.\n",
				pre.coins, coinsAdded, pre.coins + coinsAdded, pre.coins, post->coins - pre.coins, post->coins);
			ret = -1;
		}

		// Deck + discard count decreased by one
		if (pre.deckCount[p] + pre.discardCount[p] - 1 != post->deckCount[p] + post->discardCount[p])
		{
			printf("ERROR: Deck + discard decreased incorrectly.\n     Expected: %d. Actual: %d.\n",
				pre.deckCount[p] + pre.discardCount[p] - 1, post->deckCount[p] + post->discardCount[p]);
			ret = -1;
		}
	}
	else if (numTreasures == 0)	// Zero treasures in deck + discard
	{
		// Hand count remained the same
		if (pre.handCount[p] != post->handCount[p])
		{
			printf("ERROR: Player hand did not remain unchanged with zero treasures in deck.\n     Expected: %d. Actual: %d\n",
				pre.handCount[p], post->handCount[p]);
			ret = -1;
		}

		// Hand composition remained the same
		if (memcmp(&pre.hand[p], post->hand[p], sizeof(post->hand[p])) != 0)
		{
			printf("ERROR: Change in player hand with zero treasures in deck.\n");
			ret = -1;
		}

		if (pre.coins != post->coins)
		{
			printf("ERROR: Change in coins with zero treasures in deck.\n");
			ret = -1;
		}

		// Deck + discard count remained the same
		if (pre.deckCount[p] + pre.discardCount[p] != post->deckCount[p] + post->discardCount[p])
		{
			printf("ERROR: Change in deck + discard count with zero treasures in deck.\n");
			ret = -1;
		}
	}
	else
	{
		printf("Error counting numTreasures.\n");
	}

	if (r != 0)
	{
		printf("ERROR: -1 returned from playCard()\n");
		ret = -1;
	}

	/******
	if (ret == 0)
	{
		printf("All tests passed.\n");
	}
	******/

	return ret;
}




/****************************************************
*
* listCards()
*
****************************************************/

void listCards(int *arr, int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		if (i != 0 && i % 10 == 0)
		{
			printf("\n");
		}

		if (arr[i] == copper)
		{
			printf("copper");
		}
		else if (arr[i] == silver)
		{
			printf("silver");
		}
		else if (arr[i] == gold)
		{
			printf("gold");
		}
		else if (arr[i] == curse)
		{
			printf("curse");
		}
		else if (arr[i] == estate)
		{
			printf(" estate");
		}
		else if (arr[i] == duchy)
		{
			printf("duchy");
		}
		else if (arr[i] == province)
		{
			printf("province");
		}
		else if (arr[i] == adventurer)
		{
			printf("adventurer");
		}
		else if (arr[i] == council_room)
		{
			printf("council_room");
		}
		else if (arr[i] == feast)
		{
			printf("feast");
		}
		else if (arr[i] == gardens)
		{
			printf("gardens");
		}
		else if (arr[i] == mine)
		{
			printf("mine");
		}
		else if (arr[i] == remodel)
		{
			printf("remodel");
		}
		else if (arr[i] == smithy)
		{
			printf("smithy");
		}
		else if (arr[i] == village)
		{
			printf("village");
		}
		else if (arr[i] == baron)
		{
			printf("baron");
		}
		else if (arr[i] == great_hall)
		{
			printf("great_hall");
		}
		else if (arr[i] == minion)
		{
			printf("minion");
		}
		else if (arr[i] == steward)
		{
			printf("steward");
		}
		else if (arr[i] == tribute)
		{
			printf("tribute");
		}
		else if (arr[i] == ambassador)
		{
			printf("ambassador");
		}
		else if (arr[i] == cutpurse)
		{
			printf("cutpurse");
		}
		else if (arr[i] == embargo)
		{
			printf("embargo");
		}
		else if (arr[i] == outpost)
		{
			printf("outpost");
		}
		else if (arr[i] == salvager)
		{
			printf("salvager");
		}
		else if (arr[i] == sea_hag)
		{
			printf("sea_hag");
		}
		else if (arr[i] == treasure_map)
		{
			printf("treasure_map");
		}
		else
		{
			printf("CARD_NOT_FOUND");
		}

		if (i == size - 1)
		{
			printf(".\n");
		}
		else
		{
			printf(", ");
		}
	}

	return;
}