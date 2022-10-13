target1 = hello_server
target2 = hello_client
objects = hello_server.o hello_client.o

all: $(target1) $(target2)

$(target1): hello_server.o
	cc -o $@ $^ -Wall

$(target2): hello_client.o
	cc -o $@ $^ -Wall

hello_server.o: hello_server.c
hello_client.o: hello_client.c

.PHONY: clean
clean:
	$(RM) $(target1) $(target2) $(objects)
