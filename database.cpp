#include "database.hpp"

sqlite3 *db;
char* ErrMsg=0;
int rc;


void Database_TABLE_CREATION()
{
    rc = sqlite3_open("commands.db", &db);

    if(rc) // check if the database was opened or not
    {
        std::cout << "Can't open database : " << sqlite3_errmsg(db) << "\n";
    }
    else
    {
        std::cout << "Database opened successfully\n";
    }  
    
    const char* sql = "CREATE TABLE IF NOT EXISTS COMMANDS_HISTORY(" \
                      "COMMAND CHAR(50) );";

    rc = sqlite3_exec(db, sql, 0, 0, &ErrMsg);

    if(rc!=SQLITE_OK) // checks if the table was created or not
    {
        std::cout << "SQL Error : " << ErrMsg << "\n";
        sqlite3_free(ErrMsg);
    }
    else
    {
        std::cout << "SQL Table was created successfully\n";
    }
}


std::string trim(const std::string& command) 
{
    auto start = command.begin();
    while (start != command.end() && std::isspace(*start)) {
        start++;
    }

    auto end = command.end();
    do {
        end--;
    } while (std::distance(start, end) > 0 && std::isspace(*end));

    return std::string(start, end + 1);
}




void Database_INSERT(const std::string& command )
{
    std::string commandd="anaaaa";

    
    //command.erase(std::find(command.begin(), command.end(), '\0'), command.end());
    //command.erase(std::remove(command.begin(), command.end(), '\0'), command.end());


    std::string insert_sql = "INSERT INTO COMMANDS_HISTORY (COMMAND) VALUES (\'" + command + "\');";
    //std::string insert_sql = "INSERT INTO COMMANDS_HISTORY (COMMAND) VALUES ('open');";
    std::cout << insert_sql << "\n";
    rc = sqlite3_exec(db, insert_sql.c_str(), 0, 0, &ErrMsg);

    if(rc!=SQLITE_OK) //checks if the insertion was successful or not
    {
        std::cout << "SQL Error (INSERT) : " << ErrMsg << "\n";
        sqlite3_free(ErrMsg);
    }
    else
    {
        std::cout << "SQL Insertion was Successful\n";
    }
}

void Database_SELECT()
{
    const char *selectSQL = "SELECT * FROM COMMANDS_HISTORY;";
    rc = sqlite3_exec(db, selectSQL, callback, 0, &ErrMsg );
    if(rc!=SQLITE_OK) //checks if the selection was successful or not
    {
        std::cout << "SQL Error (SELECT) : " << ErrMsg << "\n";
        sqlite3_free(ErrMsg);
    }
    else
    {
        std::cout << "SQL Select was Successful\n";
    }
}

void Database_DELETE()
{
    // SQL statement to delete all rows from the table
    const char* deleteSQL = "DELETE FROM COMMANDS_HISTORY;";

    // Execute the DELETE SQL statement to clear the table
    rc = sqlite3_exec(db, deleteSQL, 0, 0, &ErrMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error (DELETE): " << ErrMsg << std::endl;
        sqlite3_free(ErrMsg);
    } else {
        std::cout << "Table cleared successfully\n";
    }
}

void Database_Close()
{
    sqlite3_close(db);
}

std::string History;

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    
    // argc: number of columns, argv: array of column values, azColName: array of column names
    for (int i = 0; i < argc; i++) 
    {
        std::cout << azColName[i] << ": " << argv[i] << "\n";
        History += std::string(azColName[i])+ ": " + argv[i];
    }
    return 0;
}
