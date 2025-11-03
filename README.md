Steps for running code:

1. Clone repository from github on CLion
2. Download latest stable version of SFML (3.0.2) and place in the correct file to work with CLion:
   https://www.sfml-dev.org/download/sfml/3.0.2/
3. Make sure your compiler version matches (WinLibs UCRT 14.2.0) which can be found in the same link as above
4. Change the settings in CLion to work with the downloaded compiler (found in Settings>Build, Execution, 
   Deployment>Toolchains)
** I also had to add an environmental variable to my computer under Path in system variables (I believe this was 
   because the program needed the matching DLLs from the SFML installation in the build directory):
      C:\SFML-3.0.2-windows-gcc-14.2.0-mingw-64-bit\SFML-3.0.2\bin
5. Run the project file 'Project2DSA'

Some issues you might run into:
Different group members had to change the location of certain files for it to work. The version on the git 
repository has the star data file '1761687300163O-result.csv' and the ttf 'OpenSans.ttf' in the cmake-build-debug 
file. That worked on two out of three members computers, while the third member had to place the ttf in resources 
while the star data file had to be moved to the general Project2DSA folder. Change file paths in code to match the 
changed location if needed.
