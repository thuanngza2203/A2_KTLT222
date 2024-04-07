#include "knight2.h"

/* * * BEGIN implementation of class BaseBag * * */

BaseBag::BaseBag(BaseKnight *knight, int phoenixI, int antidote)
{
    this->size = 0;
    this->head = NULL;
    this->tail = NULL;
    this->knight = knight;
    // xac dinh typeknight de biet limit bag
    if (knight->getType() == DRAGON)
    {
        antidote = 0;
        this->limit = 14;
    }
    else if (knight->getType() == LANCELOT)
        this->limit = 16;
    else if (knight->getType() == PALADIN)
        this->limit = 10000;
    //gioi han phoenix
    if (phoenixI > 0)
    {
        if (phoenixI > 5)
            phoenixI = 5;
        for (int i = 0; i < phoenixI; i++)
        {
            BaseItem *item = new BaseItem(PHOENIXI);
            this->insertFirst(item);
        }
    }
    // gioi han antidote
    if (antidote > 0)
    {
        if (antidote > 5)
            antidote = 5;
        for (int i = 0; i < antidote; i++)
        {
            BaseItem *item = new BaseItem(ANTIDOTE);
            this->insertFirst(item);
        }
    }
}
// dieu kien bo vat pham vao tui
bool BaseBag::insertFirst(BaseItem *item)
{
    if (this->size >= this->limit)
        return false;
    if (this->knight->getType() == DRAGON)
    {
        if (item->itemType == ANTIDOTE)
            return false;
    }
    //them vao dau linked list
    if (this->size == 0)
    {
        this->head = item;
        this->tail = item;
    }
    else
    {
        item->next = this->head;
        this->head = item;
    }
    this->size++;
    return true;
}
// đổi chỗ vật phẩm
void BaseBag::swap(BaseItem *item)
{
    BaseItem *tmp = new BaseItem();
    tmp->itemType = item->itemType;
    tmp->next = this->head->next;//dua item ra đầu dslk
    item->itemType = this->head->itemType;//itemType head được đưa đến item
    this->head = tmp;//địa chỉ của head được chuyển thành tmp
}
// xóa vật phẩm
void BaseBag::popItem()
{
    if (this->head != NULL)
    {
        BaseItem *tmp = this->head;
        this->head = this->head->next;
        this->size--;
        free(tmp);
    }
}
bool BaseBag::check_can_use_phoenix(BaseItem *item)
{
    if (item == NULL)
        return false;
    switch (item->itemType)
    {
    case PHOENIXII:
        if (this->knight->getHp() <= (int)(this->knight->getMaxHp() / 4))
        {
            this->use(item);
            return true;
        }
        break;
    case PHOENIXIII:
        if (this->knight->getHp() <= (int)(this->knight->getMaxHp() / 3))
        {
            this->use(item);
            return true;
        }
        break;
    case PHOENIXIV:
        if (this->knight->getHp() <= (int)(this->knight->getMaxHp() / 2))
        {
            this->use(item);
            return true;
        }
        break;
    default:
        break;
    }
    return check_can_use_phoenix(item->next);
};

bool BaseBag::use(ItemType itemType)
{
    BaseItem *item = this->get(itemType);
    if (item == NULL)
        return false;
    this->swap(item);
    this->popItem();
    return true;
}

