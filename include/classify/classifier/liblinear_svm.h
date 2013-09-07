/**
 * @file liblinear_svm.h
 * @author Sean Massung
 *
 * All files in META are released under the MIT license. For more details,
 * consult the file LICENSE in the root of the project.
 */

#ifndef _LIBLINEAR_SVM_H_
#define _LIBLINEAR_SVM_H_

#include "classify/classifier/classifier.h"
#include "index/forward_index.h"
#include "meta.h"

namespace meta {
namespace classify {

/**
 * Wrapper class for liblinear (http://www.csie.ntu.edu.tw/~cjlin/liblinear/)
 * implementation of support vector machine classification.
 */
class liblinear_svm: public classifier<index::forward_index>
{
    public:

        /**
         * Constructor.
         * @param idx The index to run the classifier on
         * @param liblinear_path The path to the liblinear library
         */
        liblinear_svm(index::forward_index & idx, const std::string & liblinear_path);

        /**
         * Classifies a document into a specific group, as determined by
         * training data.
         * @param doc The document to classify
         * @return the class it belongs to
         */
        class_label classify(doc_id d_id) override;

        /**
         * Creates a classification model based on training documents.
         * @param docs The training documents
         */
        void train(const std::vector<doc_id> & docs) override;

        /**
         * Classifies a collection document into specific groups, as determined
         * by training data; this function will make repeated calls to
         * classify().
         * @param docs The documents to classify
         * @return a confusion_matrix detailing the performance of the
         * classifier
         */
        confusion_matrix test(const std::vector<doc_id> & docs) override;

        /**
         * Clears any learned data from this classifier.
         */
        void reset() override;

    private:

        /** the path to the liblinear library */
        const std::string _liblinear_path;
};

}
}

#endif