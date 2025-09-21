#ifndef UTILS_H
#define UTILS_H

#include <unordered_map>
#include <iostream>
#include <array>
#include <cstdlib>
#include <ctime> 
using namespace std;

unordered_map<string, int> encodeTypes = {
    {"Normal", 0}, {"Feu", 1}, {"Eau", 2}, {"Électrik", 3}, {"Plante", 4},
    {"Glace", 5}, {"Combat", 6}, {"Poison", 7}, {"Sol", 8}, {"Vol", 9},
    {"Psy", 10}, {"Insecte", 11}, {"Roche", 12}, {"Spectre", 13}, {"Dragon", 14},
    {"Ténèbres", 15}, {"Acier", 16}, {"Fée", 17},

    {"Normal", 0}, {"Fire", 1}, {"Water", 2}, {"Electric", 3}, {"Grass", 4},
    {"Ice", 5}, {"Fighting", 6}, {"Poison", 7}, {"Ground", 8}, {"Flying", 9},
    {"Psychic", 10}, {"Bug", 11}, {"Rock", 12}, {"Ghost", 13}, {"Dragon", 14},
    {"Dark", 15}, {"Steel", 16}, {"Fairy", 17}
};

string frTypesList[18] = {"Normal", "Feu", "Eau", "Électrik", "Plante",
                    "Glace", "Combat", "Poison", "Sol", "Vol",
                    "Psy", "Insecte", "Roche", "Spectre", "Dragon",
                    "Ténèbres", "Acier", "Fée"};

string enTypesList[18] = {"Normal", "Fire", "Water", "Electric", "Grass",
                        "Ice", "Fighting", "Poison", "Ground", "Flying",
                        "Psychic", "Bug", "Rock", "Ghost", "Dragon",
                        "Dark", "Steel", "Fairy"};

// https://pokemondb.net/type

double strweachart[18][18] = { // [Attaquant][Défenseur]
    //   Nor  Fir  Wat  Ele  Gra  Ice  Fig  Poi  Gro  Fly  Psy  Bug  Roc  Gho  Dra  Dar  Ste  Fai
        {1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 0.5, 0  , 1  , 1  , 0.5, 1  },  // Normal
        {1  , 0.5, 0.5, 1  , 2  , 2  , 1  , 1  , 1  , 1  , 1  , 2  , 0.5, 1  , 0.5, 1  , 2  , 1  },  // Fire
        {1  , 2  , 0.5, 1  , 0.5, 1  , 1  , 1  , 2  , 1  , 1  , 1  , 2  , 1  , 0.5, 1  , 1  , 1  },  // Water
        {1  , 1  , 2  , 0.5, 0.5, 1  , 1  , 1  , 0  , 2  , 1  , 1  , 1  , 1  , 0.5, 1  , 1  , 1  },  // Electric
        {1  , 0.5, 2  , 1  , 0.5, 1  , 1  , 0.5, 2  , 0.5, 1  , 0.5, 2  , 1  , 0.5, 1  , 0.5, 1  },  // Grass
        {1  , 0.5, 0.5, 1  , 2  , 0.5, 1  , 1  , 2  , 2  , 1  , 1  , 1  , 1  , 2  , 1  , 0.5, 1  },  // Ice
        {2  , 1  , 1  , 1  , 1  , 2  , 1  , 0.5, 1  , 0.5, 0.5, 0.5, 2  , 0  , 1  , 2  , 2  , 0.5},  // Fighting
        {1  , 1  , 1  , 1  , 2  , 1  , 1  , 0.5, 0.5, 1  , 1  , 1  , 0.5, 0.5, 1  , 1  , 0  , 2  },  // Poison
        {1  , 2  , 1  , 2  , 0.5, 1  , 1  , 2  , 1  , 0  , 1  , 0.5, 2  , 1  , 1  , 1  , 2  , 1  },  // Ground
        {1  , 1  , 1  , 0.5, 2  , 1  , 2  , 1  , 1  , 1  , 1  , 2  , 0.5, 1  , 1  , 1  , 0.5, 1  },  // Flying
        {1  , 1  , 1  , 1  , 1  , 1  , 2  , 2  , 1  , 1  , 0.5, 1  , 1  , 1  , 1  , 0  , 0.5, 1  },  // Psychic
        {1  , 0.5, 1  , 1  , 2  , 1  , 0.5, 0.5, 1  , 0.5, 2  , 1  , 1  , 0.5, 1  , 2  , 0.5, 0.5},  // Bug
        {1  , 2  , 1  , 1  , 1  , 2  , 0.5, 1  , 0.5, 2  , 1  , 2  , 1  , 1  , 1  , 1  , 0.5, 1  },  // Rock
        {0  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 2  , 1  , 0.5, 1  , 1  },  // Ghost
        {1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 1  , 2  , 1  , 0.5, 0  },  // Dragon
        {1  , 1  , 1  , 1  , 1  , 1  , 0.5, 1  , 1  , 1  , 2  , 1  , 1  , 2  , 1  , 0.5, 1  , 0.5},  // Dark
        {1  , 0.5, 0.5, 0.5, 1  , 2  , 1  , 1  , 1  , 1  , 1  , 1  , 2  , 1  , 1  , 1  , 0.5, 2  },  // Steel
        {1  , 0.5, 1  , 1  , 1  , 1  , 2  , 0.5, 1  , 1  , 1  , 1  , 1  , 1  , 1  , 2  , 0.5, 1  },  // Fairy
    };


// https://pwo-wiki.info/index.php/Priority_Moves

int movesPriority[354] = {0}; // Using attacks.csv

void initializeMovesPriority() {
    movesPriority[270] = 5; // Helping Hand

    // +4 Priority
    movesPriority[277] = 4; // Magic Coat
    movesPriority[197] = 4; // Detect
    movesPriority[203] = 4; // Endure
    movesPriority[182] = 4; // Protect

    // +3 Priority
    movesPriority[252] = 3; // Fake Out
    movesPriority[266] = 3; // Follow Me

    // +2 Priority
    movesPriority[185] = 2; // Feint
    movesPriority[245] = 2; // Extremespeed

    // +1 Priority
    // movesPriority[] = 1; // Aqua Jet
    movesPriority[117] = 1; // Bide
    // movesPriority[] = 1; // Bullet Punch
    movesPriority[420] = 1; // Ice Shard
    movesPriority[183] = 1; // Mach Punch
    movesPriority[98]  = 1; // Quick Attack
    // movesPriority[] = 1; // Shadow Sneak
    movesPriority[389] = 1; // Sucker Punch
    // movesPriority[] = 1; // Vacuum Wave

    // -1 Priority
    movesPriority[233] = -1; // Vital Throw

    // -3 Priority
    movesPriority[264] = -3; // Focus Punch

    // -4 Priority
    // movesPriority[] = -4; // Avalanche
    movesPriority[279] = -4; // Revenge

    // -5 Priority
    movesPriority[68]  = -5; // Counter
    movesPriority[243] = -5; // Mirror Coat

    // -6 Priority
    movesPriority[46]  = -6; // Roar
    movesPriority[18]  = -6; // Whirlwind

    // -7 Priority
    // movesPriority[] = -7; // Trick Room
}

// https://pwo-wiki.info/index.php/Status_Effects

#endif