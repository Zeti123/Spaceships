#ifndef ILEVELOBJECT_HPP
#define ILEVELOBJECT_HPP

class ILevelObject
{
public:
    virtual ~ILevelObject() = default;
    virtual void kill() = 0;
    virtual bool isAlive() = 0;
    virtual void onDestroy() = 0;
    virtual bool blockLevel() = 0;
};

#endif // ILEVELOBJECT_HPP
