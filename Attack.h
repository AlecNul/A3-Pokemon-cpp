#include <iostream>
#include <vector>
#include <string>

#include "Utils.h"

class Attack {

// Attributes
    private:
        int const id;
        string const name;
        string const desc;

        int power;
        double accuracy;
        int type;
        string kind;
        int pp;


// Constructors
    public:
        Attack(int i, string n, string d, string t, string k, int pow, double a, int p) : id(i), name(n), desc(d) {
            power = pow;
            accuracy = a;
            type = encodeTypes[t];
            kind = k;
            pp = p;
        }

// Getters
        int getId() const {
            return id;
        }
        string getName() const { 
            return name;
        }
        string getDesc() const {
            return desc;
        }
        string getKind() const {
            return kind;
        }
        int getPower() const {
            return power;
        }
        int getType() const {
            return type;
        }

        bool operator==(const Attack& a) {
            return id == a.getId();
        }
        bool operator!=(const Attack& a) {
            return id != a.getId();
        }
// Affichage
        void display() const {
            cout << "Attaque : " << name << endl;
            cout << "Description : " << desc << endl;
            cout << "PP : " << pp << endl;
            cout << "Puissance : " << power << endl;
            cout << "Précision : " << accuracy*100 << "%" << endl;
            cout << "Type : " << frTypesList[type] << endl << endl;
        }
};