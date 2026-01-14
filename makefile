all:
	g++ -o main.o src/main.cpp src/session.cpp src/display.cpp src/inputs.cpp src/db_operations.cpp src/user.cpp -lmysqlcppconn -lcrypto -L/usr/lib/x86_64-linux-gnu