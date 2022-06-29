# Introduction

This game has been implemented as part of the application for the "Advanced Programming for AAA Video Games" master's degree offered by UPC Talents School.

This game is a variation on the Zork game where you must find a way to escape the mysterious ruins you have found yourself in by accident. 

Author: Jan Marc Costa

# Information
You can find the source code for the game following this link: https://github.com/TheGeminis/zork.git

# Goal of this game:
This game contains 9 rooms as seen on the map provided with their disposition and the connections between them. The goal of the game is to unlock and enter the portal located at the center of the Portal Room.

# Walkthrough

1. Go to the Portal Room and take the key.
```
take/pick key
```
2. Use the key to unlock the vault room, enter and pick both the sword and the pearl from the chest.
```
unlock north with key
take/pick sword from chest
take/pick pearl from chest
```
3. You must have the sword equipped to be able to fight the skeleton in the room Intersection as you need to have a weapon equipped. However, it is recommended to use the pearl and acquire the yellow aura, it will make the combat with the skeleton more favorable for you since the skeleton has a blue aura. You should see a message when you decide to attack tell you the state of interaction between your aura and the aura of the enemy, and when asked to continue the attack, respond yes.
```
equip sword
use pearl
attack skeleton
yes/y
```
4. Loot the skeleton and equip it's weapons just as you did with the sword since they offer better stats, also you will need the opal to be able to use the blue aura.
```
loot skeleton
equip ...
```
5. Go to the library, unlock it using the yellow aura, when asked if you want to offer your soul, say yes, this is how you unlock the aura based exits. You can see what are you need by trying to go to the exit before unlocking it. If you don't use the correct aura you will receive a punishment.
```
unlock east with aura
yes/y
go east
```
6. Fight the ghost using the blue aura to have a favorable combat. Once you have defeated it, loot it to gain the garnet and the ability to have a red aura.
7. You can now go to the lab and unlock it using your yellow aura and defeat the witch inside. The witch has a very powerful weapon so it is recommended to use your red aura to do max damage against her while not taking any damage in return. Loot the witch and obtain one of the two pieces to craft the key to open the portal and escape: the gem.
8. While you can try and defeat the zombie located in the Crypt before you fight the witch, it is recommended to do it afterwards since the zombie has a big health pool on top of having a very powerful defensing item. Equip the wand looted from the witch and the red aura to have defeated the zombie fast. To unlock the crypt you need the blue aura. Loot the zombie and get the jade that allows you to have the green aura.
9. Now that you have the most powerful offensive and defensive weapons as well as all the items to obtain all the areas you can try to defeat the demon located at the Chapel. To unlock it you will require the red aura and to defeat it, it is recommended to use the green aura. Once defeated loot it and obtain the second and last piece to escape: the stone.
10. Go to the Portal Room and craft the device that acts as a key for the portal using the combine/comb command, then unlock the portal exit and go through it to escape and finish the game.
```
combine gem with stone
unlock center with device
go portal
```
Congratulations, you have finished the game.

# Commands:
* "look" or "look [blank]"
* "Go [blank]"
* Stats
* Inventory
* take [blank]
* drop [blank]
* equip [blank]
* unequip [blank]
* examine [blank]
* attack [blank]
* loot [blank]
* use [blank]
* unlock [blank] with [blank]
* lock [blank] with [blank]
* drop/put [blank] on [blank]
* combine [blank] with [blank]
		
# License
MIT License

Copyright © 2022 Jan Marc Costa Rodenas

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
