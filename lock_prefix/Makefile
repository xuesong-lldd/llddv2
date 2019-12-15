target:=main
$(target):main.cpp 
	g++ -ggdb3 -O0 -std=c++11 -Wall -Wextra -pedantic -o $@ $< -pthread
clean:
	rm -f $(target)
