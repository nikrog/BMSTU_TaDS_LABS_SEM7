#!/bin/bash
export PGPASSWORD="admin"
psql -h localhost --port 5435 -U postgres -d postgres < ../../data_access/sql_scripts/create.sql
psql -h localhost --port 5435 -U postgres -d postgres < ../../data_access/sql_scripts/fill_tables.sql
./testsUserRepo.exe
./testsBankRepo.exe
./testsManagerRepo.exe
./testsClientRepo.exe
./testsProductRepo.exe
./testsRequestRepo.exe
