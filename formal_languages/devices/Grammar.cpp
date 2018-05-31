#include "Grammar.hpp"

namespace formal_device
{
namespace grammar
{

const Regular::vocabulary_set_type& Regular::vn() const
{
    return m_vn;
}

const Regular::vocabulary_set_type& Regular::vt() const
{
    return m_vt;
}

const Regular::production_map_type& Regular::productions() const
{
    return m_productions;
}

const Regular::symbol_type& Regular::initial_symbol() const
{
    return m_initial_symbol;
}

Regular::string_type Regular::to_string() const
{
    string_type string;
    string = m_initial_symbol.value() + " -> ";

    auto productions(m_productions);

    int i = productions[m_initial_symbol].size();
    for (auto production : productions[m_initial_symbol])
    {
        if (production->is_terminal())
            string += " " + production->to_string() + " ";
        else
            string += production->to_string();

        if (--i > 0)
            string += " | ";
    }

    string += "\n";

    for (auto non_terminal : m_vn)
    {
        if (non_terminal == m_initial_symbol)
            continue;

        string += non_terminal.value() + " -> ";

        i = productions[non_terminal].size();
        for (auto production : productions[non_terminal])
        {
            if (production->is_terminal())
                string += " " + production->to_string() + " ";
            else
                string += production->to_string();

            if (--i > 0)
                string += " | ";
        }
        string += "\n";
    }

    return string;
}

Regular::set_type<Regular::string_type> Regular::sentences_generator(int n) const
{
    container_type<SentencialForm> sentencial_forms{SentencialForm(m_initial_symbol, "&")};

    int current_size = 0;
    while (current_size < sentencial_forms.size())
    {
        auto sentence = sentencial_forms[current_size++];

        if (sentence.is_sentence())
            continue;

        production_map_type productions(m_productions);
        for (auto production: productions[sentence.non_terminal()]) {
            if (!production.get())
                continue;

            SentencialForm new_form = production << sentence;
            if (new_form.sentence().size() <= n)
                sentencial_forms.push_back(new_form);
            else if (n == 0)
                if (new_form.sentence() == "&")
                    sentencial_forms.push_back(new_form);
        }
    }

    set_type<string_type> sentences;

    for (auto sentence : sentencial_forms)
        if (sentence.is_sentence())
            if ((sentence.sentence().size() == n && sentence.sentence() != "&")
                                      || (n == 0 && sentence.sentence() == "&"))
                sentences.insert(sentence.sentence());

    return sentences;
}

bool Regular::operator==(const Regular &regular) const
{
    return m_vn             == regular.m_vn
        && m_vt             == regular.m_vt
        && m_productions    == regular.m_productions
        && m_initial_symbol == regular.m_initial_symbol;
}

}   // namespace grammar
}   // namespace formal_device
