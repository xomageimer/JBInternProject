#include <iostream>

// git submodule update --init --recursive
// C:\TDM-GCC-64\bin\mingw32-make -j4 -f makefile.gcc BUILD=release SHARED=0 UNICODE=1 setup_h
// C:\TDM-GCC-64\bin\mingw32-make -j4 -f makefile.gcc BUILD=release SHARED=0 UNICODE=1

#include "Back/Searcher.h"
#include <memory>
#include "Back/ThreadPool.h"

int main(){
    Searcher search("words.txt");
    ThreadPool tp (7);
    search.PrepareSource(tp, std::make_shared<ConsecutiveSearch>("cat"));

    return 0;
}