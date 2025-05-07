#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

enum ItemType { AntidoteItem, PhoenixDownI_Item, PhoenixDownII_Item, PhoenixDownIII_Item, PhoenixDownIV_Item };
enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
enum OpponentType { MadBearType, BanditType, LordLupinType, ElfType, TrollType, TornberyType, QueenOfCardsType, NinaDeRingsType, DurianGardenType, OmegaWeaponType, HadesType ,BOSS};
class BaseBag;

class Events {
protected:
	int numEvents = 0;
	int* events;
public:
	Events();
	~Events();
	Events(const string& file_events);
	int count() const {
		return this->numEvents;
	}
	void setcout(int count) {
		this->numEvents = count;
	}
	int get(int i) const {
		if (i >= numEvents || i < 0) {
			return -1;
		}
		return events[i];
	};
};
class BaseKnight {
protected:
	int id =0;
	int hp ;
	int maxhp ;
	int level ;
	int gil ;
	int antidote;
	int phoenixdownI;
	int PhoenixDownII;
	int PhoenixDownIII;
	int PhoenixDownIV;
	double BaseDamageKnight;
	BaseBag* bag;
	KnightType knightType;
public:
	static BaseKnight* create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI) {
		BaseKnight* knight = new BaseKnight;
		knight->id = id;
		knight->maxhp = maxhp;
		knight->level = level;
		knight->gil = gil;
		knight->antidote = antidote;
		knight->phoenixdownI = phoenixdownI;
		return knight;
	}
	BaseKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
	BaseKnight();
	KnightType checkHP(int maxhp);
	double getBaseDamage() const { return this->BaseDamageKnight; }
	int getHP() const { return this->hp; };
	int getid()const { return this->id; };
	int getMaxhp()const { return this->maxhp; }
	int getLevel() const { return this->level; }
	int getGil() const { return this->gil; }
	int getAntidote() const { return this->antidote; }
	int getPhoenixdownI()const { return this->phoenixdownI; }
	int getKnight()const { return this->knightType; }
	int getPhoenixDownII()const { return this->PhoenixDownII; }
	int getPhoenixDownIII() const { return this->PhoenixDownIII; }
	int getPhoenixDownIV() const { return this->PhoenixDownIV; }
	string toString() const;
	BaseBag* OpenBag() {
		return this->bag;
	}
	BaseBag* ConnectToBag() {
		return this->bag;
	}
	void setBag();
	void setHP(int hp) {
		if (hp < 0) {
			this->hp = 0;
		}
		else if (hp < this->maxhp) {
			this->hp = hp;
		}
		else {
			this->hp = this->maxhp;
		}
	}
	void setMaxHP(int maxhp) {
		this->maxhp = maxhp;
	}
	void setLevel(int lvl)
	{
		if (lvl < 1)
		{
			this->level = 1;
		}
		else if (lvl > 10)
		{
			this->level = 10;
		}
		else
		{
			this->level = lvl;
		}
	}
	void setAntidote(int anti) {
		this->antidote = anti;
	}
	void setGil(int money)
	{
		this->gil = money;
	}
	void setPhoenixDownI(int pd)
	{
		this->phoenixdownI = pd;
	}
	void setId(int id) {
		this->id = id;
	}
	void setKnight(KnightType type) {
		this->knightType = type;
	}
	void setPhoenixDownII(int PhoenixDownII) {
		this->PhoenixDownII = PhoenixDownII;
	}
	void setPhoenixDownIII(int PhoenixDownIII) {
		this->PhoenixDownIII = PhoenixDownIII;
	}
	void setPhoenixDownIV(int PhoenixDownIV) {
		this->PhoenixDownIV = PhoenixDownIV;
	}
};
class BaseItem {
protected:
	ItemType type;
public:
	BaseItem() {}
	virtual bool canUse(BaseKnight* knight) = 0;
	virtual void use(BaseKnight* knight) = 0;
	void setItemType(ItemType type) {
		this->type = type;
	}
	ItemType getItemType() {
		return this->type;
	}
};

class Node
{
public:
	BaseItem* item;
	Node* next;
	Node(BaseItem* init_data)
	{
		this->item = init_data;
		this->next = nullptr;
	}
};

