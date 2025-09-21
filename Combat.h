#include "Pokemon.h"

int calculatePriority(array<int,2> move1, Pokemon Poke1, array<int,2> move2, Pokemon Poke2) {
    int res;
    int fastest;
    Poke1.getSpeed() > Poke2.getSpeed() ? fastest = 0 : fastest = 1;

    // Inventory

    if (move1[0] == 3 && move2[0] == 3) {
        return rand() % 2;
    }

    // I'll consider inventory as first priority as I found nothing online
    else if (move1[0] == 3) {
        return 0;
    }
    else if (move2[0] == 3) {
        return 1;
    }

    // Attack and Team Swap

    // MovePriority first
    else if (move1[0] == 1 && move2[0] == 1) {
        if (movesPriority[Poke1.getMoveset()[move1[1]-1].getId()] > movesPriority[Poke2.getMoveset()[move2[1]-1].getId()]) {
            return 0;
        }
        else if (movesPriority[Poke1.getMoveset()[move1[1]-1].getId()] < movesPriority[Poke2.getMoveset()[move2[1]-1].getId()]) {
            return 1;
        }
        else {
            return fastest;
        }
    }

    // Team Swap and Attack

    else if (move1[0] == 1 && move2[0] == 2) {
        if (movesPriority[Poke1.getMoveset()[move1[1]-1].getId()] > 1) {
            return 0;
        }
        else {
            return fastest;
        }
    }
    else if (move2[0] == 2 && move2[0] == 1) {
        if (movesPriority[Poke2.getMoveset()[move2[1]-1].getId()] > 1) {
            return 1;
        }
        else {
            return fastest;
        }

    // Team Swap only
    }
    else {
        return fastest;
    }
}

void displayPokemons(vector<Pokemon> Pokemons) {
    for (int i = 0; i < Pokemons.size(); i++) {
        cout << i+1 << " : " << Pokemons[i].getName() << endl;
    }
}

void displayAttacks(vector<Attack> Attacks) {
    for (int i = 0; i < Attacks.size(); i++) {
        cout << i+1 << " : " << Attacks[i].getName() << endl;
    }
}
