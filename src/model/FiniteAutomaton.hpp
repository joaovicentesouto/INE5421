#ifndef MODEL_FINITEAUTOMATON_HPP
#define MODEL_FINITEAUTOMATON_HPP

#include <unordered_set>
#include <unordered_map>

namespace formal_device
{

//class State {};
//class Simbol {};

//class MinimumDFA;

//class DFA
//{
//  public:
//    template <class T>
//    using set_type            = std::unordered_set<T>;
//    template <class Key, class T>
//    using map_type            = std::unordered_map<Key, T>;

//    using state_type          = State;
//    using simbol_type         = Simbol;
//    using state_set_type      = set_type<state_type>;
//    using simbol_set_type     = set_type<simbol_type>;
//    using transition_map_type = map_type<state_type, map_type<simbol_type, state_type>>;

//    // Class constructors
//    DFA() = delete;

//    DFA(const DFA &) = default;
//    DFA &operator=(const DFA &) = default;

//    DFA(DFA &&) = default;
//    DFA &operator=(DFA &&) = default;

//    template <class Arg1, class Arg2, class Arg3, class Arg4, class Arg5>
//    DFA(Arg1 &&alphabet, Arg2 &&states, Arg3 &&transitions, Arg4 &&final_states, Arg5 &&initial_state) :
//        m_alphabet{std::forward<Arg1>(alphabet)},
//        m_states{std::forward<Arg2>(states)},
//        m_transitions{std::forward<Arg3>(transitions)},
//        m_final_states{std::forward<Arg4>(final_states)},
//        m_initial_state{std::forward<Arg5>(initial_state)}
//    {
//    }

//    // Class member functions

//    // union using operator+
//    // denial using operator!
//    // intersection using operator^
//    // difference using operator-
//    // reverse using operator^(char 'r') ???

//  private:
//    simbol_set_type     m_alphabet;
//    state_set_type      m_states;
//    transition_map_type m_transitions;
//    state_set_type      m_final_states;
//    state_type          m_initial_state;
//};

//class DFAEpsilon;

//class NDFA;

//class NDFAEpsilon;

} // namespace formal_device

#endif // MODEL_FINITEAUTOMATON_HPP
