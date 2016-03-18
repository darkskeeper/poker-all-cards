#include <vector>
#include <iostream>
#include <string>
using namespace std;

#define Ncards_one_suit 13
#define Ncards_hand 5

enum RANK { FIVE = 3, TEN = 8, JACKET, QUEEN, KING, ACE };
enum SUIT { CLUBS, DIAMONDS, HEARTS, SPADES };

int determine_cards ( string );
string straight_flash_check ( vector <int> );

int main()
{
    int Ntests;
    cin >> Ntests;
    vector <string> answers;
    while( Ntests-- )
    {
        vector <int> cards(52, 0);
        vector <int> combs(5, 0);
        vector <int> your_hand(Ncards_hand, 0);
        vector <string> your_cards(Ncards_hand);
        for ( int i = 0 ; i < Ncards_hand ; i++ )
        {
            cin >> your_cards[i];
        }
        for ( int i = 0 ; i < Ncards_hand ; i++ )
        {
            your_hand[i] = determine_cards ( your_cards[i] );
            cards[ your_hand[i] ] = 1;
        }
        for (int i = 0; i < Ncards_one_suit; i++)
        {
            combs[cards[i] + cards[i + (1 * Ncards_one_suit )] + cards[i + (2 * Ncards_one_suit )] + cards[i + (3 * Ncards_one_suit )] ]++;
        }
        if( combs[1] == Ncards_hand )
        {
            answers.push_back ( straight_flash_check(your_hand) );
        }
        else if ( combs[4] == 1 )
        {
            answers.push_back ("four of a kind");
        }
        else if ( combs[3] == 1 )
        {
            if ( combs[2] == 1 )
            {
                answers.push_back ("full house");
            }
            else
            {
                answers.push_back ("three of a kind");
            }
        }
        else if ( combs[2] == 2 )
        {
            answers.push_back ("two pairs");
        }
        else
        {
            answers.push_back ("pair");
        }
    }
    vector <string> :: iterator it;
    for ( it = answers.begin(); it != answers.end(); ++it )
    {
        cout << *it << endl;
    }
    return 0;
}

int determine_cards (string str)
{
    int rank, suit;
    if ( str.at(0) <= '9' && str.at(0) >= '2' )
    {
        rank = str.at(0) - '2';//переводим char в int, где rank будет значение (карты - 2), то есть для 5 rank = 3
    }
    else
    {
        switch(str.at(0))
        {
        case 'A':
            rank = ACE;
            break;
        case 'J':
            rank = JACKET;
            break;
        case 'K':
            rank = KING;
            break;
        case 'Q':
            rank = QUEEN;
            break;
        case 'T':
            rank = TEN;
            break;
        }
    }
    switch(str.at(1))
    {
    case 'C':
        suit = CLUBS;
        break;
    case 'D':
        suit = DIAMONDS;
        break;
    case 'H':
        suit = HEARTS;
        break;
    case 'S':
        suit = SPADES;
        break;
    }
    return rank + Ncards_one_suit * suit;
}

string straight_flash_check ( vector <int> hand )
{
    bool is_flash = true;
    int your_suit = hand[0]/Ncards_one_suit;
    bool is_straight;
    int min = hand[0]%Ncards_one_suit;
    int max = min;
    for( int i = 1 ; i < Ncards_hand ; i++ )
    {
        if( hand[i] / Ncards_one_suit != your_suit && is_flash )
        {
            is_flash = false;
        }
        if( hand[i] % Ncards_one_suit > max )
        {
            max = hand[i] % Ncards_one_suit;
        }
        if ( hand[i] % Ncards_one_suit < min )
        {
            min = hand[i] % Ncards_one_suit;
        }
    }
    if(max-min == 4)
    {
        is_straight = true;
    }
    else
    {
        is_straight = false;
        if ( max == ACE )
        {
            max = 0;
            for ( int i = 0 ; i < Ncards_hand ; i++ )
            {
                if( hand[i] % Ncards_one_suit > max && hand[i] % Ncards_one_suit != ACE)
                {
                    max = hand[i] % Ncards_one_suit;
                }
            }
            if ( max == FIVE )
            {
                is_straight = true;
            }
        }
    }
    if (is_straight == false && is_flash == false)
    {
        return "high card";
    }
    else
    {
        if(is_straight == true)
        {
            if (is_flash == true)
            {
                if (max == ACE)
                {
                    return "royal flush";
                }
                else
                {
                    return "straight flush";
                }
            }
            else
            {
                return "straight";
            }
        }
        else
        {
            return "flush";
        }
    }
}