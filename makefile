all:
	g++ -o main.o main.cpp session.cpp -lmysqlcppconn -L/usr/lib/x86_64-linux-gnu