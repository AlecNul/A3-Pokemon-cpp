#include <iostream>
#include <vector>
#include <string>

#include "Combat.h"

class Trainer {

// Attributes
    protected:
        string const name;
        string const gym;
        string const badge;

        vector<Pokemon> team;

// Constructors
public:
    Trainer(string n, string g, string b, vector<Pokemon> t) : name(n), gym(g), badge(b) {
            team = t;
        }

// Getters
    string const getName() {
        return name;
    }
    string const getGym() {
        return gym;
    }
    string const getBadge() {
        return badge;
    }

    vector<Pokemon> const getTeam() {
        return team;
    }

// Setters
    void setTeam(vector<Pokemon> t) {
        team = t;
    }

// Affichage
    virtual void display() {
        cout << "Nom : " << name << endl;
        cout << "Arène : " << gym << endl;
        cout << "Badge : " << badge << endl;
        cout << "Team : " << endl;
        for (int i = 0; i < team.size() - 1; i++) {
            cout << team[i].getName() << ", ";
        }
        cout << team[team.size() - 1].getName() << endl;
    }

    virtual void teamDisplay() {
        cout << "Equipe : " << endl;
        for (int i = 0; i < team.size(); i++) {
            cout << i + 1 << " : ";
            team[i].display();
        }
    }

// Methods
    void swapOrder(int indexPoke1, int indexPoke2) {
        swap(team[indexPoke1 - 1], team[indexPoke2 - 1]);
    }

    bool lose() {
        for (int i = 0; i < team.size(); i++) {
            if (team[i].getHp() > 0) {
                return false;
            }
        }
        return true;
    }

    bool isKO(Pokemon Poke) {
        return (Poke.getHp() == 0) ? 1 : 0;
    }

