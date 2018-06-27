#include "Grammar.hpp"

namespace formal_device
{
namespace grammar
{

ContextFree::ContextFree()
{
    calculate_first();
    calculate_follow();
}

const ContextFree::non_terminal_set_type &ContextFree::vn() const
{
    return m_vn;
}

const ContextFree::terminal_set_type &ContextFree::vt() const
{
    return m_vt;
}

const ContextFree::production_map_type &ContextFree::productions() const
{
    return m_productions;
}

const ContextFree::non_terminal_symbol_type &ContextFree::initial_symbol() const
{
    return m_initial_symbol;
}

ContextFree::first_map_type ContextFree::first() const
{
    return m_first;
}

ContextFree::follow_map_type ContextFree::follow() const
{
    return m_follow;
}

ContextFree::first_nt_map_type ContextFree::first_nt() const
{
    return m_first_nt;
}

bool ContextFree::operator==(const ContextFree &another) const
{
    return m_vn             == another.m_vn
        && m_vt             == another.m_vt
        && m_productions    == another.m_productions
        && m_initial_symbol == another.m_initial_symbol;
}

bool ContextFree::operator!=(const ContextFree &another) const
{
    return m_vn             != another.m_vn
        || m_vt             != another.m_vt
        || m_productions    != another.m_productions
        || m_initial_symbol != another.m_initial_symbol;
}

bool ContextFree::operator<(const ContextFree &another) const
{
    return to_string() < another.to_string();
}

template<class T, class V>
bool contains(const ContextFree::set_type<T>& set, const V& value)
{
    auto value_cast = dynamic_cast<const T*>(&value);

    if (!value_cast)
        return false;

    return set.find(*value_cast) != set.end();
}

void ContextFree::calculate_first()
{
    //! Follows algorithm seen in class, in particular,
    //! first-NT construction is done together.

    //! Step 1
    for (const auto& symbol : m_vt)
    {
        symbol_ptr_type ptr{new terminal_symbol_type(symbol)};
        m_first[ptr] = {symbol};
    }

    //! Step 2
    for (const auto& symbol : m_vn)
    {
        m_first_nt[symbol];
        symbol_ptr_type ptr{new non_terminal_symbol_type(symbol)};
        m_first[ptr];

        production_map_type copy(m_productions);
        for (const auto& prod : copy[symbol])
            if (prod[0]->is_terminal())
                m_first[ptr].insert(terminal_symbol_type(prod[0]->value()));
    }

    first_map_type previous;

    //! Step 3
    while (m_first != previous)
    {
        previous = m_first;

        for (const auto& symbol : m_vn)
        {
            symbol_ptr_type source{new non_terminal_symbol_type(symbol)};

            production_map_type copy(m_productions);
            for (const auto& prod : copy[symbol])
            {
                int i = 0;
                for (const auto& target : prod)
                {
                    if (target->is_terminal())
                    {
                        m_first[source].insert(terminal_symbol_type(target->value()));
                        break;
                    }
                    else
                    {
                        //! Create first-NT
                        m_first_nt[symbol].insert(non_terminal_symbol_type(target->value()));

                        for (const auto& first_target : m_first[target])
                            if (first_target != terminal_symbol_type("&"))
                                m_first[source].insert(first_target);

                        if (!contains(m_first[target], terminal_symbol_type("&")))
                            break;
                    }
                    i++;
                }

                if (i == prod.size())
                    m_first[source].insert(terminal_symbol_type("&"));
            }
        }
    }
}

void ContextFree::calculate_follow()
{
    //! Follows algorithm seen in class

    //! Step 1
    m_follow[m_initial_symbol] = {terminal_symbol_type("$")};

    //! Step 2
    for (const auto& pair : m_productions)
        for (const auto& prod : pair.second)
            for (int i = 0; i < prod.size(); ++i)
            {
                if (!prod[i]->is_terminal())
                {
                    auto non_term = *dynamic_cast<const non_terminal_symbol_type*>(prod[i].get());

                    for (int j = i + 1; j < prod.size(); ++j)
                    {
                        for (const auto& symbol : m_first[prod[j]])
                            if (symbol != terminal_symbol_type("&"))
                                m_follow[non_term].insert(symbol);

                        if (prod[j]->is_terminal() || !contains(m_first[prod[i]], terminal_symbol_type("&")))
                            break;
                    }
                }
            }

    follow_map_type previous;

    //! Step 3
    while (m_follow != previous)
    {
        previous = m_follow;

        for (const auto& pair : m_productions)
            for (const auto& prod : pair.second)
                for (auto it = prod.rbegin(); it != prod.rend(); ++it)
                {
                    if (!(*it)->is_terminal())
                    {
                        auto non_term = *dynamic_cast<const non_terminal_symbol_type*>(it->get());

                        for (const auto& symbol : m_follow[pair.first])
                            m_follow[non_term].insert(symbol);

                        if (!contains(m_first[*it], terminal_symbol_type("&")))
                            break;
                    }
                    else
                        break;
                }
    }
}

ContextFree ContextFree::own(non_terminal_set_type &derives_epsilon,
                             simple_production_map_type &na,
                             non_terminal_set_type &fertile_symbols,
                             symbol_ptr_set_type &reachable_symbols) const
{
    //! Calls another functions to make own grammar
    return epsilon_free(derives_epsilon)
           .remove_simple_productions(na)
           .remove_useless_symbols(fertile_symbols, reachable_symbols);
}

ContextFree ContextFree::epsilon_free(non_terminal_set_type &derives_epsilon) const
{
    non_terminal_set_type previous;
    production_map_type productions(m_productions);
    non_terminal_set_type does_not_derives_epsilon(m_vn);

    //! Creates two sets, one with all non terminal that derives epsilon, directly or not
    //! and another that do not derives epsilon
    do
    {
        previous = derives_epsilon;

        for (const auto& symbol : non_terminal_set_type{does_not_derives_epsilon})
        {
            bool generate_epsilon = false;

            for (const auto& prod : productions[symbol])
            {
                generate_epsilon = true;

                for (const auto& alfa : prod)
                    generate_epsilon &= ((*alfa == "&") | contains(derives_epsilon, *alfa));

                if (generate_epsilon)
                    break;
            }

            if (generate_epsilon)
            {
                does_not_derives_epsilon.erase(symbol);
                derives_epsilon.insert(symbol);
            }
        }

    } while (derives_epsilon != previous);

    non_terminal_set_type new_vn{m_vn};
    terminal_set_type new_vt{m_vt};
    production_map_type new_productions;
    non_terminal_symbol_type new_initial_symbol{m_initial_symbol};
    production_type epsilon_production{new terminal_symbol_type("&")};

    //! Copy of non epsilon productions to new production map
    for (const auto& pair : m_productions)
        for (const auto& prod : pair.second)
            if (prod != epsilon_production)
                new_productions[pair.first].insert(prod);

    //! Copy the productions from symbols X (where X derivates epsilon at old grammar)
    //! to symbols Y that derivates X
    production_map_type copy(new_productions);
    for (const auto& pair : copy)
    {
        for (const auto& prod : pair.second)
        {
            symbol_type::vector_type<production_type> intermediate{production_type()};

            for (const auto& symbol : prod)
            {
                if (symbol->is_terminal() || !contains(derives_epsilon, *symbol))
                    for (auto & new_prod : intermediate)
                        new_prod.push_back(symbol);
                else
                    for (auto new_prod : symbol_type::vector_type<production_type>(intermediate))
                    {
                        new_prod.push_back(symbol);
                        intermediate.push_back(new_prod);
                    }
            }

            for (const auto& new_prod : intermediate)
                if (!new_prod.empty())
                    new_productions[pair.first].insert(new_prod);
        }
    }

    //! Case the initial symbol derivates epsilon then create a new initial symbol,
    //! copy the productions from old initial symbol to new initial symbol and insert
    //! a epsilon-production on new initial symbol
    if (contains(derives_epsilon, m_initial_symbol))
    {
        new_initial_symbol = m_initial_symbol.value() + "0";
        new_productions[new_initial_symbol] = new_productions[m_initial_symbol];
        new_productions[new_initial_symbol].insert(epsilon_production);
        new_vt.insert(terminal_symbol_type("&"));
        new_vn.insert(new_initial_symbol);
    }

    return ContextFree(new_vn, new_vt, new_productions, new_initial_symbol);
}

ContextFree ContextFree::remove_simple_productions(simple_production_map_type &na) const
{
    //! Every non-terminal symbol generates it in zero steps
    for (const auto& non_terminal : m_vn)
        na[non_terminal] = {non_terminal};

    //! Find the Simple Direct productions
    for (const auto& pair : m_productions)
        for (const auto& prod : pair.second)
            if (prod.size() == 1 && !prod[0]->is_terminal())
                na[pair.first].insert(*dynamic_cast<const non_terminal_symbol_type*>(prod[0].get()));

    //! Find the Simple Indirect productions
    simple_production_map_type na_previous;
    while (na != na_previous)
    {
        na_previous = na;

        for (const auto& pair : na_previous)
            for (const auto& simple : pair.second)
                for (const auto& another_simple : na_previous[simple])
                    na[pair.first].insert(another_simple);
    }

    production_map_type new_productions;

    //! Replicate non-terminal symbol productions not simple
    for (const auto& pair : m_productions)
        for (const auto& prod : pair.second)
            if ((prod.size() > 1) || prod[0]->is_terminal())
                new_productions[pair.first].insert(prod);

    //! Copies non-terminal productions of the symbols belonging to the simple productions
    for (const auto& source : m_vn)
        for (const auto& target : na[source])
        {
            if (source == target)
                continue;

            for (const auto& prod : new_productions[target])
                new_productions[source].insert(prod);
        }

    return ContextFree(m_vn, m_vt, new_productions, m_initial_symbol);
}

ContextFree ContextFree::remove_infertile_symbols(non_terminal_set_type &fertile_symbols) const
{
    non_terminal_set_type previous;
    production_map_type productions(m_productions);
    non_terminal_set_type still_infertile(m_vn);

    //! Algorithm follows what was seen in class

    //! Check to see if the symbols that are still
    //! infertile have some production formed only of hatching symbols
    do
    {
        previous = fertile_symbols;

        //! For each non-terminal infertile symbol
        for (const auto& symbol : non_terminal_set_type{still_infertile})
        {
            bool fertile = false;

            //! Check if there is any production of it that is formed only of fertile symbols
            for (const auto& prod : productions[symbol])
            {
                fertile = true;

                for (const auto& alfa : prod)
                    fertile &= alfa->is_terminal() | contains(fertile_symbols, *alfa);

                if (fertile)
                    break;
            }

            if (fertile)
            {
                still_infertile.erase(symbol);
                fertile_symbols.insert(symbol);
            }
        }

    } while (fertile_symbols != previous);

    non_terminal_set_type new_vn{fertile_symbols};
    terminal_set_type new_vt;
    production_map_type new_productions;
    non_terminal_symbol_type new_initial_symbol{m_initial_symbol};

    //! Maintains only productions with fertile symbols
    for (const auto& fertile : fertile_symbols)
        for (const auto& prod : productions[fertile])
        {
            bool fertile_production = true;
            for (const auto& symbol : prod)
                fertile_production &= symbol->is_terminal() | contains(fertile_symbols, *symbol);

            if (fertile_production)
                new_productions[fertile].insert(prod);
        }

    //! New vt
    for (const auto& pair : new_productions)
        for (const auto& prod : pair.second)
            for (const auto& symbol : prod)
                if (symbol->is_terminal())
                {
                    terminal_symbol_type term = *dynamic_cast<const terminal_symbol_type*>(symbol.get());
                    new_vt.insert(term);
                }

    return ContextFree(new_vn, new_vt, new_productions, new_initial_symbol);
}

ContextFree ContextFree::remove_unreachable_symbols(symbol_ptr_set_type &reachable_symbols) const
{
    non_terminal_set_type new_vn;
    terminal_set_type new_vt;
    production_map_type new_productions;
    non_terminal_symbol_type new_initial_symbol{m_initial_symbol};

    production_map_type productions(m_productions);

    size_t i = 0;
    symbol_type::vector_type<symbol_ptr_type> to_process{new non_terminal_symbol_type{m_initial_symbol}};
    reachable_symbols.insert(to_process.front());

    //! Algorio follows what was seen in class

    //! From the initial symbol I will reach new
    //! symbols and insert into the set, when no new symbol is reached, stop.
    do
    {
        const auto * symbol = dynamic_cast<const non_terminal_symbol_type*>(to_process[i].get());

        if (!symbol) //! Terminal Symbol
        {
            new_vt.insert(*dynamic_cast<const terminal_symbol_type*>(to_process[i].get()));
            continue;
        }
        else
            new_vn.insert(*symbol);

        if (productions[*symbol].empty())
            continue;

        //! Achieveable Productions
        new_productions[*symbol] = productions[*symbol];

        //! Updates queue of symbols achieved
        for (const auto& prod : productions[*symbol])
            for (const auto& alfa : prod)
                if (!contains(reachable_symbols, alfa))
                {
                    reachable_symbols.insert(alfa);
                    to_process.push_back(alfa);
                }

    } while (++i < to_process.size());

    return ContextFree(new_vn, new_vt, new_productions, new_initial_symbol);
}

ContextFree ContextFree::remove_useless_symbols(non_terminal_set_type &fertile_symbols,
                                                symbol_ptr_set_type &reachable_symbols) const
{
    //! As seen in class, just run the following algorithms in the following order.
    auto fertible = remove_infertile_symbols(fertile_symbols);
    return fertible.remove_unreachable_symbols(reachable_symbols);
}

ContextFree ContextFree::factor(unsigned max_steps) const
{
    recursion_map_type ignore;
    //! Eliminates recursion
    ContextFree no_recursion_g = has_recursion()? remove_recursion(ignore) : *this;

    //! Symbols not yet verified
    symbol_type::vector_type<non_terminal_symbol_type> to_factor(no_recursion_g.m_vn.begin(),
                                                                 no_recursion_g.m_vn.end());

    //! First copy
    first_map_type first{no_recursion_g.m_first};

    non_terminal_set_type new_vn{no_recursion_g.m_vn};
    terminal_set_type new_vt{no_recursion_g.m_vt};
    production_map_type new_productions{no_recursion_g.m_productions};
    non_terminal_symbol_type new_initial_symbol{no_recursion_g.m_initial_symbol};

    size_t i = 0;
    size_t steps = 0;

    //! As long as there are symbols not yet verified or reached the maximum number of steps
    while (i < to_factor.size() && steps < max_steps)
    {
        auto current = to_factor[i];
        terminal_set_type unfactored_terminal;
        map_type<terminal_symbol_type, non_terminal_set_type> symbols_to_derive;

        //! Derives production in the form S-> ABeta... for S -> GammaBeta... If A -> Gamma
        
        //! As long as there is indirect factoring it will be derived thus creating new productions
        production_map_type previous_productions;
        while (new_productions != previous_productions)
        {
            previous_productions = new_productions;
            terminal_set_type visited;

            if (previous_productions[current].empty())
                break;

            //! Verifies that a terminal symbol can start two existing productions
            //! Or find non-terminal symbols that cause indirect factoring
            for (const auto& prod : previous_productions[current])
            {
                if (prod[0]->is_terminal())
                {
                    if (contains(visited, *prod[0]))
                        unfactored_terminal.insert(terminal_symbol_type(prod[0]->value()));

                    visited.insert(terminal_symbol_type(prod[0]->value()));
                }
                else
                {
                    non_terminal_symbol_type target(prod[0]->value());

                    //! Checks for the intersection of the first minus &
                    for (const auto& prod_first : first[prod[0]])
                    {
                        if (prod_first != terminal_symbol_type("&") && contains(visited, prod_first))
                            unfactored_terminal.insert(prod_first);

                        visited.insert(prod_first);
                        symbols_to_derive[prod_first].insert(target);
                    }
                }
            }

            //! Derives non-terminal symbols that cause factoring minus &
            for (const auto& cause_factor : unfactored_terminal)
            {
                for (const auto& to_derive : symbols_to_derive[cause_factor])
                {
                    for (const auto& prod_current : previous_productions[current])
                    {
                        if (to_derive != prod_current[0])
                            continue;

                        for (const auto& prod_derive : previous_productions[to_derive])
                        {
                            auto p = terminal_symbol_type("&") != prod_derive[0]? prod_derive : production_type();

                            for (int x = 1; x < prod_current.size(); ++x)
                                p.push_back(prod_current[x]);

                            if (p.empty())
                                p = {new terminal_symbol_type("&")};

                            new_productions[current].insert(p);
                        }

                        new_productions[current].erase(prod_current);
                    }
                }
            }

            //! Derives non-terminal simbols who derives &
            for (const auto& to_derive : symbols_to_derive[terminal_symbol_type("&")])
            {
                for (const auto& prod_current : previous_productions[current])
                {
                    if (to_derive != prod_current[0])
                        continue;

                    if (prod_current.size() == 1 && !contains(previous_productions[current], production_type{new terminal_symbol_type("&")}))
                        continue;

                    production_type p = prod_current.size() == 1? production_type(++prod_current.begin(), prod_current.end()) : production_type();

                    if (p.empty())
                        p = {new terminal_symbol_type("&")};

                    new_productions[current].insert(p);
                    new_productions[current].erase(prod_current);
                }
            }
        }

        previous_productions = new_productions;

        //! Factoring step
        int f = 0;
        for (auto terminal : unfactored_terminal)
        {
            //! New Symbol
            non_terminal_symbol_type new_non_term(current.value() + std::to_string(f++));
            new_vn.insert(new_non_term);

            //! Inserts it into the scan queue
            to_factor.push_back(new_non_term);

            //! Eliminates Unfactored Productions and inserts the new production into the new terminal
            for (const auto& prod : previous_productions[current])
            {
                if (terminal == prod[0])
                {
                    //! new_non_term productions
                    if (prod.size() > 1)
                    {
                        production_type p((++prod.begin()), prod.end());
                        new_productions[new_non_term].insert(p);
                    }
                    else
                    {
                        new_productions[new_non_term].insert({new terminal_symbol_type("&")});
                        new_vt.insert(terminal_symbol_type("&"));
                    }
                    
                    new_productions[current].erase(prod);
                }
            }

            //! New factored production
            production_type new_prod_factored{new terminal_symbol_type(terminal),
                                              new non_terminal_symbol_type(new_non_term)};
            new_productions[current].insert(new_prod_factored);
        }

        //! If factoring occurred then increments the step
        if (!unfactored_terminal.empty())
            steps++;

        i++;

        //! Update first
        ContextFree update_first(new_vn, new_vt, new_productions, new_initial_symbol);
        first = update_first.first();
    }

    return ContextFree(new_vn, new_vt, new_productions, new_initial_symbol);
}

ContextFree ContextFree::remove_recursion(recursion_map_type &recursions) const
{
    non_terminal_set_type derives_epsilon;
    simple_production_map_type na;
    non_terminal_set_type fertile_symbols;
    symbol_ptr_set_type reachable_symbols;

    //! Turns into a grammar of its own
    auto own_grammar = own(derives_epsilon, na, fertile_symbols, reachable_symbols);

    non_terminal_set_type new_vn{own_grammar.m_vn};
    terminal_set_type new_vt{own_grammar.m_vt};
    production_map_type new_productions;
    non_terminal_symbol_type new_initial_symbol{own_grammar.m_initial_symbol};

    symbol_type::vector_type<non_terminal_symbol_type> order(new_vn.begin(), new_vn.end());

    //! Algorithm follows what was seen in class
    for (auto i = 0; i < order.size(); ++i)
    {
        auto Ai = order[i];

        recursions[Ai][Recursion::Direct];
        recursions[Ai][Recursion::Indirect];
        set_type<production_type> new_prod_Ai;

        for (auto j = 0; j < i; ++j)
        {
            auto Aj = order[j];

            for (const auto& prod_Ai : own_grammar.m_productions[Ai])
                if (Aj == prod_Ai[0])
                {
                    for (const auto& prod_Aj : new_productions[Aj])
                    {
                        if (Ai == prod_Aj[0])
                            recursions[Ai][Recursion::Indirect].insert(Aj);

                        auto new_prod = prod_Aj;

                        for (int x = 1; x < prod_Ai.size(); ++x)
                            new_prod.push_back(prod_Ai[x]);

                        new_prod_Ai.insert(new_prod);
                    }
                }
                else
                    new_prod_Ai.insert(prod_Ai);
        }

        if (i == 0)
            new_prod_Ai = own_grammar.m_productions[Ai];

        symbol_type::vector_type<production_type> recursion, no_recursion;
        for (const auto& prod : new_prod_Ai)
            if (Ai == prod[0])
                recursion.push_back(prod);
            else
                no_recursion.push_back(prod);

        if (recursion.empty())
        {
            new_productions[Ai] = new_prod_Ai;
            continue;
        }

        recursions[Ai][Recursion::Direct].insert(Ai);

        non_terminal_symbol_type symbol_line{Ai.value() + "0"};
        symbol_ptr_type symbol_line_ptr(new non_terminal_symbol_type(symbol_line));
        new_vn.insert(symbol_line);

        for (const auto& prod : no_recursion)
        {
            auto new_prod = prod;
            new_prod.push_back(symbol_line_ptr);
            new_productions[Ai].insert(new_prod);
        }

        for (const auto& prod : recursion)
        {
            production_type new_prod((++prod.begin()), prod.end());
            new_prod.push_back(symbol_line_ptr);
            new_productions[symbol_line].insert(new_prod);
        }

        production_type epsilon_prod = {new terminal_symbol_type("&")};
        new_productions[symbol_line].insert(epsilon_prod);
        new_vt.insert(terminal_symbol_type("&"));
    }

    return ContextFree(new_vn, new_vt, new_productions, new_initial_symbol);
}

bool ContextFree::emptiness() const
{
    //! Checks whether the initial symbol is fertile
    non_terminal_set_type fertile;
    auto g = remove_infertile_symbols(fertile);

    return !contains(fertile, g.initial_symbol());
}

bool ContextFree::finitiness() const
{
    non_terminal_set_type temporary;
    non_terminal_set_type permanent;

    //! Performs an in-depth search, visiting all the symbols of the grammar.
    return !contains_cycle(m_initial_symbol, temporary, permanent);
}

bool ContextFree::contains_cycle(non_terminal_symbol_type state,
                                 non_terminal_set_type & temporary,
                                 non_terminal_set_type & permanent) const
{
    if (contains(permanent, state))
        return false;

    if (contains(temporary, state))
        return true;

    temporary.insert(state);

    production_map_type copy(m_productions);
    for (const auto& prod : copy[state])
        for (const auto& symbol : prod)
            if (!symbol->is_terminal())
            {
                non_terminal_symbol_type target = *dynamic_cast<const non_terminal_symbol_type*>(symbol.get());
                if (contains_cycle(target, temporary, permanent))
                    return true;
            }

    temporary.erase(state);
    permanent.insert(state);

    return false;
}

bool ContextFree::is_factored() const
{
    production_map_type copy{m_productions};
    first_map_type first{m_first};

    //! Verifies that from a non-terminal symbol you can initially
    //! derive a terminal by more than one production using the
    //! visited set. If it is visited twice then it is not factored.
    for (const auto& non_term : m_vn)
    {
        terminal_set_type visited;

        for (const auto& prod : copy[non_term])
            for (const auto& symbol : prod)
                if (symbol->is_terminal())
                {
                    if (contains(visited, *symbol))
                        return false;

                    visited.insert(terminal_symbol_type(symbol->value()));
                    break;
                }
                else
                {
                    for (const auto& symbol_first : first[symbol])
                        if (symbol_first != terminal_symbol_type("&"))
                        {
                            if (contains(visited, symbol_first))
                                return false;
                            
                            visited.insert(symbol_first);
                        }

                    if (!contains(first[symbol], terminal_symbol_type("&")))
                        break;
                }
    }

    return true;
}

bool ContextFree::has_recursion() const
{
    //! Removes recursion and verifies that some direct recursion has
    //! been detected, in case if an indirect has been made direct also counts.
    recursion_map_type recursions;
    remove_recursion(recursions);

    for (const auto& non_terminal : m_vn)
        if (!recursions[non_terminal][Recursion::Direct].empty())
            return true;

    return false;
}

ContextFree::string_type ContextFree::to_string() const
{
    string_type string;
    string = m_initial_symbol.value() + " -> ";

     auto productions(m_productions);

     int i = productions[m_initial_symbol].size();
     for (auto production : productions[m_initial_symbol])
     {
         string += production.to_string();

         if (--i > 0)
             string += " | ";
     }

     for (auto non_terminal : m_vn)
     {
         if (non_terminal == m_initial_symbol)
             continue;

         string += "\n" + non_terminal.value() + " -> ";

         i = productions[non_terminal].size();
         for (auto production : productions[non_terminal])
         {
             string += production.to_string();

             if (--i > 0)
                 string += " | ";
         }

     }

    return string;
}

} // namespace grammar
} // namespace formal_device
