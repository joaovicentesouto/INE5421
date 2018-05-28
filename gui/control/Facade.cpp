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
    else if (machine == 2)
        emit update_automaton_to_m2(automaton, "");
    else
    {
        std::map<QString, automaton_type_ptr> * map;
        automaton_type_ptr * machine_ptr;
        QString automaton_name;

        if (machine == 11)
            map = &m_m1_history;
        else
            map = &m_m2_history;

        automaton_type_ptr equal;

        for (auto p : *map)
        {
            const dfa_type* dfa = dynamic_cast<const dfa_type*>(p.second.get());

            if (!dfa)
                continue;

            if (automaton == *dfa)
            {
                equal = p.second;
                break;
            }
        }

        if (equal.get())
        {
            machine_ptr = new automaton_type_ptr(equal);

            for (auto pair : *map)
                if (pair.second == equal)
                {
                    automaton_name = pair.first;
                    break;
                }
        }
        else
        {
            machine_ptr = new automaton_type_ptr(new dfa_type(automaton));

            automaton_name = "Máquina " + QString::number(map->size());
            (*map)[automaton_name] = *machine_ptr;
        }

        if (machine == 11)
            emit update_automaton_to_m1(automaton, automaton_name);
        else
            emit update_automaton_to_m2(automaton, automaton_name);

        delete machine_ptr;
    }
}

void Facade::new_automaton(unsigned machine, ndfa_type automaton)
{
    if (machine == 1)
        emit update_automaton_to_m1(automaton, "");
    else if (machine == 2)
        emit update_automaton_to_m2(automaton, "");
    else
    {
        std::map<QString, automaton_type_ptr> * map;
        automaton_type_ptr * machine_ptr;
        QString automaton_name;

        if (machine == 11)
            map = &m_m1_history;
        else
            map = &m_m2_history;

        automaton_type_ptr equal;

        for (auto p : *map)
        {
            const ndfa_type* ndfa = dynamic_cast<const ndfa_type*>(p.second.get());

            if (!ndfa)
                continue;

            if (automaton == *ndfa)
            {
                equal = p.second;
                break;
            }
        }

        if (equal.get())
        {
            machine_ptr = new automaton_type_ptr(equal);

            for (auto pair : *map)
                if (pair.second == equal)
                {
                    automaton_name = pair.first;
                    break;
                }
        }
        else
        {
            machine_ptr = new automaton_type_ptr(new ndfa_type(automaton));

            automaton_name = "Máquina " + QString::number(map->size());
            (*map)[automaton_name] = *machine_ptr;
        }

        if (machine == 11)
            emit update_automaton_to_m1(automaton, automaton_name);
        else
            emit update_automaton_to_m2(automaton, automaton_name);

        delete machine_ptr;
    }
}

void Facade::complement(automaton_type_ptr automaton)
{
    automaton_ptr_container_type intermediates{std::make_pair(automaton, "Original")};

    dfa_type complet;
    dfa_type negation;

    const dfa_type * dfa = dynamic_cast<const dfa_type*>(automaton.get());
    if (dfa)
    {
        complet  = dfa->complete();
        negation = !complet;
    }
    else
    {
        const ndfa_type * ndfa = dynamic_cast<const ndfa_type*>(automaton.get());

        dfa_type deterministic = ndfa->determination();
        complet                = deterministic.complete();
        negation               = !complet;

        result_pair_type deterministic_pair = std::make_pair
                (automaton_type_ptr(new dfa_type(deterministic)), "Determinístico");

        intermediates.push_back(deterministic_pair);
    }

    intermediates.push_back(
        std::make_pair(automaton_type_ptr(new dfa_type(complet)), "Completo"));
    intermediates.push_back(
        std::make_pair(automaton_type_ptr(new dfa_type(negation)), "!Complemento"));

    m_result_history.clear();
    for (auto pair : intermediates)
        m_result_history[pair.second] = pair.first;

    emit update_result(intermediates);
}

