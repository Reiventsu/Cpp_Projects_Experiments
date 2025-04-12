## Snake Game

> [!IMPORTANT]  
> This project uses [raylib](https://github.com/raysan5/raylib) you will not be able to successfully compile the project without the library.

### Goals
- Use raylib
  - Learn to import libraries
- Follow the [YouTube tutorial](https://youtu.be/LGqsnM_WEK4?si=SsRK6Q5oAe8VNbuw) on how to make a snake game
- Learn how to change it from the final product in the YouTube video (add something or change something)

Focus of this project is to create a small snake game simply because I want to, and within the first moments I've already encountered
my first problem. Importing libraries to use. I have many options, either try to manually add it or make from source, use vcpkg or conan.
I haven't decided which way to go yet, but I'll be testing the different routes out.

> [!TIP] 
> #### Controls
> Use the [ARROW KEYS] to move the snake, when the snake "dies" 
by hitting the wall or itself it will reset to initial position. Press any [ARROW KEY] to continue the game.  
Use [ESC] or close the game window to quit.  
Use [SPACE] to boost!

---

```
Project status: Almost done!

Planned fixes: 
- Due to the games interval based update it is possible to
  collide with yourself by very quickly pressing the
  arrow keys and colliding into yourself, 
  I will find a way to prevent this from happening.

- I would like to add a menu of some kind in the future possibly.
  or at least some extra polish to the game to test my skills.
```
