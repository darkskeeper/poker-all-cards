#include <vector>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    int Ntests;
    cin >> Ntests;
    while( (Ntests--) != 0 )
    {
        vector <int> cards(52, 0);
        vector <int> combs(5, 0);
        vector <int> your_cards(5, 0);
        string *a;
        a = new string[5];
        for ( int i = 0 ; i < 5 ; i++ )
        {
            cin >> a[i];
        }
        int rank, suit;
        for ( int i = 0 ; i < 5 ; i++ )
        {
            if(a[i].at(0)<='9'&&a[i].at(0)>='2')
            {
                rank = a[i].at(0) - '2';
            }
            else
            {
                switch(a[i].at(0))
                {
                case 'A':
                    rank = 12;
                    break;
                case 'J':
                    rank = 9;
                    break;
                case 'K':
                    rank = 11;
                    break;
                case 'Q':
                    rank = 10;
                    break;
                case 'T':
                    rank = 8;
                    break;
                }
            }
            switch(a[i].at(1))
            {
            case 'C'://clubs
                suit = 0;
                break;
            case 'D'://diamons
                suit = 1;
                break;
            case 'H'://hearts
                suit = 2;
                break;
            case 'S'://spades
                suit = 3;
                break;
            }
            cards [rank + 13 * suit] = 1;
            your_cards[i] = rank + 13 * suit;
        }
        for (int i = 0; i < 13; i++)
        {
            combs[ cards[i] + cards[i + ( 1 * 13 ) ] + cards[i + ( 2 * 13 ) ] + cards[i + ( 3 * 13 ) ] ]++;
        }
        while(true)
        {
            if( combs[1] == 5 )
            {
                bool is_flash = true;
                int your_suit = your_cards[0]/13;
                bool is_straight;
                int min = your_cards[0]%13;
                int max = min;
                for( int i = 1 ; i < 5 ; i++ )
                {
                    if( your_cards[i] / 13 != your_suit && is_flash )
                    {
                        is_flash = false;
                    }
                    if( your_cards[i] % 13 > max )
                    {
                        max = your_cards[i]%13;
                    }
                    if ( your_cards[i] % 13 < min )
                    {
                        min = your_cards[i]%13;
                    }
                }
                
                if(max-min == 4)
                {
                    is_straight = true;
                }
                else
                {
                    is_straight = false;
                    if ( max == 12 )
                    {
                        max = 0;
                        for ( int i = 1 ; i < 5 ; i++ )
                        {
                            if( your_cards[i] % 13 > max && your_cards[i] % 13 != 12)
                            {
                                max = your_cards[i]%13;
                            }
                        }
                        if ( max == 3 )
                        {
                            is_straight = true;
                        }
                    }
                }
                if (is_straight == false && is_flash == false)
                {
                    cout << "high card";
                }
                else
                {
                    if(is_straight == true)
                    {
                        if (is_flash == true)
                        {
                            if (max == 12)
                            {
                                cout << "royal flush";
                            }
                            else
                            {
                                cout << "straight flush";
                            }
                        }
                        else
                        {
                            cout << "straight";
                        }
                    }
                    else
                    {
                        cout << "flush";
                    }
                }
                break;
            }
            if ( combs[4] == 1 )
            {
                cout << "four of a kind";
                break;
            }
            if ( combs[3] == 1 )
            {
                if ( combs[2] == 1 )
                {
                    cout << "full house";
                    break;
                }
                else
                {
                    cout << "three of a kind";
                    break;
                }
            }
            if ( combs[2] == 2 )
            {
                cout << "two pairs";
                break;
            }
            cout << "one pair";
            break;
        }
        cout << endl;
    }
    return 0;
}