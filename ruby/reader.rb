#!/usr/bin/env ruby
# Reader.rb
# Read in a specified file or dump out the specified number of records
# @author FoxBoxPDX
require_relative 'weblogmodule'

command = ARGV.shift
param = ARGV.shift

if command.nil?
  puts "Usage:\n\t#{$0} parse <filename>\n\t#{$0} fetch <num records>\n\t#{$0} create table"
  exit(1)
end

case command
when 'parse'
  if param.nil?
    puts "Usage:\n\t#{$0} parse <filename>\n\t#{$0} fetch <num records>\n\t#{$0} create table"
    exit(1)
  end
  db = WeblogDB.new("test.db")
  p = Parser.new(db)
  puts "Reading file: #{param}"
  f = File.open(param, 'r')
  f.each_line { |line| p.parse_weblog(line) }
  f.close
  puts "Processed #{p.count} logs."
  p.to_database
  puts "Wrote to database ok."
  exit(0)
when 'fetch'
  db = WeblogDB.new("test.db")
  param = 50 if param.nil?
  puts "Fetching #{param} records from database..."
  logs = db.fetch_all(param)
  logs.each { |log| puts log }
  exit(0)
when 'create'
  db = WeblogDB.new("test.db")
  db.create_tables
  puts "Created Tables"
else
  puts "Usage:\n\t#{$0} parse <filename>\n\t#{$0} fetch <num records>\n\t#{$0} create table"
  exit(1)
end
