# Lab9_Space_Invaders
In today's laboratory session you will finalize the necessary control for our small space invaders game.
Therefore, two things need to be done:
1. enable usage of the rotary encoder to control defender's movement (left, right only)
2. enable usage of button TL as trigger to shoot

## Relevant material
> [!TIP]
> In case you need the manual for Git again, click [here](https://github.com/MicrocontrollerApplications/Utilities/blob/main/git.md)<br>
> If you need the development board's schematic, click [here](https://raw.githubusercontent.com/MicrocontrollerApplications/Lab2_InputOutput/refs/heads/main/images/uCquick_Board_2018_01.svg)<br>
> The latest datasheet can be found [here](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ProductDocuments/DataSheets/PIC18%28L%29F2X-4XK22-Data-Sheet-40001412H.pdf)<br>

For today's laboratory you need to know how to configure Pins as digital inputs and how configure an interrupt for a pin. As you're close to the end of this course, it's up to you to find out how this works and where to look for the relevant information.
>[!IMPORTANT]
>Of course, you can __always__ ask for support! But try to find a solution by yourself, first.

>[!TIP]
>Finish both exercises first, as your code will not be buildable before. Keep also in mind the past laboratories, which might act as a template for some parts of this lab. ;)

## Exercise 1 - Configure Button TL as trigger to shoot
To shoot the invaders later, you need to configure an interrupt for button TL. The interrupt shall be set up as follows.

>[!TIP]
>Have a look at the schematic if you don't know the relevant Pin for button TL.

1. interrupt needs to be triggered on a falling edge, to shoot immediately if the button is pressed instead of when it is released.
2. the relevant if-statement is prepared in line 62. You only need to implement the relevant checks and handling of the interrupt flag. https://github.com/MicrocontrollerApplications/Lab9_Space_Invaders/blob/64f5550636e2c14bff2bb50631acf0ba9e763abb/Lab9_Space_Invaders.X/main.c#L61-L67
3. Last but not least, you need to activate the projectile. Have a look at line 66 and activate it. Remember that there are no booleans in C, but 0 represents a _false_ while 1 is commonly used for _true_.

If that is done, you can proceed with the next exercise.

## Exercise 2 - Implement interrupts and level checks for rotary encoder
To move our defender, we will use the rotary encoder. Therefore, we need to catch the interrupts of the encoder's "_A_" signal and check the level of its "_B_" signal. Look at the schematic's "Digital Input / Ext. Interrupt" section to see where the relevant signals are connected to the microcontroller.

> [!WARNING]
> JP4 should connect Pins 2 and 3. Check also if that's set up correctly on your board.

To enable the required functionality, do the following:
1. look for the relevant pins, using the schematic
2. implement the interrupt in line 74 so that is triggered on a falling edge of signal "_A_" https://github.com/MicrocontrollerApplications/Lab9_Space_Invaders/blob/64f5550636e2c14bff2bb50631acf0ba9e763abb/Lab9_Space_Invaders.X/main.c#L73-L76
3. within the ISR check the level of signal "_B_". If the level is low the defender shall move left, otherwise right
   
  >[!IMPORTANT]
  >for the movement of the defender you need to set either _flags.move\_left_ or _flags.move\_right_ to 1. The rest is handeled by the code within space_invaders.c

4. don't forget to handle the interrupt flag and to return from the ISR

## Exercise 3 - Start the code in debug mode and check if everything works as expected
Now that everything works as expected, start the code and check if you can play space invaders, using the rotary encoder and button TL.
If so, great you're done! If not, try to find the error.

## For those interested
Check how the timing of the game is realized using Timer1. If you want to change the speed of either the invaders or the projectile.
