linux:
	g++ ./src/*.cpp -O2 -o build.out -Wall -Wno-missing-braces -I ./include/ -L ./lib/linux -lraylib
	mv -rf ./ressources ./build/linux/ressources
	mv ./build.out ./build/linux/build.out
windows:
	g++ ./src/*.cpp -O2 -o build.exe -Wall -Wno-missing-braces -I ./include/ -L ./lib/win -lraylib -lopengl32 -lgdi32 -lwinmm
	Xcopy /E /I .\ressources .\build\windows\ressources
	move .\build.exe .\build\windows