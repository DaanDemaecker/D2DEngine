# D2D engine

The D2D engine is a very small 2D engine made by Daan Demaecker for the end assignment for Programming 4 in the Game development course in Digital Arts and Entertainment at Howest.  
[Digital Arts and Entertainment](https://www.digitalartsandentertainment.be/)

## Goals

The goal was to make a small component-based engine that teaches us programming patterns often used in the industry. To prove that our engine actually works, we were each assigned a game to recreate using our very own engine.

## Features

The main features of this engine are:
- GameObjects
- Components
- Scenes
- Sound effects
- Box and capsule physics
- Keyboard and controller input

## Patterns

Programming patterns used in this engine are:
- Command
- Observer
- Singleton
- State
- Game loop
- Update method
- Component
- Event queue
- Service locator
- Dirty flag

## Choices

Some choices that I have made are:
- Self-made physics: After I finish my studies at DAE, I would like to focus on physics programming. So I could not let up this chance to try and incorporate self-made physics instead of using an existing library.
- Observer instead of event queue: While event queue adds more decoupling which is better in the long run, I felt like the scope of the project wasn't quite big enough to need it and chose the observer pattern instead.
- Game loop: For the game loop, I chose the following:
  * Start frame: This gets called before the update loop so that objects that were marked to be added last frame can be added to avoid errors.
  * FixedUpdate: A fixed update is implemented for physics-based objects to avoid wall clipping.
  * Update: The main update is called for anything that needs it.
  * LateUpdate: Functions that should always be called after everything is updated are called here.
  * PostUpdate: Objects and components that were marked as deleted are deleted here to avoid errors.
  * Render: After updating everything, it is all rendered to the screen.
  * Sleep: The main thread sleeps so that a desired framerate is held, and the CPU isn't always at 100%.

