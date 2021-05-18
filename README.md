# OOPGame

## Abstract

This is a demonstration of my design / development / algorithmic capabilities.  
Hope you'll that find my skill are up to the task :nerd_face:

I used CMakeLists.  
Hence the following instructions:  

* Inside this CMakeLists there are 2 variable's:
  
  * **ShowDebugMap** - Setting this flag will show a snapshot of the game each turn,Also it'll show tha canning of neighbors for each pawn.Note: This will slow down the game. Commenting this line will make the game run faster.

  * **UtiliseBonus** - Setting this flag will change the pawn targeting system according to given optional bonus.  
  **Note** Setting this variable to true - may cause the game to never end (thus triggering the maximum turns breakout)
  
## Usage

 ```shell
 # Compile
 cd ~/<path-to-project>/Game
 mkdir build && cd build
 cmake .. && make -j

# Run the executable
~/<path-to-project>/Game/Game
 ```

## Using Doxygen (Recommended)

Assuming *Doxygen* installed.

1. ```shell
   cd ~/<path-to-project>/Game/docs
   export PATH_TO_GAME=<path-to-project> && doxygen Game # Example: export PATH_TO_GAME=/home/gal/dev/ && doxygen Game
   ```

2. Drag the `<path-to-project>/docs/doxygen/html/index.html` file to your favorite browser.

### Dependencies

* OpenCV (Any version)

### Notes

* The game will run for a maximum amount of **300** turns.
  
* If there's a situation where theres 2 pawns, 1 of each side. And they are not suppose to reach each other (i.e their targetLocation is different). Than they will move randomly on the map until they kill each other or until the game reaches **300** turns. At that case, the **defence** have **won!**

* If no pawn left on the map - it means all pawns have died, than **Offense** have **won!**
