[![Build status](https://ci.appveyor.com/api/projects/status/ip3p02l0mnrowooi?svg=true)](https://ci.appveyor.com/project/dwarzecha/gl-craft)
![GitHub last commit](https://img.shields.io/github/last-commit/dwarzecha/gl-craft)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/9ef38cd122c94c23b92aa6d892771b8f)](https://www.codacy.com/manual/dwarzecha/gl-craft/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=dwarzecha/gl-craft&amp;utm_campaign=Badge_Grade)
[![CodeFactor](https://www.codefactor.io/repository/github/dwarzecha/gl-craft/badge)](https://www.codefactor.io/repository/github/dwarzecha/gl-craft)

# gl-craft

![Image](/screenshots/screenshot1.png)

## Description
C++ implementation of Minecraft game, using OpenGL and SFML, planned as a project on which I could learn OpenGL and practice object-oriented C++ programming.

Project is still in development stages, currently moving from fixed-size to infinite world.

## Build instructions
gl-craft uses [Premake](https://premake.github.io/) as its build system, to generate compiler-specific files and perform necessary post-build steps. Below are the platform specific instrucions.

### Windows
As all the dependencies are included in the project folder, the only necessary step is to run
```
vendor/bin/premake/premake5.exe vs2017
```

in the root directory. This will generate a Visual Studio 2017 solution file, which can be used to compile the application.

### Linux (Debian based distributions)
First of all, it is necessary to install OpenGL and SFML packages, running

```
sudo apt-get install libsfml-dev
```
```
sudo apt-get install build-essential libgl1-mesa-dev
```
```
sudo apt-get install libglew-dev libglm-dev
```

Then Makefiles can be generated using Premake, and compiled
```
vendor/bin/premake/premake5 gmake2
```