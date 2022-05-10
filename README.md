# cpp_sqlite

Пример сборки проекта:
```bash
mkdir build&&cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

См. файлы `sqlite3.c` и `sqlite3.h`, которые будут распакованы в build-директорию `sqlite3-src` с помощью cmake-пакета FetchContent.

Пример использования:

```bash
./cpp_sqlite
# Usage: ./cpp_sqlite <SQL>

ls *.sqlite
# Нет такого файла или каталога
./cpp_sqlite "SELECT * FROM t;"
# cpp_sqlite_db.sqlite database opened successfully!
# Can't execute query: no such table: t

ls --size *.sqlite
# 0 cpp_sqlite_db.sqlite
```
Первый запуск неуспешный, потому файл с БД не будет создан. Второй запуск создаёт БД, но ввиду отсутствия таблицы t в БД, завершается с ошибкой.

Создаём таблицу, добавляем в ней данные и выводим её содержимое.

```bash
./cpp_sqlite "CREATE TABLE t (a int, b text);"
# cpp_sqlite_db.sqlite database opened successfully!
ls --size *.sqlite
# 8 cpp_sqlite_db.sqlite

./cpp_sqlite "INSERT INTO t VALUES(100, 'Hello');"
# cpp_sqlite_db.sqlite database opened successfully!
./cpp_sqlite "INSERT INTO t VALUES(200, 'World\!');"
# cpp_sqlite_db.sqlite database opened successfully!
ls --size *.sqlite
# 8 cpp_sqlite_db.sqlite

./cpp_sqlite "SELECT * FROM t;"
# cpp_sqlite_db.sqlite database opened successfully!
# a = 100
# b = Hello
#
# a = 200
# b = World\!
```
