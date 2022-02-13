#include "thing.h"
//do NOT include anything else, write your code below

Thing::Thing(ThingType type) : type(type) {};
bool Thing::isWeapon() const 
{
    if (type==MACE || type==DAGGER || type==SWORD)
        return true;
    
    return false;
}
bool Thing::isMonster() const
{
    if (type==VAMPIRE || type==SKELETON || type==DRAGON)
        return true;

    return false;
}
ThingType Thing::getType() const
{
    return this->type;
}
void Thing::setType(ThingType type)
{
    this->type = type;
}
char Thing:: getSymbol() const
{
    ThingType t =getType();
    /*if (t == MACE)
        return 'm';
    if (t==DAGGER)
        return 'd';
    if (t==SWORD)
        return 's';
    if (t==SKELETON)
        return 'K';
    if (t==VAMPIRE)
        return 'V';
    if (t==DRAGON)
        return 'D';*/
    switch (t)
    {
        case MACE:
            return 'm'; break;
        case DAGGER:
            return 'd'; break;
        case SWORD:
            return 's'; break;
        case SKELETON:
            return 'K'; break;
        case VAMPIRE:
            return 'V'; break;
        case DRAGON:
            return 'D'; break;
        default:
            return 'm';
            break;
    }
}






