/**
 * @file depth_tokenizer.h
 *
 * All files in META are released under the MIT license. For more details,
 * consult the file LICENSE in the root of the project.
 *
 * @author Sean Massung
 * @author Chase Geigle
 */

#ifndef _META_TOKENIZERS_DEPTH_TOKENIZER_H_
#define _META_TOKENIZERS_DEPTH_TOKENIZER_H_

#include "tokenizers/tree/tree_tokenizer.h"

namespace meta {
namespace tokenizers {

/**
 * Tokenizes parse trees by extracting depth features.
 */
class depth_tokenizer : public tree_tokenizer<depth_tokenizer> {
    public:
        using mapping_fn = std::function<term_id(const std::string &)>;

        /**
         * Extracts the height of each parse tree.
         * @param document - the document to parse
         * @param tree - the current parse_tree in the document
         */
        void tree_tokenize(index::document & document,
                           const parse_tree & tree, 
                           mapping_fn mapping);
};

}
}

#endif