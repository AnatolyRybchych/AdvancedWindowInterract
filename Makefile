
out     := run.exe

objects := build/obj/Main.o
objects += build/obj/GlobalWindowInput.o
objects += build/obj/Notifyicon.o
objects += build/obj/Window.o
objects += build/obj/AppNotifyicon.o
objects += build/obj/App.o
objects += build/obj/MainWindow.o
objects += build/obj/WindowParams.o

build: $(objects)
	g++ -o build/$(out) $^ -lgdi32

run: build
	./build/$(out)

build/obj/%.o: src/%.cpp
	g++ -c -o $@ $<

.PHONY: build run
