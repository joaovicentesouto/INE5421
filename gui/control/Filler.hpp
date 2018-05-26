#ifndef FILLER_HPP
#define FILLER_HPP

#include <QTableWidget>
#include <QTableView>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <formal_languages/devices/FiniteAutomaton.hpp>

using dfa_type = formal_device::finite_automaton::Deterministic;
using ndfa_type = formal_device::finite_automaton::NonDeterministic;

QTableWidget* operator<<(QTableWidget* table, const dfa_type& machine);
QTableWidget* operator<<(QTableWidget* table, const ndfa_type& machine);


#endif // FILLER_HPP
