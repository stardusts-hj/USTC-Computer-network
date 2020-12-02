all: tcp 


tcp: server client

server: create_build_dir server.c
	gcc -pthread -o build/$@ server.c

client: create_build_dir client.c
	gcc -pthread -o build/$@ client.c

create_build_dir:
	mkdir -p build

clean:
	rm -r build