#include "knight2.h"

bool primeNumber(int n) {
	if (n < 2) {
		return false;
	}
	for (int i = 2; i <= n / 2; i++) {
		if (n % i == 0)
			return false;
	}
	return true;
}
//End primeNumber of Paladin

//Pythagoras
bool  Pythagoras(int n) {
	int a = 0, b = 0, c = 0;
	a = n / 100;
	b = (n / 10) % 10;
	c = n % 10;
	if (pow(a, 2) == pow(b, 2) + pow(c, 2)) {
		return true;
	}
	else if (pow(b, 2) == pow(a, 2) + pow(c, 2)) {
		return true;
	}
	else if (pow(c, 2) == pow(a, 2) + pow(b, 2)) {
		return true;
	}
	else return false;
}
//End Pythagoras of Dragon Knight
/* * * BEGIN implementation of class BaseBag * * */

/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseItem * * */

class Antidote :public BaseItem {
public:
	Antidote() :BaseItem() { this->type = AntidoteItem; }
	bool canUse(BaseKnight* Antidote) override {
		if (Antidote->getAntidote() > 0) {
			return true;
		}
		else return false;
	}
	void use(BaseKnight* antidote) override {
		if (canUse(antidote)) {
			antidote->setAntidote(antidote->getAntidote() - 1);
		}
		else;
	}

};
class PhoenixDownI :public BaseItem {
public:
	PhoenixDownI() :BaseItem() { this->type = PhoenixDownI_Item; }
	bool canUse(BaseKnight* PhoenixDownI)override {
		if (PhoenixDownI->getHP() <= 0) {
			return true;
		}
		return false;
	}
	void use(BaseKnight* PhoenixDownI)override {
		PhoenixDownI->setPhoenixDownI(PhoenixDownI->getPhoenixdownI() - 1);
		PhoenixDownI->setHP(PhoenixDownI->getMaxhp());
		PhoenixDownI->setPhoenixDownI(PhoenixDownI->getPhoenixdownI() - 1);
	}
};
class PhoenixDownII :public BaseItem {
public:
	PhoenixDownII() :BaseItem() { this->type = PhoenixDownII_Item; }
	bool canUse(BaseKnight* PhoenixDownII) override {
		if (PhoenixDownII->getHP() < PhoenixDownII->getMaxhp() / 4) {
			return true;
		}
		else return false;
	}
	void use(BaseKnight* PhoenixDownII) override {
		if (PhoenixDownII->getHP() < PhoenixDownII->getMaxhp() / 4) {
			PhoenixDownII->setHP(PhoenixDownII->getMaxhp());
			PhoenixDownII->setPhoenixDownII(PhoenixDownII->getPhoenixDownII() - 1);
		}
	}
};
class PhoenixDownIII :public BaseItem {
public:
	PhoenixDownIII() :BaseItem() { this->type = PhoenixDownIII_Item; }
	bool canUse(BaseKnight* PhoenixDownIII) override {
		if (PhoenixDownIII->getHP() < PhoenixDownIII->getMaxhp() / 3 || PhoenixDownIII->getHP() <= 0) {
			return true;
		}
		else return false;
	}
	void use(BaseKnight* PhoenixDownIII) override {
		if (PhoenixDownIII->getHP() < PhoenixDownIII->getMaxhp() / 3) {
			if (PhoenixDownIII->getHP() > 0) {
				PhoenixDownIII->setHP(PhoenixDownIII->getHP() + PhoenixDownIII->getMaxhp() / 4);
			}
			else
				PhoenixDownIII->setHP(PhoenixDownIII->getMaxhp() / 3);
			PhoenixDownIII->setPhoenixDownIII(PhoenixDownIII->getPhoenixDownIII() - 1);
		}
		else;

	}
};
class PhoenixDownIV :public BaseItem {
public:
	PhoenixDownIV() :BaseItem() { this->type = PhoenixDownIV_Item; }
	bool canUse(BaseKnight* PhoenixDownIV) override {
		if (PhoenixDownIV->getHP() < PhoenixDownIV->getMaxhp() / 2 || PhoenixDownIV->getHP() <= 0) {
			return true;
		}
		else return false;
	}
	void use(BaseKnight* PhoenixDownIV)  override {
		if (PhoenixDownIV->getHP() < PhoenixDownIV->getMaxhp() / 2) {
			if (PhoenixDownIV->getHP() > 0) {
				PhoenixDownIV->setHP(PhoenixDownIV->getHP() + PhoenixDownIV->getMaxhp() / 5);
			}
			else
				PhoenixDownIV->setHP(PhoenixDownIV->getMaxhp() / 2);
			PhoenixDownIV->setPhoenixDownIV(PhoenixDownIV->getPhoenixDownIV() - 1);
		}
		else;
	}
};
/* * * END implementation of class BaseItem * * */

