#include <vector>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    const int Ace = 12, King = 11, Queen = 10, Jacket = 9, Ten = 8, Five = 3, Ncards_one_suit = 13, Ncards_hand = 5;
    int Ntests;
    cin >> Ntests;
    while( Ntests-- )
    {
        vector <int> cards(52, 0);
        vector <int> combs(5, 0);
        vector <int> your_cards(Ncards_hand, 0);
        string *a;
        a = new string[Ncards_hand];
        for ( int i = 0 ; i < Ncards_hand ; i++ )
        {
            cin >> a[i];
        }
        int rank, suit;
        for ( int i = 0 ; i < Ncards_hand ; i++ )
        {
            if ( a[i].at(0) <= '9' && a[i].at(0) >= '2' )
            {
                rank = a[i].at(0) - '2';//переводим char в int, где rank будет значение (карты - 2), то есть для 5 rank = 3
            }
            else
            {
                switch(a[i].at(0))
                {
                case 'A':
                    rank = Ace;
                    break;
                case 'J':
                    rank = Jacket;
                    break;
                case 'K':
                    rank = King;
                    break;
                case 'Q':
                    rank = Queen;
                    break;
                case 'T':
                    rank = Ten;
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
            your_cards[i] = rank + Ncards_one_suit * suit;
            cards [your_cards[i]] = 1;
        }
        for (int i = 0; i < Ncards_one_suit; i++)
        {
            combs[cards[i] + cards[i + (1 * Ncards_one_suit )] + cards[i + (2 * Ncards_one_suit )] + cards[i + (3 * Ncards_one_suit )] ]++;
        }
        while(true)
        {
            if( combs[1] == Ncards_hand )
            {
                bool is_flash = true;
                int your_suit = your_cards[0]/Ncards_one_suit;
                bool is_straight;
                int min = your_cards[0]%Ncards_one_suit;
                int max = min;
                for( int i = 1 ; i < Ncards_hand ; i++ )
                {
                    if( your_cards[i] / Ncards_one_suit != your_suit && is_flash )
                    {
                        is_flash = false;
                    }
                    if( your_cards[i] % Ncards_one_suit > max )
                    {
                        max = your_cards[i] % Ncards_one_suit;
                    }
                    if ( your_cards[i] % Ncards_one_suit < min )
                    {
                        min = your_cards[i] % Ncards_one_suit;
                    }
                }
                if(max-min == 4)
                {
                    is_straight = true;
                }
                else
                {
                    is_straight = false;
                    if ( max == Ace )
                    {
                        max = 0;
                        for ( int i = 0 ; i < Ncards_hand ; i++ )
                        {
                            if( your_cards[i] % Ncards_one_suit > max && your_cards[i] % Ncards_one_suit != Ace)
                            {
                                max = your_cards[i] % Ncards_one_suit;
                            }
                        }
                        if ( max == Five )
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
                            if (max == Ace)
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
    system("pause");
    return 0;
}