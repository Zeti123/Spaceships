#ifndef LEVELSGROUPINFO_HPP
#define LEVELSGROUPINFO_HPP

#include <functional>
#include <vector>
#include "LevelInfo.hpp"

class LevelsGroupInfo
{
public:
    LevelsGroupInfo(const std::vector<std::function<LevelInfo()>>& levelLoaders);
    std::function<LevelInfo()> getLoaderFunction(size_t num);
    size_t levelsNum() const;

private:
    std::vector<std::function<LevelInfo()>> _levelLoaders;
};

#endif // LEVELSGROUPINFO_HPP
