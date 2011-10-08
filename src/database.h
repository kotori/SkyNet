/*! \file database.h
    \brief SQLite3 C++ Wrapper Header

    SQLite3 C++ Wrapper Header. Contains the framework for the Database class.
*/

#ifndef DATABASE_H
#define DATABASE_H

// Default location of the database
#define DEFAULT_LOC "database.db"

// Turn off/on logging
#define ACTIVE_LOGGING false

#include "sqlite3/sqlite3.h"

/*! \namespace KotoriApp
    \brief Kotori's Application Namespace.

    Kotori's Application Namespace.
*/
namespace KotoriApp
{

/*! \class Database
    \brief Database class

    Database class provides SQLite3 I/O functionality.
*/
class Database
{
public:
    /*! \fn Database()
            \brief Database class constructor

    Database class constructor. Takes no arguments. Sets db_loc_ to DEFAULT_LOC
    		*/
    Database();

    /*! \fn Database(char *loc)
        \brief Database class constructor. With override.
    		    \param loc string representing the location of the SQLite3 database on the filesystem.

        Database class constructor. This function will allow you to specify the location of the database.
    */
    Database(char *loc);

    /*! \fn ~Database()
        \brief Database class destructor.

        Database class destructor. Nothing special here, should not be called directly.
    */
    ~Database();

    /*! \fn bool SelectInt(int &refVal, const char *sql, ...)
        \brief Select a single integer from the database.
    		    \param refVal Integer reference containing the value where are selecting.
    		    \param sql SQL string containing the select integer statement.
        \return bool False on success, True on error.

        Retrieves a single integer from the database. If an error is thrown during the select process,
    		     this function will return true. Otherwise false.
    */
    bool SelectInt(int &refVal, const char *sql, ...);

    /*! \fn bool SelectStr(std::string &refVal, const char *sql, ...)
        \brief Select a single string from the database.
        \param refVal std::string reference containing the value where are selecting.
        \param sql SQL string containing the select string statement.
        \return bool False on success, True on error.

        Retrieves a single std::string from the database. If an error is thrown during the select process,
         this function will return true. Otherwise false.
    */
    bool SelectStr(std::string &refVal, const char *sql, ...);

    /*! \fn bool SelectChar(char* refVal, const char *sql, ...)
        \brief Select a single string from the database.
        \param refVal char string array  containing the value where are selecting.
        \param sql SQL string containing the select string statement.
        \return bool False on success, True on error.

        Retrieves a single char string array from the database. If an error is thrown during the select process,
         this function will return true. Otherwise false.
    */
    bool SelectChar(char* refVal, const char *sql, ...);

    /*! \fn char* Format(const char *msg, ...)
        \brief Formats a string with printf style arguments.
        \param msg string to process containing printf arguments.
        \return A printf style formatted string.

    		    Formats a string with printf style arguments "%s,%i" and returns a string with the variables embedded.
    */
    char* Format(const char *msg, ...);

    /*! \fn bool Exec(const char *sql, ...)
        \brief Executes a SQL statement that does NOT require a returned value.
        \param sql SQL string containing the code you want to execute.
        \return bool False on success, True on error.

        Executes a SQL command that does not require a returned value, example: CREATE, DROP, UPDATE, INSERT. If an error
         is thrown during the process, this function will return true. Otherwise false.
    */
    bool Exec(const char *sql, ...);

private:

    /*! \fn void Common()
        \brief Runs routines that are common among the constructors.

        This function is called by the different constructors to maximize code reusage.
    */
    void Common();

    /*! \fn void Close()
        \brief Closes an open connection to the SQLite3 database.

        This function should safely close an open connection to /a db_ SQLite3 database.
    */
    void Close();

    /*! \fn bool Open()
        \brief Opens a connection to a SQLite3 database.

        This function should safely opens a connection to /a db_ SQLite3 database.
    */
    bool Open();

    bool is_open_;
    bool log_enabled_;
    char *db_loc_;
    sqlite3 *db_;
    sqlite3_stmt *stmt_;
};
}

#endif // DATABASE_H

