
out		:= run.exe

objects	:= build/obj/Main.o
objects	+= build/obj/GlobalWindowInput.o
objects	+= build/obj/TrayWindow.o
objects	+= build/obj/Window.o

build: $(objects)
	g++ -o build/$(out) $^ -lgdi32

run: build
	./build/$(out)

build/obj/%.o: src/%.cpp
	g++ -c -o $@ $<



.PHONY: build run