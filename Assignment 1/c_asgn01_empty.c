/*c_asgn01.c
 *
 *      EE474 introductory C programming assignment #1
 *      Spring 2021
 *
 *     Student Name: Arnav Mathur and ID# 1934724
 *
 */

/*  Objectives:
       Gain experience and proficiency with C programming.
Format of assignment:
  1)  make a backup copy of this file
  2)  enter your name into the space above
  3)  Read through the comments below and
edit code into this file to solve the problems.
  4)  check your results against posted solution

Notes:   You are not required to use #defines for all constants
in this assignment but please do so for problem 3.

Printing:   Use the following functions to print unless
directed not to do so:

  print_int(int x)                prints out an integer
  print_usi(unsigned int x)       prints out an unsigned int
  print_newl()                    prints a "newline" character
  print_str(char *x)                 prints a string (pointed to by x)
  print_dble(double)              prints out a double precision floating point number

These functions are at the bottom of this file.  Feel free to study
them to see how they work.
*/
/*  #include some system library function prototypes */
      //  we will use printf()
#include <stdio.h>
//  also get math function
#include <math.h>
#include <string.h>    // for strlen (ONLY)
#include <stdlib.h>    // for random()


#define LINUX            1
//#define VISUALC          1

#define CARD_ERROR (unsigned char)0xFF  //  a value that cannot be a card
#define N_DECK 52 // standard # of cards in a deck
// data types
typedef int shuffle;
//typedef unsigned char hand[7];


/*  function prototypes for simplified printing functions */
void print_int(int);
void print_usi(unsigned int);
void print_newl();
void print_str(char*);
void print_chr(char);
void print_dble(double);


// solution functions

/**********************************************************************
                 All variable declarations
**********************************************************************/

int i,j,k;      // these make good loop iterators.
int card, suit;

//  Random number seed.
//  try  43227 (player 1 has 4 10s)
int seed = 43227;

// Part 1.2
int t1, t2;

// Part 1.4
int length;

// Part 2.0

shuffle cards[N_DECK][2];

//  Part 2.2

unsigned char testhand[7]={0};


//Part 3.0

// Part 3.1

// Part 3.2

int dealer_deck_count = 0;  // how many cards have been dealt from a deck
// Part 3.3


/***********************************************************************
                      Function prototypes
**************************************************************************/
char* length_pad(char*, int);     // prob 1.4
int randN(int);                   // 2.1
void fill(shuffle[N_DECK][2]);             // 2.1
unsigned char convert(int card, int suit);  // 2.2
int valid_card(unsigned char card); // 2.2
int gcard(unsigned char card);   // 2.2
int gsuit(unsigned char card);   // 2.2
void names(int n, int j, char *answer); // 2.3
void iterate(char *p);
void deal(int M, unsigned char hand[7], shuffle deck[N_DECK][2]);    // 3.2
void printhand(int M, unsigned char* hand, char* buff1);
int trip_s(int M, unsigned char hand[]);
int four_kind(int M, unsigned char hand[]);
int pairs(int M, unsigned char hand[]);


