#ifndef CLASSES_H
#define CLASSES_H

#include "Utils.h"

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

/* Afin de réaliser un code enclin à de potentielles amélioration (ex. plusieurs attaques par pokémon) 
   j'ai choisi de réaliser une classe Attack */

class Attack {

    private:
        string name;
        int power;
        double accuracy;
        int type;
        string kind;
        string desc;
        int pp;
        int id;
    
    public:
        Attack(int i, string n, string d, string t, string k, int pow, double a, int p) {
            id = i;
            name = n;
            kind = k;
            power = pow;
            accuracy = a;
            type = encodeTypes[t];
            desc = d;
            pp = p;
        }

        string getKind() {
            return kind;
        }

        int getPower() {
            return power;
        }

        string getName() {
            return name;
        }

        int getType() {
            return type;
        }

        bool operator==(const Attack &a) {
            return name == a.name;
        }
    
        void display() {
            cout << "Attaque : " << name << endl;
            cout << "Description : " << desc << endl;
            cout << "PP : " << pp << endl;
            cout << "Puissance : " << power << endl;
            cout << "Précision : " << accuracy*100 << "%" << endl;
            cout << "Type : " << frTypesList[type] << endl << endl;
        }
};
    
    /* On pourrait penser à ajouter vector<int> stats (maxhp, , defense, speed, strength...) et int level qui seraient 
       deux attributs intéressants. Par exemple, si les stats augmentaient linéairement avec le niveau, on 
       pourrait se rapprocher d'un cas "réel" pour les maitres, en leur donnant simplement des pokémons avec
       un niveau plus élevé que ceux du joueur pour simuler le "+25%" */

    class Pokemon {
    
        protected:
            int pokedexID;
            string name;
            int types[2];
            vector<int> weakness;
            vector<int> resistance;
            int stats[6]; // maxhp, str, def, speed, spatk, spdef
        
            vector<Attack> moveset;
            double hp;
            int level; // On devrait faire double xp; aussi pour augmenter les lvls 
            
            int sprite; // Potentiellement pour le display ? pour l'instant un int
        
        public:

    // Constructors 
    
            Pokemon(int id, string n, vector<string> t, vector<Attack> mv, double h, int s[6], int l = 1) {
                pokedexID = id;
                name = n;
                types[0] = encodeTypes[t[0]];
                types[1] = (t.size() > 1) ? encodeTypes[t[1]] : -1;
        
                moveset = mv;
                hp = h;
                for (int i = 0; i < 6; i++) {
                    stats[i] = s[i];
                }
                level = l;
            }
    
    // Getters
    
            string getName() {
                return name;
            }
            double getHp() {
                return hp;
            }
            vector<int> getTypes() {
                return {types[0], types[1]};
            }

            vector<Attack> getMoveset() {
                return moveset;
            }

            int getLevel() {
                return level;
            }

            int getStrength() {
                return stats[1];
            }

            int getSpecialAttack() {
                return stats[4];
            }

            int getDefense() {
                return stats[2];
            }

            int getSpecialDefense() {
                return stats[5];
            }
    
    // Methods
        
            virtual void display() {
                cout << "Nom : " << name << endl;
                if (types[1] != -1) {
                    cout << "Type(s) : " << frTypesList[types[0]] << " " << frTypesList[types[1]] << endl;
                } else {
                    cout << "Type : " << frTypesList[types[0]] << endl;
                }
                cout << "PV : " << hp << endl;
                cout << "Attaques : " << endl;
                for (int i = 0; i < moveset.size(); i++) {
                    cout << moveset.size();
                    cout << i+1 << " : " << moveset[i].getName() << endl << endl;
                }

            }

            virtual void displayEVs() {
                cout << "Statistiques (EVs) : " << endl;
                cout << "PV max : " << stats[0] << endl;
                cout << "Attaque : " << stats[1] << endl;
                cout << "Défense : " << stats[2] << endl;
                cout << "Vitesse : " << stats[3] << endl;
                cout << "Attaque Spéciale : " << stats[4] << endl;
                cout << "Défense Spéciale : " << stats[5] << endl << endl;
            }

            virtual void displayMoveset() {
                for (int i = 0; i < moveset.size(); i++) {
                    cout << i+1 << " : " << moveset[i].getName() << endl;
                }
            }

            void addAttack(Attack a) {
                if (find(moveset.begin(), moveset.end(), a) == moveset.end()) {
                moveset.push_back(a);
                }
            }

            void attack(Pokemon &target, int index) {
                // double damage = moveset[index].getPower();
                double damage = stats[1]; // To do
                target.takeDamage(damage);
            }
    
            void takeDamage(double damage) {
                hp -= damage;
                if (hp < 0) {
                    hp = 0;
                }
            }
            
        };
    
        
    // Test utilisation héritage, sinon je ne vois pas vraiment comment s'en servir intelligemment
    
    class Starter : public Pokemon {
        void display() override {
            cout << "Un starter !" << endl;
            cout << "Nom : " << name << endl;
            cout << "Type(s) : " << types << endl;
            cout << "Statistiques : " << stats << endl;
            // Afficher le sprite ?
        }
    };


class Dresseur {