/* * * BEGIN implementation of class BaseKnight * * */
KnightType BaseKnight::checkHP(int maxhp) {
	this->maxhp = maxhp;
	if (maxhp < 1000) {
		if (maxhp == 888) {
			this->knightType = LANCELOT;
		}
		else if (primeNumber(maxhp)) {
			this->knightType = PALADIN;
		}
		else if (Pythagoras(maxhp)) {
			this->knightType = DRAGON;
		}
		else this->knightType = NORMAL;
	}
	else {
		if (primeNumber(maxhp)) {
			this->knightType = PALADIN;
		}
		else this->knightType = NORMAL;
	}
	return this->knightType;
}
BaseKnight::BaseKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdown)
	: id(id), maxhp(maxhp), hp(maxhp), level(level), gil(gil), antidote(antidote), phoenixdownI(phoenixdown) {
	if (primeNumber(maxhp)) {
		knightType = KnightType::PALADIN;
		BaseDamageKnight = 0.06;
		bag = new PaladinBag(this);
	}
	else if (maxhp == 888) {
		knightType = KnightType::LANCELOT;
		BaseDamageKnight = 0.05;
		bag = new LancelotBag(this);
	}
	else if (maxhp >= 100 && maxhp <= 999 && Pythagoras(maxhp)) {
		knightType = KnightType::DRAGON;
		BaseDamageKnight = 0.075;
		bag = new DragonBag(this);
	}
	else {
		knightType = KnightType::NORMAL;
		BaseDamageKnight = 0;
		bag = new NormalBag(this);
	}
	for (int i = 0; i < phoenixdown; i++) {
		bag->insertFirst(new PhoenixDownI());
		bag->getList()->CountNodes();
	}
	for (int i = 0; i < antidote; i++) {
		bag->insertFirst(new Antidote());
		bag->getList()->CountNodes();
	}
}

void BaseKnight::setBag() {
	bag = new BaseBag(this);
}

BaseKnight::BaseKnight() {
	this->id = id;
	this->maxhp = maxhp;
	this->level = level;
	this->gil = gil;
	this->antidote = antidote;
	this->phoenixdownI = phoenixdownI;
}

string BaseKnight::toString() const {
	string typeString[4] = { "PALADIN", "LANCELOT", "DRAGON", "NORMAL" };
	// inefficient version, students can change these code
	//      but the format output must be the same
	string s("");
	s += "[Knight:id:" + to_string(id)
		+ ",hp:" + to_string(hp)
		+ ",maxhp:" + to_string(maxhp)
		+ ",level:" + to_string(level)
		+ ",gil:" + to_string(gil)
		+ "," + bag->toString()
		+ ",knight_type:" + typeString[knightType]
		+ "]";
	return s;
}

/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */
void ArmyKnights::printInfo() const {
	cout << "No. knights: " << this->count();
	if (this->count() > 0) {
		BaseKnight* lknight = lastKnight(); // last knight
		cout << ";" << lknight->toString();
	}
	cout << ";PaladinShield:" << this->hasPaladinShield()
		<< ";LancelotSpear:" << this->hasLancelotSpear()
		<< ";GuinevereHair:" << this->hasGuinevereHair()
		<< ";ExcaliburSword:" << this->hasExcaliburSword()
		<< endl
		<< string(50, '-') << endl;
}

