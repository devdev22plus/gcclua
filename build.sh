# gcc -o test main.cpp -I./lua52/include/ -L./lua52/ ./lua52/liblua.a
# gcc -o test main.cpp -I./lua52/include/ -L./lua52/ -l:./lua52/liblua52.a
# gcc -o test main.cpp -I./lua54/include/ -L./lua54/ -l./lua54/liblua.a
gcc -o test main.cpp -lstdc++ -std=c++11 -I./lua54/include/ -L./lua54/ -llua -lm
# g++ -o test main.cpp -lstdc++ -std=c++11 -I./lua54/include/ -L./lua54/ -llua -lm
