# SMB1C
 This is a transpilation of Super Mario Bros. into C, partially aiming to port it natively to the PC.

# Goals
### Main Goal
The main goal is to have a functionally equivalent, portable Version of the original Super Mario Bros. for Microsoft Windows and Linux Computers.

### Accuracy
If possible, I'd like to preserve as many glitches as possible, though some might disappear to make way for Quality of Life changes, such as an uncapped sprite limit or similar. I definitely want glitches like the Minus World or Wall-jumping to remain!

### Flexibility
While I want this to be a fairly accurate port, I want to liberate Super Mario Bros. of some of it's limitations, such as it's sprite, object or resolution limits.

# Non-Goals
### Getting a matching binary
Since the original Super Mario Bros. was written by hand in 6502 Assembler, there is little point in trying to have a Compiler like CC65 create a perfectly accurate Binary. The main goal is to have it work similar enough to the original game.

### Ports
I do plan having this transpilation run natively on PCs, so this is technically a Port as well, though it'll largely be targeting PCs alone. Other hardware will not be considered directly, but I'll still make an effort to keep the Code largely portable.

### Moddability
While I'd love to provide some kind of easy to use modding API, I simply don't know how I'd do this. Additionally, that just seems like a lot of extra work I don't have the time for. If anyone wants to make a moddable Fork to add mmo-style online multiplayer or whatever, go right ahead. Just please credit me.

# Acknowledgements
### What about the C++ Port by MitchellSternke?
[SuperMarioBros-C](https://github.com/MitchellSternke/SuperMarioBros-C/tree/master)

While this is a great 1:1 port of the game, it was made via automated methods, and mostly ends up reimplementating CPU Registers and similar. The goal of this transpilation is to reimagine the Code as a fully native C Program, and having the game run natively on the end-users hardware. 

### What about the C++ by Łykasz Jakowski?
[uMario_Jakowski](https://github.com/jakowskidev/uMario_Jakowski)

This is a Remake of the game, not using it's original source-code as a guideline.

# Building
As this is largely incomplete code, building for the sake of playing is quite pointless.
However, for those that want to contribute, any C99 compatible Compiler should suffice (at least until I've decided what graphics library I want to use for rendering the graphics).

Either way, in all likelyhood, you'll need an original Super Mario Bros. ROM. From this ROM I'll later provide scripts to extract the Character ROM, used by the games' graphics. These'll then be loaded into the game.

# Inspirations
- [zelda3 by snesrev](https://github.com/snesrev/zelda3)
- [The Legend of Zelda: Ocarina of Time Decompilation](https://github.com/zeldaret/oot)
- [Ship of Harkinian](https://www.shipofharkinian.com/)
- [Super Mario 64 Decompilation](https://github.com/n64decomp/sm64)

# License
[GNU GENERAL PUBLIC LICENSE v2](LICENSE)