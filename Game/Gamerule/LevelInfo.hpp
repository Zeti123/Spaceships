#ifndef LEVELINFO_HPP
#define LEVELINFO_HPP

#include "Spaceship.hpp"

class LevelInfo
{
public:
    LevelInfo();
    struct SpaceshipInfo
    {
        SpaceshipInfo(double st, Vector2f sp, Spaceship* s);
        double startTime;
        Vector2f startPosition;
        Spaceship* spaceship;
    };

public:
    Spaceship* nextShipIf(double currentTime);
    void setMusicPath(const std::string& filename);
    void addSpaceship(const SpaceshipInfo& spinfo);
    void addNewPart(double duration);
    void nextPart();
    void clear();

    const std::string& getMusicPath() const;
    double partDuration() const;
    size_t partsNumber() const;
    bool endOfPart() const;
    bool endOfLevel() const;

private:
    class Part
    {
    public:
        Part(double duration);
        SpaceshipInfo& getSpaceshipInfo(size_t num);
        void add(const SpaceshipInfo& spinfo);
        size_t shipsNumber() const;
        double duration() const;

    private:
        std::vector<SpaceshipInfo> _spaceships;
        double _duration;
    };

    std::string _music;
    std::vector<Part> _parts;
    size_t _shipNum;
    size_t _partNum;

};

bool operator <(const LevelInfo::SpaceshipInfo& a, const LevelInfo::SpaceshipInfo& b);

#endif // LEVELINFO_HPP
