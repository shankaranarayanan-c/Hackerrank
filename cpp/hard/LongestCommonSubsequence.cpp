#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Spell {
 private:
  string scrollName;

 public:
  Spell() : scrollName("") {}
  Spell(string name) : scrollName(name) {}
  virtual ~Spell() {}
  string revealScrollName() { return scrollName; }
};

class Fireball : public Spell {
 private:
  int power;

 public:
  Fireball(int power) : power(power) {}
  void revealFirepower() { cout << "Fireball: " << power << endl; }
};

class Frostbite : public Spell {
 private:
  int power;

 public:
  Frostbite(int power) : power(power) {}
  void revealFrostpower() { cout << "Frostbite: " << power << endl; }
};

class Thunderstorm : public Spell {
 private:
  int power;

 public:
  Thunderstorm(int power) : power(power) {}
  void revealThunderpower() { cout << "Thunderstorm: " << power << endl; }
};

class Waterbolt : public Spell {
 private:
  int power;

 public:
  Waterbolt(int power) : power(power) {}
  void revealWaterpower() { cout << "Waterbolt: " << power << endl; }
};

class SpellJournal {
 public:
  static string journal;
  static string read() { return journal; }
};
string SpellJournal::journal = "";

void counterspell(Spell *spell) {
  if (dynamic_cast<Fireball *>(spell) != nullptr) {
    Fireball *fireball = dynamic_cast<Fireball *>(spell);
    fireball->revealFirepower();
  } else if (dynamic_cast<Frostbite *>(spell) != nullptr) {
    Frostbite *frostbite = dynamic_cast<Frostbite *>(spell);
    frostbite->revealFrostpower();
  } else if (dynamic_cast<Thunderstorm *>(spell) != nullptr) {
    Thunderstorm *thunderstorm = dynamic_cast<Thunderstorm *>(spell);
    thunderstorm->revealThunderpower();
  } else if (dynamic_cast<Waterbolt *>(spell) != nullptr) {
    Waterbolt *waterbolt = dynamic_cast<Waterbolt *>(spell);
    waterbolt->revealWaterpower();
  } else {
    const char *journal = SpellJournal::journal.c_str();
    int journallength = SpellJournal::journal.length();
    std::string scrollStr = spell->revealScrollName();
    const char *scroll = scrollStr.c_str();
    int scrollLength = spell->revealScrollName().length();

    std::vector<std::vector<int>> dp(scrollLength + 1,
                                     std::vector<int>(journallength + 1, 0));
    for (int i = 1; i < scrollLength + 1; i++) {
      for (int j = 1; j < journallength + 1; j++) {
        if (scroll[i - 1] == journal[j - 1]) {
          dp[i][j] = 1 + dp[i - 1][j - 1];
        } else {
          dp[i][j] = dp[i - 1][j] > dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1];
        }
      }
    }
    std::cout << dp[scrollLength][journallength] << std::endl;
  }
}

class Wizard {
 public:
  Spell *cast() {
    Spell *spell;
    string s;
    cin >> s;
    int power;
    cin >> power;
    if (s == "fire") {
      spell = new Fireball(power);
    } else if (s == "frost") {
      spell = new Frostbite(power);
    } else if (s == "water") {
      spell = new Waterbolt(power);
    } else if (s == "thunder") {
      spell = new Thunderstorm(power);
    } else {
      spell = new Spell(s);
      cin >> SpellJournal::journal;
    }
    return spell;
  }
};

int main() {
  int T;
  cin >> T;
  Wizard Arawn;
  while (T--) {
    Spell *spell = Arawn.cast();
    counterspell(spell);
  }
  return 0;
}