CFLAGS = -g -O4 -Wall -Wextra -pedantic

test:
	g++ $(CFLAGS) -ldl test.cpp -o test_exec
	./test_exec
	rm -rf test_exec

test_checkmem:
	g++ $(CFLAGS) -ldl test.cpp -o test_exec
	valgrind --leak-check=summary ./test_exec
	rm -rf test_exec
