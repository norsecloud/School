// invertebrates.cpp
// F. Raae
// 11/20/17
// Polymorphism and Virtual Functions

using namespace std;
#include <iostream>
#include "invertebrates.h"
//invertebrate constructors
Invertebrate::Invertebrate()
{
    setName("unknown");
    setSkeletonType(NONE);
    setNumLegs(0);
};
Invertebrate::Invertebrate(string name, Skeleton_Type skeletonType, int numLegs)
{
    setName(name);
    setNumLegs(numLegs);
}
//all sets and gets
void Invertebrate::setName(string name){this->name = name;};
void Invertebrate::setNumLegs(int numLegs){this->numLegs = numLegs;};
void Invertebrate::setSkeletonType(Skeleton_Type skeletonType){this->skeletonType = skeletonType;};
string Invertebrate::getName() const {return this->name;};
int Invertebrate::getNumLegs() const {return this->numLegs;};
Skeleton_Type Invertebrate::getSkeletonType() const {return this->skeletonType;};
// end sets and gets
Spider::Spider() // spider constructor
{
    Invertebrate::setName("unknown");
};
Spider::Spider(string name):Invertebrate(name,EXOSKELETON,8){}; // spider name constructor
Spider::Spider(const Spider &obj) : Invertebrate (obj.getName(), EXOSKELETON, 8) // copy constructor
{
          if (this != &obj)
        {
                Invertebrate::setName(obj.getName());
                Invertebrate::setSkeletonType(obj.getSkeletonType());
                Invertebrate::setNumLegs(obj.getNumLegs());
        }
};
Spider& Spider::operator=(const Spider &obj) // = sign overload for copying
{
          if (this != &obj)
        {
                Invertebrate::setName(obj.getName());
                Invertebrate::setSkeletonType(obj.getSkeletonType());
                Invertebrate::setNumLegs(obj.getNumLegs());
        }
        return *this;
};

void Spider::print() // virtual print function
{
    string skeleton = "";
    Skeleton_Type strSkType = (this->getSkeletonType());
    switch (strSkType)
    {
        case 0:
        {
            skeleton = "None";
            break;
        }
        case 1:
        {
            skeleton = "Hydrostatic";
            break;
        }
        case 2:
        {
            skeleton = "Exoskeleton";
            break;
        }
        default:
        {
            skeleton = "Unknown";
        }
    }

    cout << this->NAME_PREFIX + getName();
    cout << ", number of legs = " << this->getNumLegs() << ", skeleton type = " << skeleton << endl;
 };





int main()
{

    Spider *sp = new Spider("Brown Recluse");
    sp->print();

    Spider sp2("Black Widow");
    sp2.print();

    Spider sp3 = *sp; // calls copy constructor
    sp3.print();

    sp2 = *sp; // calls = overload
    sp2.print();
    delete sp;

    return 0;
}
