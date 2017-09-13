connect4: main.cpp win.cpp eval.cpp minmax.cpp
        g++ -O main.cpp win.cpp eval.cpp minmax.cpp -o connect4

win.cpp: genwin.cpp
        g++ genwin.cpp
        ./a.out

eval.cpp: geneval.cpp
        g++ geneval.cpp
        ./a.out

minmax.cpp: genminmax.cpp
        g++ genminmax.cpp
        ./a.out

clean:
        rm a.out connect4 win.cpp eval.cpp minmax.cpp
