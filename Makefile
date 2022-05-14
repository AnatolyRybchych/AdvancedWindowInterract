
out     := run.exe

objects := build/obj/Main.o
objects += build/obj/GlobalWindowInput.o
objects += build/obj/Notifyicon.o
objects += build/obj/Window.o
objects += build/obj/AppNotifyicon.o
objects += build/obj/App.o
objects += build/obj/MainWindow.o
objects += build/obj/WindowParams.o
objects += build/obj/SwitchWindow.o
objects += build/obj/HorisontalStackPanel.o
objects += build/obj/ExternalAppNotifyicon.o
objects += build/obj/ExternalAppNotifyicons.o

build: $(objects) build/obj/resources.res
	g++ -mwindows -o build/$(out) $^ -lgdi32 -lgdiplus

run: build
	./build/$(out)

build/obj/%.o: src/%.cpp
	@mkdir -p ./build/obj
	g++ -c -o $@ $<

build/obj/resources.res: src/resources.rc
	windres $< -O coff -o $@

.PHONY: build run
