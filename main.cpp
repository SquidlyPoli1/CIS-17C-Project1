/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: SquidlyPoli1
 *
 * Created on October 16, 2023, 12:34 PM
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <array>
#include <string>
#include <cstring>
#include <ctime>
#include <new>
#include <map>
#include "card.h"

using namespace std;

//Function prototypes

int game(deckMaster&,deckPlayer&,deckPlayer&);
deckPlayer createPlr(deckMaster&);
void retPair(deckMaster&,deckPlayer);
void drawCard(deckMaster&,deckPlayer&);
card drawCard(deckPlayer&,deckPlayer&);
int turn_plr(deckMaster&,deckPlayer&,deckPlayer&);
int turn_cpu(deckMaster&,deckPlayer&,deckPlayer&);
int retPair_AI(deckMaster&,deckPlayer&);
int pwdCard(int, int, deckPlayer&, deckMaster&);
void swapDeck(deckPlayer&,deckMaster&);
void testyyy();
void rules();
string random_rank(int);
int det_rank(string);

int main() {
    //Init random seed
    srand(static_cast<unsigned int>(time(0)));
    
    int choice;
    
    cout << "Welcome to Old Maid!\nA simple card game involving matching pairs." << endl;
    while (choice != 4) {
    cout << "1: Play the game\n2: Read the game rules\n3: Compare deck extremes (ends program)\n4: Exit" << endl;
    cout << "What would you like to do?: ";
    cin >> choice;
    cout << endl;
    if (choice == 1) {
    int p1_score = 0,p2_score = 0,gamec;
    char trya;
    while (trya != 'N' && trya != 'n') {
        //Create all decks
        deckMaster deck;
        card test_card = deck.ersCard((rand() % 4),11);
        deckPlayer player = createPlr(deck);
        deckPlayer cpu = createPlr(deck);
        gamec = game(deck,player,cpu);
        //Add to tally based on result
        if (gamec == 2) {
            p2_score++;
        }
        if (gamec == 1) {
            p1_score++;
        }
        //Ask for rematch
        while (toupper(trya) != 'Y' && toupper(trya) != 'N') {
            cout << "Game count: " << p1_score << "-" << p2_score << endl;
            cout << "Try again? (Y or N): ";
            cin >> trya;
            if (toupper(trya) != 'Y' && toupper(trya) != 'N')
                cout << "Please enter a valid option and try again." << endl;
        }
        cin.ignore();
        cin.clear();
    }
    }
    else if (choice == 2) {
        rules();
    }
    else if (choice == 3) {
        testyyy();
        choice = 4;
    }
    //Exit
    else if (choice == 4) {
        cout << "Have a good one!" << endl;
    }
    //Invalid choice
    else {
        cout << "Please enter a valid option and try again." << endl;
    }
    cin.ignore();
    cin.clear();
    }
    
    return 0;
}

