#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <cctype>
#include <sqlite3.h>    // for sqlite3
#include "socket-setup.hpp"

extern sqlite3 *db;
extern char* ErrMsg;
extern int rc;
extern std::string History;

void Database_TABLE_CREATION();
void Database_INSERT(const std::string& command );
void Database_SELECT();
void Database_DELETE();
void Database_Close();
static int callback(void *NotUsed, int argc, char **argv, char **azColName);


std::string trim(const std::string& command) ;


#endif