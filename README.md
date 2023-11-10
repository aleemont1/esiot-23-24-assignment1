# esiot-23-24-assignment1
Assignment 1 for Embedded Systems and Internet of Things

# RESTORE THE LIGHTS

The game board is based on 4 green leds L1, L2, L3, L4 and red led LS,
four tactile buttons B1, B2, B3, B4 and a potentiometer Pot, displaced in the following layout:

[Image](https://imgur.com/a/ibcRWAC)

During a game, the leds L1…L4 are initially all on. Then, after some random time T1,
the leds start turning off, one by one in sequence, in some random order, taking some T2 time.
As soon as the last led is turned off, the player must turn on the leds in the reverse order by
pressing the corresponding buttons B1…B4, within some time T3. Each button Bi turns on the
corresponding led Li. So if the order in which the leds were turned off  was for instance 3,1,2,4
(that is: the first led to be turned off was L3, then L1, etc),  then the leds must be turned on
again in order 4,2,1,3 (that is: first L4, then L2, etc). If the player restores the leds on time,
the score - starting from zero - is increased and the game goes on, repeating the sequence,
but reducing the times T2 and T3 of some factor F.
If the player does not restore the leds on time in the correct order, the red led Ls is turned on
for 1 second and the game ends, displaying the score on the serial line. 

