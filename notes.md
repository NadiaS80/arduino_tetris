### 09.03.2026

``
After a hot body wrap, I take a shower, and the idea comes to me to make Tetris. In terms of code logic, it is much more complex than tic-tac-toe. As I had promised myself while finishing tic-tac-toe, before implementation it is necessary to build a logical framework. So. The maximum vertical and horizontal span of a figure is 4 up and 4 down. That means the figure field is 4×4. And in a loop, the figure is updated in the virtual field where there are 'v' for empty cells and 'f' where the figure’s cells are. There are functions for drawing the figure. Each of them goes through the same field and changes it depending on the current figure, which can, for example, be defined in an enum array. And when the figure falls, the virtual big_game_field simply changes. Every second, the loop changes the field, lowering the figure, and since loop() runs 1000 times per second, we measure intervals in an external variable, and at certain intervals we speed up the falling time. Conditionally, something like if (already_figures > 5) { interval_time += 0.1; }. Having the first cell, we draw figures both through RGB and on the virtual field through the XY function. Each figure can have its own symbols for more diverse lighting when the RGB class reads the virtual field. And figures accumulate in the virtual array. Then the status of the array is checked. It is important while writing the code to separate: the functions for falling and moving the current figure, meaning all operations on the moving figure; and all operations on the figures that are already lying in place. In fact, the task of the RGB class is to scan the virtual big_game_field and update it. That is all. The actual game itself happens in the class with the large field, where loops change the field depending on the commands that were read. In the RGB class, it is enough to have an initialization function, a field-reading function, and entertaining animation functions. It is also possible to work with the real-time clock module for reading delays. And instead of a joystick, use buttons, because they are faster to press, especially at speed, and they are also used in the original Tetris.
``

``
For now, this is just a sketch at 2:50 a.m. The first thoughts on the project. Actually, according to the plan, I was supposed to make the Body project, a simplified analogue of the tabletop EMO bot that costs $1500. But after tic-tac-toe, I feel like increasing the complexity specifically in game embedded. I do not know whether I will implement this project at all. We will see. For now, this is just a mental sketch.
``

``
Twenty minutes after the previous text hahaha.
In fact, moving figures horizontally is easy, because there are cells, and the figure moves like the cross and the zero did, without overlapping the current coordinates onto the previous ones. And vertically it is just +1 to start_string, conditionally speaking. And for the figure to descend smoothly, the field has to be larger than what is displayed, so that the figure fully enters the virtual field before it appears in the real one. So, when a signal is read from the buttons, we move it right or left. During drawing, in order not to overlap with other figures that are already lying there, in the figure field, when reading, it is possible to do if ... == 'v', then we ignore it and do not draw it. And at the top there should be 4 extra cells: if the field is completely filled and the figure has nowhere to fall, it will understand this when it cannot move down from those four upper non-displayed cells. And if in a row there is not a single 'v', then a function should run, probably one that is constantly checked inside loop(), and it iterates through the rows, changing the char values of the figures row by row and shifting the upper ones downward.
``


---


### 13.03.2026

``
In a couple of days, through the IDE on my phone, whenever I had free time, I implemented the virtual game class for Tetris. Everything except figure rotations. I am genuinely surprised, considering that on my previous tic-tac-toe project I spent a really long time. On the other hand, in that previous project I was working with C++ classes for the first time, working with a matrix for the first time, and with a joystick for the first time. And now there is a clear understanding. But this project has to be another step upward, toward the more complex projects that I set for myself. More specifically, in this project I use a real-time clock module. All that is left is to implement figure rotation, I think I will do it through a separate class for figures, then the RGB class, where there are only 4 functions, namely init(), end_game_animation(), start_game_animation(), and draw_actual_field(). And after that, call the commands in the correct sequence inside loop().
``


---


### 15.03.2026

``
It was difficult to think through the logic of the turns. Initially, the indexes of the shapes (along with its rotations) were stored in an imaginary 4x4 field, relative to which the shapes were drawn in a large field. It has become much more difficult with turns, as there is an offset and a border check. And the rotation inside a separate matrix becomes more difficult. I came to the conclusion that in this situation it would be much more correct to write the values already in the field into the index matrix. And then just add the position of the shape to them, thereby changing one shape to another when turning.
``


---


### 14.04.2026

``
To be honest, I've been putting off completing the project for a long time. I had written classes for playing, drawing, and reading buttons. That is, the Tetris engine has been fully implemented in one form or another. But at some point, the chain of thoughts that had been going on for days in my subconscious broke off and I just looked at the code that I had written myself as if it were something alien. It's a very strange brain mode, to be honest. After a month off from the project, which I wrote in a week, I assembled all the previously written functions into loop logic. And so, having allocated a little time for several evenings in a row, falling asleep at the computer, Tetris is ready. The only thing I encountered was the limitation of the Arduino UNO's SRAM memory, which temporarily caused me to disable the beautiful animation. 
``

``
After completing the project, and finally playing Tetris, I realized that I had created a wonderful toy for myself. I decided to buy an Arduino MEGA, which will be necessary for my subsequent projects and with which I will be able to display the animation that I originally prescribed, which requires extended memory for the local array variable `CRGB blinks[256]". And I realized that I want to play this Tetris game on a regular basis. Now there is an inconvenience with the fact that I use a solderless breadboard, and all my components are solderless. Because of this, some components fall off during the game and the game process may be disrupted. The solution is simple. To play on a permanent basis, buy an Arduino NANO (the beautiful animation of the end of the round does not matter to me) and solder the components to it. The contacts that connect to the RGB matrix can be connected via separate contacts (the contacts themselves are soldered, but they are designed for a solder-free connection).
``