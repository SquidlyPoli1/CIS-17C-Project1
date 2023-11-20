/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   card.cpp
 * Author: SquidlyPoli1
 * 
 * Created on October 26, 2023, 1:21 PM
 */

#include "card.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <sstream>
#include <deque>
#include <algorithm>

using namespace std;

deckMaster::deckMaster() {
    card placeholder;
    
    for(int i = 0; i < 4; i++) {
    list<card> check1;
    for(int j = 0; j < 13; j++) {
        placeholder = defCard(i,j);
        check1.push_back(placeholder);
    }
    IntDeck.push_back(check1);
    }
}

card deckMaster::defCard(int i, int j) {
    card refe;
    //Set Card Type
    if (i == 0)
        refe.type = 'S'; //Spade
    else if (i == 1)
        refe.type = 'H'; //Heart
    else if (i == 2)
        refe.type = 'C'; //Club
    else
        refe.type = 'D'; //Diamond
    
    //Set Card ID
    if (j == 8)
        refe.ID = "10";
    else if (j == 9)
        refe.ID = "JK"; //Jack
    else if (j == 10)
        refe.ID = "KN"; //King
    else if (j == 11)
        refe.ID = "QN"; //Queen
    else if (j >= 12)
        refe.ID = "AC"; //Ace
    else {
        stringstream ememe;
        ememe << "0" << (j + 2);
        refe.ID = ememe.str();
    }
    
    return refe;
}

void deckMaster::crtCard(card valie) {
    //Define necessary  variables
    int a = 0, i;
    if(valie.type == 'S') i = 0;
    else if(valie.type == 'H') i = 1;
    else if(valie.type == 'C') i = 2;
    else i = 3;
    
    //Define iterators
    list<list<card>>::iterator it;
    list<card>::iterator it2;
    
    //Loop until int elements are found
    for(it = IntDeck.begin(); it != IntDeck.end() && (a < (i + 1)); ++it) {
        list<card> valor = *it;
        if(a == i) valor.push_back(valie);
        a++;
    }
}

card deckMaster::retCard(int i, int j) {
    //Define necessary  variables
    card valie;
    int a = 0, b;
    
    //Define iterators
    list<list<card>>::iterator it;
    list<card>::iterator it2;
    
    //Loop until int elements are found
    for(it = IntDeck.begin(); it != IntDeck.end() && (a < (i + 1)); ++it) {
        b = 0;
        list<card>& valor=*it;
        for(it2 = valor.begin(); it2 != valor.end() && (b < (j + 1)); ++it2) {
            valie = *(it2);
            b++;
        }
        a++;
    }
    return valie;
}

card deckMaster::ersCard(int i, int j) {
    //Define necessary  variables
    int a = 0, b;
    card testy = retCard(i,j);
    
    //Define iterators
    list<list<card>>::iterator it;
    list<card>::iterator it2;
    //Loop until int elements are found
    for(it = IntDeck.begin(); it != IntDeck.end() && (a < (i + 1)); ++it) {
        b = 0;
        list<card>& valor=*it;
        for(it2 = valor.begin(); it2 != valor.end() && (b < (j + 1)); ++it2) {
            if(a == i && b == j)
                valor.erase(it2);
            b++;
        }
        a++;
    }
    return testy;
}

void deckMaster::prntDeck() {
    //Define iterators
    list<list<card>>::iterator it;
    list<card>::iterator it2;
    //Loop until int elements are found
    for(it = IntDeck.begin(); it != IntDeck.end(); ++it) {
        list<card>& valor=*it;
        for(it2 = valor.begin(); it2 != valor.end(); ++it2) {
            card valie = *it2;
            cout << valie.type << valie.ID << " ";
        }
        cout << endl;
    }
    cout << endl;
}


int deckMaster::rnkSize(int rank) {
    //Define necessary  variables
    int a = 0, b;
    
    //Define iterators
    list<list<card>>::iterator it;
    list<card>::iterator it2;
    
    //Loop until int elements are found
    for(it = IntDeck.begin(); it != IntDeck.end(); ++it) {
        if (a == rank) {
            list<card>& valor = *it;
            b = valor.size();
        }
        a++;
    }
    return b;
}


card deckPlayer::retCard(int i) {
    //Define necessary  variables
    card valie;
    int a = 0, b;
    
    //Define iterators
    deque<card>::iterator it;
    
    //Loop until int elements are found
    for(it = PlrDeck.begin(); it != PlrDeck.end() && (a < (i + 1)); ++it) {
        valie = *it;
        a++;
    }
    return valie;
}

card deckPlayer::ersCard(int i) {
    //Define necessary  variables
    int a = 0;
    card testy = retCard(i);
    //Define iterators
    deque<card>::iterator it;
    //Loop until int elements are found
    for(it = PlrDeck.begin(); it != PlrDeck.end() && (a < (i + 1)); ++it) {
        if(a == i)
            PlrDeck.erase(it);
        a++;
    }
    return testy;
}

void deckPlayer::prntDeck() {
    int size = PlrDeck.size();
    for(int i = 0; i < size; i++) {
    cout << retCard(i).type << retCard(i).ID << " ";
    if (i == (abs(size / 2) - 1))
        cout << endl;
    }
    cout << endl;
}

int deckPlayer::srcDeck(card val) {
    deque<card>::iterator it;
    int valor;
    it = find(PlrDeck.begin(), PlrDeck.end(), val);
    if (it != PlrDeck.end())
        valor = 1;
    else
        valor = -1;
    return valor;
}

void deckPlayer::swpDeck(deckPlayer &other) {
    swap(PlrDeck,other.PlrDeck); //Simply use the swap algorithm lol
}

int deckPlayer::meido_un() {
    int instances = 0;
    if (PlrDeck.size() == 3) {
        if (retCard(0).ID != retCard(1).ID) {
            instances++;
        }
        if (retCard(1).ID != retCard(2).ID) {
            instances++;
        }
        if (retCard(2).ID != retCard(0).ID) {
            instances++;
        }
    }
    if (instances >= 3) {
        return 1;
    }
    return -1;
}