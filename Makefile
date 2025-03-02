libfilehelper:
ifeq ($(OS),Windows_NT)
	@if not exist ./libs/libfilehelper.a ( \
		g++ -std=c++17 -O -c ./filehelper/filehelper.cpp -o filehelper.o && \
		ar rcs libfilehelper.a filehelper.o && \
		del /F /Q filehelper.o && \
		move libfilehelper.a libs\libfilehelper.a \
	)
else
	mkdir -p libs
	@if [ ! -f ./libs/libfilehelper.a ]; then \
		g++ -std=c++17 -O -c ./filehelper/filehelper.cpp -o filehelper.o && \
		ar rcs libfilehelper.a filehelper.o && \
		rm -f filehelper.o && \
		mv libfilehelper.a libs/; \
	fi
endif

libcatch:
ifeq ($(OS),Windows_NT)

	@if not exist ./libs/libcatch.a ( \
		g++ -std=c++17 -O -c ./catch/catch_amalgamated.cpp -o catch.o && \
		ar rcs libcatch.a catch.o && \
		del /F /Q catch.o && \
		move libcatch.a libs/libcatch.a \
	) else ( \
		echo "Compiled" \
	)
else
	mkdir -p libs
	@if [ ! -f ./libs/libcatch.a ]; then \
		g++ -std=c++17 -O -c ./catch/catch_amalgamated.cpp -o catch.o && \
		ar rcs libcatch.a catch.o && \
		rm -f catch.o && \
		mv libcatch.a libs/; \
	else \
		echo "Compiled"; \
	fi
endif


libs: libcatch libfilehelper

test: libs
ifeq ($(OS),Windows_NT)
	g++ -std=c++17 test.cpp -Ifilehlper -Icatch -Llibs -lfilehelper -lcatch -lssl -lcrypto -o test.exe
	.\test.exe
else
	g++ -std=c++17 test.cpp -Ifilehlper -Icatch -Llibs -lfilehelper -lcatch -lssl -lcrypto -o test.out
	./test.out
endif

build: libfilehelper
ifeq ($(OS),Windows_NT)
	g++ -std=c++17 main.cpp -Ifilehelper -Llibs -lfilehelper -lssl -lcrypto -o main.exe -Wno-unused-parameter
else
	g++ -std=c++17 main.cpp -Ifilehelper -Llibs -lfilehelper -lssl -lcrypto -o main.out -Wno-unused-parameter
endif

run: build
ifeq ($(OS),Windows_NT)
	.\main.exe
else
	./main.out
endif

clean:
ifeq ($(OS),Windows_NT)
	del /F /Q main.exe
	del /F /Q libs
else
	rm -f main.o
	mr -f ./libs
endif
