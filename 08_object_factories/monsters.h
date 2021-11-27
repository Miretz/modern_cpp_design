#ifndef monsters_h
#define monsters_h

#include <iostream>

class Soldier {
public:
  virtual void Shout() = 0;
  virtual ~Soldier() {}
};

class SillySoldier : public Soldier {
public:
  void Shout() override { std::cout << "Don't shoot!\n"; }
};

class BadSoldier : public Soldier {
public:
  void Shout() override { std::cout << "Bring it on!\n"; }
};

// Monsters

class Monster {
public:
  virtual void Growl() = 0;
  virtual ~Monster() {}
};

class SillyMonster : public Monster {
public:
  void Growl() override { std::cout << "Rawr!\n"; }
};

class BadMonster : public Monster {
public:
  void Growl() override { std::cout << "grrrrrrr!\n"; }
};

// Super Monsters

class SuperMonster {
public:
  virtual void Snarl() = 0;
  virtual ~SuperMonster() {}
};

class SillySuperMonster : public SuperMonster {
  void Snarl() override { std::cout << "hhhrrraaaeeeerrrr!!!\n"; }
};

class BadSuperMonster : public SuperMonster {
  void Snarl() override { std::cout << "LET ME TALK TO THE MANAGER!\n"; }
};

#endif