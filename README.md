# Tetris on Raspberry Pi Sense Hat

This code allows the user to play tetris within the terminal aswell as a visual represnetation of the tetris blocks on the 8x8 LED matrix.


Using the Raspberry Pi Joystick we can pull user input and make the LED matrix update accordingly. 

Each tile gets a sequential color from the colors defined in the top. 

> Based on template given by NTNU in the subject `TDT4258 Low Level Programming`

## How to run

In order to run the tetris game use the following `Make` command
  `make run`

If you get the following error : `File not found` that means that your raspberry pi's dev folders location is relative to somewhere else, make sure that you update the **PATH** macro in the `stetris.c` file

