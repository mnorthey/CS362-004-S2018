/***************************************************
 * Date: May 13, 2018
 * Name: Matthew Northey
 * Assignment: #4 Random Test 1 - Steward
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

// Function headers
int testSteward(int p, int pos, struct gameState *post);
void listCards(int *arr, int size);

/****************************************************
 *
 * main()
 *
 ****************************************************/

int main() {
    // Output file header
    printf("------------------------------------------------------------------\n-\n");
    printf("- RANDOM TEST SET 1: Steward\n-\n");
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
		
		G.playedCardCount = floor(Random() * MAX_DECK);
		for (i = 0; i < G.playedCardCount; i++)
		{
			G.playedCards[i] = floor(Random() * treasure_map);
		}
        
		// Set counts
        G.deckCount[p] = floor(Random() * MAX_DECK);
        G.discardCount[p] = floor(Random() * MAX_DECK);
        G.handCount[p] = floor(Random() * MAX_HAND);
        
        // Fill deck, discard, hand with random cards
		for (i = 0; i < G.deckCount[p]; i++)
		{
			G.deck[p][i] = floor(Random() * treasure_map);
		}
		
		for (i = 0; i < G.discardCount[p]; i++)
		{
			G.discard[p][i] = floor(Random() * treasure_map);
		}
		
		for (i = 0; i < G.handCount[p]; i++)
		{
			G.hand[p][i] = floor(Random() * treasure_map);
		}
		
		// Add steward to hand
        int pos = floor(Random() * G.handCount[p]);
        G.hand[p][pos] = steward;
		
		// Update coins
		updateCoins(p, &G, 0);

		printf("Run %d\n", n);
        testSteward(p, pos, &G);

    }
	#endif
	
    // Final message
    printf("\n");
    
    return 0;
}





/****************************************************
 *
 * testSteward()
 *
 ****************************************************/

int testSteward(int p, int pos, struct gameState *post)
{
    // Run simulations
	int i;
	int ret = 0;
	struct gameState pre;
	
	// Check +2 Cards
	memcpy (&pre, post, sizeof(struct gameState));
	
	int r = playCard(pos, 1, 0, 0, post);
		
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
	
	int deckdiscard = pre.deckCount[p] + pre.discardCount[p];
	if (deckdiscard >= 2)	// At least two cards in deck + discard
	{
		// Hand increased by two
		if (pre.handCount[p] + 1 != post->handCount[p])
		{
			printf("ERROR: Player hand count increased incorrectly after draw cards.\n");
			ret = -1;
		}
		
		// If either new card is treasure, coins increased correctly
		int coins = 0;
		for (i = 0; i < post->handCount[p]; i++)
		{
			if (post->hand[p][i] == copper)
			{
				coins += 1;
			}
			else if (post->hand[p][i] == silver)
			{
				coins += 2;
			}
			else if (post->hand[p][i] == gold)
			{
				coins += 3;
			}
		}
		
		if (coins != post->coins)
		{
			printf("ERROR: Coins added to state incorrectly after draw cards.\n");
			ret = -1;
		}
		
		// Deck + discard count decreased by two
		if (pre.deckCount[p] + pre.discardCount[p] - 2 != post->deckCount[p] + post->discardCount[p])
		{
			printf("ERROR: Deck + discard decreased incorrectly after draw cards.\n");
			ret = -1;
		}
		
	}
	else if (deckdiscard == 1)	// One card in deck + discard
	{
		// Hand increased by one
		if (pre.handCount[p] != post->handCount[p])
		{
			printf("ERROR: Player hand count increased incorrectly after draw card.\n");
			ret = -1;
		}
		
		// If new card is treasure, coins increased correctly
		int coins = 0;
		for (i = 0; i < post->handCount[p]; i++)
		{
			if (post->hand[p][i] == copper)
			{
				coins += 1;
			}
			else if (post->hand[p][i] == silver)
			{
				coins += 2;
			}
			else if (post->hand[p][i] == gold)
			{
				coins += 3;
			}
		}
		
		if (coins != post->coins)
		{
			printf("ERROR: Coins added to state incorrectly after draw cards.\n");
			ret = -1;
		}
		
		// Deck + discard count decreased by one
		if (pre.deckCount[p] + pre.discardCount[p] - 1 != post->deckCount[p] + post->discardCount[p])
		{
			printf("ERROR: Deck + discard decreased incorrectly after draw card.\n");
			ret = -1;
		}
	}
	else if (deckdiscard == 0)	// Zero cards in deck + discard
	{
		// Hand remained the same
		if (pre.handCount[p] - 1 != post->handCount[p])
		{
			printf("ERROR: Player should not have changed after drawing no cards.\n");
			ret = -1;
		}
		
		// Coins stayed the same
		if (pre.coins != post->coins)
		{
			printf("ERROR: Coins should not have changed after drawing no cards.\n");
			ret = -1;
		}
		
		// Deck + discard count stayed the same
		if (pre.deckCount[p] + pre.discardCount[p] != post->deckCount[p] + post->discardCount[p])
		{
			printf("ERROR: Deck + discard count should not have changed after drawing no cards.\n");
			ret = -1;
		}
	}
   
	if (r != 0)
	{
		printf("ERROR: -1 returned from playCard()\n");
		ret = -1;
	}
   
   
   
   
   
   
	// Check +2 Coins
	memcpy (post, &pre, sizeof(struct gameState));
	
	r = playCard(pos, 2, 0, 0, post);
		
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
	
	if (pre.coins + 2 != post->coins)
	{
		printf("ERROR: Coins added incorrectly.\n");
		ret = -1;
	}

	if (r != 0)
	{
		printf("ERROR: -1 returned from playCard()\n");
		ret = -1;
	}
	
	
	
	// Check Discard 2
	memcpy (post, &pre, sizeof(struct gameState));
	
	int card1 = floor(Random() * pre.handCount[p]);
	int card2 = floor(Random() * pre.handCount[p] - 1);

	r = playCard(pos, 3, card1, card2, post);
		
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
	
	if (memcmp(&pre.deck[p], post->deck[p], sizeof(post->deck[p])) != 0)
	{
		printf("ERROR: Change in current player deck.\n");
		ret = -1;
	}
	
	if (pre.deckCount[p] != post->deckCount[p])
	{
		printf("ERROR: Change in current player deck count.\n");
		ret = -1;
	}
	
	if (memcmp(&pre.discard[p], post->discard[p], sizeof(post->discard[p])) != 0)
	{
		printf("ERROR: Change in current player discard.\n");
		ret = -1;
	}
	
	if (pre.discardCount[p] != post->discardCount[p])
	{
		printf("ERROR: Change in current player discard count.\n");
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
	
	if (pre.handCount[p] - 3 != post->handCount[p])
	{
		printf("ERROR: Player hand count decreased incorrectly.\n");
		ret = -1;
	}
	
	int coins = 0;
	for (i = 0; i < post->handCount[p]; i++)
	{
		if (post->hand[p][i] == copper)
		{
			coins += 1;
		}
		else if (post->hand[p][i] == silver)
		{
			coins += 2;
		}
		else if (post->hand[p][i] == gold)
		{
			coins += 3;
		}
	}
	
	if (coins != post->coins)
	{
		printf("ERROR: Coins altered incorrectly after trash card.\n");
		ret = -1;
	}

	if (r != 0)
	{
		printf("ERROR: -1 returned from playCard()\n");
		ret = -1;
	}
	
	if (ret == 0)
	{
		printf("All tests passed.\n");
	}

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