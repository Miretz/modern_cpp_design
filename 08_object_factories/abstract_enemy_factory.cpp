#include <iostream>

// By today's standards this is not "modern" code. I just wanted it to be close
// to the code in the book.

// And remember some old ways of doing things.

// Soldiers

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

// Abstract Factory

class AbstractEnemyFactory {
public:
  virtual Soldier *MakeSoldier() = 0;
  virtual Monster *MakeMonster() = 0;
  virtual SuperMonster *MakeSuperMonster() = 0;
  virtual ~AbstractEnemyFactory() = default;
};

// Concrete Factories

class EasyLevelEnemyFactory : public AbstractEnemyFactory {
public:
  Soldier *MakeSoldier() override { return new SillySoldier; }
  Monster *MakeMonster() override { return new SillyMonster; }
  SuperMonster *MakeSuperMonster() override { return new SillySuperMonster; }
};

class DieHardLevelEnemyFactory : public AbstractEnemyFactory {
public:
  Soldier *MakeSoldier() override { return new BadSoldier; }
  Monster *MakeMonster() override { return new BadMonster; }
  SuperMonster *MakeSuperMonster() override { return new BadSuperMonster; }
};

enum class Difficulty { Easy, DieHard };

// Factory user

#define MAX_MONSTERS 300

class GameApp {
public:
  GameApp() : pFactory_(nullptr), monster_count_(0) {
    monsters_ = new Monster *[MAX_MONSTERS];
  }
  void SelectLevel(Difficulty difficulty, int monster_count) {
    if (pFactory_) {
      delete pFactory_;
    }
    if (difficulty == Difficulty::Easy) {
      pFactory_ = new EasyLevelEnemyFactory;
    } else {
      pFactory_ = new DieHardLevelEnemyFactory;
    }
    monster_count_ = monster_count;
  }
  void SpawnMonsters() {
    for (size_t i = 0; i < monster_count_; ++i) {
      if (monsters_[i]) {
        delete monsters_[i];
      }
      monsters_[i] = pFactory_->MakeMonster();
    }
  }
  void AlertMonsters() {
    for (size_t i = 0; i < monster_count_; ++i) {
      monsters_[i]->Growl();
    }
  }
  ~GameApp() {
    if (pFactory_) {
      delete pFactory_;
    }
    pFactory_ = nullptr;
    for (size_t i = 0; i < MAX_MONSTERS; ++i) {
      delete monsters_[i];
    }
    delete[] monsters_;
    monsters_ = nullptr;
  }

private:
  AbstractEnemyFactory *pFactory_;
  size_t monster_count_;
  Monster **monsters_;

  // old way of removing assignment operator and copy constructor
  GameApp &operator=(const GameApp &);
  GameApp(const GameApp &);
};

auto main() -> int {
  GameApp game;
  game.SelectLevel(Difficulty::Easy, 10);
  game.SpawnMonsters();
  game.AlertMonsters();
  return 0;
}
