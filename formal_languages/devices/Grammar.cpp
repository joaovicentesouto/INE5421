#include "Grammar.hpp"

namespace formal_device
{
namespace grammar
{

Regular::set_type<Regular::string_type> Regular::sentences_generator(int n) const
{
    std::vector<SentencialForm> sentencial_forms{SentencialForm(m_initial_symbol, "&")};

    for (auto sentence: sentencial_forms) {
        if (sentence.is_sentence())
            continue;

        for (auto production: production_map_type(m_productions)[sentence.non_terminal()]) {
            SentencialForm new_form = production << sentence;
            if (new_form.sentence().size() <= n)
                sentencial_forms.push_back(new_form);
        }
    }

    set_type<string_type> sentences;

    for (auto sentence : sentencial_forms)
        if (sentence.is_sentence())
            if (sentence.sentence().size() == n)
                sentences.insert(sentence.sentence());

    return sentences;
}

}   // namespace grammar
}   // namespace formal_device