/**********************************************************************
                          main()
***********************************************************************/
int main()
{
/************************************************************************
                    Start code here                                     */

/************************************************************************
 *
 * PROBLEM 1,  C-Basics
 *
 */

// initialize random numbers.
//  change the seed for testing.  Use this value to compare results with
#ifdef VISUALC
srand(seed);
#endif
#ifdef LINUX
// srandom(seed);
#endif

print_str("Random seed: "); print_int(seed); print_newl();


// 1.1  Prints out the 10 integers between 1 and 10 on separate lines:

print_str("Problem 1.1 Test Results: \n");

for(int i = 0; i < 10; i++) {
    print_int(i + 1);
    print_newl();
}

// 1.2 Prints the first 10 integers and
// a) sum of the ints.  b) sum of the ints squared.

print_str("Problem 1.2 Test Results: \n");

for(int i = 0; i < 10; i++) {
    print_int(i + 1);
    print_newl();
}

t1 = 0 ; t2 = 0;
for(int i = 0; i < 10; i++) {
    t1 += i + 1;
    t2 += (i + 1) * (i + 1);
}

//printf("TST: t1-%d\n", t1);

print_int(t1) ;  print_int(t2) ;   print_newl();


print_str("Problem 1.3 Test Results:\n");

// you code for 1.3 here ...
char *l1 = "sum: ";
char *l2 = "sum of squares: ";

print_str(l1) ; print_int(t1) ; print_newl();
print_str(l2) ; print_int(t2) ; print_newl();


//  1.4  Write a fcn, char* length_pad(char *st, int n), which takes a string and adds
//       the right amount of spaces so that it's length is n.  It should return a pointer
//       the new string.  If the length of st is < n, use malloc() to get memory for a new,
//       longer string.
//

//  Add your length_pad function below main.

//   Modify 1.3 to use length_pad() so that the numbers are all starting in col 21
//      (i.e. all labels have length 20).

print_str("Problem 1.4 Test Results: \n");

print_str(length_pad(l1,20)) ; print_int(t1) ; print_newl();
print_str(length_pad(l2,20)) ; print_int(t2) ; print_newl();

/************************************************************************
 * 2.0   Card games
 *
 *  A 'shuffle' is an array of N_DECK pairs of integers.   The first of the pair is the card type
(0-13 representing ace, 2, 3, .... King) and the second representing the suit (hearts, diamonds, clubs, spades).   Thus a pair of numbers (1-13)(1-4) describes a unique card in the deck.
 */

// 2.1 Write a function to fill a shuffle with N_DECK random integer pairs, BUT,
//     as with your playing cards, there must be exactly one of each pair in the
//     shuffle.
//    Use your function to print out all the "cards" of the shuffle, 7 cards per line.

print_str("Problem 2.1 Test Results: ");    ; print_newl();

fill(cards);

// print out the random cards.
for(i=0;i<N_DECK;i++) {
    print_str(" [");
    print_int(cards[i][0]); print_str(" "); print_int(cards[i][1]) ;
    print_str("] ");
    if(!((i+1)%7)) print_newl();
}
print_newl();


// 2.2    A 'hand' is an array of seven unsigned chars.  Each char represents one card.  We use a four bit field in the char for each of the two numbers above:  the four most significant bits [7...4] represent the card number (1-13) and the lower four [3...0] represent the suit.


//        Write functions to:  a)  convert two integers (from  a shuffle for example) into a char as above.
//                                    if the ints are invalid (e.g. convert(294802984,138142) is not a card)
//                                    return CARD_ERROR
//                             b)  test if a char equals a valid integer pair
//                             c)  get the integer suit from a char
//                             d)  get the integer card from a char

//        Both functions a and b must return CARD_ERROR if they get invalid input (such as suit > 4).

//        Write code which verifies these functions work properly and prints results.
//

//

print_str("Problem 2.2  Test Results: ");  print_newl();

//  your code for convert() (2.2.a) below main.
print_str("   2.2.a"); print_newl();
// to test, lets fill a hand up with some cards:
testhand[0] = convert(5,2);
testhand[1] = convert(15,2); // Oops!   15 is invalid card #
testhand[2] = convert(12,1);
testhand[3] = convert(6,3);
testhand[4] = convert(-1,7);  // Hey!  both -1 and 7 are invalid
testhand[5] = convert(10,4);
testhand[6] = convert(3,3);

// Let's check them carefully!
for (i =0; i<7; i++){
    if (testhand[i] == CARD_ERROR) {
        print_str(" check 1 card error: ");
        print_int(i);
        print_newl();
    }
}

// new test hand
testhand[0] = convert(1,1);  // Ace of Hearts
testhand[1] = convert(1,2);  // Ace of Diamonds
testhand[2] = convert(1,3);  // Ace of Clubs
testhand[3] = convert(1,4);  // Ace of Spades
testhand[4] = convert(11,2); // Jack of Diamonds
testhand[5] = convert(12,2); // Queen of Diamonds
testhand[6] = convert(13,4); // King of Spades

int i;
for (i=0; i<7; i++){
    if (testhand[i] == CARD_ERROR) {
        print_str(" check 2 card error: ");
        print_int(i); print_newl();
        exit(0);
    }
}

//  your code for convert() (2.2.a) below main.
print_str("   2.2.b"); print_newl();

unsigned char card1, card2;

card1 = 0xFF;  // an invalid card
card2 = convert(1,4); // ace of spades

if (valid_card(card1) == CARD_ERROR)
    print_str(" 0xFF is not a valid card\n");
else print_str(" Somethings wrong with 2.2.b\n");
if (valid_card(card2) == CARD_ERROR)
    print_str(" Somethings wrong with 2.2.b\n");
else print_str("8-bit version of Ace of Spades is a VALID card.\n");

//  your code for convert() (2.2.a) below main.
print_str("   2.2.c,d"); print_newl();


for(i=0;i<7;i++) {
   int card = gcard(testhand[i]);  //    This part tests 2.2c,d
   int suit = gsuit(testhand[i]);
   print_str("card: "); print_int(card); print_str("   suit: "); print_int(suit);print_newl();
}

/////////////////  Part 3

char buffer[] = "   *empty*       ";


//  your code for convert() (2.2.a) below main.
print_str("Part 3.1 Test Results:");print_newl();

for(i=0;i<7;i++) {
   card = gcard(testhand[i]);  //    This part tests 2.2c,d
   suit = gsuit(testhand[i]);
   print_str(" >>>>");
   print_int(i); print_str(": "); print_int(card);print_int(suit) ;
   names(card,suit,buffer); // convert card,suit to string name in buffer
   print_str(buffer);
   print_newl();
   }
print_newl();

/*
 *     Test Part 3.2
 */
print_str("Part 3.2 Test Results:");print_newl();
print_str("Test the deal() function\n");
char buff[20]="";
for (i=0;i<3;i++) {
    print_str("\n\n----testing deal: hand: "); print_int(i);print_newl();
    print_str("Deck count: ");print_int(dealer_deck_count); print_newl();
    deal(7,testhand,cards); // see Prob 2.1 for "cards"
    print_str("--------dealt hand: \n");
    printhand(7,testhand, buff);
    print_newl();
    }

/*
 *     Test Part 3.3
 */
print_str("Part 3.3 Test Results:");print_newl();
print_str("Test the finding pokerhands function(s).\n");
unsigned char hands[10][7];   //array of 10 hands

dealer_deck_count = 0; // reset to full deck (hands should reappear)

int n_hands = 7;

for (i=0;i<n_hands;i++) {
    deal(7,hands[i],cards);
}
print_str(" I have ");print_int(n_hands); print_str(" new hands\n");
for (i=0;i<n_hands;i++) {
    int pct = pairs(7,hands[i]);
    int trips = trip_s(7,hands[i]);
    int fourk = four_kind(7,hands[i]);
    printf("I found %d pairs in hand %d\n",pct,i);
    printf("I found %d three-of-a-kinds in hand %d\n",trips,i);
    printf("I found %d four-of-a-kinds in hand %d\n",fourk,i);
    printf("Hand %d:\n",i);
    printhand(7,hands[i],buff);
    print_newl();
}

#ifdef VISUALC
getchar();
return 0;
#endif


//****************************************************************************
}  //  END OF MAIN

