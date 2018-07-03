g++ -std=c++11 p_gen.cpp -o p_gen
g++ -std=c++11 generator.cpp -o generator
g++ -std=c++11 encoder.cpp -o encoder
g++ -std=c++11 decoder.cpp -o decoder

for i in {1..1000}
    do    ./p_gen | ./generator | ./encoder | ./decoder
    done
