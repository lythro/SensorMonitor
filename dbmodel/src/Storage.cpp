#include <Storage.hpp>

#include <odb/sqlite/database.hxx>
#include <odb/schema-catalog.hxx>

#include <iostream>

Storage::Storage()
{
    database_ = new odb::sqlite::database("sensor-db.sqlite", SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);

    try {
        odb::transaction t(database_->begin());
        odb::schema_catalog::create_schema(*database_);
        t.commit();
    } catch (const odb::exception& e) {
        std::cerr << e.what() << '\n';
    }
}

Storage::~Storage()
{
    delete database_;
}
