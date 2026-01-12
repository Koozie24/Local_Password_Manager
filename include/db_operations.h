#ifndef DB_OPERATIONS_H

#define DB_OPERATIONS_H
/*Takes a string argument of a username to search and a shared pointer to a connection to sql database.
substitutes username to a prepared statement and return a pointer to a result set*/
std::unique_ptr<sql::ResultSet> get_username(const std::string &search_name, std::shared_ptr<sql::Connection> conn);

#endif
