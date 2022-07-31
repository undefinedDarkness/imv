build:
	g++ -g src/*.cpp -Isrc -lfltk_images -lfltk -lX11 -o app -Wall -fsanitize=address 