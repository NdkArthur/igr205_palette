# Playful Palette
## Building

Most of the dependencies are managed using git submodule.
To initialize the submodules and fetch the appropriate commit use :

```
    $ git submodule init
    $ git submodule update
```

Or directly clone the repository with the submodule using :

```
    git clone --recurse-submodules git@gitlab.com:tlambert/playful-palette.git
```

Then to build the application
```
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make
	$ ./viewer
```

On Windows with visual studio 2017, File->Open->CMake and then select the CMakeLists.txt at the root of the project.
Once cmake configuration done choose viewer.exe as startup item.