//Rulebook function
void rules() {
    int choice = 0;
    while (choice != 4) {
        if (choice == 0) {
        cout << "1: General Rules & Setup\n2: Card Ranks & Pairing\n3: Score Counts and Rematches\n4: Go Back" << endl;
        cout << "Which one do you want to view?: ";
        cin >> choice;
        }
        cout << endl;
        cin.ignore();
        cin.clear();
        if (choice == 1) {
            char conf = '0';
            cout << "A typical deck has 52 cards." << endl;
            cout << "Each player gets one half of the deck, or at least as much of the half as possible." << endl;
            cout << "Each player removes a pair from their deck as the game goes along." << endl;
            cout << "After removing a pair, they draw a card from the other player's deck." << endl;
            cout << "After both players have drawn their cards, the player will be prompted to swap decks." << endl;
            while (conf != 'Y' && conf != 'y' && conf != 'N' && conf != 'n') {
                cout << "Would you like to continue into the Card Ranks & Pairing section? (Y or N): ";
                cin >> conf;
                if (conf == 'Y' || conf == 'y') choice = 2;
                else if (conf == 'N' || conf == 'n') {
                    choice = 0;
                    cout << endl;
                }
                else cout << "Please enter a valid option and try again." << endl;
            }
        }
        else if (choice == 2) {
            char conf = '0';
            cout << "A typical deck looks like this:" << endl;
            deckMaster testdeck;
            testdeck.prntDeck();
            cout << "One Queen card is removed from the deck to make the deck uneven when distributing." << endl;
            cout << "A pair of cards includes two cards of the same rank, such as C02 and H02." << endl;
            cout << "If a player gets a three of a kind, they only return two of those cards," << endl;
            cout << "leaving one of the three unpaired." << endl;
            cout << "The player who is left with the odd Queen card is considered the Old Maid, and loses the game." << endl;
            cout << "If a player is left with three unpaired cards instead of one, they also lose the game." << endl;
            cout << "Invalid card pairings will be noted by the interface, as the text \"Invalid pair!\" will show up if a pair has non-equal rankings." << endl;
            while (conf != 'Y' && conf != 'y' && conf != 'N' && conf != 'n') {
                cout << "Would you like to continue into the Score Counts & Rematches section? (Y or N): ";
                cin >> conf;
                if (conf == 'Y' || conf == 'y') choice = 3;
                else if (conf == 'N' || conf == 'n') {
                    choice = 0;
                    cout << endl;
                }
                else cout << "Please enter a valid option and try again." << endl;
            }
        }
        else if (choice == 3) {
            char conf = '0';
            cout << "When a game ends, the loser and their method of losing will be declared by the interface," << endl;
            cout << "and the total score between the two players will be displayed." << endl;
            cout << "The interface will ask if the player wants a rematch." << endl;
            cout << "If they answer with 'Y', a rematch will begin and the decks will be redefined." << endl;
            cout << "If they answer with 'N', they will go back to the main menu, where they can exit or view the rules." << endl;
            cout << "Starting a new game without declaring a rematch will reset the score between both players." << endl;
            while (conf != 'Y' && conf != 'y' && conf != 'N' && conf != 'n') {
                cout << "Would you like to return to the Rules menu? (Y or N): ";
                cin >> conf;
                if (conf == 'Y' || conf == 'y') {
                    choice = 0;
                    cout << endl;
                }
                else if (conf == 'N' || conf == 'n') choice = 4;
                else cout << "Please enter a valid option and try again." << endl;
            } 
        }
        else if (choice > 4 || choice < 1) {
            cout << "Please enter a valid option and try again." << endl;
            cout << "Which one do you want to view?: ";
            cin >> choice;
        }
    }
    cin.ignore();
    cin.clear();
    cout << endl;
}

//Min and max debug function
void testyyy() {
    deckMaster deck;
    card test_card = deck.ersCard((rand() % 4),11);
    deckPlayer player = createPlr(deck);
    deckPlayer cpu = createPlr(deck);
    
    card player_max= player.maxCard();
    card player_min = player.minCard();
    card cpu_max= cpu.maxCard();
    card cpu_min = cpu.minCard();
    
    cout << det_rank(player_max.ID) << det_rank(player_min.ID) << endl;
    cout << "Min of Player deck is " << player_min.type << player_min.ID << endl;
    cout << "Max of Player deck is " << player_max.type << player_max.ID << endl;
    cout << "Min of CPU deck is " << cpu_min.type << cpu_min.ID << endl;
    cout << "Max of CPU deck is " << cpu_max.type << cpu_max.ID << endl;
}

//Game function
int game (deckMaster &deck, deckPlayer &player, deckPlayer &cpu) {
    int plr_true = 0, cpu_true = 0;
    int meid1, meid2,turns = 0;
    int unp1, unp2;
    int test_size1 = player.size(), test_size2 = cpu.size();
    int numbey1 = 0,numbey2 = 0;
    char swapch;
    while((meid1 != 1 && meid2 != 1 && unp1 != 1 && unp2 != 1) && (test_size1 >= 1 && test_size2 >= 1)) {
        //Determine card sizes
        test_size1 = player.size();
        test_size2 = cpu.size();
        //Determine if player has only Maid
        meid1 = player.maid();
        meid2 = cpu.maid();
        //Determine if cards are unpaired
        unp1 = player.meido_un();
        unp2 = cpu.meido_un();
        if (meid1 != 1 && meid2 != 1 && unp1 != 1 && unp2 != 1) {
            cout << "Player Cards" << endl;
            player.prntDeck();
            cout << endl;
            cout << "CPU Cards" << endl;
            cpu.prntDeck();
            cout << endl;
            if (turns % 2 == 0 && player.meido_un() != 1 && cpu.meido_un() != 1) {
                turns += turn_plr(deck,player,cpu); //First turn is player turn
            }
            cout << endl;
            if (turns % 2 == 1 && player.meido_un() != 1 && cpu.meido_un() != 1) {
                turns += turn_cpu(deck,player,cpu); //Second turn is CPU turn
            }
            if (player.meido_un() != 1 && cpu.meido_un() != 1) {
            cout << endl;
            cout << "Player Cards" << endl;
            player.prntDeck();
            cout << endl;
            cout << "CPU Cards" << endl;
            cpu.prntDeck();
            //Prompt to swap decks
            do {
                cout << "Swap decks? (Y or N): ";
                cin >> swapch;
                cout << endl;
                if (swapch == 'Y' || swapch == 'y') {
                    player.swpDeck(cpu);
                    cout << "Swapped decks." << endl;
                }
                else if (swapch != 'Y' && swapch != 'y' && swapch != 'N' && swapch != 'n') {
                    cout << "Enter a valid option and try again." << endl;
                }
            } while (swapch != 'Y' && swapch != 'y' && swapch != 'N' && swapch != 'n');
            }
        }
        else {
            break;
        }
    };
    if (meid1 == 1 && test_size1 == 1) {
        cout << "You have only the odd queen left, so you became the Old Maid!\nYou lose." << endl;
        return 2;
    }
    else if (meid2 == 1 && test_size2 == 1) {
        cout << "The CPU has only the odd queen left, and they became the Old Maid!\nYou win!" << endl;
        return 1;
    }
    else if (meid1 != 1 && test_size1 > 1) {
        cout << "You have three unpaired cards, and you became the Old Maid!\nYou lose." << endl;
        return 2;
    }
    else if (meid2 != 1 && test_size1 > 1) {
        cout << "The CPU has three unpaired cards, and they became the Old Maid!\nYou win!" << endl;
        return 1;
    }
    //Poor stalemate
    else {
        cout << "Somebody goofed. whoops." << endl;
    }
    return -1;
}

