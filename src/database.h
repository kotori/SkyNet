#ifndef DATABASE_H
#define DATABASE_H

// Default location of the database
#define DEFAULT_LOC "database.db"

// Turn off/on logging
#define ACTIVE_LOGGING false

namespace KotoriApp
{
	class Database
	{
	public:
		Database();
		Database(char *loc);
		~Database();

		bool SelectInt(int &refVal, const char *sql, ...);
		bool SelectStr(std::string &refVal, const char *sql, ...);
		bool SelectChar(char* refVal, const char *sql, ...);

		char* Format(const char *msg, ...);
		bool Exec(const char *sql, ...);
	private:
		void Common();
		void Close();
		bool Open();

		bool is_open_;
		bool log_enabled_;
		char *db_loc_;
		sqlite3 *db_;
		sqlite3_stmt *stmt_;
	};
}

#endif // DATABASE_H

