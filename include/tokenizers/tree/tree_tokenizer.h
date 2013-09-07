/**
 * @file tree_tokenizer.h
 *
 * All files in META are released under the MIT license. For more details,
 * consult the file LICENSE in the root of the project.
 *
 * @author Sean Massung
 * @author Chase Geigle
 */

#ifndef _TREE_TOKENIZER_H_
#define _TREE_TOKENIZER_H_

#include <string>
#include <memory>
#include <unordered_map>
#include "tokenizers/tokenizer.h"
#include "tokenizers/tree/parse_tree.h"
#include "index/document.h"

namespace meta {
namespace tokenizers {

/**
 * Tokenizes parse trees with various methods.
 */
template <class DerivedTokenizer>
class tree_tokenizer: public tokenizer
{
    public:
        /**
         * Tokenizes a file into a document.
         * @param document - the document to store the tokenized information in
         */
        void tokenize_document(index::document & document,
                std::function<term_id(const std::string &)> mapping)
        {
            std::vector<parse_tree> trees =
                parse_tree::get_trees( document.path() + ".tree" );
            for( auto & tree : trees )
                derived().tree_tokenize( document, tree, mapping);
        }

    private:
        /**
         * Convenience method to obtain this tokenizer as its derived
         * class.
         */
        DerivedTokenizer & derived()
        {
            return static_cast<DerivedTokenizer &>( *this );
        }
};

}
}

#endif