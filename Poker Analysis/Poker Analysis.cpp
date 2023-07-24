// Poker Analysis.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;
string card(int);
void shuffle(int[], int);
void deal(int[], int[]);
void sort(int[]);
string card(int a) {
	string ranks = "";
	string suits = "";
	string r[] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
	string s[] = { "S", "H", "D", "C" };
	int rank = a / 4 + 1;
	int suit = a % 4;
	ranks = r[rank - 1];
	suits = s[suit];
	return  ranks + suits;
}
void shuffle(int deck[], int e) {
	int t;
	int randOne;
	int randTwo;
	for (int j = 0; j < e; j++)
	{
		randOne = rand() % 52;
		randTwo = rand() % 52;
		t = deck[randOne];
		deck[randOne] = deck[randTwo];
		deck[randTwo] = t;
	}
}
void deal(int d[], int h[]) {
	int i;
	for (i = 0; i < 5; i++)
	{
		h[i] = d[i];
	}
}
void sort(int h[]) {
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4 - i; j++)
		{
			if (h[j] > h[j + 1])
			{
				int t = h[j];
				h[j] = h[j + 1];
				h[j + 1] = t;
			}
		}
	}
}
int analyzeHand(int h[]) {
    int r[5];
    int s[5];
    int Full = 0;
    int Flush = 0;
    int Straight = 0;
    int Pair = 0;
    int ThreeKind = 0;
    int FourKind = 0;
    for (int i = 0; i < 5; i++)
    {
        r[i] = h[i] / 4 + 1;
    }
    for (int i = 0; i < 5; i++) {
        s[i] = h[i] % 4;
    }
    for (int i = 0; i < 5; i++)
    {
        if (r[i] == r[i + 1] - 1)
        {
            Straight++;
        }
    }
    for (int i = 0; i < 5; i++)
    {
        if (s[i] == s[i + 1])
        {
            Flush++;
        }
    }
    for (int i = 0; i < 5; i++)
    {
        if (r[i] == r[i + 1])
        {
            Pair++;
        }
    }
    for (int i = 0; i < 5; i++)
    {
        if (r[i] == r[i + 1] && r[i] == r[i + 2])
        {
            ThreeKind++;
        }
    }
    for (int i = 0; i < 5; i++)
    {
        if (r[i] == r[i + 1] && r[i] == r[i + 2] && r[i] == r[i + 3])
        {
            FourKind++;
        }

    }
    for (int i = 0; i < 5; i++) {
        if (((r[i] == r[i + 1] && r[i] == r[i + 2]) && (r[i + 3] == r[i + 4]))
            || ((r[i] == r[i + 2] && r[i] == r[i + 3]) && (r[i + 1] == r[i + 4]))
            || ((r[i] == r[i + 3] && r[i] == r[i + 4]) && (r[i + 1] == r[i + 2]))
            || ((r[i] == r[i + 2] && r[i] == r[i + 4]) && (r[i + 1] == r[i + 3]))
            || ((r[i] == r[i + 1] && r[i] == r[i + 4]) && (r[i + 2] == r[i + 3]))
            || ((r[i] == r[i + 1] && r[i] == r[i + 3]) && (r[i + 2] == r[i + 4]))
            || ((r[i + 2] == r[i + 3] && r[i + 2] == r[i + 4]) && (r[i] == r[i + 1]))
            || ((r[i + 1] == r[i + 3] && r[i + 1] == r[i + 4]) && (r[i] == r[i + 2]))
            || ((r[i + 1] == r[i + 2] && r[i + 1] == r[i + 4]) && (r[i] == r[i + 3]))
            || ((r[i + 1] == r[i + 3] && r[i + 1] == r[i + 2]) && (r[i] == r[i + 4]))) {
            Full++;
        }

    }
    if (Straight == 4 && Flush == 4)
    {
        return 1;
    }
    else if (FourKind == 1)
    {
        return 2;
    }
    else if (Full == 1)
    {
        return 3;
    }
    else if (Flush == 4)
    {
        return 4;
    }
    else if (Straight == 4)
    {
        return 5;
    }
    else if (ThreeKind == 1)
    {
        return 6;
    }
    else if (Pair == 2)
    {
        return 7;
    }
    else if (Pair == 1)
    {
        return 8;
    }
    else
    {
        return 9;
    }
}
int main() {
    int seed;
    int deck[52];
    int hand[5];
    int numHands;
    unsigned long int hands[10] = { 0 };
    cout << "Enter the seed value : ";
    cin >> seed;
    srand(seed);
    for (int i = 0; i < 52; i++)
    {
        deck[i] = i;
    }
    for (int i = 0; i < 5; i++)
    {
        shuffle(deck, 338);
        deal(deck, hand);
        sort(hand);
        cout << "  " << card(hand[0]) << "  " << card(hand[1]) << "  " << card(hand[2]) << "  " << card(hand[3]) << "  " << card(hand[4]) << endl;

    }
    cout << "Enter the number of hands : ";
    cin >> numHands;
    for (int i = 0; i < numHands; i++)
    {
        shuffle(deck, 338);
        deal(deck, hand);
        sort(hand);
        int type = analyzeHand(hand);
        hands[type]++;
    }
    cout << "Straight Flush\t" << setw(10) << right << hands[1] << left << "   " << fixed << setprecision(5) << abs((double)hands[1] / numHands * 100) << "%" << endl;
    cout << "Four of a Kind\t" << setw(10) << right << hands[2] << left << "   " << fixed << setprecision(5) << abs((double)hands[2] / numHands * 100) << "%" << endl;
    cout << "Full House\t" << setw(10) << right << hands[3] << left << "   " << fixed << setprecision(5) << abs((double)hands[3] / numHands * 100) << "%" << endl;
    cout << "Flush\t\t" << setw(10) << right << hands[4] << left << "   " << fixed << setprecision(5) << abs((double)hands[4] / numHands * 100) << "%" << endl;
    cout << "Straight\t" << setw(10) << right << hands[5] << left << "   " << fixed << setprecision(5) << abs((double)hands[5] / numHands * 100) << "%" << endl;
    cout << "Three of a Kind\t" << setw(10) << right << hands[6] << left << "   " << fixed << setprecision(5) << abs((double)hands[6] / numHands * 100) << "%" << endl;
    cout << "Two Pair\t" << setw(10) << right << hands[7] << left << "   " << fixed << setprecision(5) << abs((double)hands[7] / numHands * 100) << "%" << endl;
    cout << "One Pair\t" << setw(10) << right << hands[8] << left << "   " << fixed << setprecision(5) << abs((double)hands[8] / numHands * 100) << "%" << endl;
    cout << "High Card\t" << setw(10) << right << hands[9] << left << "   " << fixed << setprecision(5) << abs((double)hands[9] / numHands * 100) << "%" << endl;
    return 0;

}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
