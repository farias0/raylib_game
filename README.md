## Dependencies:

### Raylib

https://github.com/raysan5/raylib

Compile and install it as a shared library, or use a package manager.

Example of building and installing it on Linux:

```
git clone https://github.com/raysan5/raylib.git raylib
cd raylib
mkdir build && cd build
cmake -DBUILD_SHARED_LIBS=ON ..     # REMEMBER TO INCLUDE SHARED LIBRARY DEPENDENCIES
make
sudo make install
```

**PROTIP**: To uninstall a lib installed with `make install` that doesn't contain a `make uninstall` rule (like raylib), create and install a .deb of it using `checkinstall`, and then uninstall it. https://stackoverflow.com/questions/1439950/whats-the-opposite-of-make-install-i-e-how-do-you-uninstall-a-library-in-li