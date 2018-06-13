#include "IteratorWrapper.hpp"

namespace formal_device
{
namespace parser
{

IteratorWrapper::IteratorWrapper(const string_iterator_type &it) :
    m_iterator{it}
{
}

string_iterator_type IteratorWrapper::next()
{
    return m_iterator++;
}

string_iterator_type IteratorWrapper::iterator() const
{
    return m_iterator;
}

}
}