// Part 1.4
/*  Prints out original string to n length, if string is smaller than n characters
  adds spaces till it becomes n characters long, else truncates the string.
*/
char* length_pad(char *st, int n) {
    char *str = (char*)malloc(n);
    int length = strlen(st);
    for(int i = 0; i < length && i < n; i++) {
        str[i] = st[i];
    }
    for(int i = length - 1; i < n; i++) {
        str[i] = ' ';
    }
    return str;
}

//Part 2.1
// Creates a deck of cards from 1-13 with a suit number 1-4 and shuffles the deck.
void fill(shuffle deck[N_DECK][2]) {

    // Adds values into a deck.
    for(int i = 0; i < 52; i++) {
        deck[i][0] = (i % 13) + 1;
        deck[i][1] = (i / 13) + 1;
    }

    // Shuffles the values added randomly.
    for(int j = 0; j < 51; j++) {
      int r = j + randN(51 - j);
      int temp = deck[r][0];
      int temp2 = deck[r][1];

      deck[r][0] = deck[j][0];
      deck[r][1] = deck[j][1];

      deck[j][0] = temp;
      deck[j][1] = temp2;
    }
}

// Part 2.2
//  Converts a card number and suit number into one character and outputs if the card is valid.
unsigned char convert(int card, int suit) {
    unsigned char a = (card << 4) | suit;
    if(card > 13 || card < 0 || suit > 4 || suit < 0) {
        printf("Convert: I don't know how to handle card = %d", card);
        print_newl();
        print_int(-1);
        print_newl();
        return CARD_ERROR;
    }
    return a;
}

