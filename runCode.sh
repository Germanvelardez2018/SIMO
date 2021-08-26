red=  `tput setaf 1`
blue=`tput setaf 4`   #2
reset=`tput sgr0`

#Run code in linux
echo "-----------------------------------"
echo "Author: German Velardez"
echo "Project Name: SIMO"
echo "-----------------------------------"

echo "-----------------------------------"
echo "Compiling project in build folder "
    cmake . -B ./build
echo "-----------------------------------"
echo "after that you introduce: ${blue} cd build  ${reset} "
echo "then introduce:           ${blue} make simo ${reset} "
echo "-----------------------------------"

echo  "Move the file called ${blue}simo.uf2${reset} to the raspberry pi pico"
echo "Dont forget to connect the board while holding pressing the boot botton"
echo "-----------------------------------"