void Facade::reflexive_closure(automaton_type_ptr automaton)
{
    automaton_ptr_container_type intermediates{std::make_pair(automaton, "Original")};

    ndfa_type reflexive;

    const dfa_type * dfa = dynamic_cast<const dfa_type*>(automaton.get());
    if (dfa)
        reflexive = (*dfa)^formal_device::finite_automaton::Operation::Reflexive;
    else
    {
        const ndfa_type * ndfa = dynamic_cast<const ndfa_type*>(automaton.get());
        reflexive = (*ndfa)^formal_device::finite_automaton::Operation::Reflexive;
    }

    intermediates.push_back(
        std::make_pair(automaton_type_ptr(new ndfa_type(reflexive)), "Fecho Reflexivo"));

    m_result_history.clear();
    for (auto pair : intermediates)
        m_result_history[pair.second] = pair.first;

    emit update_result(intermediates);
}

void Facade::transitive_closure(automaton_type_ptr automaton)
{
    automaton_ptr_container_type intermediates{std::make_pair(automaton, "Original")};

    ndfa_type reflexive;

    const dfa_type * dfa = dynamic_cast<const dfa_type*>(automaton.get());
    if (dfa)
        reflexive = (*dfa)^formal_device::finite_automaton::Operation::Transitive;
    else
    {
        const ndfa_type * ndfa = dynamic_cast<const ndfa_type*>(automaton.get());
        reflexive = (*ndfa)^formal_device::finite_automaton::Operation::Transitive;
    }

    intermediates.push_back(
        std::make_pair(automaton_type_ptr(new ndfa_type(reflexive)), "Fecho Transitivo"));

    m_result_history.clear();
    for (auto pair : intermediates)
        m_result_history[pair.second] = pair.first;

    emit update_result(intermediates);
}

void Facade::optional(automaton_type_ptr automaton)
{
    automaton_ptr_container_type intermediates{std::make_pair(automaton, "Original")};

    ndfa_type reflexive;

    const dfa_type * dfa = dynamic_cast<const dfa_type*>(automaton.get());
    if (dfa)
        reflexive = (*dfa)^formal_device::finite_automaton::Operation::Optional;
    else
    {
        const ndfa_type * ndfa = dynamic_cast<const ndfa_type*>(automaton.get());
        reflexive = (*ndfa)^formal_device::finite_automaton::Operation::Optional;
    }

    intermediates.push_back(
        std::make_pair(automaton_type_ptr(new ndfa_type(reflexive)), "Optional"));

    m_result_history.clear();
    for (auto pair : intermediates)
        m_result_history[pair.second] = pair.first;

    emit update_result(intermediates);
}

void Facade::reverse(automaton_type_ptr automaton)
{
    automaton_ptr_container_type intermediates{std::make_pair(automaton, "Original")};

    ndfa_type reverse;

    const dfa_type * dfa = dynamic_cast<const dfa_type*>(automaton.get());
    if (dfa)
        reverse = (*dfa)^formal_device::finite_automaton::Operation::Reverse;
    else
    {
        const ndfa_type * ndfa = dynamic_cast<const ndfa_type*>(automaton.get());
        reverse = (*ndfa)^formal_device::finite_automaton::Operation::Reverse;
    }

    intermediates.push_back(
        std::make_pair(automaton_type_ptr(new ndfa_type(reverse)), "Reverso"));

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
        ndfa_type aux;

        if (ndfa->contains_epsilon_transition())
        {
            aux = ndfa->remove_epsilon();
            intermediates.push_back(
                std::make_pair(automaton_type_ptr(new ndfa_type(aux)), "Remove & transições"));
        }
        else
            aux = *ndfa;

        dfa_type reverse = aux.determination();

        intermediates.push_back(
            std::make_pair(automaton_type_ptr(new dfa_type(reverse)), "Determinístico"));
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

        intermediates.push_back(
            std::make_pair(automaton_type_ptr(new dfa_type(deterministic)), "Determinístico"));

        dfa = new dfa_type(deterministic);
    }

    dfa_type reachable = dfa->remove_unreachable_states();
    dfa_type live_states = reachable.remove_dead_states();
    dfa_type minimum = live_states.minimization();

    intermediates.push_back(
        std::make_pair(automaton_type_ptr(new dfa_type(reachable)), "Elimina inalcançáveis"));
    intermediates.push_back(
        std::make_pair(automaton_type_ptr(new dfa_type(live_states)), "Elimina estados mortos"));
    intermediates.push_back(
        std::make_pair(automaton_type_ptr(new dfa_type(minimum)), "Remove estados equivalentes"));

    m_result_history.clear();
    for (auto pair : intermediates)
        m_result_history[pair.second] = pair.first;

    emit update_result(intermediates);

    delete dfa;
}

