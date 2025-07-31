# Werewolves Manager

## What is it?

This is custom program I created to help run games of Ultimate Werewolf. Tracking player roles and activities, especially in large groups or games with lots of roles, can get very complicated. As such I designed this program to help simplify the act of GMing a game of Ultimate Werewolf by letting the program keep track of details while the GM gets to concentrate on flavour and keeping the game running smooth. 

## How does it work?

The program is constructed in C++ and uses an abstract class as the basis for all the roles in the game. Each card has it's own concrete class which inherits the basic data structure from the abstract class. The game then tracks each player's role and status within the game and tells the GM what is happening and when, along with displaying a table containing all the player's roles and indexes. 

## How to use it?

Set up a game of Ultimate Werewolf and prepare a deck to play with. Compile the program and run it. It will prompt you for the number of players (you can change this later) and the program will take you to the main menu. Here you can follow the onscreen commands to add roles to the game as well as set some of the rules. Once the game starts the program will prompt the GM with which steps to complete and when.

> [!NOTE]
> This is a work in progress and currently in alpha testing. See changelog for details.
