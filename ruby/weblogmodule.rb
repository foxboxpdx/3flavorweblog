# Weblogmodule.rb
# This is just a module that we can use to define any sort of
# static variables and bind together the other components.
# @author FoxBoxPDX
module WeblogModule
  VERSION = '0.0.1'

  PATTERN = %r{(\S+)\s(\S+)\s(\S+)\s\[(\d{2}/\w+/\d{4}\:\d{2}\:\d{2}\:\d{2}\s+.+?)\]\s\"(\w+\s\S+\s\w+\/\d+\.\d+)\"\s(\d+)\s(\d+)\s\"(\S+)\"\s\"(.+)\"}

end

require 'rubygems'
require 'sqlite3'
require_relative 'weblog'
require_relative 'weblogdb'
require_relative 'parser'
