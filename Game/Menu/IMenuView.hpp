#ifndef IMENUVIEW_HPP
#define IMENUVIEW_HPP

class MainMenu;

class IMenuView
{
public:
    virtual void create(MainMenu* parent) = 0;
    virtual void destroy() = 0;
    virtual ~IMenuView() = default;
};

#endif // IMENUVIEW_HPP
