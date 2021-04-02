# Spaceships

Spaceships - bullet hell game

![](https://i.imgur.com/zXLRxUP.png)

![](https://i.imgur.com/lUZVA7E.png)

![](https://i.imgur.com/UHrqC5F.png)

## About the game

### Description
The game has a few levels, where you fly a spaceship and you have to defeat enemies. Each level ends upon defeating all the enemies. Try to defeat them as fast you can, because opponents often come in waves. If you don't take care of a previous wave fast enough, the next wave will get there, which means more enemies to defeat.

### Controls
The spaceship can be moved in any direction by using the W, A, S, and D keys, like this:
- W - move up
- A - move left
- S - move down
- D - move right

You can also rotate the ship along its axis, like this:
- Right arrow - rotate clockwise
- Left arrow - rotate counter-clockwise

To shoot, press the up arrow.
Also, you can pause and unpause the game with the spacebar.

### Enemies
![](https://i.imgur.com/Jld56Ny.png)

The simplest enemy, moves only in a straight line, usually isn't much of a problem

Stats:
- HP - 100
- Speed - 50
- Shooting rate - 1/2
- Bullet speed - 100
- Additional behaviour: none

![](https://i.imgur.com/4557MR1.png)

This ship can fly in any trajectory, it is not difficult to defeat, however it can be a bit problematic.

Stats:
- HP - 250
- Speed - 150
- Shooting rate - 2/3
- Bullet speed - 240
- Additional behaviour: 
    - always faces the player and shoots directly at them

![](https://i.imgur.com/0fLxTgw.png)

This ship can fly in any trajectory and it slowly rotates along its axis. It can fire 8 bullets at once, so the smallest number of such ships can make it so that the entire screen is filled with bullets.

Stats:
- HP - 300
- Speed - 75
- Shooting rate - 1
- Bullet speed - (0 - 240)
- Additional behaviour:
    - shoots 8 bullets at once
    - the bullets do not move at a constant velocity, which makes a "pulse" effect

![](https://i.imgur.com/wbgZr1N.png)

This ship can fly in any trajectory. It shoots 2 bullets simultaneously, and it always faces the direction it moves in. It's not very dangerous by itself, however it can spawn smaller ships (see below), which can make the game harder

Stats:
- HP - 400
- Speed - 150
- Shooting rate - 1/3
- Bullet speed - 240
- Additional behaviour:
    - it spawns smaller ships every 10 seconds, as long as there are fewer than 4 such ships on the screen - if one of them is destroyed, this ship gets to spawn another smaller one 

![](https://i.imgur.com/e0epAiW.png)

This small ship can only be created by the ship described above. It moves randomly, always trying to get close to the player.

Stats:
- HP - 40
- Speed - 300
- Shooting rate - 1/2
- Bullet speed - 250
- Additional behaviour:
    - moves around the player
    - always faces the player and shoots directly at them

![](https://i.imgur.com/sDJCPiR.png)

This ship can fly in any trajectory. It shoots a series of 3 bullets, and then a missile. It always faces the direction it moves in, it can really quickly destroy/kill the player, because the missiles it shoots deal a high amount of damage.

Stats:
- HP - 300
- Speed - 150
- Shooting rate - (2/3 - 2)
- Bullet speed - 240
- Missile speed - (0 - 500)
- Additional behaviour:
    - it shoots a series of 3 bullets with a 0.5s interval, then after 1.5s shoots a missile
    - the missile it shoots moves slowly in a straight line for a bit, then it shoots fast directly at the player


## Compilation
The project includes a .pro file, which makes it easy to compile it in *QT Creator*. Aside from standard C++ libraries, you also need sfml, which you can download from https://www.sfml-dev.org/. This project can be compiled on any platform - Windows, Linux and MacOS.

## Credits
All of the code was made by Bartosz Głowacki, the owner of this GitHub repo. \
All the graphical assets were created by Sławomir Nowaczewski. \
In game music was created by: \
Jakub Daković, Jakub Klimkiewicz and Kacper Banach (*Fobia* band - **All rights reserved)** \
Main menu music by Sławomir Nowaczewski \
Voice acting by Oskar Tuchowski \
This README file was edited by Ari Kaczmarek.
