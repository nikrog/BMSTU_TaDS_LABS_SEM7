#!/bin/bash
export PGPASSWORD="admin"
psql -h localhost --port 5435 -U postgres -d postgres < test.sql
