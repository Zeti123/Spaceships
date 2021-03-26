#ifndef MAINCLASS_HPP
#define MAINCLASS_HPP

class MainClass
{
    friend class Engine;

public:
    MainClass();
    virtual ~MainClass() = default;
    virtual void onFrame() = 0;
    virtual void onExit();

private:
    static MainClass* _instance;
};

#endif // MAINCLASS_HPP
