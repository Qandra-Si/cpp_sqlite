#include <iostream>
#include <cstdarg>

#include "sqlite3.h"


int main(int argc, char **argv)
{
  if (argc != 2)
  {
    std::cerr << "Usage: " << argv[0] << " <SQL>" << std::endl;
    return EXIT_FAILURE;
  }

  const char* db_name = "cpp_sqlite_db.sqlite";
  //const char* db_name = ":memory:"; // <--- без файла, БД размещается в памяти
  sqlite3* handle = nullptr;

  if (sqlite3_open(db_name, &handle))
  {
    std::cerr << "Can't open database: " << sqlite3_errmsg(handle) << std::endl;
    sqlite3_close(handle);
    return EXIT_FAILURE;
  }
  std::cout << db_name << " database opened successfully!"<< std::endl;

  auto print_results = [](void *, int columns, char **data, char **names) -> int{
    for (int i = 0; i < columns; ++i)
      std::cout << names[i] << " = " << (data[i] ? data[i] : "NULL") << std::endl;
    std::cout << std::endl;
    return 0;
  };

  char *errmsg;
  int rc = sqlite3_exec(handle, argv[1], print_results, 0, &errmsg);
  if (rc != SQLITE_OK)
  {
    std::cerr << "Can't execute query: " << errmsg << std::endl;
    sqlite3_free(errmsg); // <--- обратите внимание не C-style работу с памятью
    return EXIT_FAILURE;
  }
  sqlite3_close(handle);

  return EXIT_SUCCESS;
}
