Legend of Zelda Opengl 3D Game
=========================
This game is based on [Legend of Zelda]( https://www.youtube.com/watch?v=-F6mewS47Fg#t=10m15s).  More details in [problem.pdf](Assignment-1.pdf). 

The prime objective is to score as much as possible before the ship runs out of fuel.

[TOC]

### Installation
--------

You need to install the development packages of the following libraries:

1. GLEW

2. GLFW3

3. GLM

4. AO

5. MPG123

####Installing packages

```bash
sudo apt install cmake pkg-config
sudo apt install libglew-dev libglfw3-dev libglm-dev
sudo apt install libao-dev libmpg123-dev
```

####Run the code

```bash
cd path/to/project
mkdir build
cd build
cmake ..
# Run from here after editing
make
./game
```

###Extra Features

------

- Background music on firing fireball
- Sail movement in the direction wind 
- Score, Health and countdown-timer using seven segment display
- Speed ,Health and fuel boosters 
- Modular codebase
- Physics have been followed
- Boss monster comes after killing small monsters
- 6 different camera views

###World

-----

1. **Ship with Cannon and Sail**
2. **Water** 
3. **Rocks**
4. **Monsters**
5. **Boss Monsters**
6. **Gifts and Boosters** 

**Health Points** is displayed on **top left** of window.

**Score** is displayed on **top right** of  window.

**Countdown timer / Fuel** is displayed on **middle** of window.

**Objective** is displayed on **title bar** of window.

###Scoring

------

Collision with rock : Reduces health points by 10.

Collision with monster : Reduces health points by 30

Collision with bossmonster : Reduces health points by 50

Killing with monster:  Increases score by 10

Killing with bossmonster:  Increases score by 30

### Controls

------

#### Keyboard Controls:

- Space - Jump
- Arrow keys - Movement of the boat
- C - To move to ortho view
- V - Change camera views
- F - Fire fireballs
- Tower View:
  - S - revolve camera
  - Z/X - change camera y coordinate

#### Mouse Controls:

- Mousewheel - Zoom In/Out
- Helicopter View
  - mouse click and drag - move camera
  - mouse scroll - move camera near/far

###License

-----

Music Credits: Eric Matyas (http://www.soundimage.org)