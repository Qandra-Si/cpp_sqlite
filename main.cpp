#include <iostream>
#include <cstdarg>

#include "sqlite3.h"


static int callback(void *NotUsed, int argc, char **argv, char **azColName);

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    std::cerr << "Usage: " << argv[0] << " <SQL>" << std::endl;
    return EXIT_FAILURE;
  }

  const char* db_name = "cpp_sqlite_db.sqlite";
  sqlite3* handle = nullptr;

  if (sqlite3_open(db_name, &handle))
  {
    std::cerr << "Can't open database: " << sqlite3_errmsg(handle) << std::endl;
    sqlite3_close(handle);
    return EXIT_FAILURE;
  }
  std::cout << db_name << " database opened successfully!"<< std::endl;

  char *errmsg;
  int rc = sqlite3_exec(handle, argv[1], callback, 0, &errmsg);
  if (rc != SQLITE_OK)
  {
    std::cerr << "Can't execute query: " << errmsg << std::endl;
    sqlite3_free(errmsg);
    return EXIT_FAILURE;
  }
  sqlite3_close(handle);

  return EXIT_SUCCESS;
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
  for (int i = 0; i < argc; ++i)
    std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << std::endl;
  std::cout << std::endl;
  return 0;
}
