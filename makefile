#Author: Justin Cain @AffinityForFun
CC			= g++
FLAGS		= -Wall -std=c++11


final : resourcemanager main
	$(CC) $(FLAGS) main.o ResourceManager.o -o ResourceManager

main : 
	$(CC) $(FLAGS) -c main.cpp
	
resourcemanager :
	$(CC) $(FLAGS) -c ResourceManager.cpp

	
remake : clear final

clear : clean
	clear
	
clean :
	rm -f ./ResourceManager ResourceManager.o main.o
	

