#include <Storage.hpp>

#include <odb/sqlite/database.hxx>

Storage::Storage()
{
    database_ = new odb::sqlite::database("sensor-db.sqlite");
}

Storage::~Storage()
{
    delete database_;
}