class LinkedList
{
public:
	Node* head;
	Node* tail;
	LinkedList()
	{
		this->head = nullptr;
		this->tail = nullptr;
	}
	void AddHead(Node* node)
	{
		if (this->head == nullptr)
		{
			this->head = node;
			this->tail = node;
		}
		else
		{
			node->next = this->head;
			this->head = node;
		}
	}
	int CountNodes()
	{
		int count = 0;
		Node* current = this->head;
		while (current != nullptr)
		{
			count++;
			current = current->next;
		}
		return count;
	}
};

class BaseBag {
protected:
	int capacity;
	LinkedList* list;
public:
	BaseBag(BaseKnight* knight) {
		capacity = maxBag(knight);
		list = new LinkedList();
	}
	int maxBag(BaseKnight* knight) {
		if (knight->getKnight() == LANCELOT) {
			return 16;
		}
		else if (knight->getKnight() == NORMAL) {
			return 19;
		}
		else if (knight->getKnight() == DRAGON) {
			return 14;
		}
		else return 10000;
	}
	LinkedList* getList() {
		return this->list;
	}
	virtual bool insertFirst(BaseItem* item) {
		list->AddHead(new Node(item));
		item->setItemType(item->getItemType());
		return true;
	}
	virtual BaseItem* get(ItemType itemType) {
		Node* current = list->head;
		BaseItem* result = nullptr;
		if (current == nullptr) {
			return result;
		}
		if (current != nullptr && current->item->getItemType() == itemType)
		{
			list->head = list->head->next;
			result = current->item;
			delete current;
			return result;
		}
		while (current->next != nullptr)
		{
			if (current->next->item->getItemType() == itemType)
			{
				BaseItem* temp = current->next->item;//temp la cai can lay
				current->next->item = list->head->item;//cho toi data
				list->head->item = temp;//current item len dau

				Node* luuTruHead = list->head;//tao bien cho list.head
				list->head = list->head->next;//chuyen con tro head
				delete luuTruHead;
				return temp;
			}
			else
			{
				current = current->next;
			}
		}
		current = current->next;
		delete current;
		return result;
	}
	virtual string toString() const {
		string list_items = "";
		Node* current = list->head;
		while (current != nullptr) {
			string item_name = "";
			if (current->item->getItemType() == AntidoteItem) {
				item_name = "Antidote";
			}
			else if (current->item->getItemType() == PhoenixDownI_Item) {
				item_name = "PhoenixI";
			}
			else if (current->item->getItemType() == PhoenixDownII_Item) {
				item_name = "PhoenixII";
			}
			else if (current->item->getItemType() == PhoenixDownIII_Item) {
				item_name = "PhoenixIII";
			}
			else if (current->item->getItemType() == PhoenixDownIV_Item) {
				item_name = "PhoenixIV";
			}
			list_items += item_name + ",";
			current = current->next;
		}
		if (!list_items.empty()) {
			list_items.pop_back();
		}
		return "Bag[count=" + to_string(list->CountNodes()) + ";" + list_items + "]";
	}

