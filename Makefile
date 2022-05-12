
out		:= run.exe

objects	:= build/obj/Main.o
objects	+= build/obj/GlobalWindowInput.o

build: $(objects)
	g++ -o build/$(out) $^

run: build
	./build/$(out)

build/obj/%.o: src/%.cpp
	g++ -c -o $@ $<



.PHONY: build run