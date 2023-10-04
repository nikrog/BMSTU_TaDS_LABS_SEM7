#!/bin/bash
export PGPASSWORD="admin"
psql -h localhost --port 5435 -U postgres -d postgres < ../../src/data_access/sql_scripts/create.sql
psql -h localhost --port 5435 -U postgres -d postgres < ../../src/data_access/sql_scripts/fill_tables.sql
rm -R in
mkdir in
export GTEST_OUTPUT="xml:./in/"
./testsUserRepo.exe
./testsBankRepo.exe
./testsManagerRepo.exe
./testsClientRepo.exe
./testsProductRepo.exe
./testsRequestRepo.exe
python2 ../gen_report_scripts/genHtmlReportFromGtest.py "out/gtest_report.html" "in/*.xml"
