#include "Filler.hpp"

QTableWidget* operator<<(QTableWidget* table, const dfa_type& machine)
{
    table->reset();
    table->horizontalHeader()->hide();
    table->verticalHeader()->hide();

    table->setRowCount(machine.states().size() + 1);
    table->setColumnCount(machine.alphabet().size() + 1);

    QTableWidgetItem *item = new QTableWidgetItem("+");
    //item->setFlags(Qt::NoItemFlags);

    table->setItem(0, 0, item);

    unsigned i = 0, j = 1;
    for (auto symbol : machine.alphabet())
        table->setItem(i, j++, new QTableWidgetItem(QString::fromStdString(symbol.value())));

    dfa_type::transition_map_type transitions(machine.transitions());
    bool explicit_error = machine.states().find(dfa_type::state_type("Error")) != machine.states().end();

    j = 0;
    i++;
    for(auto state : machine.states())
    {
        if (state == ndfa_type::state_type())
            continue;

        QString state_name("");

        if (machine.final_states().find(state) != machine.final_states().end())
            state_name += "*";

        if (state == machine.initial_state())
            state_name += "->";

        table->setItem(i, j++, new QTableWidgetItem(state_name + QString::fromStdString(state.value())));

        for (auto symbol : machine.alphabet())
        {
            auto target = transitions[state][symbol];

            if (!(target == "Error"))
                table->setItem(i, j++, new QTableWidgetItem(QString::fromStdString(target.value())));
            else
            {
                if (explicit_error)
                    table->setItem(i, j++, new QTableWidgetItem("Error"));
                else
                    table->setItem(i, j++, new QTableWidgetItem("-"));
            }
        }

        i++;
        j = 0;
    }

    if (explicit_error)
    {
        dfa_type::state_type error;

        QString error_name("");
        if (machine.final_states().find(error) != machine.final_states().end())
            error_name += "*";

        if (error == machine.initial_state())
            error_name += "->";

        table->setItem(i, j++, new QTableWidgetItem(error_name + "Error"));

        for (auto symbol : machine.alphabet())
            table->setItem(i, j++, new QTableWidgetItem(QString::fromStdString(transitions[error][symbol].value())));
    }

    return table;
}

QTableWidget* operator<<(QTableWidget* table, const ndfa_type& machine)
{
    table->reset();
    table->horizontalHeader()->hide();
    table->verticalHeader()->hide();

    table->setRowCount(machine.states().size() + 1);
    table->setColumnCount(machine.alphabet().size() + 1);

    QTableWidgetItem *item = new QTableWidgetItem("+");
    //item->setFlags(Qt::NoItemFlags);

    table->setItem(0, 0, item);

    unsigned i = 0, j = 1;
    for (auto symbol : machine.alphabet())
        table->setItem(i, j++, new QTableWidgetItem(QString::fromStdString(symbol.value())));

    ndfa_type::transition_map_type transitions(machine.transitions());
    bool explicit_error = machine.states().find(ndfa_type::state_type("Error")) != machine.states().end();

    j = 0;
    i++;
    for(auto state : machine.states())
    {
        if (state == ndfa_type::state_type())
            continue;

        QString state_name("");

        if (machine.final_states().find(state) != machine.final_states().end())
            state_name += "*";

        if (state == machine.initial_state())
            state_name += "->";

        table->setItem(i, j++, new QTableWidgetItem(state_name + QString::fromStdString(state.value())));

        for (auto symbol : machine.alphabet())
        {
            auto target_set = transitions[state][symbol];

            QString target_name;
            unsigned it = 0;
            for (auto target_state : target_set)
            {
                target_name += QString::fromStdString(target_state.value());
                if (it++ < target_set.size() - 1)
                    target_name += ", ";
            }

            if (!target_set.empty())
                table->setItem(i, j++, new QTableWidgetItem(target_name));
            else
            {
                if (explicit_error)
                    table->setItem(i, j++, new QTableWidgetItem("Error"));
                else
                    table->setItem(i, j++, new QTableWidgetItem("-"));
            }
        }

        i++;
        j = 0;
    }

    if (explicit_error)
    {
        ndfa_type::state_type error;

        QString error_name("");
        if (machine.final_states().find(error) != machine.final_states().end())
            error_name += "*";

        if (error == machine.initial_state())
            error_name += "->";

        table->setItem(i, j++, new QTableWidgetItem(error_name + "Error"));

        for (auto symbol : machine.alphabet())
            table->setItem(i, j++, new QTableWidgetItem("Error"));
    }

    return table;
}
