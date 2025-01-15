all:
	g++ -o main.o main.cpp src/session.cpp src/display.cpp src/inputs.cpp src/db_operations.cpp -lmysqlcppconn -lcrypto -L/usr/lib/x86_64-linux-gnu