all: tcp udp


tcp: tcp_receiver tcp_sender

tcp_receiver: create_build_dir tcp_receiver.c
	gcc -o build/$@ tcp_receiver.c

tcp_sender: create_build_dir tcp_sender.c
	gcc -o build/$@ tcp_sender.c


udp: udp_receiver udp_sender

udp_receiver: create_build_dir udp_receiver.c
	gcc -o build/$@ udp_receiver.c

udp_sender: create_build_dir udp_sender.c
	gcc -o build/$@ udp_sender.c


create_build_dir:
	mkdir -p build

clean:
	rm -r build