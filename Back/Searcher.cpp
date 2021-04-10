#include "Searcher.h"

#include <utility>

Searcher::Searcher(const std::string &file_name, wxTextCtrl * Out, wxStatusBar * Status) : Output(Out), statusBar(Status){
    file.open(file_name);
    if (!file.is_open())
        throw std::logic_error("Can't open file: " + file_name);
}

void Searcher::PrepareSource(ThreadPool &threadPool, const std::shared_ptr<class SearchPredicate>& predicate) {
    file.clear();
    file.seekg(0);

    threadPool.AddTask([this, &threadPool, predicate] {
           while (threadPool.WorkersCount() != 1) {
               std::this_thread::yield();
               if (!Output->IsEmpty())
                   Output->Clear();
           }
        statusBar->SetStatusText("Searching...");
        Broke = false;
        process_count++;
//        std::vector<std::future<void>> To_Wait;
//        {
            std::vector<std::string> chunk;
            chunk.reserve(ChunkAvrSize);
            std::string word;
            size_t i = 0;
            while (getline(file, word)) {
                if (Broke) {
                    process_count--;
                    if (!process_count)
                        statusBar->SetStatusText("Ready!");
                    return;
                }

                chunk.push_back(word);
                i++;
                if (i == ChunkAvrSize) {
                    i = 0;
                    threadPool.AddTask(&Searcher::Process, this, std::move(chunk), predicate);
                    chunk.clear();
                }
            }
            if (i != 0) {
                threadPool.AddTask(&Searcher::Process, this, std::move(chunk), predicate);
            }
//        }
        process_count--;
        if (!process_count)
            statusBar->SetStatusText("Ready!");

//        for (auto &fut : To_Wait)
//            fut.get();

//        statusBar->SetStatusText("Ready!");
    });
}

void Searcher::Process(std::vector<std::string> chunk, const std::shared_ptr<class SearchPredicate>& pred) {
    process_count++;
    for (auto & el : chunk){
        if (Broke) {
            process_count--;
            if (!process_count)
                statusBar->SetStatusText("Ready!");
            return;
        }

        if (pred->Compare(el))
            Write(el);
    }
    chunk.clear();
    process_count--;
    if (!process_count)
        statusBar->SetStatusText("Ready!");
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

void Searcher::Write(std::string const & word) {
    std::lock_guard lk(console_mut);
    Output->AppendText(word + " ");
}