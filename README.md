### Puzzle solver for https://yppedia.puzzlepirates.com/Patching
A basic solver which will calculate the best move (it thinks) using multi threaded random simulations to gather the longest path.

### Building
To build this you will need to run ```make``` within the root directory

### How to use
Inputting parameters into the program will appear to be complicated.
You will need to look at ```Definitions.hpp``` and lookup pieces of your board according to it to find the corresponding character representation.

For example, imagine you have the piece
![banner](http://i.imgur.com/dB3zN31.png)
This piece is considered a ```SPOOL_LEFT``` (read the comments and illustrations in ```Definitions.hpp```).

The define in ```Definitions.hpp``` tells us that this piece has a character representation of ```'A'```.
```
#define SPOOL_LEFT 0              // --0-      // A
```
Please note that the conversion from visual to textual can be quite confusing for the human brain the way I have done it so expect to make mistakes the first time you try to use this program.

Here is an example of parsing an entire board:
Visual representation
![banner](http://i.imgur.com/Jssxw37.jpg)

Character representation
```
IIIIIII
IOYPONI
IMPFZYI
INYPMAI
IYNONMI
IIIIIII
```

Program input
```
IIIIIIIIOYPONIIMPFZYIINYPMAIIYNONMIIIIIIII
```

Input to the program a series of 42 alphabetical characters to represent the board state.

The program will continuously apply random moves to find better solutions on the go and output them in the same format as input.

### Testing
Testing is currently in progress..
