/*! \file database.cpp
    \brief SQLite3 C++ Wrapper

    SQLite3 C++ Wrapper. Contains the definitions for the Database class.
*/

#include <iostream>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>

// Load the SQLite3 Library
#include "sqlite3/sqlite3.h"

// Load the Database class header.
#include "database.h"

/*! \namespace KotoriApp
    \brief Kotori's Application Namespace.

    Kotori's Application Namespace.
*/
namespace KotoriApp
{
Database::Database()
{
    db_loc_ = DEFAULT_LOC;
    Common();
}

Database::Database(char *loc)
{
    db_loc_ = loc;
    Common();
}

Database::~Database() { }

void Database::Common()
{
    is_open_ = false;
}

bool Database::Open()
{
    int err = sqlite3_open_v2(db_loc_, &db_, SQLITE_OPEN_READWRITE, NULL );
    if(err != SQLITE_OK)
    {
        // Return true if an error occurred.
        std::cout << "Can't open database: " << sqlite3_errmsg(db_) << "\n";
        sqlite3_close(db_);
        return true;
    }
    else
    {
        // Return false if database opened properly.
        is_open_ = true;
        return false;
    }
}

void Database::Close()
{
    sqlite3_close(db_);
    is_open_ = false;
}

bool Database::SelectStr(std::string &refVal, const char *sql, ...)
{
    if(Open())
    {
        return true;
    }

    char *tmp;
    int rc;

    sqlite3_stmt *stmt;
    const char *tail;

    va_list argList;
    va_start(argList, sql);

    tmp = sqlite3_vmprintf(sql, argList);

    va_end(argList);

    // Prepare the SQL statement via the sqlite3_prepare function.
    rc = sqlite3_prepare(db_, tmp, strlen(tmp), &stmt, &tail);
    if(rc != SQLITE_OK)
    {
        std::cout << "Error Processing SQL Statement: " << sqlite3_errmsg(db_) << "\n";
        return true;
    }

    int ncols = sqlite3_column_count(stmt);
    rc = sqlite3_step(stmt);

    refVal = (char*)sqlite3_column_text(stmt, 0);

    sqlite3_finalize(stmt);

    Close( );
    return false;
}

bool Database::SelectInt(int &refVal, const char *sql, ...)
{
    if(Open())
    {
        return true;
    }

    char *tmp;
    int rc;

    sqlite3_stmt *stmt;
    const char *tail;

    va_list argList;
    va_start(argList, sql);

    tmp = sqlite3_vmprintf(sql, argList);

    va_end(argList);

    // Prepare the SQL statement via the sqlite3_prepare function.
    rc = sqlite3_prepare(db_, tmp, strlen(tmp), &stmt, &tail);
    if(rc != SQLITE_OK)
    {
        std::cout << "Error Processing SQL Statement: " << sqlite3_errmsg(db_) << "\n";
        return true;
    }

    int ncols = sqlite3_column_count(stmt);
    rc = sqlite3_step(stmt);

    refVal = sqlite3_column_int(stmt, 0);

    sqlite3_finalize(stmt);

    Close();
    return false;
}

bool Database::SelectChar(char *refVal, const char *sql, ...)
{
    if(Open())
    {
        return true;
    }

    char *tmp;
    int rc;

    sqlite3_stmt *stmt;
    const char *tail;

    va_list argList;
    va_start(argList, sql);

    tmp = sqlite3_vmprintf(sql, argList);

    va_end(argList);

    // Prepare the SQL statement via the sqlite3_prepare function.
    rc = sqlite3_prepare(db_, tmp, strlen(tmp), &stmt, &tail);
    if(rc != SQLITE_OK)
    {
        std::cout << "Error Processing SQL Statement: " << sqlite3_errmsg(db_) << "\n";
        return true;
    }

    int ncols = sqlite3_column_count(stmt);
    rc = sqlite3_step(stmt);

    char *tmps = NULL;

    tmps = (char*)sqlite3_column_text(stmt, 0);

    //strcpy_s(refVal, sizeof refVal, tmps);
    strcpy(refVal, tmps);

    //strcpy_s( refVal, tmps );

    sqlite3_finalize(stmt);

    Close( );
    return false;
}

bool Database::Exec(const char *sql, ...)
{
    if(Open())
    {
        return true;
    }

    char *err;
    char *tmp;
    va_list ap;
    va_start(ap, sql);
    tmp = sqlite3_vmprintf(sql, ap);
    va_end(ap);

    // Database functionality goes here.
    int rc = sqlite3_exec(db_, tmp, NULL, NULL, &err);
    if(rc != SQLITE_OK)
    {
        if(err != NULL)
        {
            sqlite3_free(err);
        }
    }

    sqlite3_free(tmp);

    Close();
    return false;
}

char* Database::Format(const char *msg, ...)
{
    char *val;
    va_list ap;

    va_start(ap, msg);
    val = sqlite3_vmprintf(msg, ap);
    va_end(ap);

    return val;
}
}
