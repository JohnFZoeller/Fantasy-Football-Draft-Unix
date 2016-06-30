#include "team.h"

Team::Team()
{
    name = " ";         //default blank name
    position = 11;      //default is outside of draft range. 
    user = false;
}   

Team::Team(string n, int p, bool a)
{
    name = n;
    position = p;
    user = a;
}

Team::Team(const Team &obj)
{
    name = obj.name;
    position = obj.position;
    user = obj.user;
}

void Team::setUser(bool u)
{
    user = u;
}

bool Team::getUser()
{
    return user;
}

void Team::setPosition(int p)
{
    position = p;
}

int Team::getPosition()
{
    return position;
}

const Team &Team::operator=(const Team &rhs)
{
    if(this != &rhs)
    {
        name = rhs.name;
        position = rhs.position;
        user = rhs.user;
    }
}

bool Team::operator==(const Team &rhs) const
{
    if(name == rhs.name && position == rhs.position && user == rhs.user)
        return true;
}

bool Team::operator!=(const Team &rhs) const
{
    if(*this == rhs)
        return false;
    else return true;
}


void Team::displayBasics()
{
    cout << endl << "Team name : " << name << endl;
    cout << "Draft Position : " << position << endl << endl;
}