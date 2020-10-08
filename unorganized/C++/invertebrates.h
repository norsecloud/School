// invertebrates.h
// invertebrate specifications
#ifndef _INVERTEBRATE_H_
#define _INVERTEBRATE_H_

enum Skeleton_Type { NONE, HYDROSTATIC, EXOSKELETON };

class Invertebrate {
  private:
    string name;
    Skeleton_Type skeletonType;
    int numLegs;
  protected:
    void setName(string name);
    void setSkeletonType(Skeleton_Type skeletonType);
    void setNumLegs(int numLegs);
  public:
    Invertebrate();
    Invertebrate(string name, Skeleton_Type skeletonType, int numLegs);
    string getName() const;
    Skeleton_Type getSkeletonType() const;
    int getNumLegs() const;
    virtual void print() = 0;
};

class Spider : public Invertebrate {
  private:
    const string NAME_PREFIX = "Spider: ";
  public:
    Spider();
    Spider(string name);
    Spider(const Spider &obj); // copy constructor
    Spider& operator=(const Spider &obj); // = overload
    virtual void print();
};
#endif // _INVERTEBRATE_H_
