MODE=Release

make:
	mkdir build || \
		cd ./build && \
		cmake .. && \
		cmake --build . --config $(MODE)

# clean build dir
clean:
	del /q /S build

# run the cmake executable
run:
	.\build\$(MODE)\HiveMindPS2.exe
