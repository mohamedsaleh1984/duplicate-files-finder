libfinder:
	$(info    Building libfinder)
ifeq ($(OS),Windows_NT)
	@if not exist libs mkdir libs
	@if not exist ./libs/libfinder.a ( \
		g++ -std=c++17 -O -c ./finder/finder.cpp -o finder.o && \
		ar rcs libfinder.a finder.o && \
		del /F /Q finder.o && \
		move libfinder.a libs\libfinder.a \
	) else ( \
		echo "nothing to do"; \
	)
else
	$(info    Building libfinder linux)
	@if [ ! -f ./libs/libfinder.a ]; then \
		mkdir -p libs && \
		g++ -std=c++17 -O -c ./finder/finder.cpp -o finder.o && \
		ar rcs libfinder.a finder.o && \
		rm -f finder.o && \
		mv libfinder.a libs/ ; \
	else \
		echo "nothing to do";\
	fi
endif

libcatch:
	$(info    Building libcatch)
ifeq ($(OS),Windows_NT)
	
	@if not exist ./libs/libcatch.a ( \
		g++ -std=c++17 -O -c ./catch/catch_amalgamated.cpp -o catch.o && \
		ar rcs libcatch.a catch.o && \
		del /F /Q catch.o && \
		move libcatch.a libs/libcatch.a \
	) else ( \
		echo "nothing to do" \
	)
else
	mkdir -p libs
	@if [ ! -f ./libs/libcatch.a ]; then \
		g++ -std=c++17 -O -c ./catch/catch_amalgamated.cpp -o catch.o && \
		ar rcs libcatch.a catch.o && \
		rm -f catch.o && \
		mv libcatch.a libs/; \
	else \
		echo "nothing to do"; \
	fi
endif

libxxhash:
	$(info    Building xxhash)
ifeq ($(OS),Windows_NT)
	
	@if not exist ./libs/libxxhash.a ( \
		g++ -std=c++17 -O -c ./xxhash/xxhash.c -o xxhash.o && \
		ar rcs libxxhash.a xxhash.o && \
		del /F /Q xxhash.o && \
		move libxxhash.a libs/libxxhash.a \
	) else ( \
		echo "nothing to do"; \
	)
else
	mkdir -p libs
	@if [ ! -f ./libs/libxxhash.a ]; then \
		g++ -std=c++17 -O -c ./xxhash/xxhash.c -o xxhash.o && \
		ar rcs libxxhash.a xxhash.o && \
		rm -f xxhash.o && \
		mv libxxhash.a libs/; \
	else \
		echo "nothing to do"; \
	fi
endif


libs: libcatch libfinder libxxhash

test: libs
	$(info    Test Build)
ifeq ($(OS),Windows_NT)
	g++ -std=c++17 test.cpp -Ifilehlper -Icatch -Llibs -lfinder -lcatch  -lxxhash -o test.exe
	$(info    Test Run)
	.\test.exe
else
	g++ -std=c++17 test.cpp -Ifilehlper -Icatch -Llibs -lfinder -lcatch -lxxhash -o test.out
	./test.out
endif

build: clean libfinder libxxhash
	$(info    Binary build)
ifeq ($(OS),Windows_NT)
	g++ -std=c++17 main.cpp -Ifinder -Llibs -lfinder -lxxhash -o main.exe -Wno-unused-parameter -Wno-deprecated-declarations
else
	g++ -std=c++17 main.cpp -Ifinder -Llibs -lfinder -lxxhash.a -o main.out -Wno-unused-parameter -Wdeprecated-declarations
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
	rm -r -f ./libs
endif




