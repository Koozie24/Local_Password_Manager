all:
	g++ -o main.o main.cpp src/session.cpp src/display.cpp src/inputs.cpp -lmysqlcppconn -L/usr/lib/x86_64-linux-gnu