#include "Facade.hpp"

Facade::Facade()
{

}

Facade::~Facade()
{

}

Facade::automaton_type_ptr Facade::request_automaton(unsigned machine, QString automaton)
{
    if (machine == 1)
        return m_m1_history[automaton];
    else if (machine == 2)
        return m_m2_history[automaton];
    else
        return m_result_history[automaton];
}

void Facade::new_grammar(unsigned machine, grammar_type grammar)
{
    formal_device::manipulator::DevicesConverter converter;

    ndfa_type automaton = converter.convert(grammar);

    std::map<QString, automaton_type_ptr> * map;
    automaton_type_ptr * machine_ptr;

    if (machine == 1)
    {
        machine_ptr = &m_m1;
        map = &m_m1_history;
    }
    else
    {
        machine_ptr = &m_m2;
        map = &m_m2_history;
    }

    *machine_ptr = automaton_type_ptr(new ndfa_type(automaton));

    QString automaton_name = "Máquina " + QString::number(map->size());

    (*map)[automaton_name] = *machine_ptr;

    if (machine == 1)
        emit update_automaton_to_m1(automaton, automaton_name);
    else
        emit update_automaton_to_m2(automaton, automaton_name);
}

void Facade::new_expression(unsigned machine, expression_type_ptr expression)
{
    formal_device::manipulator::DeSimoneTree tree(expression);

    dfa_type automaton = tree.execute();

    std::map<QString, automaton_type_ptr> * map;
    automaton_type_ptr * machine_ptr;

    if (machine == 1)
    {
        machine_ptr = &m_m1;
        map = &m_m1_history;
    }
    else
    {
        machine_ptr = &m_m2;
        map = &m_m2_history;
    }

    *machine_ptr = automaton_type_ptr(new dfa_type(automaton));

    QString automaton_name = "Máquina " + QString::number(map->size());

    (*map)[automaton_name] = *machine_ptr;

    if (machine == 1)
        emit update_automaton_to_m1(automaton, automaton_name);
    else
        emit update_automaton_to_m2(automaton, automaton_name);
}

void Facade::new_automaton(unsigned machine, dfa_type automaton)
{
    if (machine == 1)
        emit update_automaton_to_m1(automaton, "");
    else
        emit update_automaton_to_m2(automaton, "");
}

void Facade::new_automaton(unsigned machine, ndfa_type automaton)
{
    if (machine == 1)
        emit update_automaton_to_m1(automaton, "");
    else
        emit update_automaton_to_m2(automaton, "");
}

void Facade::complement(automaton_type_ptr automaton)
{
    result_pair_type original_pair = std::make_pair(automaton, "Original");

    automaton_ptr_container_type intermediates{original_pair};

    const dfa_type * dfa = dynamic_cast<const dfa_type*>(automaton.get());
    if (dfa)
    {
        dfa_type complet = dfa->complete();
        dfa_type negation = !complet;


        result_pair_type complet_pair = std::make_pair
                (automaton_type_ptr(new dfa_type(complet)), "Completo");

        result_pair_type negation_pair = std::make_pair
                (automaton_type_ptr(new dfa_type(negation)), "Complemento");

        intermediates.push_back(complet_pair);
        intermediates.push_back(negation_pair);
    }
    else
    {
        const ndfa_type * ndfa = dynamic_cast<const ndfa_type*>(automaton.get());

        dfa_type deterministic = ndfa->determination();
        dfa_type complet       = deterministic.complete();
        dfa_type negation      = !complet;

        result_pair_type deterministic_pair = std::make_pair
                (automaton_type_ptr(new dfa_type(deterministic)), "Deterministico");

        result_pair_type complet_pair = std::make_pair
                (automaton_type_ptr(new dfa_type(complet)), "Completo");

        result_pair_type negation_pair = std::make_pair
                (automaton_type_ptr(new dfa_type(negation)), "Complemento");

        intermediates.push_back(deterministic_pair);
        intermediates.push_back(complet_pair);
        intermediates.push_back(negation_pair);
    }

    m_result_history.clear();

    for (auto pair : intermediates)
        m_result_history[pair.second] = pair.first;

    emit update_result(intermediates);
}

