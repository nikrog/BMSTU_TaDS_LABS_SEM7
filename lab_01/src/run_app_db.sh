#qmake -makefile -o Makefile
#make
#make clean
#!/bin/bash
export PGPASSWORD="admin"
psql -h localhost --port 5435 -U postgres -d postgres < ./data_access/sql_scripts/create.sql
psql -h localhost --port 5435 -U postgres -d postgres < ./data_access/sql_scripts/constraints.sql
psql -h localhost --port 5435 -U postgres -d postgres < ./data_access/sql_scripts/fill_tables.sql
psql -h localhost --port 5435 -U postgres -d postgres < ./data_access/sql_scripts/functions.sql
psql -h localhost --port 5435 -U postgres -d postgres < ./data_access/sql_scripts/procedures.sql
psql -h localhost --port 5435 -U postgres -d postgres < ./data_access/sql_scripts/triggers.sql
psql -h localhost --port 5435 -U postgres -d postgres < ./data_access/sql_scripts/roles.sql
./ppo