    protected:
        string name;
        string gym;
        string badge;
    public:
        vector<Pokemon> team;

        string getName() {
            return name;
        }
        
        Dresseur(string n, string g, string b, vector<Pokemon> t) {
            name = n;
            gym = g;
            badge = b;
            team = t;
        }

            virtual void display() {
                cout << "Nom : " << name << endl;
                cout << "Arène : " << gym << endl;
                cout << "Badge : " << badge << endl;
                cout << "Team : " << endl;
                for (int i = 0; i < team.size()-1; i++) {
                    cout << team[i].getName() << ", ";
                }
                cout << team[team.size()-1].getName() << endl;
            }
        
            virtual void teamDisplay() {
                cout << "Equipe : " << endl;
                for (int i = 0; i < team.size(); i++) {
                    cout << i+1 << " : ";
                    team[i].display();
                }
            }
        
            void swapOrder(int indexPoke1, int indexPoke2) {
                swap(team[indexPoke1-1], team[indexPoke2-1]);
            }

            bool lose() {
                for (int i = 0; i < team.size(); i++) {
                    if (team[i].getHp() > 0) {
                        return false;
                    }
                }
                return true;
            }

            // Fonctions statiques pour le chooseMove

            array<int, 2> chooseMove(Pokemon activePoke) {
                array<int, 2> res = {0, 0};
                string move;
                cout << name << "\'s turn : " << endl;
                while (true) {
                    cout << "1. Attack" << endl;
                    cout << "2. Team" << endl;
                    cout << "3. Inventory" << endl;
                    cout << "4. Run" << endl;
                    cout << "Enter your choice: ";
                    cin >> move;

                    if (move == "4" || move == "run") {
                        cout << "You run..." << endl;
                        res = {4, 0};
                        break;
                    }

                    else if (move == "3" || move == "inventory") {
                        string choice;
                        while (true) {
                            cout << "You opened your inventory!" << endl;
                            cout << "1. Potion" << endl;
                            cout << "2. Back" << endl;
                            cout << "Enter your choice : ";
                            cin >> choice;
                            if (choice == "2") {
                                cout << "You closed your inventory!" << endl;
                                break;
                            }
                            if (choice == "1") {
                                cout << "You used a potion!" << endl;
                                res = {3, 1};
                                break;
                            }
                            else {
                                cout << "Try again...";
                            }
                        }
                        if (res[0] != 0) { break; }
                    }

                    else if (move == "2" || move == "team") {
                        string choice;
                        while(true) {
                            cout << "Choose the Pokemon to switch with :" << endl;
                            for (int i = 0; i<team.size(); i++) {
                                if (team[i].getName() != activePoke.getName()) {
                                    cout << i+1 << ". " << team[i].getName() << endl;
                                }
                            }
                            cout << "6. Back" << endl;
                            cout << "Enter your choice : ";
                            cin >> choice;
                            if (choice == "6") {
                                cout << "You closed your team!" << endl;
                                break;
                            }
                            if (choice >= "1" && choice <= "5") {
                                (team[stoi(choice)-1].getName() == activePoke.getName()) ? res = {2, stoi(choice)} : res = {2, stoi(choice)-1};
                                cout << "You switched Pokemon!" << endl;
                                break;
                                }
                            }
                        if (res[0] != 0) { break; }
                    }

                    else if (move == "1" || move == "attack") {
                        string choice;
                        while (true) {
                            activePoke.displayMoveset();
                            cout << "5 : Back" << endl;
                            cout << "Enter your choice : ";
                            cin >> choice;
                            if (choice == "5") {
                                cout << "Going back..." << endl;
                                break;
                            }
                            if (choice >= "1" && choice <= "4") {
                                cout << "You used move " << activePoke.getMoveset()[stoi(choice)-1].getName() << " !" << endl;
                                res = {1, stoi(choice)};
                                break;
                            }
                        if (res[0] != 0) { break; }
                        }
                    }

                    else {
                        cout << "Try again...";
                    }
                }
            cout << res[0] << ", " << res[1];
            return res;
            }

            void Duel(Dresseur opponent) {
                Dresseur winner = *this;
                Pokemon activePoke1 = team[0];
                Pokemon activePoke2 = opponent.team[0];

                while (!lose() && !opponent.lose()) {
                    array<int,2> playerMove = chooseMove(activePoke1);
                    array<int,2> opponentMove = opponent.chooseMove(activePoke2);

                    // Run case
                    if (playerMove[0] == 4) {
                        winner = opponent;
                    }
                    if (opponentMove[0] == 4) {
                        winner = *this;
                    }

                    // Priority calculation
                    

                    // Inventory case
                    if (playerMove[0] == 3) {
                        if (playerMove[1] == 1) {
                            
                        }
                    }
                    if (opponentMove[0] == 3) {
                        if (opponentMove[1] == 1) {
                            
                        }
                    }

                }
                cout << winner.getName() << " won the duel !" << endl;
            }

};

        class Professeur : public Dresseur {
            // Bienvenue dans le monde merveilleux des Pokémons !
        };
     
        class Rival : public Dresseur {
            // Ah screugneugneu
        };

#endif // CLASSES_H