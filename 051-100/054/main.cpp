#include <iostream>
#include <cstdlib> // qsort
//#include "../../include/file.h"

#define NLINES 1000

using namespace std;

char *texts[11] = 
{
  "",
  "High Card  ",
  "Pair       ",
  "Two Pairs  ",
  "Three Kind ",
  "Straight   ",
  "Flush      ",
  "Full House ",
  "Four Kind  ",
  "Strt. Flush",
  "Royal Flush"
};

struct card
{
  char rank, suit;
};

struct hand
{
  card cards[5];
};

int rankToNum(char r)
{
  switch (r)
  {
  case 'T': return 10; break;
  case 'J': return 11; break;
  case 'Q': return 12; break;
  case 'K': return 13; break;
  case 'A': return 14; break;
  default :
    return r - '0';
    break;
  }
}

int card_cmp(const void *c1, const void *c2)
{
  card *C1 = (card *) c1;
  card *C2 = (card *) c2;

  int a = rankToNum(C1->rank);
  int b = rankToNum(C2->rank);
  return a - b;
}

void swapCards(hand &h, int i, int j)
{
  char tmp_r, tmp_s;

  tmp_r = h.cards[i].rank;
  tmp_s = h.cards[i].suit;
  h.cards[i].rank = h.cards[j].rank;
  h.cards[i].suit = h.cards[j].suit;
  h.cards[j].rank = tmp_r;
  h.cards[j].suit = tmp_s;
}

bool isFourOfAKind(hand &h)
{
  if ( (h.cards[1].rank == h.cards[2].rank) &&
       (h.cards[1].rank == h.cards[3].rank) )
  {
    if ( (h.cards[1].rank == h.cards[0].rank) ||
         (h.cards[1].rank == h.cards[4].rank) )
    {
      if (h.cards[0].rank == h.cards[1].rank)
        swapCards(h, 0, 4);
      return true;
    }
  }
  return false;
}

bool isFlush(hand &h)
{
  for (int i = 0; i < 4; i++)
    if (h.cards[i].suit != h.cards[i+1].suit)
      return false;
  return true;
}

bool isStraight(hand &h)
{
  for (int i = 0; i < 4; i++)
    if ( rankToNum(h.cards[i+1].rank) - rankToNum(h.cards[i].rank) != 1)
      return false;
  return true;
}

bool isThreeOfAKind(hand &h)
{
  if ( (h.cards[0].rank == h.cards[1].rank) &&
       (h.cards[1].rank == h.cards[2].rank) )
  {
    swapCards(h, 0, 4);
    swapCards(h, 1, 3);
    return true;
  }
  if ( (h.cards[1].rank == h.cards[2].rank) &&
       (h.cards[2].rank == h.cards[3].rank) )
  {
    swapCards(h, 1, 4);
    return true;
  }
  if ( (h.cards[2].rank == h.cards[3].rank) &&
       (h.cards[3].rank == h.cards[4].rank) )
    return true;
  return false;
}

bool isTwoPairs(hand &h)
{
  if ( h.cards[0].rank == h.cards[1].rank )
  {
    if (h.cards[2].rank == h.cards[3].rank)
    {
      swapCards(h, 2, 4);
      swapCards(h, 0, 2);
      return true;
    }
    if (h.cards[3].rank == h.cards[4].rank)
    {
      swapCards(h, 0, 2);
      return true;
    }
  }
  if ( h.cards[1].rank == h.cards[2].rank )
  {
    return ( (h.cards[3].rank == h.cards[4].rank) );
  }
  return false;
}

bool isPair(hand &h)
{
  if (h.cards[0].rank == h.cards[1].rank)
  {
    swapCards(h, 0, 3);
    swapCards(h, 1, 4);
    return true;
  }
  if (h.cards[1].rank == h.cards[2].rank)
  {
    swapCards(h, 1, 3);
    swapCards(h, 2, 4);
    return true;
  }
  if (h.cards[2].rank == h.cards[3].rank)
  {
    swapCards(h, 2, 4);
    return true;
  }
  return (h.cards[3].rank == h.cards[4].rank);
}

bool isFullHouse(hand &h)
{
  if (isThreeOfAKind(h) && isTwoPairs(h))
  {
    qsort(h.cards, 5, sizeof(card), card_cmp);
    return true;
  }
}

bool isStraightFlush(hand &h)
{
  return isStraight(h) && isFlush(h);
}

bool isRoyalFlush(hand &h)
{
  return isStraightFlush(h) && h.cards[0].rank == 'T';
}

int handToNum(hand &h)
{
  if (isRoyalFlush(h))    return 10;
  if (isStraightFlush(h)) return 9;
  if (isFourOfAKind(h))   return 8;
  if (isFullHouse(h))     return 7;
  if (isFlush(h))         return 6;
  if (isStraight(h))      return 5;
  if (isThreeOfAKind(h))  return 4;
  if (isTwoPairs(h))      return 3;
  if (isPair(h))          return 2;
  return 1;
}

int winner(hand p1, hand p2)
{
  qsort(p1.cards, 5, sizeof(card), card_cmp);
  qsort(p2.cards, 5, sizeof(card), card_cmp);

  int a = handToNum(p1);
  int b = handToNum(p2);

  // TEST OUTPUT
  for (int i = 0; i < 5; i++)
    cout << p1.cards[i].rank << p1.cards[i].suit << " ";
  cout << texts[a] << " ";

  // DIFFERENT TEST OUTPUT
  for (int i = 0; i < 5; i++)
    cout << p2.cards[i].rank << p2.cards[i].suit << " ";
  cout << texts[b] << " ";

  if (a > b) return 1;
  if (a < b) return 2;

  for (int i = 4; i >= 0; i--)
  {
    a = rankToNum(p1.cards[i].rank);
    b = rankToNum(p2.cards[i].rank);
    if (a > b) return 1;
    if (a < b) return 2;
  }
  
  return 0;
}

int main(int argc, char* argv[])
{
  int wins;
  hand p1, p2;
  string c;

  wins = 0;

  for (int line = 0; line < NLINES; line++) //while (cin.peek() != -1)
  {
    for (int i = 0; i < 5; i++)
    {
      cin >> c;
      p1.cards[i].rank = c[0];
      p1.cards[i].suit = c[1];
    }
    
    for (int i = 0; i < 5; i++)
    {
      cin >> c;
      p2.cards[i].rank = c[0];
      p2.cards[i].suit = c[1];
    }

    if (winner(p1, p2) == 1)
    { cout << " ~~~ P1 Wins" << endl;
      wins++;
    }
    else cout << " ~~~ P1 Loses" << endl;
  }

  cout << wins << endl;

  return 0;
}