void Facade::reflexive_closure(automaton_type_ptr automaton)
{
    result_pair_type original_pair = std::make_pair(automaton, "Original");

    automaton_ptr_container_type intermediates{original_pair};

    const dfa_type * dfa = dynamic_cast<const dfa_type*>(automaton.get());
    if (dfa)
    {
        ndfa_type reflexive = (*dfa)^formal_device::finite_automaton::Operation::Reflexive;

        result_pair_type reflexive_pair = std::make_pair
                (automaton_type_ptr(new ndfa_type(reflexive)), "Fecho Reflexivo");

        intermediates.push_back(reflexive_pair);
    }
    else
    {
        const ndfa_type * ndfa = dynamic_cast<const ndfa_type*>(automaton.get());

        ndfa_type reflexive = (*ndfa)^formal_device::finite_automaton::Operation::Reflexive;

        result_pair_type reflexive_pair = std::make_pair
                (automaton_type_ptr(new ndfa_type(reflexive)), "Fecho Reflexivo");

        intermediates.push_back(reflexive_pair);
    }

    m_result_history.clear();

    for (auto pair : intermediates)
        m_result_history[pair.second] = pair.first;

    emit update_result(intermediates);
}

void Facade::reverse(automaton_type_ptr automaton)
{
    result_pair_type original_pair = std::make_pair(automaton, "Original");

    automaton_ptr_container_type intermediates{original_pair};

    const dfa_type * dfa = dynamic_cast<const dfa_type*>(automaton.get());
    if (dfa)
    {
        ndfa_type reverse = (*dfa)^formal_device::finite_automaton::Operation::Reverse;

        result_pair_type reverse_pair = std::make_pair
                (automaton_type_ptr(new ndfa_type(reverse)), "Reverso");

        intermediates.push_back(reverse_pair);
    }
    else
    {
        const ndfa_type * ndfa = dynamic_cast<const ndfa_type*>(automaton.get());

        ndfa_type reverse = (*dfa)^formal_device::finite_automaton::Operation::Reverse;

        result_pair_type reverse_pair = std::make_pair
                (automaton_type_ptr(new ndfa_type(reverse)), "Reverso");

        intermediates.push_back(reverse_pair);
    }

    m_result_history.clear();

    for (auto pair : intermediates)
        m_result_history[pair.second] = pair.first;

    emit update_result(intermediates);
}

void Facade::determination(automaton_type_ptr automaton)
{
    result_pair_type original_pair = std::make_pair(automaton, "Original");

    automaton_ptr_container_type intermediates{original_pair};

    const ndfa_type * ndfa = dynamic_cast<const ndfa_type*>(automaton.get());
    if (ndfa)
    {
        ndfa_type reverse = ndfa->determination();

        result_pair_type det_pair = std::make_pair
                (automaton_type_ptr(new ndfa_type(reverse)), "Deterministico");

        intermediates.push_back(det_pair);
    }

    m_result_history.clear();

    for (auto pair : intermediates)
        m_result_history[pair.second] = pair.first;

    emit update_result(intermediates);
}

void Facade::minimization(automaton_type_ptr automaton)
{
    result_pair_type original_pair = std::make_pair(automaton, "Original");

    automaton_ptr_container_type intermediates{original_pair};

    const dfa_type * dfa = dynamic_cast<const dfa_type*>(automaton.get());
    if (dfa)
        dfa = new dfa_type(*dfa);
    else
    {
        const ndfa_type * ndfa = dynamic_cast<const ndfa_type*>(automaton.get());

        dfa_type deterministic = ndfa->determination();

        result_pair_type deterministic_pair = std::make_pair
                (automaton_type_ptr(new dfa_type(deterministic)), "Deterministico");

        intermediates.push_back(deterministic_pair);

        dfa = new dfa_type(deterministic);
    }

    dfa_type reachable = dfa->remove_unreachable_states();
    dfa_type live_states = reachable.remove_dead_states();
    dfa_type minimum = live_states.minimization();

    result_pair_type reachable_pair = std::make_pair
            (automaton_type_ptr(new dfa_type(reachable)), "Elimina inalcançáveis");

    result_pair_type live_states_pair = std::make_pair
            (automaton_type_ptr(new dfa_type(live_states)), "Elimina estados mortos");

    result_pair_type minimum_pair = std::make_pair
            (automaton_type_ptr(new dfa_type(minimum)), "Remove estados equivalentes");

    intermediates.push_back(reachable_pair);
    intermediates.push_back(live_states_pair);
    intermediates.push_back(minimum_pair);

    m_result_history.clear();

    for (auto pair : intermediates)
        m_result_history[pair.second] = pair.first;

    emit update_result(intermediates);

    delete dfa;
}