	int RemoveHead(LinkedList* l, void*& x)
	{
		if (l->head != nullptr)
		{
			Node* node = l->head;
			x = node->item;      
			l->head = node->next;
			delete node;         
			if (l->head == nullptr)
				l->tail = nullptr;
			return 1;
		}
		return 0;
	}
	void RemoveFirstThree(LinkedList* l)
	{
		void* x;
		int count = 0;
		while (count < 3 && RemoveHead(l, x))
		{
			count++;
			if (x != nullptr) {
				x = nullptr;
			}
		}
		// Xử lý trường hợp danh sách rỗng
		if (l->head == nullptr) {
			l->tail = nullptr;
		}
	}
	BaseItem* getPhoenix(ItemType itemType[], int num,BaseKnight* knight) {
		Node* current = list->head;
		BaseItem* result = nullptr;
		if (list->head == nullptr) {
			return result;
		}
		if (list->head != nullptr)
		{
			for (int i = 0; i < num; i++)// check head is item ?
			{
				if (list->head->item->getItemType() == itemType[i]) {
					if (knight->getHP() <= 0) {
					list->head = list->head->next;
					result = current->item;
					delete current;
					return result;
					}
					else if (i == 1 && knight->getHP() < knight->getMaxhp() / 4) {
						list->head = list->head->next;
						result = current->item;
						delete current;
						return result;
					}
					else if (i == 2 && knight->getHP() < knight->getMaxhp() / 3) {
						list->head = list->head->next;
						result = current->item;
						delete current;
						return result;
					}
					else if (i == 3 && knight->getHP() < knight->getMaxhp() / 2) {
						list->head = list->head->next;
						result = current->item;
						delete current;
						return result;
					}
				}
			}
		}
		while (current->next != nullptr)//check except head
		{
			for (int i = 0; i < num; i++)
			{
				if (current->next->item->getItemType() == itemType[i])
				{
					if (knight->getHP() <= 0) {
						BaseItem* temp = current->next->item;//temp la cai can lay
						current->next->item = list->head->item;//cho toi data
						list->head->item = temp;//current item len dau

						Node* luuTruHead = list->head;//tao bien cho list.head
						list->head = list->head->next;//chuyen con tro head
						delete luuTruHead;
						return temp;
					}
					else if (i == 1 && knight->getHP() < knight->getMaxhp() / 4) {
						BaseItem* temp = current->next->item;//temp la cai can lay
						current->next->item = list->head->item;//cho toi data
						list->head->item = temp;//current item len dau

						Node* luuTruHead = list->head;//tao bien cho list.head
						list->head = list->head->next;//chuyen con tro head
						delete luuTruHead;
						return temp;
					}
					else if (i == 2 && knight->getHP() < knight->getMaxhp() / 3) {
						BaseItem* temp = current->next->item;//temp la cai can lay
						current->next->item = list->head->item;//cho toi data
						list->head->item = temp;//current item len dau

						Node* luuTruHead = list->head;//tao bien cho list.head
						list->head = list->head->next;//chuyen con tro head
						delete luuTruHead;
						return temp;
					}
					else if (i == 3 && knight->getHP() < knight->getMaxhp() / 2) {
						BaseItem* temp = current->next->item;//temp la cai can lay
						current->next->item = list->head->item;//cho toi data
						list->head->item = temp;//current item len dau

						Node* luuTruHead = list->head;//tao bien cho list.head
						list->head = list->head->next;//chuyen con tro head
						delete luuTruHead;
						return temp;
					}
				}
			}
			current = current->next;
		}
		current = current->next;
		delete current;
		return result;
	}

};
class DragonBag : public BaseBag {
public:
	DragonBag(BaseKnight* knight) :BaseBag(knight) {}
	bool insertFirst(BaseItem* item) {
		if (item->getItemType() == AntidoteItem) {
			return true;
		}
		int cap = list->CountNodes();
		if (capacity < cap) {
			list->AddHead(new Node(item));
			return true;
		}
		return false;
	}
};
class LancelotBag : public BaseBag {
public:
	LancelotBag(BaseKnight* knight) :BaseBag(knight) {}
	bool insertFirst(BaseItem* item) {
		int cap = list->CountNodes();
		if (capacity < cap) {
			list->AddHead(new Node(item));
			return true;
		}
		return false;
	}
};
class PaladinBag : public BaseBag {
public:
	PaladinBag(BaseKnight* knight) :BaseBag(knight) {}
	bool insertFirst(BaseItem* item) {
		int cap = list->CountNodes();
		if (capacity > cap) {
			list->AddHead(new Node(item));
			return true;
		}
		return false;
	}
};
class NormalBag : public BaseBag {
public:
	NormalBag(BaseKnight* knight) :BaseBag(knight) {}
	bool insertFirst(BaseItem* item)  {
		int cap = list->CountNodes();
		if (cap < capacity) {
			list->AddHead(new Node(item));
			return true;
		}
		return false;
	}
};

