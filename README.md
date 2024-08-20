# Pengo
This is a simple remake of the 1982 arcade game [Pengo](https://en.wikipedia.org/wiki/Pengo_(video_game)). It contains all the gameplay features of the original Pengo, including all 16 original levels and 2 player co-op using keyboard and controller.

[![Build Status](https://github.com/Akadeax/cpp-pengo/actions/workflows/msbuild.yml/badge.svg)](https://github.com/Akadeax/cpp-pengo/actions)

![GIF of Gameplay](./RepoIMG/PengoGameplay.gif)

## Level Editor
The project comes packaged with a level editor and its' source code under `Tools/LevelEditor`. This is a simple [flutter](https://flutter.dev/) application that allows you to export custom levels and import them into the game with ease.

![GIF of Level Editor](./RepoIMG/PengoLevelEditor.gif)

## Engine Features
The project is split up into a generic engine (`Minigin/`) and a game project (`Game/`), both written in C++ from almost-scratch using SDL2 and glm. A big thanks to Alex Vanden Abeele for assisting with the set-up of SDL2.
The Engine has several features that are only partially displayed in the game, including:
- A generic input system that allows you to bind keyboard & controller input to actions via the Command pattern
- A service locator giving access to a multi-threaded sound system and a resource cache
- A component system reminiscient of Unity Engine (GameObjects that hold polymorphic components)
- A sprite animation system inspired by Godot Engine
- A UI system similar to Unity's that allows you to anchor ui elements to either corners of the screen or each other, along with a collection of half a dozen pre-made UI components
- A templated implementation of the Signals and Slots pattern (think more flexible Observer) similar to Godot & Qt
- A traditional imlementation of the State pattern
- A json-based level loader and highscore saver powered by [nlohmann](https://github.com/nlohmann/json)

As you may be able to tell, large parts of this engine are an amalgamation of positive experiences I've had with other engines and tried to replicate in C++. While the code is relatively well-documented throughout, this is meant as an educational project and not as an actual engine ready for use in projects.

If you wish to do so anyway, this entire project is under [Unlicense](https://unlicense.org/), so feel free to do with it whatever you'd like to.