#include "Data.h"

// IV / EV calculation : https://bulbapedia.bulbagarden.net/wiki/Individual_values

// Stats calculation : https://bulbapedia.bulbagarden.net/wiki/Stat

int main() {

    // Initatilization
    allPokemon = {};
    allAttacks = {};
    initializeMovesPriority();
    
    // Fill
    fillAttackData(readAttacksCSV("data/attacks.csv"));
    fillPokeData(readPokeCSV("data/pokemonfull.csv"));
    fillLeadersData(readLeadersCSV("data/leaders.csv"));

    // Main
    Pokemon* Poke = &allLeaders[1].getTeam()[0];
    Pokemon Poke2 = allLeaders[1].getTeam()[0];
    // Poke2.displayMoveset();
    Poke->displayMoveset();
    //    allLeaders[1].chooseMove(Poke);
    //    allLeaders[1].Duel(allLeaders[2]);
    return 0;
}

