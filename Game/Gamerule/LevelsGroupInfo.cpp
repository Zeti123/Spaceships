#include "LevelsGroupInfo.hpp"

LevelsGroupInfo::LevelsGroupInfo(const std::vector<std::function<LevelInfo()>>& levelLoaders)
    : _levelLoaders(levelLoaders) {}

std::function<LevelInfo()> LevelsGroupInfo::getLoaderFunction(size_t num)
{
    if (num >= _levelLoaders.size())
        throw "there is no such level in group";

    return _levelLoaders[num];
}

size_t LevelsGroupInfo::levelsNum() const
{
    return _levelLoaders.size();
}
