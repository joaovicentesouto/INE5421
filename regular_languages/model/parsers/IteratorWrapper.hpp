//! João Vicente Souto e Bruno Izaias Bonotto

#ifndef ITERATORWRAPPER_HPP
#define ITERATORWRAPPER_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <algorithm>
#include <regex>

namespace formal_device
{
namespace parser
{

using string_type          = std::string;
using string_iterator_type = string_type::iterator;


struct IteratorWrapper
{
    IteratorWrapper(const string_iterator_type &it);

    string_iterator_type next();
    string_iterator_type iterator() const;

    string_iterator_type m_iterator;
};

}
}

#endif // ITERATORWRAPPER_HPP