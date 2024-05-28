# Bottleneck_prediction

## Windows
Running the program in Windows as opposed to [Linux and WSL](https://github.com/SW6-g11/Bottleneck_prediction/edit/main/README.md#linux-and-wsl) works with no defienciencies, but is more tedious to run:
### Requirements
- QT Creator: https://www.qt.io/download
- Graphviz: https://graphviz.org/download/
- CMake: https://cmake.org/download/
- Visual Studio 2019 version: https://visualstudio.microsoft.com/vs/older-downloads/

### Running the program
- Clone this repo
- In CMake set the source code as the root directory of repo
- In CMake set the location to build binaries as root directory/build
- Press Configure
- Use Visual Studio 16 2019 as the generator
- Press Configure, Generate, and then Open Project
- In Visual Studio, set Network_Simulator as startup project
- Run the project

## Linux and WSL
Linux is the recommended way to run the program
### Requirements
Update repositories (Ubuntu/Debian): apt-get update
Update repositories (arch/yay): yay -Sy

Install the following in WSL or Linux:
- Graphviz:
  - Installation Command (Ubuntu/Debian): ```apt-get install graphviz```
  - Installation Command (arch/yay): ```yay -S graphwiz``` 
- libxslt:
  - Installation Command (Ubuntu/Debian): ```apt-get install libxslt1-dev```
  - Installation Command (arch/yay): ```yay -S libxslt1```
- QT:
  - Installation Command (Ubuntu/Debian): ```apt-get install qt6-default```
  - Installation Command (arch/yay): ```yay -S qt6-base```
### Running the program
- Clone this repo
- ```cd``` into the repo
- run ```./buildAndRun.sh```
