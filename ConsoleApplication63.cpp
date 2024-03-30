#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

class Weapon {
public:
    virtual void shoot() = 0;
    virtual void reload() = 0;
    virtual void drop() = 0;
    virtual void pickUp() = 0;
};

class Character {
private:
    vector<Weapon*> weapons;
public:
    void pickUpWeapon(Weapon* weapon) {
        if (weapons.size() < 3) {
            weapons.push_back(weapon);
            cout << "Weapon picked up!" << endl;
        }
        else {
            cout << "Cannot pick up more than 3 weapons!" << endl;
        }
    }

    void dropWeapon(int index) {
        if (index >= 1 && index <= weapons.size()) {
            delete[]weapons[index];
            weapons.erase(weapons.begin() + index);
            cout << "Weapon dropped!" << endl;
        }
        else {
            cout << "Invalid weapon index!" << endl;
        }
    }

    void shoot(int index) {
        if (index >= 0 && index < weapons.size()) {
            weapons[index]->shoot();
        }
        else {
            cout << "Invalid weapon index!" << endl;
        }
    }
};

class Shotgun : public Weapon {
public:
    void shoot() override {
        cout << "Shotgun shoots!" << endl;
    }

    void reload() override {
        cout << "Reloading shotgun..." << endl;
        this_thread::sleep_for(chrono::seconds(3));
        cout << "Shotgun reloaded!" << endl;
    }

    void drop() override {
        cout << "Shotgun dropped!" << endl;
    }

    void pickUp() override {
        cout << "Shotgun picked up!" << endl;
    }
};


int main()
{
    Character player;
    Weapon* AWP = new Shotgun();
    player.pickUpWeapon(AWP);
    player.shoot(0);

    dynamic_cast<Shotgun*>(AWP)->reload();

    player.dropWeapon(0);
    delete[]AWP;
}