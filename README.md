# Space Invaders Clone

## Observations

* The game should be ran from the `build` directory. Currently, all paths are relative to it (technically, from a directory one level above the project base dir). We should look into using absolute paths, while keeping in mind that OS-agnostic paths might be a problem.

## Dependencies

### Raylib

[Github](https://github.com/raysan5/raylib)

For Linux, compile and install it as a shared library, or use a package manager. Example:

```
git clone https://github.com/raysan5/raylib.git raylib
cd raylib
mkdir build && cd build
cmake -DBUILD_SHARED_LIBS=ON ..     # REMEMBER TO INCLUDE SHARED LIBRARY DEPENDENCIES
make
sudo make install
```

**PROTIP**: To uninstall a lib installed with `make install` that doesn't contain a `make uninstall` rule (like raylib), create and install a .deb of it using `checkinstall`, and then uninstall it. ([StackOverflow](https://stackoverflow.com/questions/1439950/whats-the-opposite-of-make-install-i-e-how-do-you-uninstall-a-library-in-li))


I still haven't managed to properly set up the project on Windows. Ideally it would use raylib as a shared library to keep consistency with Linux, but it seems it will have to be added to the project structure. Meanwhile the game can be compiled and ran through WSL2 with no issues.

## Assets

### Space Eaters! Asset Pack

[itch.io](https://cluly.itch.io/space-eaters/download/eyJleHBpcmVzIjoxNjkwNzcwNDU1LCJpZCI6NTIyMDM1fQ%3d%3d%2eUSTlqOsYFu9kOJUnZIM2oTVyXwg%3d)