void ArmyKnights::printResult(bool win) const {
	cout << (win ? "WIN" : "LOSE") << endl;
}
ArmyKnights::ArmyKnights(const string& file_armyknights) {
	string line;
	ifstream input_file_ArmyKnights(file_armyknights);
	input_file_ArmyKnights >> num_knight;
	knight = new BaseKnight[num_knight];
	for (id = 0; id < num_knight; id++) {
		input_file_ArmyKnights >> maxhp >> level >> phoenixdownI >> gil >> antidote;
		knight[id] = BaseKnight(id + 1, maxhp, level, gil, antidote, phoenixdownI);
	}
	input_file_ArmyKnights.close();
}
BaseKnight* ArmyKnights::lastKnight() const {
	if (num_knight == 0) {
		return NULL;
	}
	else
		return &knight[num_knight - 1];
}

bool ArmyKnights::adventure(Events* events) {
	for (int i = 0; i < events->count(); i++) {
		int levelO = (i + events->get(i)) % 10 + 1;
		int MaSuKien = events->get(i);
		BaseOpponent* opponent = new BaseOpponent(levelO, 0);
		if (MaSuKien == 1) {
			opponent = new MadBear(levelO);
			fight(opponent);
			printInfo();
		}
		else if (MaSuKien == 2) {
			opponent = new Bandit(levelO);
			fight(opponent);
			printInfo();
		}
		else if (MaSuKien == 3) {
			opponent = new LordLupin(levelO);
			fight(opponent);
			printInfo();
		}
		else if (MaSuKien == 4) {
			opponent = new Elf(levelO);
			fight(opponent);
			printInfo();
		}
		else if (MaSuKien == 5) {
			opponent = new Troll(levelO);
			fight(opponent);
			printInfo();
		}
		else if (MaSuKien == 6) {
			opponent = new Tornbery(levelO);
			fight(opponent);
			printInfo();
		}
		else if (MaSuKien == 7) {
			opponent = new QueenOfCards(levelO);
			fight(opponent);
			printInfo();
		}
		else if (MaSuKien == 8) {
			opponent = new NinaDeRings(levelO);
			fight(opponent);
			printInfo();
		}
		else if (MaSuKien == 9) {
			opponent = new DurianGarden(levelO);
			fight(opponent);
			printInfo();
		}
		else if (MaSuKien == 10) {
			if (this->DoMeetOmega) {
				printInfo();
				continue;
			}
			opponent = new OmegaWeapon(levelO);
			fight(opponent);
			printInfo();
		}
		else if (MaSuKien == 11) {
			if (this->DoMeetHaDes) {
				printInfo();
				continue;
			}
			opponent = new Hades(levelO);
			fight(opponent);
			printInfo();
		}
		else if (MaSuKien == 95) {//nhat PaladinShield
			if (this->PaladinShield == false) {
				this->PaladinShield = true;
			}
			printInfo();
		}
		else if (MaSuKien == 96) {//nhat LancelotSpear
			if (this->LancelotSpear == false) {
				this->LancelotSpear = true;
			}
			printInfo();
		}
		else if (MaSuKien == 97) {//nhat GuinevereHair
			if (this->GuinevereHair == false) {
				this->GuinevereHair = true;
			}
			printInfo();
		}
		else if (MaSuKien == 98) {
			if (this->hasGuinevereHair() && this->hasLancelotSpear() && this->hasPaladinShield()) {
				this->ExcaliburSword = true;
			}
			printInfo();
		}
		else if (MaSuKien == 112) {//nhat phoenix2
			for (int i = num_knight - 1; i >= 0; i--)
			{
				if (knight[i].OpenBag()->insertFirst(new PhoenixDownII)) {
					knight[i].OpenBag()->getList()->CountNodes();
					break;
				}
			}
			printInfo();
		}
		else if (MaSuKien == 113) {//nhat Phoenix3
			for (int i = num_knight - 1; i >= 0; i--)
			{
				if (knight[i].OpenBag()->insertFirst(new PhoenixDownIII)) {
					knight[i].OpenBag()->getList()->CountNodes();
					break;
				}
			}
			printInfo();
		}
		else if (MaSuKien == 114) {//nhat phoenix4
			for (int i = num_knight - 1; i >= 0; i--)
			{
				if (knight[i].OpenBag()->insertFirst(new PhoenixDownIV)) {
					knight[i].OpenBag()->getList()->CountNodes();
					break;
				}
			}
			printInfo();
		}
		else if (MaSuKien == 99) {
			this->DoMeetUltimecia = true;
			double hpUltimecia = 5000;
			if (this->hasExcaliburSword()) {
				printInfo();
				return true;
			}
			else if (this->hasGuinevereHair() && this->hasLancelotSpear() && this->hasPaladinShield()) {
				for (int i = num_knight - 1; i >= 0; i--)
				{
					hpUltimecia -= knight[i].getBaseDamage() * knight[i].getLevel() * knight[i].getHP();
					if (hpUltimecia <= 0) {
						printInfo();
						return true;
					}
					knight[i].setHP(0);
					num_knight--;
					printInfo();
					return false;
				}
			}
			else {
				num_knight = 0;
				printInfo();
				return false;
			}
			printInfo();
		}
		if (this->count() <= 0) {
			return false;
		}
	}
	return true;
}
bool ArmyKnights::fight(BaseOpponent* opponent) {
	for (int i = num_knight - 1; i >= 0; i--)
	{
		if (opponent->getType() == MadBearType) {
			if (knight[i].getLevel() >= opponent->getLevel() || knight[i].getKnight() == LANCELOT || knight[i].getKnight() == PALADIN)
			{
				// Knight wins
				this->HandleGil(i, 100);
				return true;
			}
			else
			{
				// Knight loses
				knight[i].setHP(knight[i].getHP() - ((opponent->getLevel() - knight[i].getLevel()) * 10));
				ItemType* vatpham = new ItemType[4];
				vatpham[0] = PhoenixDownI_Item;
				vatpham[1] = PhoenixDownII_Item;
				vatpham[2] = PhoenixDownIII_Item;
				vatpham[3] = PhoenixDownIV_Item;
				BaseItem* Sudung = knight[i].OpenBag()->getPhoenix(vatpham, 4, &knight[i]);
				if (Sudung == nullptr) {
					if (knight[i].getHP() <= 0) {
						callPhoenix(&knight[i]);
						if (knight[i].getHP() <= 0) {
							this->setCount(this->count() - 1);
							break;
						}
					}
				}
				else {
					Sudung->use(&knight[i]);
				}
			}
		}
		if (opponent->getType() == BanditType) {
			if (knight[i].getLevel() >= opponent->getLevel() || knight[i].getKnight() == LANCELOT || knight[i].getKnight() == PALADIN)
			{
				// Knight wins
				this->HandleGil(i, 150);
				return true;
			}
			else
			{
				// Knight loses
				knight[i].setHP(knight[i].getHP() - ((opponent->getLevel() - knight[i].getLevel()) * 15));
				ItemType* vatpham = new ItemType[4];
				vatpham[0] = PhoenixDownI_Item;
				vatpham[1] = PhoenixDownII_Item;
				vatpham[2] = PhoenixDownIII_Item;
				vatpham[3] = PhoenixDownIV_Item;
				BaseItem* Sudung = knight[i].OpenBag()->getPhoenix(vatpham, 4, &knight[i]);
				if (Sudung == nullptr) {
					if (knight[i].getHP() <= 0) {
						callPhoenix(&knight[i]);
						if (knight[i].getHP() <= 0) {
							this->setCount(this->count() - 1);
							break;
						}
					}
				}
				else {
					Sudung->use(&knight[i]);
				}
			}
		}
		if (opponent->getType() == LordLupinType) {
			if (knight[i].getLevel() >= opponent->getLevel() || knight[i].getKnight() == LANCELOT || knight[i].getKnight() == PALADIN)
			{
				// Knight wins
				this->HandleGil(i, 450);
				return true;
			}
			else
			{
				// Knight loses
				knight[i].setHP(knight[i].getHP() - ((opponent->getLevel() - knight[i].getLevel()) * 45));
				ItemType* vatpham = new ItemType[4];
				vatpham[0] = PhoenixDownI_Item;
				vatpham[1] = PhoenixDownII_Item;
				vatpham[2] = PhoenixDownIII_Item;
				vatpham[3] = PhoenixDownIV_Item;
				BaseItem* Sudung = knight[i].OpenBag()->getPhoenix(vatpham, 4, &knight[i]);
				if (Sudung == nullptr) {
					if (knight[i].getHP() <= 0) {
						callPhoenix(&knight[i]);
						if (knight[i].getHP() <= 0) {
							this->setCount(this->count() - 1);
							break;
						}
					}
				}
				else {
					Sudung->use(&knight[i]);
				}
			}
		}
		if (opponent->getType() == ElfType) {
			if (knight[i].getLevel() >= opponent->getLevel() || knight[i].getKnight() == LANCELOT || knight[i].getKnight() == PALADIN)
			{
				// Knight wins
				this->HandleGil(i, 750);
				return true;
			}
			else
			{
				// Knight loses
				knight[i].setHP(knight[i].getHP() - ((opponent->getLevel() - knight[i].getLevel()) * 75));
				ItemType* vatpham = new ItemType[4];
				vatpham[0] = PhoenixDownI_Item;
				vatpham[1] = PhoenixDownII_Item;
				vatpham[2] = PhoenixDownIII_Item;
				vatpham[3] = PhoenixDownIV_Item;
				BaseItem* Sudung = knight[i].OpenBag()->getPhoenix(vatpham, 4, &knight[i]);
				if (Sudung == nullptr) {
					if (knight[i].getHP() <= 0) {
						callPhoenix(&knight[i]);
						if (knight[i].getHP() <= 0) {
							this->setCount(this->count() - 1);
							break;
						}
					}
				}
				else {
					Sudung->use(&knight[i]);
				}
			}
		}
		if (opponent->getType() == TrollType) {
			if (knight[i].getLevel() >= opponent->getLevel() || knight[i].getKnight() == LANCELOT || knight[i].getKnight() == PALADIN)
			{
				// Knight wins
				this->HandleGil(i, 800);
				return true;
			}
			else
			{
				// Knight loses
				knight[i].setHP(knight[i].getHP() - ((opponent->getLevel() - knight[i].getLevel()) * 95));
				ItemType* vatpham = new ItemType[4];
				vatpham[0] = PhoenixDownI_Item;
				vatpham[1] = PhoenixDownII_Item;
				vatpham[2] = PhoenixDownIII_Item;
				vatpham[3] = PhoenixDownIV_Item;
				BaseItem* Sudung = knight[i].OpenBag()->getPhoenix(vatpham, 4, &knight[i]);
				if (Sudung == nullptr) {
					if (knight[i].getHP() <= 0) {
						callPhoenix(&knight[i]);
						if (knight[i].getHP() <= 0) {
							this->setCount(this->count() - 1);
							break;
						}
					}
				}
				else {
					Sudung->use(&knight[i]);
				}
			}
		}
		if (opponent->getType() == TornberyType) {
			if (knight[i].getLevel() >= opponent->getLevel() || knight[i].getKnight() == DRAGON)
			{
				// Knight wins
				knight[i].setLevel(knight[i].getLevel() + 1);
				return true;
			}
			else
			{
				Antidote* antidote = (Antidote*)(knight[i].OpenBag()->get(AntidoteItem));
				if (antidote != nullptr && antidote->canUse(knight)) {
					antidote->use(knight);
				}
				else {
					knight[i].ConnectToBag()->RemoveFirstThree((LinkedList*)knight[i].ConnectToBag()->getList());
					knight[i].setHP(knight[i].getHP() - 10);
					ItemType* vatpham = new ItemType[4];
					vatpham[0] = PhoenixDownI_Item;
					vatpham[1] = PhoenixDownII_Item;
					vatpham[2] = PhoenixDownIII_Item;
					vatpham[3] = PhoenixDownIV_Item;
					BaseItem* Sudung = knight[i].OpenBag()->getPhoenix(vatpham, 4, &knight[i]);
					if (Sudung == nullptr) {
						if (knight[i].getHP() <= 0) {
							callPhoenix(&knight[i]);
							if (knight[i].getHP() <= 0) {
								this->setCount(this->count() - 1);
								break;
							}
						}
					}
					else {
						Sudung->use(&knight[i]);
					}
				}
			}
		}
		if (opponent->getType() == QueenOfCardsType) {
			if (knight[i].getLevel() >= opponent->getLevel() || knight[i].getKnight() == LANCELOT)
			{
				// Knight wins
				this->HandleGil(i, knight[i].getGil());
			}
			else if (knight[i].getKnight() == PALADIN) {
				break;
			}
			else
			{
				// Knight loses
				knight[i].setGil(knight[i].getGil() / 2);
			}
		}
		if (opponent->getType() == NinaDeRingsType) {
			if (knight[i].getGil() < 50) {
			}
			else {
				if (knight[i].getHP() < knight[i].getMaxhp() / 3) {
					knight[i].setGil(knight[i].getGil() - 50);
					knight[i].setHP(knight[i].getHP() + knight[i].getMaxhp() / 5);
				}
			}
		}
		if (opponent->getType() == DurianGardenType) {
			knight[i].setHP(knight[i].getMaxhp());
		}
		if (opponent->getType() == OmegaWeaponType) {
			if (knight[i].getLevel() == 10 && knight[i].getHP() == knight[i].getMaxhp() || knight[i].getKnight() == DRAGON) {
				knight[i].setLevel(10);
				knight[i].setGil(999);
				this->DoMeetOmega = true;
			}
			else {
				knight[i].setHP(0);
				ItemType* vatpham = new ItemType[4];
				vatpham[0] = PhoenixDownI_Item;
				vatpham[1] = PhoenixDownII_Item;
				vatpham[2] = PhoenixDownIII_Item;
				vatpham[3] = PhoenixDownIV_Item;
				BaseItem* Sudung = knight[i].OpenBag()->getPhoenix(vatpham, 4, &knight[i]);
				if (Sudung == nullptr) {
					if (knight[i].getHP() <= 0) {
						callPhoenix(&knight[i]);
						if (knight[i].getHP() <= 0) {
							this->setCount(this->count() - 1);
							break;
						}
					}
				}
				else {
					Sudung->use(&knight[i]);
				}
			}
		}
		if (opponent->getType() == HadesType) {
			if (knight[i].getLevel() == 10 || knight[i].getKnight() == PALADIN && knight[i].getLevel() >= 8) {
				if (this->PaladinShield == false) {
					this->PaladinShield = true;
				}
				this->DoMeetHaDes = true;
			}
			else {
				knight[i].setHP(0);
				ItemType* vatpham = new ItemType[4];
				vatpham[0] = PhoenixDownI_Item;
				vatpham[1] = PhoenixDownII_Item;
				vatpham[2] = PhoenixDownIII_Item;
				vatpham[3] = PhoenixDownIV_Item;
				BaseItem* Sudung = knight[i].OpenBag()->getPhoenix(vatpham, 4, &knight[i]);
				if (Sudung == nullptr) {
					if (knight[i].getHP() <= 0) {
						callPhoenix(&knight[i]);
						if (knight[i].getHP() <= 0) {
							this->setCount(this->count() - 1);
							break;
						}
					}
				}
				else {
					Sudung->use(&knight[i]);
				}
			}
			return true;
		}
		return false;
	}
}
/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() {
	armyKnights = nullptr;
	events = nullptr;
}
void KnightAdventure::loadArmyKnights(const string& file_armyknights) {
	armyKnights = new ArmyKnights(file_armyknights);
}
void KnightAdventure::loadEvents(const string& file_events) {
	events = new Events(file_events);
}
/* * * END implementation of class KnightAdventure * * */
Events::Events(const string& file_events) {
	ifstream file_input_events(file_events);
	file_input_events >> numEvents;
	events = new int[numEvents];
	for (int i = 0; i < numEvents; i++) {
		file_input_events >> events[i];
	}
	file_input_events.close();
}

Events::Events() {
	numEvents = 0;
	events = nullptr;
}
Events::~Events() {
	numEvents = 0;
	delete[] events;
}