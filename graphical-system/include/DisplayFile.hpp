#ifndef DISPLAYFILE_HPP
#define DISPLAYFILE_HPP

#include "Object.hpp"
#include <list>

class DisplayFile: public std::list<Object>
{
    public:
        DisplayFile() {}
        ~DisplayFile() {}
        Object get_object(const std::string name)
        {
            for (auto i = begin(); i != end(); ++i)
                if ((*i).name() == name) return *i;
        }
};

#endif // DISPLAYFILE_HPP
