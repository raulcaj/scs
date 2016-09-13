all:
	gcc -Wall -g ./src/*.c ./3rd/sqlite3/*.c -ldl -lpthread -o scs
