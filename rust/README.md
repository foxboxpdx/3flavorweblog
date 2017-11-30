# multiflavorweblog - Rust
This directory contains two different examples for processing a log file using Rust.  Both read the same kind of extended log format, and utilize a simple SQLITE3 database as a backend.

## Clap
This code uses the Clap-RS crate to create a nice CLI and option-parsing front-end for the program.  Parsing is handled by the regex crate, and database operations are done via direct calls to the sqlite crate's functions.

## Diesel
This code uses more standard and basic CLI/option-parsing for the front-end, with the various operations split between files in the bin/ directory.  Parsing is again handled by regex, but in this case, database operations are done via the Diesel crate.  As such this one requires a bit more initial setup to get going.

## Pre-Requisites
*    Rust 1.22.1
*    regex and lazy_static 0.2
*    Diesel version: diesel 0.99
*    Clap version: rusqlite 0.12, clap 2.27 
