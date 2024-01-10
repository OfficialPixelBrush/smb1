# SMB1PC
 This is a transpilation of Super Mario Bros. into C, aiming to port it natively to the PC.

# Progress
 Progress: 0.0%

# Goals
### Main Goal
The main goal is to have a functionally equivalent, portable Version of the original Super Mario Bros. for Microsoft Windows and Linux Computers.

### Accuracy
If possibly, I'd like to preserve as many glitches as possible, though some might disappear to make way for Quality of Life changes, such as an uncapped sprite limit or similar. I definitely want glitches like the Minus World or Wall-jumping to remain!

### Flexibility
While I want this to be a fairly accurate port, I want to liberate Super Mario Bros. of some of it's limitations, such as it's sprite, object or resolution limits.

# Non-Goals
### Getting a matching binary
Since the original Super Mario Bros. was written by hand in 6502 Assembler, there is little point in trying to have a Compiler like CC65 create a perfectly accurate Binary. The main goal is to have it work similar enough to the original game.

### Ports
I do plan on eventually taking this transpilation and forking a PC version out of it, with features like native widescreen, but that'll have to wait until the game is actually fully transpiled. For this I'll mostly be focusing my efforts on Windows and Linux PCs, alongside the Steam Deck, but I do not plan to make ports for systems like the Switch. That can be someone elses job!

### Moddability
While I'd love to provide some kind of easy to use modding API, I simply don't know how I'd do this. Additionally, that just seems like a lot of extra work I don't have the time for. If anyone wants to make a moddable Fork to add mmo-style online multiplayer or whatever, go right ahead. Just please credit me.

# Building (ideally)
1. Put your Super Mario Bros USA ROM into the root of the Directory.
2. Run `extract_assets.py`
3. Run `make`
4. The game can run without the ROM, so feel free to delete it
5. Have fun!