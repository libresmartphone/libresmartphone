CFLAGS=  $(shell curl-config --libs)
all:
	gcc main.c request.c $(CFLAGS) -o client