// Test if a card byte is a valid card
int valid_card(unsigned char card){
    int card_v = gcard(card);
    int suit_v = gsuit(card);
    if(card_v > 13 || card_v < 0 || suit_v > 4 || suit_v < 0) {
        return CARD_ERROR;
    }
    return 1;
}

// Converts the char into its equivalent card number.
int gcard(unsigned char card) {
      int c = card >> 4;
      return c;
}

// Converts the char into its equivalent suit number.
int gsuit(unsigned char card) {
      int c = card >> 4;
      int s = card - (c << 4);
      return s;
}

//Part 3.1:
// Converts a card with a number and suit into a textual representation and stores it in answer.
char * card_names[]={"Ace","2","3","4","5","6","7","8","9","10","Jack","Queen","King"};
char * suit_names[]={"Hearts","Diamonds","Clubs","Spades"};

void names(int card, int suit, char *answer) {

    char *ans = answer;
    char *c = card_names[card - 1];
    char *s = suit_names[suit - 1];
    char *a = " of ";

    // Connects the card name to answer.
    while(*c) {
        *ans = *c;
        ans++;
        c++;
    }
    *ans = '\0';

    // Iterates the answer array.
    iterate(ans);

    // Connects answer to " of ".
    while(*a) {
        *ans = *a;
        ans++;
        a++;
    }
    *ans = '\0';

    // Iterates the answer array.
    iterate(ans);

    // Connects answer to the suit name.
    while(*s) {
        *ans = *s;
        ans++;
        s++;
    }
    *ans = '\0';
}

// Iterates an array.
void iterate(char *p) {
    while(*p != '\0') {
        p++;
    }
}

// Part 3.2
// Takes cards from a deck and deals them to a hand with each hand containing M cards.
void deal(int M, unsigned char hand[7], int deck[N_DECK][2]){
    print_str("deal: "); print_int(M); print_str(""); print_int(dealer_deck_count);
    print_newl();
    for(int i = 0; i < M; i++) {
        hand[i] = convert(deck[dealer_deck_count][0], deck[dealer_deck_count][1]);
        dealer_deck_count++;
    }
}

// Print out a hand of cards.
void printhand(int M, unsigned char* hand, char* buff1) {
    for(int i = 0; i < M; i++) {
        names(gcard(hand[i]), gsuit(hand[i]), buff1);
        print_str(buff1);
        print_newl();
    }
}

// Returns the number of pairs in a hand.
int pairs(int M, unsigned char hand[]) {
    int p = 0;
    for(int i = 0; i < M; i++) {
        for(int j = i + 1; j < M; j++) {
            if(gcard(hand[i]) == gcard(hand[j])) {
                p++;
            }
        }
    }
    return p;
}

// Returns the number of triples in a hand.
int trip_s(int M, unsigned char hand[]){
    int triple = 0;
    int t = 0;
    for(int i = 0; i < M; i++) {
        for(int j = i + 1; j < M; j++) {
            if(gcard(hand[i]) == gcard(hand[j])) {
                t++;
            }
            if(t == 2) {
                t = 0;
                triple++;
            }

        }
        t = 0;
    }
    return triple;
}

// Returns the number of 4 of a kinds in a hand.
int four_kind(int M, unsigned char hand[])  {
    int four = 0;
    int t = 0;
    for(int i = 0; i < M; i++) {
        for(int j = i + 1; j < M; j++) {
            if(gcard(hand[i]) == gcard(hand[j])) {
                t++;
            }
            if(t == 3) {
                t = 0;
                four++;
            }
        }
        t = 0;
    }
    return four;
}

/**************************************************************************
  simplified I/O and other functions for this assignment
***************************************************************************/
void print_int(int x)
  {
  printf(" %d ",x);
  }
void print_usi(unsigned int x)
  {
  printf(" %d",x);
  }
void print_dble(double x)
  {
  printf(" %f",x);
  }
void print_newl()
  {
  printf("\n");
  }
void print_str(char *x)
  {
  printf("%s",x);
  }
void print_chr(char x)
  {
  printf("%c",x);
  }

int randN(int n)   //  return a random integer between 1 and n
  {
  double x;
  x = 1.0 + (double) n * rand() / RAND_MAX;
  return((int)x);
  }
