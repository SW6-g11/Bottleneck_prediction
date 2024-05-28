# Bottleneck_prediction

## Windows
Running the program in Windows as opposed to [Linux and WSL](https://github.com/SW6-g11/Bottleneck_prediction/edit/main/README.md#linux-and-wsl) works with no defienciencies, but is more tedious to run:
 

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
