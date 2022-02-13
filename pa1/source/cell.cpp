#include "cell.h"
#include <iostream>
using namespace std;
//do NOT include anything else, write your code below

Cell::Cell()
{
    thingCount = 0;
    things = nullptr;
}

Cell::~Cell()
{
    delete [] things;
}

bool Cell::addThing(ThingType type, int quantity)
{
    if (quantity<=0) return false;
    else
    {
        //Thing newthing(type);
        if (things==nullptr)
        {
            Thing* new_things = new Thing[quantity];
            for (int i=0; i<quantity; i++)
            {
                new_things[i].setType(type);
            }
            delete [] things;
            things=new_things;
            new_things = nullptr;
            thingCount+=quantity;
            return true;
        }
        int now_count = thingCount + quantity;
        Thing* new_things = new Thing[now_count];
        for (int i=0; i<thingCount; i++)
        {
            new_things[i].setType(things[i].getType());
        }
        for (int i=thingCount; i<now_count; i++)
        {
            new_things[i].setType(type);
        }
        delete [] things;
        things = new_things;
        new_things = nullptr;
        thingCount += quantity;
        return true;
    }
    
}

bool Cell::removeThing(ThingType type, int quantity)
{
    if (quantity<=0) return false;
    int typecount=getThingCount(type);
    if (quantity>typecount) return false;
    
    int now_count = thingCount - quantity;
    if (quantity == thingCount)
    {
        delete [] things;
        things=nullptr;
        thingCount=0;
        return true;
    }
    //Thing newthing(type);
    Thing* new_things = new Thing[now_count];
    /*int j=0;
    for (int i=0; i<thingCount; i++)
    {
        if (things[i].getType() != type && j<now_count)
        {  
            new_things[j].setType(things[i].getType());
            j++;
        }
    }*/
    int j=0;
    for (int i=0; i<thingCount; i++)
    {
        if (j<quantity && things[i].getType()==type)
            j++;
        else
        {
            new_things[i-j]=things[i];
        }
        
    }
    delete [] things;
    things=new_things;
    new_things = nullptr;
    thingCount = now_count;
    return true;

}

/*bool Cell::removeAnythingFromTheFront(int quantity)
{
    if (quantity<=0) return false;
    if (quantity>thingCount) return false;
    if (quantity==thingCount)
    {
        delete [] things;
        things=nullptr;
        thingCount=0;
        return true;
    }
    int new_count = thingCount-quantity;
    Thing* new_things = new Thing[new_count];
    for (int i=0; i<new_count; i++)
    {
        //new_things[i]=things[i+count-quantity];
        new_things[i].setType(things[i+new_count].getType());
    }
    delete [] things;
    things=new_things;
    new_things = nullptr;
    thingCount=new_count;
    return true;
}
*/
bool Cell ::removeAnythingFromTheFront(int quantity)
{
    if (quantity <= 0)
    {
        return false;
    }
    if (quantity > thingCount)
    {
        return false;
    }
    int newquantity = thingCount - quantity;
    Thing *new_things = new Thing[newquantity];
    for (int i = 0; i < newquantity;)
    {
        new_things[i].setType(things[i + quantity].getType());
        i++;
    }
    delete[] things;
    things = new_things;
    thingCount = newquantity;
    return true;
}
void Cell::removeEverything()
{
    delete [] things;
    things = nullptr;
    thingCount=0;
}

const Thing& Cell::getThing(int index) const
{
    return things[index];
}

int Cell::getThingCount() const
{
    return thingCount;
}

int Cell::getThingCount(ThingType type) const
{
    int num_thing=0;
    for (int i=0; i<thingCount; i++)
    {
        if (things[i].getType() == type) 
        num_thing++;
    }
    return num_thing;
}

int Cell::getThingTypeCount() const
{
    int thingtype=0;
    for (int i=0; i<6; i++)
    {
        if (Cell::getThingCount(ThingType(i))>0) thingtype++;
    }

    return thingtype;
}

bool Cell::hasWeapons() const
{
    int num_weapon=0;
    for (int i=0; i<thingCount; i++)
    {
        if (getThing(i).getType() == MACE
        || getThing(i).getType() == DAGGER
        || getThing(i).getType() == SWORD)
        num_weapon++;
    }
    if (num_weapon!=0) return true;
    return false;
}

bool Cell::hasMonsters() const
{
    int num_monster=0;
    for (int i=0; i<thingCount; i++)
    {
        if (getThing(i).getType() == SKELETON
        || getThing(i).getType() == VAMPIRE
        || getThing(i).getType() == DRAGON)
        num_monster++;
    }
    if (num_monster!=0) return true;
    return false;
}

bool Cell::hasType(ThingType type) const
{
    for (int i=0; i<thingCount; i++)
    {
        if (getThing(i).getType() == type)
        return true;
    }
    return false;
}
