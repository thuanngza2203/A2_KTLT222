#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

enum ItemType
{
    ANTIDOTE = 0,
    PHOENIXI,
    PHOENIXII,
    PHOENIXIII,
    PHOENIXIV,
    NONE
};

class BaseKnight;
class BaseItem
{
public:
    ItemType itemType;
    BaseItem *next;
    BaseItem(ItemType itemType)
    {
        this->itemType = itemType;
        this->next = NULL;
    };
    BaseItem()
    {
        itemType = NONE;
        next = NULL;
    };
     //virtual bool canUse(BaseKnight *knight) = 0;
     //virtual void use(BaseKnight *knight);
};  
/*class itemfake: BaseItem {
    bool canUse(BaseKnight *knight){};
    use(BaseKnight *knight){};
};*/
class BaseBag
{
public:
    int size;
    int limit = 19;
    BaseKnight *knight = NULL;
    BaseItem *head = NULL;
    BaseItem *tail = NULL;

public:
    BaseBag(BaseKnight *knight, int phoenixI, int antidote);
    bool insertFirst(BaseItem *item);
    int count();
    void swap(BaseItem *item);
    void popItem();
    bool check_can_use_phoenix(BaseItem *item);
    bool use(ItemType itemType);
    bool use(BaseItem *item);
    virtual BaseItem *get(ItemType itemType);
    virtual string toString();
};

class BaseOpponent
{
public:
    int i;
    int id;
    int gil;
    int baseDamge;
    int levelO;

public:
    BaseOpponent(int i, int id);
    int attack(int knight_lvl);
};
enum KnightType
{
    PALADIN = 0,
    LANCELOT,
    DRAGON,
    NORMAL
};
class BaseKnight
{
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int phoenixdownI;
    int antidote;
    BaseBag *bag = NULL;
    KnightType knightType = NORMAL;

public:
    BaseKnight *next = NULL;

public:
    BaseKnight(int id, int maxhp, int level, int phoenixdownI, int gil, int antidote);
    BaseKnight(BaseKnight *knight);
    static BaseKnight *create(int id, int maxhp, int level, int phoenixdownI, int gil, int antidote);
    void setHp(int hp)
    {
        if (hp > this->maxhp)
            hp = this->maxhp;
        else if (hp < 0)
            hp = 0;
        this->hp = hp;
    };
    void setgil(int gil)
    {
        if (gil > 999)
            gil = 999;
        else if (gil < 0)
            gil = 0;
        this->gil = gil;
    };
    void setLevel(int level)
    {
        if (level > 10)
            level = 10;
        else if (level < 0)
            level = 0;
        this->level = level;
    }
    int getHp() { return this->hp; };
    int getId() { return this->id; };
    int getLevel() { return this->level; };
    int getMaxHp() { return this->maxhp; };
    int getGil() { return this->gil; };
    int getType() { return this->knightType; };
    bool isDead();
    BaseBag *getBag() { return this->bag; };
    string toString() const;
};

class Events
{
public:
    int size = 0;
    int *arr = new int[100];

public:
    Events(int size, int *arr)
    {
        this->size = size;
        this->arr = new int[size + 1];
        for (int i = 0; i < size; i++)
        {
            this->arr[i] = arr[i];
        }
        this->arr[size] = '\0';
    };
    int count() const
    {
        return this->size;
    };
    int get(int i) const
    {
        return (int)this->arr[i];
    };
};

class ArmyKnights
{
public:
    int numKnights = 0;
    bool paladinShield;
    bool lancelotSpear;
    bool guinevereHair;
    bool excaliburSword;
    bool meetOmegaWeapon;
    bool meetHades;
    int UltimaciaHP;
    BaseKnight *head;
    BaseKnight *tail;

public:
    ArmyKnights(const string &file_armyknights);
    void add(BaseKnight *node);
    bool fight(BaseOpponent *o);
    bool oTornbery(BaseOpponent *o);
    bool QofCards(BaseOpponent *o);
    bool NinadeRings();
    bool oOmegaWeapon();
    bool oHades();
    bool Ultimecia(int id);
    bool addGil(int id, int gil);
    bool pickItem(int id, BaseItem *item);
    bool adventure(Events *events);
    int count() const;
    BaseKnight *lastKnight() const;
    BaseKnight *get(int id) const;
    void popKnight();
    bool remove(int id);
    bool clear();
    bool hasPaladinShield() const { return this->paladinShield; };
    bool hasLancelotSpear() const { return this->lancelotSpear; };
    bool hasGuinevereHair() const { return this->guinevereHair; };
    bool hasExcaliburSword() const { return this->excaliburSword; };

    void printInfo() const;
    void printResult(bool win) const;
};

class KnightAdventure
{
private:
    ArmyKnights *armyKnights;
    Events *events;

public:
    KnightAdventure();
    ~KnightAdventure()
    {
        delete armyKnights;
        delete events;
    };
    void loadArmyKnights(const string &);
    void loadEvents(const string &);
    void run();
};

#endif // __KNIGHT2_H__