void Facade::union_(automaton_type_ptr m1, automaton_type_ptr m2)
{
    automaton_ptr_container_type intermediates{
        std::make_pair(m1, "Original: M1"),
        std::make_pair(m2, "Original: M2")
    };

    const dfa_type*   dfa_m1 = dynamic_cast<const dfa_type*>(m1.get());
    const ndfa_type* ndfa_m1 = dynamic_cast<const ndfa_type*>(m1.get());
    const dfa_type*   dfa_m2 = dynamic_cast<const dfa_type*>(m2.get());
    const ndfa_type* ndfa_m2 = dynamic_cast<const ndfa_type*>(m2.get());

    ndfa_type _union;

    if (dfa_m1 && dfa_m2)
        _union = *dfa_m1 | *dfa_m2;
    else
    {
        ndfa_type _m1 = dfa_m1? *dfa_m1 : *ndfa_m1;
        ndfa_type _m2 = dfa_m2? *dfa_m2 : *ndfa_m2;

        _union = _m1 | _m2;
    }

    intermediates.push_back(
        std::make_pair(automaton_type_ptr(new ndfa_type(_union)), "União: M1 | M2"));

    m_result_history.clear();
    for (auto pair : intermediates)
        m_result_history[pair.second] = pair.first;

    emit update_result(intermediates);
}

void Facade::concatenation(automaton_type_ptr m1, automaton_type_ptr m2)
{
    automaton_ptr_container_type intermediates{
        std::make_pair(m1, "Original: M1"),
        std::make_pair(m2, "Original: M2")
    };

    const dfa_type*   dfa_m1 = dynamic_cast<const dfa_type*>(m1.get());
    const ndfa_type* ndfa_m1 = dynamic_cast<const ndfa_type*>(m1.get());
    const dfa_type*   dfa_m2 = dynamic_cast<const dfa_type*>(m2.get());
    const ndfa_type* ndfa_m2 = dynamic_cast<const ndfa_type*>(m2.get());

    ndfa_type concat;

    if (dfa_m1 && dfa_m2)
        concat = *dfa_m1 + *dfa_m2;
    else
    {
        ndfa_type _m1 = dfa_m1? *dfa_m1 : *ndfa_m1;
        ndfa_type _m2 = dfa_m2? *dfa_m2 : *ndfa_m2;

        concat = _m1 + _m2;
    }

    intermediates.push_back(
        std::make_pair(automaton_type_ptr(new ndfa_type(concat)), "Concatenação: M1 + M2"));

    m_result_history.clear();
    for (auto pair : intermediates)
        m_result_history[pair.second] = pair.first;

    emit update_result(intermediates);
}

