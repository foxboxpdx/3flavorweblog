# parser.rb
# Define a class to parse logs and send them to the database
# @author FoxBoxPDX
class Parser
  attr_reader :logs

  def initialize(db)
    fail StandardError, 'Need to specify a WeblogDB object' if db.nil?
    @database = db
    @logs = []
  end

  def parse_weblog(line)
    m = WeblogModule::PATTERN.match(line)
    w = Weblog.new(ipaddr: m[1], date: m[4], request: m[5], code: m[6],
                   size: m[7], referer: m[8], agent: m[9])
    @logs.push(w)
  end

  def count
    @logs.size
  end

  def to_database
    @logs.each { |l| @database.write(l) }
  end

  def to_s
    @logs.each { |l| puts l }
  end
end
