#ifndef JBINTERNPROJECT_SEARCHER_H
#define JBINTERNPROJECT_SEARCHER_H

#include <fstream>
#include <iostream>
#include <string>
#include <utility>

#include "ThreadPool.h"

//#include <wx/textctrl.h>

class Searcher {
public:
    explicit Searcher(std::string const & file_name, std::ostream & Out = std::cout);
    void PrepareSource(ThreadPool & threadPool, const std::shared_ptr<class SearchPredicate>&);
    void BrokeIt();
    void Write(std::string word);
private:
    void Process(std::vector<std::string> chunk, const std::shared_ptr<class SearchPredicate>&);

    std::mutex console_mut;
    std::ostream & Output;

    std::fstream file;
    size_t const ChunkAvrSize = 500;
    std::atomic_bool Broke = false;
};

class SearchPredicate {
public:
    explicit SearchPredicate(std::string word) : compare_word(std::move(word))  {};
//    explicit SearchPredicate(std::string word, wxTextCtrl * Out) : compare_word(std::move(word)), Output(Out) {};
    virtual bool Compare(std::string const & to_compare) = 0;
protected:
    std::string compare_word;
    // wxTextCtrl *& Output;
};

class DefaultSearch : public SearchPredicate {
public:
    explicit DefaultSearch(std::string word) : SearchPredicate(std::move(word)) {};
    virtual bool Compare(std::string const & to_compare) override;
};

class ConsecutiveSearch : public SearchPredicate {
public:
    explicit ConsecutiveSearch(std::string word) : SearchPredicate(std::move(word)) {};
    virtual bool Compare(std::string const & to_compare) override;
};


#endif //JBINTERNPROJECT_SEARCHER_H
