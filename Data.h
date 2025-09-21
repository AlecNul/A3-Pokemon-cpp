#ifndef DATA_H
#define DATA_H

#include "Trainer.h"

#include <fstream>
#include <sstream>

vector<Pokemon> allPokemon;
vector<Attack> allAttacks;
vector<Trainer> allLeaders;

Attack getRandomAttack(vector<Attack> Attacks) {
    if (Attacks.size()>1) {
        return Attacks[random(0, Attacks.size()-1)];
    }
    return Attack(0, "Charge", "Charge", "Normal", "physical", 40, 1.0, 35);
}

vector<array<string, 8>> readAttacksCSV(string file) {
    ifstream f(file);
    vector<array<string, 8>> AttackList;

    if (!f.is_open()) {
        cerr << "Erreur : Impossible d'ouvrir le fichier " << file << endl;
        return AttackList;
    }

    string line;
    while(getline(f,line)) {
        array<string, 8> row;
        stringstream ssin(line);

        string cell;
        int i = 0;
        while(getline(ssin, cell, ',') && i < 8) { // On remplit la ligne avec les cellules cell correspondant aux colonnes row[i]
            row[i] = cell;
            i++;
        }

        if (i==8) {
            AttackList.push_back(row); // On ajoute la ligne à la liste des attaques
        }
    }
    return AttackList;
}

void fillAttackData(vector<array<string, 8>> AttackList) {
    for (int i = 1; i < AttackList.size(); i++) {

        double accuracy;
        if (AttackList[i][6] == "") {
            AttackList[i][6] = "100%";
        }
        AttackList[i][6].pop_back(); // On retire le "%" à la fin
        accuracy = stod(AttackList[i][6])*0.01; // et on convertit avec 0.01


        Attack newAttack(stoi(AttackList[i][0]), AttackList[i][1], AttackList[i][2], AttackList[i][3], AttackList[i][4], stoi(AttackList[i][5]), accuracy, stoi(AttackList[i][7]));
        allAttacks.push_back(newAttack);
    }
}

vector<array<string, 12>> readPokeCSV(string file) {
    ifstream f(file);
    vector<array<string, 12>> PokeList;

    if (!f.is_open()) {
        cerr << "Erreur : Impossible d'ouvrir le fichier " << file << endl;
        return PokeList;
    }

    string line;
    while (getline(f, line)) {
        array<string, 12> row;
        stringstream ssin(line);

        string cell;
        int i = 0;
        while (getline(ssin, cell, ',') && i < 12) {
            row[i] = cell;
            i++;
        }

        if (i == 12) {
            PokeList.push_back(row);
        }
    }
    return PokeList;
}

void fillPokeData(vector<array<string, 12>> PokeList) {
    for (int i = 1; i < PokeList.size(); i++) {

        vector<string> types = {};

        if (PokeList[i][3] == "") {
            types = {PokeList[i][2]};
        }
        else {
            types = {PokeList[i][2], PokeList[i][3]};
        }

        int stats [6] = {0, 0, 0, 0, 0, 0};

        stats[0] = stoi(PokeList[i][5]); // HP
        stats[1] = stoi(PokeList[i][6]); // Atk
        stats[2] = stoi(PokeList[i][7]); // Def
        stats[4] = stoi(PokeList[i][8]); // Speed
        stats[5] = stoi(PokeList[i][9]); // SpAtk
        stats[3] = stoi(PokeList[i][10]); // SpDef

        vector<Attack> moveset = {getRandomAttack(allAttacks)};

        Pokemon newPoke(stoi(PokeList[i][0]), PokeList[i][1], types, moveset, stod(PokeList[i][5]), stats);
        allPokemon.push_back(newPoke);
    }
}

vector<array<string, 9>> readLeadersCSV(string file) {
    ifstream f(file);
    vector<array<string, 9>> LeaderList;

    if (!f.is_open()) {
        cerr << "Erreur : Impossible d'ouvrir le fichier " << file << endl;
        return LeaderList;
    }

    string line;
    while (getline(f, line)) {
        array<string, 9> row;
        stringstream ssin(line);

        string cell;
        int i = 0;
        while (getline(ssin, cell, ',') && i < 9) {
            row[i] = cell;
            i++;
        }

        if (i == 9) {
            LeaderList.push_back(row);
        }
    }
    return LeaderList;
}

void fillLeadersData(vector<array<string, 9>> LeaderList) {
    for (int i = 1; i < LeaderList.size(); i++) {

        vector<Pokemon> team = {};
        for (int j = 3; j < 9; j++) {
            for (int k = 0; k < allPokemon.size(); k++) {
                if (allPokemon[k].getName() == LeaderList[i][j]) {
                    team.push_back(allPokemon[k]);
                }
            }
        }

        Trainer newLeader(LeaderList[i][0], LeaderList[i][1], LeaderList[i][2], team);
        allLeaders.push_back(newLeader);
    }
}

void fillRandomMoves(vector<Pokemon> Pokemons, vector<Attack> Attacks) {
    for(int i = 0; i < Pokemons.size(); i++) {
        for (int j=0; j<3; j++) {
            Pokemons[i].addAttack(getRandomAttack(Attacks));
        }
    }
}

#endif