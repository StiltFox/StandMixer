# Stilt Fox&reg; Stand Mixer
Stilt Fox&reg; Stand Mixer is a C++ library made with the aim of making binary operations easy. While libraries for 
these tools may already exist, a lot of them are obtuse to use and require a significant amount of code. Instead of 
setting up a context, reading a digest ect... ect... ect... why not just call `sha256(value);` and be done with it? This
project is part of the effort to make Stilt Fox&reg; Universal Library into smaller more modular pieces. It is 
recommended that you use this library instead of the functions in Stilt Fox&reg; Universal Library.

## Legal Stuff
Stilt Fox&reg; is not liable for any damages done to your hardware. For more information see LICENSE file.\
Stilt Fox&reg; is trademarked. You may not use the Stilt Fox&reg; name, however this code is free to reference and use.\
You may contribute to this library, however all contributions will share the same license as this library and you agree 
that Stilt Fox&reg; owns the copyright for any contributions.

------------------------------------------------------------------------------------------------------------------------
## Important!
These instructions assume you are using a Linux based operating system to compile the code. No testing or compiling
has been performed on Windows by Stilt Fox&reg;. If you choose to use Windows as your main development platform you are
on your own. If you have a strong desire to use Stilt Fox&reg; libraries and products, switching to Linux is highly
recommended.

With The death of Windows 10 (as of the time of writing this) directly around the corner, the roadmap to support Windows
systems has been completely canceled.
------------------------------------------------------------------------------------------------------------------------
## Prerequisites
### Main Program
- CMake
  - version 3.5.0 or greater
- C++ compiler
  - must support C++ version 20 or higher
  - We at Stilt Fox&reg; use g++
- Crypto++
  - Arch `sudo pacman -S crypto++`
  - ubuntu `sudo apt install libcrypto++-dev`
  - download directly [here](https://cryptopp.com/#download)

### Test Suite
- GTest
    - This is only required for unit testing, and can be skipped
        - To skip, use the `SFSkipTesting=true` option when compiling
    - You can obtain GTest by using `sudo apt install libgtest-dev`
        - if you are not running debian based linux, or are allergic to apt... it can be found [here](https://github.com/google/googletest)
        - Arch `sudo pacman -S gtest`

## Installation
### Linux
The following commands will install the libraries to your system. These will exist globally to all users. If you wish to
install for a single user, please adjust accordingly. Also, you will require sudo privileges to run the 
`cmake --install .` command.

```bash
mkdir build
cd build
cmake -DSFSkipTesting=true -DCMAKE_BUILD_TYPE=Release .. 
cmake --build .
cmake --install .
cd ..
```
### Mac
Mac installation works basically the same as linux, but you will need to include the toolchain file 
[mac.cmake](mac.cmake).

```shell
mkdir build
cd build
cmake -DSFSkipTesting=true -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=../mac.cmake .. 
cmake --build .
cmake --install .
cd ..
```
### Installing without sudo privileges
up and to this point we've been assuming you have sudo privileges and are able to install libraries 'system-wide'. If
for some reason you dont have access to `/usr/local` we can instead install to the home directory.

In linux you should have a folder called `.local`. You can install the files here using the following command in place
of the normal installation command: `cmake --install . --prefix ${HOME}/.local`.

On Mac, you would have a `Libraries` folder. Similar to Linux, you can use the following command instead of the normal
installation command: `cmake --install . --prefix ${HOME}/Libraries`.

Doing this will cause problems when CMake needs to find one of these packages. `find_package(StandMixer REQUIRED)` will 
fail without help. To fix this we need to tell cmake where to find the cmake configuration files. To do this we will add
the following line to our `~/.bashrc` file, or however you persist environment variables:
`export StandMixer_DIR=${HOME}/.local/Stilt_Fox/DialUp`.

**NOTE:** The path provided above could be wrong. You will ned to find where the cmake config file is installed on your
machine.

## Linking to Stilt Fox&reg; Stand Mixer
Linking to Stilt Fox&reg; Stand Mixer is easy. In your CMakeLists.txt file include the following line:\
`find_package(StandMixer)`\
then to link to your project use the following line:\
`target_link_libraries(MyProject StiltFox::StandMixer::Hash)`\
please notice that each module you want to link must be linked separately as shown above. There is no way to just 
include all modules. This allows you to include only what you need in your build.

## Tutorials and Examples
If you want to see the classes of Stilt Fox&reg; Storage Shed in action, feel free to check out the 
[test folder](src/test). All public methods are thoroughly unit tested, and also demonstrate intended usage of the 
classes.

## Helper Scripts
Due to the complexity of compiling for multiple systems, a .sh file was created for each tested system to simply run the 
unit tests. If all prerequisites are installed, these scripts should run without error. They use relative paths so 
caution should be used when executing them. Be sure to execute them from the project root like so:\
`./helper_scripts/linux_run_tests.sh`