void Facade::intersection(automaton_type_ptr m1, automaton_type_ptr m2)
{
    automaton_ptr_container_type intermediates{
        std::make_pair(m1, "Original: M1"),
        std::make_pair(m2, "Original: M2")
    };

    const dfa_type*   dfa_m1 = dynamic_cast<const dfa_type*>(m1.get());
    const ndfa_type* ndfa_m1 = dynamic_cast<const ndfa_type*>(m1.get());
    const dfa_type*   dfa_m2 = dynamic_cast<const dfa_type*>(m2.get());
    const ndfa_type* ndfa_m2 = dynamic_cast<const ndfa_type*>(m2.get());

    /* ------ Complement M1 / M2 ------ */

    dfa_type det_m1, det_m2;

    if (dfa_m1)
        det_m1 = !(*dfa_m1);
    else
        det_m1 = !(ndfa_m1->determination());

    intermediates.push_back(
        std::make_pair(automaton_type_ptr(new ndfa_type(det_m1)), "Complemento: !M1"));

    if (dfa_m2)
        det_m2 = !(*dfa_m2);
    else
        det_m2 = !(ndfa_m2->determination());

    intermediates.push_back(
        std::make_pair(automaton_type_ptr(new ndfa_type(det_m2)), "Complemento: !M2"));

    /* ------ !M1 | !M2 ------ */

    ndfa_type non_deterministic = det_m1 | det_m2;

    intermediates.push_back(
        std::make_pair(automaton_type_ptr(new ndfa_type(non_deterministic)), "União: !M1 | !M2"));

    /* ------ (!M1 | !M2) Determination ------ */

    dfa_type deterministic = non_deterministic.determination();

    intermediates.push_back(
        std::make_pair(automaton_type_ptr(new ndfa_type(deterministic)), "Determinístico: M1 | M2"));

    /* ------ !(!M1 | !M2) ------ */

    deterministic = !deterministic;

    intermediates.push_back(
        std::make_pair(automaton_type_ptr(new ndfa_type(deterministic)), "Complemento: !(M1 | M2)"));

    /* ------ M1 & M2 ------ */

    if (dfa_m1 && dfa_m2)
        non_deterministic = *dfa_m1 & *dfa_m2;
    else
    {
        ndfa_type _m1 = dfa_m1? *dfa_m1 : *ndfa_m1;
        ndfa_type _m2 = dfa_m2? *dfa_m2 : *ndfa_m2;

        non_deterministic = _m1 & _m2;
    }

    intermediates.push_back(
        std::make_pair(automaton_type_ptr(new ndfa_type(non_deterministic)), "Intersecção: M1 & M2"));


    /* ------ Result ------ */

    m_result_history.clear();

    for (auto pair : intermediates)
        m_result_history[pair.second] = pair.first;

    emit update_result(intermediates);
}

void Facade::difference(automaton_type_ptr m1, automaton_type_ptr m2)
{
    automaton_ptr_container_type intermediates{
        std::make_pair(m1, "Original: M1"),
        std::make_pair(m2, "Original: M2")
    };

    const dfa_type*   dfa_m1 = dynamic_cast<const dfa_type*>(m1.get());
    const ndfa_type* ndfa_m1 = dynamic_cast<const ndfa_type*>(m1.get());
    const dfa_type*   dfa_m2 = dynamic_cast<const dfa_type*>(m2.get());
    const ndfa_type* ndfa_m2 = dynamic_cast<const ndfa_type*>(m2.get());

    /* ------ Complement M1 / M2 ------ */

    dfa_type deterministic;

    if (dfa_m2)
        deterministic = !(*dfa_m2);
    else
        deterministic = !(ndfa_m2->determination());

    intermediates.push_back(
        std::make_pair(automaton_type_ptr(new ndfa_type(deterministic)), "Complemento: !M2"));

    /* ------ M1 & M2 ------ */

    ndfa_type non_deterministic;

    if (dfa_m1)
        non_deterministic = *dfa_m1 & deterministic;
    else
        non_deterministic = *ndfa_m1 & deterministic;

    intermediates.push_back(
        std::make_pair(automaton_type_ptr(new ndfa_type(non_deterministic)), "Intersecção: M1 & !M2"));

    /* ------ M1 - M2 (Direto) ------ */

    if (dfa_m1 && dfa_m2)
        non_deterministic = *dfa_m1 - *dfa_m2;
    else
    {
        ndfa_type _m1 = dfa_m1? *dfa_m1 : *ndfa_m1;
        ndfa_type _m2 = dfa_m2? *dfa_m2 : *ndfa_m2;

        non_deterministic = (_m1 - _m2).minimization();
    }

    intermediates.push_back(
        std::make_pair(automaton_type_ptr(new ndfa_type(non_deterministic)), "Diferença: M1 - M2 (Direto)"));

    /* ------ Result ------ */

    m_result_history.clear();

    for (auto pair : intermediates)
        m_result_history[pair.second] = pair.first;

    emit update_result(intermediates);
}