class BaseOpponent {
protected:
	int gil_receiveed;
	int Basedamage = 0;
	int levelO;
	Events events;
	OpponentType type;
public:
	BaseOpponent(int _level, int _base_damage) : levelO(_level), Basedamage(_base_damage) {}
	~BaseOpponent() {}
	void setGil(int gil) {
		this->gil_receiveed = gil;
	}
	int getLevel() {
		return this->levelO;
	}
	int getGil() {
		return this->gil_receiveed;
	}
	OpponentType getType() {
		return this->type;
	}
};
class MadBear : public BaseOpponent {
protected:
public:
	MadBear(int _level) : BaseOpponent(_level, 10) {
		this->type = MadBearType;
	}
	~MadBear();
};

class Bandit :public BaseOpponent {
public:
	Bandit(int _level) : BaseOpponent(_level, 15) {
		this->type = BanditType;
	}
};
class LordLupin :public BaseOpponent {
public:
	LordLupin(int _level) : BaseOpponent(_level, 45) {
		this->type = LordLupinType;
	}
};
class Elf :public BaseOpponent {
public:
	Elf(int _level) : BaseOpponent(_level, 75) {
		this->type = ElfType;
	}
};
class Troll :public BaseOpponent {
public:
	Troll(int _level) : BaseOpponent(_level, 95) {
		this->type = TrollType;
	}
};
class Tornbery :public BaseOpponent {
public:
	Tornbery(int _level) :BaseOpponent(_level, 0) {
		this->type = TornberyType;
	}
};
class QueenOfCards :public BaseOpponent {
public:
	QueenOfCards(int _level) :BaseOpponent(_level, 0) {
		this->type = QueenOfCardsType;
	}
};
class NinaDeRings :public BaseOpponent {
public:
	NinaDeRings(int _level) :BaseOpponent(_level, 0) {
		this->type = NinaDeRingsType;
	}
};
class DurianGarden :public BaseOpponent {
public:
	DurianGarden(int _level) :BaseOpponent(_level, 0) {
		this->type = DurianGardenType;
	}
};
class OmegaWeapon :public BaseOpponent {
public:
	OmegaWeapon(int _level) :BaseOpponent(_level, 0) {
		this->type = OmegaWeaponType;
	}
};
class Hades :public BaseOpponent {
public:
	Hades(int _level) :BaseOpponent(_level, 0) {
		this->type = HadesType;
	}
};


class ArmyKnights {
protected:
	int id, hp, maxhp, level, gil, antidote, phoenixdownI, num_knight;
	bool PaladinShield = false;
	bool LancelotSpear = false, GuinevereHair = false, ExcaliburSword = false;
	bool DoMeetOmega = false; bool DoMeetHaDes = false; bool DoMeetUltimecia = false;
	BaseKnight* knight;
public:
	ArmyKnights(const string& file_armyknights);
	~ArmyKnights();
	bool fight(BaseOpponent* opponent);
	bool adventure(Events* events);
	void setCount(int count) {
		this->num_knight = count;
	}
	int count() const {
		return this->num_knight;
	}
	BaseKnight* lastKnight() const;

	bool hasPaladinShield() const {
		return this->PaladinShield;
	}
	bool hasLancelotSpear() const {
		return this->LancelotSpear;
	}
	bool hasGuinevereHair() const {
		return this->GuinevereHair;
	}
	bool hasExcaliburSword() const {
		return this->ExcaliburSword;
	}
	void callPhoenix(BaseKnight* knight) {
		if (knight->getGil() >= 100) {
			knight->setHP(knight->getMaxhp() / 2);
			knight->setGil(knight->getGil() - 100);
		}
	}
	void printInfo() const;
	void printResult(bool win) const;
	void HandleGil(int index, int GilBonus) {
		for (int i = index ; i >= 0; i--)
		{
			int money = knight[i].getGil() + GilBonus;
			if (money > 999) {
				GilBonus = knight[i].getGil() + GilBonus - 999;
				knight[i].setGil(999);
			}
			else {
				knight[i].setGil(money);
				break;
			}
		}
	}
};

class KnightAdventure {
private:
	ArmyKnights* armyKnights;
	Events* events;
public:
	KnightAdventure();
	~KnightAdventure() {}
	void loadArmyKnights(const string& file_armyknights);
	void loadEvents(const string& file_events);
	void run() {
		bool check = false;
		check = armyKnights->adventure(events);
		armyKnights->printResult(check);
	}
};
#endif // __KNIGHT2_H__