bool BaseBag::use(BaseItem *item)
{
    if (item == NULL)
        return false;
    switch (item->itemType)
    {
    case PHOENIXI:
        this->knight->setHp(this->knight->getMaxHp());
        break;
    case PHOENIXII:
        this->knight->setHp(this->knight->getMaxHp());
        break;
    case PHOENIXIII:
        if (this->knight->getHp() <= 0)
            this->knight->setHp((int)(this->knight->getMaxHp() / 3));
        else
            this->knight->setHp(this->knight->getHp() + (int)(this->knight->getMaxHp() / 4));
        break;
    case PHOENIXIV:
        if (this->knight->getHp() <= 0)
            this->knight->setHp((int)(this->knight->getMaxHp() / 2));
        else
            this->knight->setHp(this->knight->getHp() + (int)(this->knight->getMaxHp() / 5));
        break;
    default:
        break;
    }
    this->swap(item);
    this->popItem();
    return true;
}
// lấy vật phẩm ra
BaseItem *BaseBag::get(ItemType itemType)
{
    if (this->head == NULL)
        return NULL;
    BaseItem *tmp = this->head;
    while (tmp != NULL)
    {
        if (tmp->itemType == itemType)
            return tmp;
            else {
                 tmp = tmp->next;
                 }  
    }
    return NULL;
}
int BaseBag::count()
{
    return this->size;
}
// display túi đồ
string BaseBag::toString()
{
    int size = this->count();
    string listItem="";
    string s="";
    string typeString[5] = {"Antidote", "PhoenixI", "PhoenixII", "PhoenixIII", "PhoenixIV"};
    if (size > 0)
    {
        BaseItem *tmp = this->head;
        for (int i = 0; i < size; i++)
        {
            listItem += typeString[tmp->itemType];
            if (i < size - 1)
                listItem += ",";
            tmp = tmp->next;
        }
        free(tmp);
    }

    s += "Bag[count=" + to_string(size) + ";" + listItem + "]";
    return s;
}
/* * * END implementation of class BaseBag * * */
BaseOpponent::BaseOpponent(int i, int id)
{
    switch (id)
    {
    case 1:
        this->baseDamge = 10;
        this->gil = 100;
        break;
    case 2:
        this->baseDamge = 15;
        this->gil = 150;
        break;
    case 3:
        this->baseDamge = 45;
        this->gil = 450;
        break;
    case 4:
        this->baseDamge = 75;
        this->gil = 750;
        break;
    case 5:
        this->baseDamge = 95;
        this->gil = 800;
        break;
    default:
        break;
    }
    this->levelO = (i + id) % 10 + 1;
};
int BaseOpponent::attack(int knight_lvl)
{
    return this->baseDamge * (this->levelO - knight_lvl);
}
/* * * BEGIN implementation of class BaseKnight * * */
bool isprime(int n)
{
    if (n <= 1)
        return false;
    for (int i = 2; i*i <= n; i++)
        if (n % i == 0)
            return false;

    return true;
}
//thông tin đầu vào của 1 hiệp sĩ
BaseKnight::BaseKnight(int id, int maxhp, int level, int phoenixdownI, int gil, int antidote)
{
    this->id = id;
    this->hp = maxhp;
    this->maxhp = maxhp;
    this->level = level;
    this->gil = gil;
    this->phoenixdownI = phoenixdownI;
    this->antidote = antidote;
    if (isprime(maxhp))
    {
        this->knightType = PALADIN;
    }
    else if (maxhp == 888)
    {
        this->knightType = LANCELOT;
    }
    else if (maxhp == 345 || maxhp == 354 || maxhp == 435 || maxhp == 453 || maxhp == 534 || maxhp == 543)
    {
        this->knightType = DRAGON;
        this->antidote = 0;
    }
    else
        this->knightType = NORMAL;
        this->bag = new BaseBag(this, phoenixdownI, antidote);
        this->next = NULL;
}
//copy knight qua 1 đối tượng mới
BaseKnight::BaseKnight(BaseKnight *knight)
{
    this->id = knight->id;
    this->hp = knight->maxhp;
    this->maxhp = knight->maxhp;
    this->level = knight->level;
    this->gil = knight->gil;
    this->phoenixdownI = knight->phoenixdownI;
    this->antidote = knight->antidote;
    this->knightType = knight->knightType;
    this->bag = new BaseBag(this, this->phoenixdownI, this->antidote);
    this->next = knight->next;
}
//xuất thông tin hiệp sĩ
string BaseKnight::toString() const
{
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id) + ",hp:" + to_string(hp) + ",maxhp:" + to_string(maxhp) + ",level:" + to_string(level) + ",gil:" + to_string(gil) + "," + bag->toString() + ",knight_type:" + typeString[knightType] + "]";
    return s;
}

