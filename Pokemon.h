#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "Attack.h"

using namespace std;

class Pokemon {

// Attributes
    protected:
        int const pokedexID;
        string const name;
        
        int types[2];
        int stats[6]; // maxhp, str, def, speed, spatk, spdef
        vector<Attack> moveset;
        double hp;

        int level; // On devrait faire double xp; aussi pour augmenter les lvls 
        // int sprite; // Potentiellement pour le display ? pour l'instant un int
    

// Constructors 
    public:
        Pokemon(int id, string n, vector<string> t, vector<Attack> mv, double h, int s[6], int l = 1) : pokedexID(id), name(n) {
            types[0] = encodeTypes[t[0]];
            types[1] = (t.size() > 1) ? encodeTypes[t[1]] : -1;
    
            moveset = mv;
            hp = h;
            for (int i = 0; i < 6; i++) {
                stats[i] = s[i];
            }
            level = 5;
        }

// Getters
        string getName() const {
            return name;
        }
        int getPokedexID() const {
            return pokedexID;
        }
        double getHp() const {
            return hp;
        }
        vector<int> getTypes() const {
            return {types[0], types[1]};
        }
        vector<Attack> getMoveset() const {
            return moveset;
        }

        int getMaxHp() const {
            return stats[0];
        }
        int getStrength() const {
            return stats[1];
        }
        int getDefense() const {
            return stats[2];
        }
        int getSpeed() const {
            return stats[3];
        }
        int getSpecialAttack() const {
            return stats[4];
        }
        int getSpecialDefense() const {
            return stats[5];
        }


// Setters
        void setHp(int h) {
            hp = h;
        }

// Affichage
        virtual void display() const {
            cout << "Nom : " << name << endl;
            if (types[1] != -1) { cout << "Types : " << frTypesList[types[0]] << " " << frTypesList[types[1]] << endl; } 
            else { cout << "Type : " << frTypesList[types[0]] << endl; }
            cout << "PV : " << hp << endl;
            cout << "Attaques : " << endl;
            for (int i = 0; i < moveset.size(); i++) {
                cout << i+1 << " : " << moveset[i].getName() << endl << endl;
            }
        }
        virtual void displayEVs() const {
            cout << "Statistiques (EVs) : " << endl;
            cout << "PV max : " << stats[0] << endl;
            cout << "Attaque : " << stats[1] << endl;
            cout << "Défense : " << stats[2] << endl;
            cout << "Vitesse : " << stats[3] << endl;
            cout << "Attaque Spéciale : " << stats[4] << endl;
            cout << "Défense Spéciale : " << stats[5] << endl << endl;
        }
        virtual void displayMoveset() const {
            for (int i = 0; i < moveset.size(); i++) {
                cout << i+1 << " : " << moveset[i].getName() << endl;
            }
        }

// Methods
        void addAttack(Attack a) {
            if (find(moveset.begin(), moveset.end(), a) == moveset.end()) {
            moveset.push_back(a);
             }
        }

        double const attack(Pokemon& target, int index) {
        // Variables
            int attackType = moveset[index].getType();
            int power = moveset[index].getPower();
            string attackKind = moveset[index].getKind();
            vector<int> targetTypes = target.getTypes();

            double STAB = (types[0] == attackType || types[1] == attackType) ? 1.5 : 1.0;
            double typeEffectiveness = strweachart[attackType][targetTypes[0]] * strweachart[attackType][targetTypes[1]];
            double randomValue = (rand() % (255 - 217 + 1) + 217) / 255.0; // Voir documentation
            int criticalHit = (rand() % (10000) + 1) <= 625 ? 2 : 1; // 6.25%
            double damage;
        // Calculs
            if (attackKind == "Physical") { damage = ((((2*level*criticalHit/5)+2)*power*(stats[1]/target.getDefense())) / 50) + 2; } 
            else if (attackKind == "Special") { damage = ((((2*level*criticalHit/5)+2)*power*(stats[5]/target.getSpecialDefense())) / 50) + 2; }
            else { damage = 0; } // Attaque statut ou similaire

            damage *= STAB * typeEffectiveness * randomValue;

        // Affichage
            string targetName = target.getName();
            string attackName = moveset[index].getName();

            cout << name << "utilises " << attackName << " sur " << targetName << "..." << endl;
            if (typeEffectiveness == 0) {
                cout << targetName << "est immunisé !" << endl;
            }
            else if (typeEffectiveness == 0.5) {
                cout << "Ce n'est pas très efficace..." << endl;
            }
            else if (typeEffectiveness == 2) {
                cout << "C'est très efficace !" << endl;
            }
            return damage;
        // https://bulbapedia.bulbagarden.net/wiki/Damage
        // On considèrera qu'on a special attack et special defense (normalement on ne devrait avoir que special en gen 1)
        }

        void takeDamage(double damage) {
            (hp-damage < 0) ? hp = 0 : hp -= damage;
        }
};