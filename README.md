# About this project
**Note:** If you wish to download a copy of this project, you should do so via cloning. This project makes use of Git LFS to track .uasset files due to their size, so these files don't download properly when downloading the project as a ZIP file.

## Background
This project is one I completed as part of an independent study I did during my last semester in graduate school in the M.S. Digital Production Arts program at Clemson University, lasting from August 2019 to December 2019. I wanted the independent study to focus on an aspect of game development, and I chose to focus on gameplay programming. So I challenged myself to see if I could create a finished and functional (albeit simple) game using tools and programming language(s) of my choice. I chose Unreal Engine 4 because C++ is my most familiar programming language and because using an existing engine would allow me to focus on simply programming my game's logic. 

## Game Design
Since I was building my own game, I would need to decide what type of game it would be and what the gameplay would be like. I'm personally fond of the "platformer" genre (think Super Mario Bros. as an example) so I decided to design my game with a similar gameplay style, but with strongly simplified mechanics for the sake of a smaller project scope. The main objective of the game is to simply traverse a small level (done by walking and jumping) and gather a fixed number of collectible items scattered throughout it within a time limit. If the player collects every item within the time limit, they win; otherwise, they lose. 

In terms of mandatory features and assets, this project called for an environment, collectible items, a controllable player character that can walk and jump, and an in-game timer. I also included a simple main menu at the start of the game where the player can start the game, read about the controls, or quit. 

## Implementation
I created this project as a C++ project in Unreal since I wanted to write my own classes and functionality using C++ code. This was mostly a personal choice since at the time I wasn't familiar with Unreal's Blueprint scripting system and I wanted to get exposure to writing C++ code that works with the engine. This project was developed on version 4.22 of the engine using a Mac computer.

All assets used in this project (textures, materials, meshes, animations, sounds, etc.) were pre-made assets that I found for free or purchased for a small price from sources including the Unreal Marketplace, Mixamo, TurboSquid, and Freesound.org. I had neither the skill nor the time to make my own assets within my timeframe, and asset creation wasn't the focus of the project anyway.

All user-made functionality was done using C++ classes and code (except for the Heads Up Display.) User-defined classes include those for the main character (MainCharacter), character controller (MainPlayerController), character animation instance (MainCharAnimInstance), a base item class (Item), and a collectible item class (Collectible) that derives from Item. In the finished project, Collectible is the only child class of Item, but I wanted to write an extendable item class in case I had time to possibly implement other item types.

I used Widget Blueprints to create a simple HUD to display the number of items currently collected out of total items on the map and to display the countdown timer.

I programmed both a win and loss condition, both of which play a sound effect and send the player back to the main menu upon being met.