int turn_plr(deckMaster &master, deckPlayer &plr, deckPlayer &opp) {
    int numbey1, numbey2;
    int plr_true;
    do {
        plr_true = 0;
        //Ask for cards from player
        cout << "Select cards (starting from 0 and ending with last minus 1): ";
        cin >> numbey1 >> numbey2;
        //Returns cards if both are under deck size
        if (numbey1 < plr.size() && numbey2 < plr.size()) {
            plr_true = pwdCard(numbey1,numbey2,plr, master);
            //Determines if pairing is invalid
            if (plr_true == -1) {
                cout << "Invalid pairing!" << endl;
            }
        }
        //Determines if player is only returning one card (they cannot do this)
        else if (numbey1 == numbey2) {
            cout << "You can't return only one card!" << endl;
            cin.ignore();
            cin.clear();
        }
        //If everything is invalid
        else {
            cout << "Please enter a valid number and try again." << endl;cin.ignore();
            cin.ignore();
            cin.clear();
        }
    } while(plr_true == 0);
    cout << endl;
    char drawch;
    //Prompt player to draw card
    if (plr.size() >= 3 && plr.meido_un() != 1) {
    do {
        cout << "Draw card? (Y or N): ";
        cin >> drawch;
        if (drawch == 'Y' || drawch == 'y') {
            card draw = drawCard(opp,plr);
            cout << "Player drew card " << draw.type << draw.ID << " from CPU deck" << endl;
        }
        else if (drawch != 'Y' && drawch != 'y' && drawch != 'N' && drawch != 'n') {
            cout << "Enter a valid option and try again." << endl;
        }
    } while (drawch != 'Y' && drawch != 'y' && drawch != 'N' && drawch != 'n');
    }
    cin.ignore();
    cin.clear();
    return 1;
}

int turn_cpu(deckMaster &master, deckPlayer &plr, deckPlayer &opp) {
    int plr_true = 0;
    plr_true = retPair_AI(master,opp); //Return pair algorithm
    char drawch;
    //Determines if CPU should draw card or not
    if (plr_true == 1) {
        drawch = 'Y';
    }
    else {
        drawch = 'N';
    }
    if ((toupper(drawch) == 'Y') || (toupper(drawch) == 'N' && rand() % 2 == 1)) {
        card draw = drawCard(plr,opp);
        cout << "CPU drew card " << draw.type << draw.ID << " from player deck" << endl;
    }
    else cout << "CPU chose not to draw card" << endl;
    return 1;
}