/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */
//hàm tách chuỗi số
void split(string &s, int *arr)
{
    int num, index = 0;
    stringstream ss(s);
    while (ss >> num)
    {
        arr[index] = num;
        index++;
    };
}
// đọc file theo dòng
string toString(string path, int line)
{
    int i = 0;
    string tmps, c;
    ifstream file;
    file.open(path);
    while (i < line)
    {
        getline(file, tmps);
        i++;
    }
    getline(file, tmps);
    file.close();
    return tmps;
}
//đọc 
int toInt(string path, int line)
{
    int num = 0, i = 0;
    string tmps, line_1;
    ifstream file;
    file.open(path);
    while (i < line)
    {
        getline(file, tmps);
        i++;
    }
    getline(file, line_1);
    stringstream ss(line_1);
    ss >> num;
    file.close();
    return num;
}
ArmyKnights::ArmyKnights(const string &file_path)
{
    this->numKnights = 0;
    this->paladinShield = false;
    this->lancelotSpear = false;
    this->guinevereHair = false;
    this->excaliburSword = false;
    this->meetOmegaWeapon = false;
    this->meetHades = false;
    this->UltimaciaHP = 5000;
    this->head = NULL;
    this->tail = NULL;
    int numArmies = toInt(file_path, 0);
    string tmps;
    ifstream file;
    file.open(file_path);
    int status[6];
    string c = "";
    int ele = 0, index = 0;
    for (int i = 0; i <= numArmies; i++)
    {
        getline(file, tmps);
        if (i >= 1)
        {
            split(tmps, status);
            BaseKnight *tmp = new BaseKnight(i, status[0], status[1], status[2], status[3], status[4]);
            this->add(tmp);
        }
    }
    file.close();
}
// xóa knight ở id
bool ArmyKnights::remove(int id)
{
    if (this->head == NULL)
        return false;
    if (this->head->next == NULL && this->head->getId() == id)
    {
        this->head = NULL;
        this->tail = NULL;
        this->numKnights--;
        return true;
    }
    if (this->head->getId() == id)
    {
        BaseKnight *tmp = this->head;
        this->head = this->head->next;
        this->numKnights--;
        free(tmp);
        return true;
    }
    if (this->tail->getId() == id)
    {
        this->popKnight();
        return true;
    }
    //xóa knight giữa LL
    BaseKnight *current = this->get(id);
    if (current == NULL)
        return false;
    BaseKnight *next = current->next;
    BaseKnight *prev = this->head;
    while (prev->next->getId() != id)
        prev = prev->next;
    prev->next = next;
    this->numKnights--;
    free(current);
    return true;
}
//get knight theo id
BaseKnight *ArmyKnights::get(int id) const
{
    if (this->head == NULL || id <= 0)
        return NULL;
    BaseKnight *tmp = this->head;
    while (tmp != NULL)
    {
        if (tmp->getId() == id)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
};
//xóa toàn quân
bool ArmyKnights::clear()
{
    while (this->head != NULL)
    {
        this->popKnight();
    }
    printInfo();
    return false;
};
void ArmyKnights::add(BaseKnight *newBaseKnight)
{
    if (this->numKnights == 0)
    {
        this->head = newBaseKnight;
        this->tail = newBaseKnight;
    }
    else
    {
        //them hiep si vao cuoi LL
        this->tail->next = newBaseKnight;
        this->tail = newBaseKnight;
    }
    this->numKnights++;
}
BaseKnight *ArmyKnights::lastKnight() const
{
    if (this->tail != NULL)
        return this->tail;
    else
        return NULL;
}

bool BaseKnight::isDead()
{
    this->hp = 0;
//check    
    if (this->bag->head != NULL)
    {
        BaseItem *item = this->bag->head;
        while (item != NULL)
        {
            if (item->itemType >= 1 && item->itemType <= 4)
                break;
            item = item->next;
        }
        if (item->itemType >= 1 && item->itemType <= 4)
        {
            this->bag->use(item);
            if (this->hp == 0)
                return true;
            return false;
        }
    }
    if (this->gil >= 100)
    {
        this->hp = (int)(this->maxhp / 2);
        this->gil -= 100;
        if (this->hp == 0)
            return true;
        return false;
    }
    return true;
}

bool ArmyKnights::fight(BaseOpponent *opponent)
{
    if (this->lastKnight() == NULL)
        return false;
    BaseKnight *node = this->lastKnight();
    int damge = opponent->attack(node->getLevel());
    if (node->getLevel() < opponent->levelO && (node->getType() == NORMAL||node->getType() == DRAGON))
    {
        if (node->getHp() <= damge)
        {
            if (node->isDead())
            {
                this->popKnight();
                return true;
            }
        }
        else
            node->setHp(node->getHp() - damge);
    }
    else
    {
        int id = node->getId();
        this->addGil(id, opponent->gil);
    }
    delete opponent;
    return true;
}

bool ArmyKnights::oTornbery(BaseOpponent *opponent)
{
    BaseKnight *node = lastKnight();
    if (node == NULL)
        return false;
    if (node->getLevel() < opponent->levelO)
    {
        if (node->getType() != DRAGON)
        {
            int isUseAntidote = false;
            if (node->getBag()->head != NULL)
            {
                BaseItem *item = node->getBag()->head;
                while (item->next != NULL)
                {
                    if (item->itemType == ANTIDOTE)
                        break;
                    item = item->next;
                }
                if (item->itemType == ANTIDOTE)
                {
                    node->getBag()->use(item);
                    isUseAntidote = true;
                }
            }
            if (!isUseAntidote)
            {
                node->getBag()->popItem();
                node->getBag()->popItem();
                node->getBag()->popItem();
                if (node->getHp() <= 10)
                {
                    if (node->isDead())
                    {
                        this->popKnight();
                        return true;
                    }
                }
                else
                    node->setHp(node->getHp() - 10);
            }
        }
    }
    else
        node->setLevel(node->getLevel() + 1);
    delete opponent;
    return true;
}

bool ArmyKnights::oOmegaWeapon()
{

    if (this->lastKnight() == NULL)
        return false;
    BaseKnight *knight = this->lastKnight();
    if ((knight->getLevel() == 10 && knight->getHp() == knight->getMaxHp()) || knight->getType() == DRAGON)
    {
        knight->setLevel(10);
        knight->setgil(999);
        this->meetOmegaWeapon = true;
        return true;
    }
    else
    {
        knight->setHp(0);
        if (knight->isDead())
        {
            this->popKnight();
            return true;
        }
    }
    return true;
}

bool ArmyKnights::oHades()
{

    if (this->lastKnight() == NULL)
        return false;
    BaseKnight *knight = this->lastKnight();
    if (knight->getLevel() == 10 || (knight->getType() == PALADIN && knight->getLevel() >= 8))
    {
        this->meetHades = true;
        this->paladinShield = true;
        return true;
    }
    else
    {
        knight->setHp(0);
        if (knight->isDead())
        {
            this->popKnight();
            return true;
        }
    }
    return true;
}

bool ArmyKnights::Ultimecia(int id)
{
    if (this->get(id) == NULL)
        return false;
    BaseKnight *knight = this->get(id);
    if (knight->getType() == NORMAL)
    {
        return Ultimecia(id - 1);
    }
    else
    {
        //if(knight->getType() == LANCELOT)
        double baseDamge = 0.05;
        if (knight->getType() == PALADIN)
           baseDamge = 0.06;
        else if (knight->getType() == DRAGON)
           baseDamge = 0.075;
        int damge = (int)(knight->getHp() * knight->getLevel() * baseDamge);
        this->UltimaciaHP -= damge;
        if (this->UltimaciaHP > 0)
        {
            this->remove(id);
            return Ultimecia(id - 1);
        }
        else
        {
            return true;
        }
    }
    return true;
}

bool ArmyKnights::QofCards(BaseOpponent *o)
{
    BaseKnight *node = lastKnight();
    if (node == NULL)
        return false;
    if (node->getLevel() < o->levelO)
    {
        if (node->getType() != PALADIN)
        {
            node->setgil((int)(node->getGil() / 2));
        }
    }
    else
    {
        int gil = node->getGil();
        //maybe have bug
        if ( gil + gil > 999)
        {
            node->setgil(999);
            this->addGil(node->getId() - 1, node->getGil() + gil - 999);
        }
        else
            node->setgil(gil + gil);
    }
    delete o;
    return true;
}

bool ArmyKnights::NinadeRings()
{
    if (this->lastKnight() == NULL)
        return false;
    BaseKnight *node = this->lastKnight();
    if (node->getGil() >= 50)
    {
        if (node->getHp() < (int)(node->getMaxHp() / 3))
        {
            node->setgil(node->getGil() - 50);
            node->setHp(node->getHp() + (int)(node->getMaxHp() / 5));
        }
        if (node->getGil() >= 50 && node->getHp() < (int)(node->getMaxHp() / 3))
            return this->NinadeRings();
        else
            return true;
    }
    return false;
}

bool ArmyKnights::addGil(int id, int gil)
{
    if (id == 0)
        return false;
    BaseKnight *knight = this->get(id);
    if (knight->getGil() + gil > 999)
    {
        knight->setgil(999);
        int remainGil = knight->getGil() + gil - 999;
        return this->addGil(knight->getId() - 1, remainGil);
    }
    else
        knight->setgil(knight->getGil() + gil);
    return true;
}

int ArmyKnights::count() const
{
    return this->numKnights;
}

bool ArmyKnights::pickItem(int id, BaseItem *item)
{
    if (id == 0)
        return false;
    if (this->get(id) == NULL)
        return false;

    bool insert = this->get(id)->getBag()->insertFirst(item);
    if (!insert)
    {
        return this->pickItem(id - 1, item);
    }
    return true;
}
//xóa hiệp sĩ cuối team
void ArmyKnights::popKnight()
{
    int size = this->numKnights;
    if (size == 1)
    {
        this->head = NULL;
        this->tail = NULL;
        this->numKnights--;
    }
    else if (size != 0)
    {
        BaseKnight *tmp = this->head;
        while (tmp->next->next != NULL)
              { tmp = tmp->next;}
        BaseKnight *lastNode = tmp->next;
        tmp->next = NULL;
        this->tail = tmp;
        free(lastNode);
        this->numKnights--;
    }
}
void ArmyKnights::printInfo() const
{
    cout << "No. knights: " << this->count();
    if (this->count() > 0)
    {
        BaseKnight *lknight = lastKnight();
        if (lknight != NULL)
            cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
         << ";LancelotSpear:" << this->hasLancelotSpear()
         << ";GuinevereHair:" << this->hasGuinevereHair()
         << ";ExcaliburSword:" << this->hasExcaliburSword()
         << endl
         << string(50, '-') << endl;
}

void ArmyKnights::printResult(bool win) const
{
    cout << (win ? "WIN" : "LOSE") << endl;
}

/* * * END implementation of class ArmyKnights * * */
/* * * BEGIN implementation of class KnightAdventure * * */

KnightAdventure::KnightAdventure()
{
    armyKnights = NULL;
    events = NULL;
}

void KnightAdventure::loadArmyKnights(const string &file_path)
{
    this->armyKnights = new ArmyKnights(file_path);
}

void KnightAdventure::loadEvents(const string &file_path)
{
    int size = toInt(file_path, 0);
    string s = toString(file_path, 1);
    int event[size + 1];
    split(s, event);
    this->events = new Events(size, event);
}

bool ArmyKnights::adventure(Events *events)
{
    int i = 0, event_id = 0;
    int size = events->count();
    bool iswon = true;
    bool canuse = true;
    while (i < size)
    {
        canuse = true;
        event_id = events->get(i);
        if (event_id >= 1 && event_id <= 5)
        {
            BaseOpponent *oponent = new BaseOpponent(i, event_id);
            iswon = this->fight(oponent);
        }
        else if (event_id == 6)
        {
            BaseOpponent *oponent = new BaseOpponent(i, event_id);
            iswon = this->oTornbery(oponent);
        }
        else if (event_id == 7)
        {
            BaseOpponent *oponent = new BaseOpponent(i, event_id);
            iswon = this->QofCards(oponent);
        }
        else if (event_id == 8)
        {
            this->NinadeRings();
        }
        else if (event_id == 9)
        {
            BaseKnight *knight = this->lastKnight();
            knight->setHp(knight->getMaxHp());
        }
        else if (event_id == 10)
        {
            if (this->meetOmegaWeapon == false)
                iswon = this->oOmegaWeapon();
        }
        else if (event_id == 11)
        {
            if (this->meetHades == false)
                iswon = this->oHades();
        }
        else if (event_id == 112)
        {
            canuse = false;
            BaseItem *item = new BaseItem(PHOENIXII);
            this->pickItem(this->lastKnight()->getId(), item);
        }
        else if (event_id == 113)
        {
            canuse = false;
            BaseItem *item = new BaseItem(PHOENIXIII);
            this->pickItem(this->lastKnight()->getId(), item);
        }
        else if (event_id == 114)
        {
            canuse = false;
            BaseItem *item = new BaseItem(PHOENIXIV);
            this->pickItem(this->lastKnight()->getId(), item);
        }
        else if (event_id == 95)
        {
            this->paladinShield = true;
            canuse = false;
        }
        else if (event_id == 96)
        {
            this->lancelotSpear = true;
            canuse = false;
        }
        else if (event_id == 97)
        {
            this->guinevereHair = true;
            canuse = false;
        }
        else if (event_id == 98)
        {
            if (this->paladinShield && this->lancelotSpear && this->guinevereHair)
                this->excaliburSword = true;
                canuse = false;
        }
        else if (event_id == 99)
        {
            if (this->excaliburSword)
            {
                canuse = false;
                this->printInfo();
                break;
            }
            else if (this->paladinShield == true && this->lancelotSpear == true && this->guinevereHair == true)
            {
                iswon = Ultimecia(this->lastKnight()->getId());
                if (iswon == false)
                {
                    this->clear();
                    break;
                }
            }
            else
            {
                this->clear();
                iswon = false;
                break;
            }
        }
        // print info and check use potion
        if (this->lastKnight() == NULL)
            iswon = false;
        else
        {
            if (canuse == true)
            {
                BaseKnight *node = this->lastKnight();
                if (node->getBag()->head != NULL)
                {
                    BaseItem *item = node->getBag()->head;
                    node->getBag()->check_can_use_phoenix(item);
                }
            }
        }
        this->printInfo();
        if (iswon == false)
            break;
        i++;
    }
    return iswon;
}
void KnightAdventure::run()
{
    this->armyKnights->printResult(this->armyKnights->adventure(this->events));
}
/* * * END implementation of class KnightAdventure * * */