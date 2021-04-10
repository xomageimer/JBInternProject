#include "Searcher.h"

#include <utility>

Searcher::Searcher(const std::string &file_name, std::ostream & Out) : Output(Out){
    file.open(file_name);
    if (!file.is_open())
        throw std::logic_error("Can't open file: " + file_name);
}

void Searcher::PrepareSource(ThreadPool &threadPool, const std::shared_ptr<class SearchPredicate>& predicate) {
    Broke = false;

    std::vector<std::future<void>> To_Wait;
    {
        std::vector<std::string> chunk;
        chunk.reserve(ChunkAvrSize);
        std::string word;
        size_t i = 0;
        while (getline(file, word)) {
            if (Broke)
                return;

            chunk.push_back(word);
            i++;
            if (i == ChunkAvrSize) {
                i = 0;
                To_Wait.push_back(threadPool.AddTask(&Searcher::Process, this, std::move(chunk), predicate));
                chunk.clear();
            }
        }
        if (i != 0) {
            To_Wait.push_back(threadPool.AddTask(&Searcher::Process, this, std::move(chunk), predicate));
        }
    }

    for (auto & fut : To_Wait)
        fut.get();
}

void Searcher::Process(std::vector<std::string> chunk, const std::shared_ptr<class SearchPredicate>& pred) {
    for (auto & el : chunk){
        if (Broke)
            return;

        if (pred->Compare(el))
            Write(std::move(el));
    }
    chunk.clear();
}

void Searcher::BrokeIt() {
    Broke = true;
}

bool DefaultSearch::Compare(std::string const & to_compare) {
    if (to_compare.find(compare_word) != std::string::npos)
        return true;
    return false;
}

bool ConsecutiveSearch::Compare(std::string const & to_compare) {
    size_t beg = 0;
    size_t i = 0;

    do {
        if (i >= compare_word.size())
            return true;
        beg = to_compare.find(compare_word[i++], beg);
    } while (beg != std::string::npos);

    return false;
}

void Searcher::Write(std::string word) {
    std::lock_guard lk(console_mut);
    Output << word << std::endl;
}