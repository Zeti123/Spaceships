#include "LevelInfo.hpp"
#include <algorithm>

LevelInfo::LevelInfo()
    :_shipNum(0), _partNum(0) {}

LevelInfo::SpaceshipInfo::SpaceshipInfo(double st, Vector2f sp, Spaceship* s)
    : startTime(st), startPosition(sp), spaceship(s){}

LevelInfo::Part::Part(double duration)
    :_duration(duration){}

Spaceship* LevelInfo::nextShipIf(double currentTime)
{
    if (_partNum >= _parts.size())
        return nullptr;

    if (_shipNum < _parts[_partNum].shipsNumber() &&
        currentTime >= _parts[_partNum].getSpaceshipInfo(_shipNum).startTime)
    {
        Vector2f startPosition = _parts[_partNum].getSpaceshipInfo(_shipNum).startPosition;
        _parts[_partNum].getSpaceshipInfo(_shipNum).spaceship->setPosition(startPosition);
        return  _parts[_partNum].getSpaceshipInfo(_shipNum++).spaceship;
    }
    return nullptr;
}

void LevelInfo::addSpaceship(const SpaceshipInfo& spinfo)
{
    _parts.back().add(spinfo);
}

void LevelInfo::addNewPart(double duration)
{
    _parts.push_back(Part(duration));
}

void LevelInfo::nextPart()
{
    if (_partNum >= _parts.size())
        throw "there is no such part";

    if (_shipNum != _parts[_partNum].shipsNumber())
        throw "not every ships flew out";

    _partNum++;
    _shipNum = 0;
}

double LevelInfo::partDuration() const
{
    return _parts[_partNum].duration();
}

size_t LevelInfo::partsNumber() const
{
    return _parts.size();
}

bool LevelInfo::endOfPart() const
{
    if (_partNum >= _parts.size())
        throw "there is no such part";

    return _shipNum >= _parts[_partNum].shipsNumber();
}

bool LevelInfo::endOfLevel() const
{
    return _partNum >= _parts.size();
}

LevelInfo::SpaceshipInfo& LevelInfo::Part::getSpaceshipInfo(size_t num)
{
    if (num >= _spaceships.size())
        throw "there is no such ship";

    return _spaceships[num];
}

void LevelInfo::Part::add(const SpaceshipInfo& spinfo)
{
    _spaceships.push_back(spinfo);
}

size_t LevelInfo::Part::shipsNumber() const
{
    return _spaceships.size();
}

double LevelInfo::Part::duration() const
{
    return _duration;
}

bool operator <(const LevelInfo::SpaceshipInfo& a, const LevelInfo::SpaceshipInfo& b)
{
    return a.startTime < b.startTime;
}
