#include "Grammar.hpp"

namespace formal_device
{
namespace grammar
{

Regular::set_type<Regular::string_type> Regular::sentences_generator(int n) const
{
    std::vector<SentencialForm> sentencial_forms{SentencialForm(m_initial_symbol, "&")};

    int current_size = 0;
    while (current_size < sentencial_forms.size())
    {
        auto sentence = sentencial_forms[current_size++];

        if (sentence.is_sentence())
            continue;

        production_map_type copy(m_productions);
        for (auto production: copy[sentence.non_terminal()]) {
            if (!production.get())
                continue;

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

bool Regular::operator==(const Regular &regular)
{
    return m_vn == regular.m_vn &&
           m_vt == regular.m_vt &&
           m_productions == regular.m_productions &&
           m_initial_symbol == regular.m_initial_symbol;
}

}   // namespace grammar
}   // namespace formal_device