int retPair_AI(deckMaster &master, deckPlayer &plr) {
    string rank; //Random rank
    int true2 = -1,testyt;
    int count = 0;
    map<int,int> ringos; //These are the two values for the cards drawn
    while (true2 != 1 && plr.size() > 3 && count < plr.size()) {
        //Set first card node to a random card in deck
        ringos[0] = (rand() % plr.size());
        ringos[1] = -1;
        //Check if the rank is actually found, then find another
        if (ringos[0] != -1) {
            for(int i = 0; i < plr.size(); i++) {
                card testx = plr.retCard(i); //Test X is the card at the current spot
                card testy = plr.retCard(ringos[0]); //Test Y is the card at the spot where the ID was found first
                if (i != ringos[0] && (!ringos[1] || ringos[1] == -1) && testx.ID == testy.ID) {
                    ringos[1] = i;
                }
            }
            //If both IDs are equal, return cards
            if (plr.retCard(ringos[0]).ID == plr.retCard(ringos[1]).ID && (ringos[0] != ringos[1])) {
                true2 = 1;
            }
            //If both IDs are not equal, reset
            else {
                ringos[0] = -1;
                ringos[1] = -1;
            }
        }
        count++;
    }
    //Return cards
    if (true2 == 1) {
        testyt = pwdCard(ringos[0],ringos[1],plr,master);
    }
    if (ringos[0] != ringos[1] && (ringos[0] != -1 && ringos[1] != -1)) {
        cout << "CPU returned cards " << ringos[0] << " and " << ringos[1] << endl;
    }
    else {
        cout << "CPU returned no cards" << endl;
    }
    return testyt;
}

int det_rank(string leme) {
    int numer = 0;
    if (leme == "JK")
        numer = 10;
    else if (leme == "KN")
        numer = 11;
    else if (leme == "QN")
        numer = 12;
    else if (leme == "AC")
        numer = 9;
    //Everything else
    else if (leme <= "10") {
        numer = stoi(leme);
        numer = numer - 2;
    }
    return numer;
}

string random_rank(int numer) {
    string leme;
    if (numer == 8)
        leme = "10";
    else if (numer == 10)
        leme = "JK"; //Jack
    else if (numer == 11)
        leme = "KN"; //King
    else if (numer >= 12)
        leme = "QN"; //Queen
    else if (numer >= 9)
        leme = "AC"; //Ace
    //Everything else
    else {
        stringstream ememe;
        ememe << "0" << (numer + 2);
        leme = ememe.str();
    }
    return leme;
}

int pwdCard(int num1, int num2, deckPlayer &player, deckMaster &master) {
    int truedo = -1; //Determines if pair is invalid or not
    if((num1 != num2) && (player.retCard(num1).ID == player.retCard(num2).ID)) {
        truedo = 1;
    }
    if (num1 != -1 && num2 != -1) {
        //Return first card before second
        if (num1 < num2) {
            master.crtCard(player.ersCard(num1));
            master.crtCard(player.ersCard(num2 - 1));
        }
        //Return second card before first
        else if (num1 > num2) {
            master.crtCard(player.ersCard(num2));
            master.crtCard(player.ersCard(num1 - 1));
        }
    }
    return truedo;
}

deckPlayer createPlr(deckMaster &master) {
    deckPlayer newdick; //Deck to return
    card newcard;
    int randy[2],sz; //Card values and size of current deck
    int sz_total; //Total size of master deck
    while (newdick.size() < 26 && sz_total != 0) {
        randy[0] = rand() % 4;
        sz_total = master.rnkSize(0) + master.rnkSize(1) + master.rnkSize(2) + master.rnkSize(3);
        sz = master.rnkSize(randy[0]);
        if (sz > 1) {
            randy[1] = rand() % sz;
            newcard = master.retCard(randy[0],randy[1]);
            if (newdick.srcDeck(newcard) != 1) {
                newdick.crtCard(master.ersCard(randy[0],randy[1]));
            }
        }
        else if (sz == 1) {
            randy[1] = 0;
            newcard = master.retCard(randy[0],randy[1]);
            if (newdick.srcDeck(newcard) != 1) {
                newdick.crtCard(master.ersCard(randy[0],randy[1]));
            }
        }
    }
    newdick.shfDeck();
    return newdick;
}

//Drawing function
card drawCard(deckPlayer &cpu, deckPlayer &plr) {
    card newcard;
    int randy,i = 0, test = 0;
    bool match = false;
    
    while (!match && i < cpu.size()) {
        newcard = cpu.retCard(i);
        
        if (plr.srcDeck(newcard) != -1) {
            match = true;
        }
        else {
            i++;
        }
    }
    if (match == true) {
        plr.crtCard(cpu.ersCard(i));
    }
    else {
        randy = (rand() % cpu.size());
        newcard = cpu.retCard(randy);
        plr.crtCard(cpu.ersCard(randy));
    }
    return newcard;
}

void drawCard(deckMaster &master, deckPlayer &plr) {
    card newcard;
    int randy[2],i = 0, test = 0;
    while(test != 1) {
        randy[0] = (rand() % 4);
        randy[1] = (rand() % 13);
        newcard = master.retCard(randy[0],randy[1]);
        if(plr.srcDeck(newcard) == -1) {
            plr.crtCard(master.ersCard(randy[0],randy[1]));
            test = 1;
        }
        else test = 0;
        i++;
    }
}
