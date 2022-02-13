#include "game.h"
#include <iostream>
using namespace std;
//do NOT include anything else, write your code below

Game::Game(int width, int height):width(width), height(height)
{
    cells = new Cell* [height];
    for (int i=0; i<height; i++)
    {
        cells[i] = new Cell[width];
    }
}   

Game::Game(const Game& another)
{
    width = another.width;
    height = another.height;
    heroStatus.x=another.heroStatus.x;
    heroStatus.y=another.heroStatus.y;
    heroStatus.alive=another.heroStatus.alive;
    heroStatus.maceCount=another.heroStatus.maceCount;
    heroStatus.daggerCount=another.heroStatus.daggerCount;
    heroStatus.swordCount=another.heroStatus.swordCount;

    cells = new Cell* [another.height];
    for (int i=0; i<another.height; i++)
    {
        cells[i]=new Cell[another.width];
    }
    for (int i=0; i<another.height; i++)
    {
        for (int j=0; j<another.width; j++)
        {
            for (int k=0; k<another.cells[i][j].getThingCount();k++)
            {
                cells[i][j].addThing(another.cells[i][j].getThing(k).getType(),1);
            }
        }
    }
}

Game::~Game()
{
    for (int i=0; i<height; i++)
    {
        delete [] cells[i];
    }
    delete [] cells;
}

bool Game::addThing(int x, int y, ThingType type, int quantity)
{
    if (x>width-1 || y>height-1 || x<0 || y<0) return false;
    return cells[y][x].Cell::addThing(type, quantity); 
}

bool Game::removeThing(int x, int y, ThingType type, int quantity)
{
    if (x>width-1 || y>height-1 || x<0 || y<0) return false;
    return cells[y][x].removeThing(type,quantity);
}

bool Game::moveHero(char direction)
{
    /*if ((direction =='w' && heroStatus.y == 0)
        || (direction == 'a' && heroStatus.x == 0)
        || (direction == 's' && heroStatus.y == height-1)
        || (direction =='d' && heroStatus.x == width-1))
    return false;*/
    if (direction == 'w' && heroStatus.y == 0) return false;
    if (direction == 'a' && heroStatus.x == 0) return false;
    if (direction == 's' && heroStatus.y == height-1) return false;
    if (direction == 'd' && heroStatus.x == height-1) return false;
    //moving
    if (direction == 'w') heroStatus.y--;
    if (direction == 'a') heroStatus.x--;
    if (direction == 's') heroStatus.y++;
    if (direction == 'd') heroStatus.x++;
    //judging the condition in new cell
    if (cells[heroStatus.y][heroStatus.x].hasWeapons())
    {
        for (int i=0; i<cells[heroStatus.y][heroStatus.x].getThingCount();i++)
        {
            if (cells[heroStatus.y][heroStatus.x].getThing(i).getType()==MACE)
                heroStatus.maceCount += 1; //cells[heroStatus.y][heroStatus.x].getThingCount(MACE);
            if (cells[heroStatus.y][heroStatus.x].getThing(i).getType()==DAGGER)
                heroStatus.daggerCount += 1; //cells[heroStatus.y][heroStatus.x].getThingCount(DAGGER);
            if (cells[heroStatus.y][heroStatus.x].getThing(i).getType()==SWORD)
                heroStatus.swordCount += 1; //cells[heroStatus.y][heroStatus.x].getThingCount(SWORD);
        }
        cells[heroStatus.y][heroStatus.x].removeEverything();
        return true;
    }

    if (cells[heroStatus.y][heroStatus.x].hasMonsters())
    {
        int win=0;
        int length=cells[heroStatus.y][heroStatus.x].getThingCount();
        for (int i=0; i<cells[heroStatus.y][heroStatus.x].getThingCount();)
        {
            if (cells[heroStatus.y][heroStatus.x].getThing(i).getType()==VAMPIRE)
            {
                if (heroStatus.daggerCount<1)
                {
                    heroStatus.alive=false;
                    //return true;
                    i=length;
                }
                else 
                {heroStatus.daggerCount--;
                win++;
                i++;}
                //cells[heroStatus.y][heroStatus.x].removeThing(VAMPIRE,1);
            }
            else if (cells[heroStatus.y][heroStatus.x].getThing(i).getType()==SKELETON)
            {
                if (heroStatus.maceCount<1)
                {
                    heroStatus.alive=false;
                    //return true;
                    i=length;
                }
                else
                {heroStatus.maceCount--;
                win++;
                i++;}
                //cells[heroStatus.y][heroStatus.x].removeThing(SKELETON,1);
            }
            else // (cells[heroStatus.y][heroStatus.x].getThing(i).getType()==DRAGON)
            {
                if (heroStatus.swordCount<1)
                {
                    heroStatus.alive=false;
                    //return true;
                    i=length;
                }
                else
                {heroStatus.swordCount--;
                win++;
                i++;}
                //cells[heroStatus.y][heroStatus.x].removeThing(DRAGON,1);
            } 
            //cells[heroStatus.y][heroStatus.x].removeAnythingFromTheFront(1);
        }
        cells[heroStatus.y][heroStatus.x].removeAnythingFromTheFront(win);
    }
    return true;
}

bool Game::isHeroAlive() const
{
    if (heroStatus.alive==true) return true;
    return false;
}

bool Game::isAllMonstersGone() const
{
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            if (cells[i][j].hasMonsters()) return false;
        }
    } 
    return true;
}

int Game::getMonsterCount() const
{
    int num_monster=0;
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            if(cells[i][j].hasMonsters())
            {
                num_monster += cells[i][j].getThingCount();
            }
        }
    } 
    return num_monster;
}

int Game::getHeroX() const
{
    return heroStatus.x;
}

int Game::getHeroY() const
{
    return heroStatus.y;
}

