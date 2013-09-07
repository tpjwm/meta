/**
 * @file ngram_fw_tokenizer.cpp
 */

#include "io/parser.h"
#include "util/common.h"
#include "tokenizers/ngram/ngram_fw_tokenizer.h"

namespace meta {
namespace tokenizers {

using std::deque;
using std::string;
using std::unordered_map;
using std::unordered_set;
using index::document;
using io::parser;

ngram_fw_tokenizer::ngram_fw_tokenizer(size_t n):
    ngram_tokenizer(n),
    _function_words(unordered_set<string>())
{
    init_function_words();
}

void ngram_fw_tokenizer::tokenize_document(document & document,
        std::function<term_id(const std::string &)> mapping)
{
    parser parser(document.path() + ".sen", " \n");

    // initialize the ngram
    deque<string> ngram;
    for(size_t i = 0; i < n_value() && parser.has_next(); ++i)
    {
        string next = "";
        do
        {
            next = parser.next();
        } while(_function_words.find(next) == _function_words.end() && parser.has_next());
        ngram.push_back(next);
    }

    // add the rest of the ngrams
    while(parser.has_next())
    {
        string wordified = wordify(ngram);
        document.increment(mapping(wordified), 1);
        ngram.pop_front();
        string next = "";
        do
        {
            next = parser.next();
        } while(_function_words.find(next) == _function_words.end() && parser.has_next());
        ngram.push_back(next);
    }

    // add the last token
    document.increment(mapping(wordify(ngram)), 1);
}

void ngram_fw_tokenizer::init_function_words()
{
    auto config = common::read_config("config.toml");
    parser parser{ *cpptoml::get_as<std::string>( config, "function-words" ), " \n" };
    while(parser.has_next())
        _function_words.insert(parser.next());
}

}
}