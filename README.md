### How to compile game
- First, select if you want or not Debug information by enabling or not DEBUG in `Constants.hpp`
- If you're on Windows or MacOS:
	- Get yourself a true OS and move on.
- If you're on Linux :
	- You will need **g++** and **SDL2**
	- do something like : `g++ src/main.cpp -o cppong -lSDL2` or similar, it should work

### Troubleshooting
- You may have the score digits not working. Well try to put the `digits` folder somewhere the program can find it and it should be all good.

### How to play
keyboard is AWERTY btw
- First player :
	- **Z** up
	- **S** down
	- **E** fast up
	- **D** fast down 
 - Second player :
	- **O** up
	- **L** down
	- **I** fast up
	- **K** fast down 