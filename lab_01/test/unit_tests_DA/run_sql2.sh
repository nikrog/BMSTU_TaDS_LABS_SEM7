#!/bin/bash
rm -R in
mkdir in
export GTEST_OUTPUT="xml:./in/"
export GTEST_SHUFFLE=0
./testsUserRepo2.exe
./testsBankRepo2.exe
./testsManagerRepo2.exe
./testsClientRepo2.exe
./testsProductRepo2.exe
./testsRequestRepo2.exe
python2 ../gen_report_scripts/genHtmlReportFromGtest.py "out/gtest_report.html" "in/*.xml"
