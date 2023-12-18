/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   card.h
 * Author: SquidlyPoli1
 *
 * Created on October 26, 2023, 1:21 PM
 */
#include <cstdlib>     //NULL pointer
#include <iostream>
#include <string>
#include <list>
#include <deque>
#include <algorithm>
#include <random>

#ifndef CARD_H
#define CARD_H

using namespace std;

//General card structure
struct card {
    string ID; //Rank identifier
    char type; //Suit identifier
    bool operator==(const card& other) const {
    return type == other.type && ID == other.ID;
    }
    bool operator!=(const card& other) const {
    return type != other.type && ID != other.ID;
    }
    bool operator>(const card& other) const {
    return ID > other.ID;
    }
    bool operator<(const card& other) const {
    return ID < other.ID;
    }
    card &operator=(card other) {
        swap(type,other.type);
        swap(ID,other.ID);
        return *this;
    }
};

//Master (52-card) deck
class deckMaster {
    private:
    list<list<card>> IntDeck;
    public:
    deckMaster();
    void crtCard(card);
    card defCard(int, int);
    card retCard(int, int);
    card ersCard(int, int);
    int rnkSize(int);
    void prntDeck();
};

//Player decks
class deckPlayer {
    private:
    deque<card> PlrDeck;
    public:
    void crtCard(card data) {
        PlrDeck.push_back(data);
    }
    card retCard(int);
    card ersCard(int);
    void prntDeck();
    void shfDeck() {
        shuffle(PlrDeck.begin(), PlrDeck.end(), default_random_engine(time(0)));
    }
    int srcDeck(card);
    void swpDeck(deckPlayer&);
    int find_ID(string);
    int size() {
        int size = PlrDeck.size();
        return size;
    }
    //Determine if queen is only card
    int maid() {
        card meido;
        meido.type = 'S';
        meido.ID = "QN";
        if (PlrDeck.size() <= 1) {
            if (maxCard().ID == meido.ID) {
                return 1;
            }
            else {
                return -1;
            }
        }
        else return -1;
    }
    //Maximum card identifier
    card maxCard() {
        deque<card>::iterator max = max_element(PlrDeck.begin(), PlrDeck.end());
        card maxe = *max;
        return maxe;
    }
    //Minimum card identifier
    card minCard() {
        deque<card>::iterator min = min_element(PlrDeck.begin(), PlrDeck.end());
        card mine = *min;
        return mine;
    }
    int meido_un();
};

#endif /* CARD_H */