    array<int, 2> chooseMove(Pokemon* activePoke) {
        array<int, 2> res = {0, 0};
        string move;
        cout << name << "\'s turn : " << endl;
        cout << activePoke->getName() << " : " << activePoke->getHp() << " HP" << endl;
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
                    } else {
                        cout << "Try again...";
                    }
                }
                if (res[0] != 0) {
                    break;
                }
            } 

            else if (move == "2" || move == "team") {
                string choice;
                vector<int> available;
                while (true) {
                    cout << "Choose the Pokemon to switch with :" << endl;
                    for (int i = 0; i < team.size(); i++) {
                        if (team[i].getName() != activePoke->getName() && !isKO(team[i])) {
                            available.push_back(i);
                            cout << i + 1 << ". " << team[i].getName() << endl;
                        }
                    }
                    cout << "6. Back" << endl;
                    cout << "Enter your choice : ";
                    cin >> choice;
                    if (choice == "6") {
                        cout << "You closed your team!" << endl;
                        break;
                    }
                    if (find(available.begin(), available.end(), stoi(choice)-1) != available.end()) {
                        (team[stoi(choice) - 1].getName() == activePoke->getName()) ? res = {2, stoi(choice)} : res = {2, stoi(choice) - 1};
                        cout << "You switched Pokemon!" << endl;
                        break;
                    }
                    else { cout << "Try again..." << endl; }
                }
                if (res[0] != 0) {
                    break;
                }
            } 
            
            else if (move == "1" || move == "attack") {
                string choice;
                while (true) {
                    activePoke->displayMoveset();
                    cout << "5 : Back" << endl;
                    cout << "Enter your choice : ";
                    cin >> choice;
                    if (choice == "5") {
                        cout << "Going back..." << endl;
                        break;
                    }
                    if (choice >= "1" && choice <= "4") {
                        cout << "You used move " << activePoke->getMoveset()[stoi(choice) - 1].getName() << " !" << endl;
                        res = {1, stoi(choice)};
                        break;
                    }
                }
                if (res[0] != 0) {
                    break;
                }
            } 
            else {
                cout << "Try again...";
            }
        }
        cout << res[0] << " " << res[1] << endl;
        return res;
    }

    void Duel(Trainer& opponent) {
        Trainer winner = *this;
    
        Pokemon* activePoke1 = &team[0];
        Pokemon* activePoke2 = &opponent.getTeam()[0];
    
        while (!lose() && !opponent.lose()) {
            array<int, 2> playerMove = chooseMove(activePoke1);
            array<int, 2> opponentMove = opponent.chooseMove(activePoke2);
    
            // Run case
            if (playerMove[0] == 4) {
                winner = opponent;
                break;
            }
            if (opponentMove[0] == 4) {
                winner = *this;
                break;
            }
    
            // Priority calculation
            int priority = calculatePriority(playerMove, *activePoke1, opponentMove, *activePoke2);
    
            // When player comes first
            if (priority == 0) {
                // Player's move
                if (playerMove[0] == 1) { // Attack
                    activePoke1->attack(*activePoke2, playerMove[1] - 1);
                    if (opponent.isKO(*activePoke2)) {
                        string choice;
                        vector<int> available;
                        while (true) {
                            cout << activePoke2->getName() << " is K.O..." << endl;
                            cout << "Choose the Pokemon to switch with:" << endl;
                            for (int i = 0; i < opponent.getTeam().size(); i++) {
                                if (!opponent.isKO(opponent.getTeam()[i])) {
                                    available.push_back(i);
                                    cout << i + 1 << ". " << opponent.getTeam()[i].getName() << endl;
                                }
                            }
                            cout << "Enter your choice: ";
                            cin >> choice;
                            if (find(available.begin(), available.end(), stoi(choice) - 1) != available.end()) {
                                activePoke2 = &opponent.getTeam()[stoi(choice) - 1]; // Mise à jour du pointeur
                                cout << "Opponent switched to " << activePoke2->getName() << "!" << endl;
                                break;
                            } else {
                                cout << "Try again..." << endl;
                            }
                        }
                    }
                } else if (playerMove[0] == 2) { // Switch Pokémon
                    cout << "Come back " << activePoke1->getName() << "!" << endl;
                    activePoke1 = &team[playerMove[1] - 1]; // Mise à jour du pointeur
                    cout << "Go " << activePoke1->getName() << "!" << endl;
                }
    
                // Opponent's move
                if (opponentMove[0] == 1) { // Attack
                    activePoke2->attack(*activePoke1, opponentMove[1] - 1);
                    if (isKO(*activePoke1)) {
                        string choice;
                        vector<int> available;
                        while (true) {
                            cout << activePoke1->getName() << " is K.O..." << endl;
                            cout << "Choose the Pokemon to switch with:" << endl;
                            for (int i = 0; i < team.size(); i++) {
                                if (!isKO(team[i])) {
                                    available.push_back(i);
                                    cout << i + 1 << ". " << team[i].getName() << endl;
                                }
                            }
                            cout << "Enter your choice: ";
                            cin >> choice;
                            if (find(available.begin(), available.end(), stoi(choice) - 1) != available.end()) {
                                activePoke1 = &team[stoi(choice) - 1]; // Mise à jour du pointeur
                                cout << "You switched to " << activePoke1->getName() << "!" << endl;
                                break;
                            } else {
                                cout << "Try again..." << endl;
                            }
                        }
                    }
                }
            }
    
            // When opponent comes first
            else {
                // Opponent's move
                if (opponentMove[0] == 1) { // Attack
                    activePoke2->attack(*activePoke1, opponentMove[1] - 1);
                    if (isKO(*activePoke1)) {
                        string choice;
                        vector<int> available;
                        while (true) {
                            cout << activePoke1->getName() << " is K.O..." << endl;
                            cout << "Choose the Pokemon to switch with:" << endl;
                            for (int i = 0; i < team.size(); i++) {
                                if (!isKO(team[i])) {
                                    available.push_back(i);
                                    cout << i + 1 << ". " << team[i].getName() << endl;
                                }
                            }
                            cout << "Enter your choice: ";
                            cin >> choice;
                            if (find(available.begin(), available.end(), stoi(choice) - 1) != available.end()) {
                                activePoke1 = &team[stoi(choice) - 1]; // Mise à jour du pointeur
                                cout << "You switched to " << activePoke1->getName() << "!" << endl;
                                break;
                            } else {
                                cout << "Try again..." << endl;
                            }
                        }
                    }
                }
    
                // Player's move
                if (playerMove[0] == 1) { // Attack
                    activePoke1->attack(*activePoke2, playerMove[1] - 1);
                    if (opponent.isKO(*activePoke2)) {
                        string choice;
                        vector<int> available;
                        while (true) {
                            cout << activePoke2->getName() << " is K.O..." << endl;
                            cout << "Choose the Pokemon to switch with:" << endl;
                            for (int i = 0; i < opponent.getTeam().size(); i++) {
                                if (!opponent.isKO(opponent.getTeam()[i])) {
                                    available.push_back(i);
                                    cout << i + 1 << ". " << opponent.getTeam()[i].getName() << endl;
                                }
                            }
                            cout << "Enter your choice: ";
                            cin >> choice;
                            if (find(available.begin(), available.end(), stoi(choice) - 1) != available.end()) {
                                activePoke2 = &opponent.getTeam()[stoi(choice) - 1]; // Mise à jour du pointeur
                                cout << "Opponent switched to " << activePoke2->getName() << "!" << endl;
                                break;
                            } else {
                                cout << "Try again..." << endl;
                            }
                        }
                    }
                }
            }
        }
    
        if (lose()) {
            winner = opponent;
        }
        cout << winner.getName() << " won the duel!" << endl;
    }
};
