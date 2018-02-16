Saurabh Chand Ramola
20161106
Graphics Assignment 1




* TO START THE GAME, GO THE BUILD DIRECTORY AND RUN ./graphics_asgn1 ON YOUR TERMINAL.

* THE SCORING OF THE GAME WILL BE:
+100 - IF YOU JUMP OF NORMAL BALL
-10 - IF YOU COME IN CONTACT WITH A PORCUPINE
IF YOU GO IN THE AREA OCCUPIED BY THE PORCUPINE WHEN THE PORCUPINE IS PRESENT, YOUR SCORE WILL DECREASE.

THE NUMBER OF PORCUPINES WILL INCREASE WITH EACH LEVEL.

IF YOUR SCORE GOES LESS THEN 0 AT ANY POINT IN THE GAME, YOUR GAME GETS OVER.


* FOR ADDITIONAL INFORMATION REGARDING CONTROLS OF THE GAME, see help.pdf.

How to run:
1. Make sure you are in the directory 20161106_Assignment1
2. Run the command mkdir build
3. Run the command cd build
4. Run the command cmake ..
5. Run the command make
6. Run the command ./graphics_asgn1


Controls:
● The player’s ball is metallic and is multicolored and can be attracted by a magnet on 2nd and 4th level.
● To move left use key a and to move right press d.
● To jump use the spacebar.
● To move the camera left, right, up or down use the arrow keys.
● Use the scroll wheel or + and - to zoom in or out
● Score and Level is displayed in the window title bar.
● The game starts with the level 1 and score = 0.
● In the game after that if the score again gets 0 at any point in time, game gets over and Game over is displayed on the screen for two seconds before the screen is closed.
● As the level increases, the number of porcupines keep on increasing
● There are four levels and magnet appears on level 2 and 4 and porcupines keep on increasing in every level and they subtract something from your score everytime you come in touch with them.
● The game is infinitely and the player can move anywhere horizontally on the ground.


Things I have implemented:
Version 1.0: Flying balls, floor, player and slopes on some flying balls. Basic physics
Version 2.0: Water, Trampoline and accompanied physics. Zooming and panning.
Version 3.0: Moving porcupines, Magnet and accompanied physics.
Version 4.0: 4 Levels, different types of scoring , disappearing and reappearing magnets, infinite world.