bool Facade::contains(automaton_type_ptr m1, automaton_type_ptr m2)
{
    automaton_ptr_container_type intermediates{
        std::make_pair(m2, "Original: M1"),
        std::make_pair(m1, "Original: M2")
    };

    const dfa_type*   dfa_m1 = dynamic_cast<const dfa_type*>(m1.get());
    const ndfa_type* ndfa_m1 = dynamic_cast<const ndfa_type*>(m1.get());
    const dfa_type*   dfa_m2 = dynamic_cast<const dfa_type*>(m2.get());
    const ndfa_type* ndfa_m2 = dynamic_cast<const ndfa_type*>(m2.get());

    /* ------ M1 - M2 (Direto) ------ */

    ndfa_type non_deterministic;

    if (dfa_m1 && dfa_m2)
        non_deterministic = *dfa_m1 - *dfa_m2;
    else
    {
        ndfa_type _m1 = dfa_m1? *dfa_m1 : *ndfa_m1;
        ndfa_type _m2 = dfa_m2? *dfa_m2 : *ndfa_m2;

        non_deterministic = _m1 - _m2;
    }

    intermediates.push_back(
        std::make_pair(automaton_type_ptr(new ndfa_type(non_deterministic)), "M1 ⊆ M2: M2 - M1 = φ?"));

    /* ------ Result ------ */

    m_result_history.clear();

    for (auto pair : intermediates)
        m_result_history[pair.second] = pair.first;

    emit update_result(intermediates);

    /* ------ Contains ------ */

    if (dfa_m1)
    {
        if (dfa_m2)
            return dfa_m1->containment(*dfa_m2);
        else
            return dfa_m1->containment(ndfa_m2->determination());
    }
    else
    {
        if (dfa_m2)
            return ndfa_m1->containment(*dfa_m2);
        else
            return ndfa_m1->containment(*ndfa_m2);
    }
}

bool Facade::equivalence(automaton_type_ptr m1, automaton_type_ptr m2)
{
    automaton_ptr_container_type intermediates{
        std::make_pair(m2, "Original: M1"),
        std::make_pair(m1, "Original: M2")
    };

    const dfa_type*   dfa_m1 = dynamic_cast<const dfa_type*>(m1.get());
    const ndfa_type* ndfa_m1 = dynamic_cast<const ndfa_type*>(m1.get());
    const dfa_type*   dfa_m2 = dynamic_cast<const dfa_type*>(m2.get());
    const ndfa_type* ndfa_m2 = dynamic_cast<const ndfa_type*>(m2.get());

    /* ------ M2 - M1 ------ */

    ndfa_type non1diff2, non2diff1;

    if (dfa_m1 && dfa_m2)
    {
        non2diff1 = *dfa_m1 - *dfa_m2;
        non1diff2 = *dfa_m2 - *dfa_m1;
    }
    else
    {
        ndfa_type _m1 = dfa_m1? *dfa_m1 : *ndfa_m1;
        ndfa_type _m2 = dfa_m2? *dfa_m2 : *ndfa_m2;

        non2diff1 = _m1 - _m2;
        non1diff2 = _m2 - _m1;
    }

    intermediates.push_back(
        std::make_pair(automaton_type_ptr(new ndfa_type(non2diff1)), "M1 ⊆ M2: M2 - M1 = φ?"));

    intermediates.push_back(
        std::make_pair(automaton_type_ptr(new ndfa_type(non1diff2)), "M2 ⊆ M1: M1 - M2 = φ?"));

    /* ------ Result ------ */

    m_result_history.clear();

    for (auto pair : intermediates)
        m_result_history[pair.second] = pair.first;

    emit update_result(intermediates);

    /* ------ Contains ------ */

    if (dfa_m1)
    {
        if (dfa_m2)
            return dfa_m1->equivalence(*dfa_m2);
        else
            return dfa_m1->equivalence(ndfa_m2->determination());
    }
    else
    {
        if (dfa_m2)
            return ndfa_m1->equivalence(*dfa_m2);
        else
            return ndfa_m1->equivalence(*ndfa_m2);
    }
}
