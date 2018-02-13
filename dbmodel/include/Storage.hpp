#ifndef STORAGE_HPP_
#define STORAGE_HPP_

#include <odb/core.hxx>

/**
    The database backend. This module is used to access Sensors etc. in a
    convenient way and manages their persistence / updates.
*/
class Storage {
    odb::database* database_;
public:
    Storage();
    ~Storage();
};


#endif /* end of include guard: STORAGE_HPP_ */
