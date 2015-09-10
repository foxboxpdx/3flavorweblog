# Weblogdb.rb
# Define a class that loads and saves to the database
# @author FoxBoxPDX
class WeblogDB
  def initialize(filename)
    fail StandardError, 'Filename required' if filename.nil?
    @filename = filename
    @dbh = SQLite3::Database.new @filename
    @dbh.results_as_hash = true
  end

  def filename=(filename)
    fail StandardError, 'Filename required' if filename.nil?
    @filename = filename
    # Reinitialize the DB Handle
    @dbh.close unless @dbh.closed?
    @dbh = SQLite3::Database.new @filename
    @dbh.results_as_hash = true
  end

  def write(log)
    sth = @dbh.prepare("INSERT OR IGNORE INTO weblogs
                 (ipaddr, date, request, code, size, referer, agent)
                 VALUES (?,?,?,?,?,?,?)")

    sth.execute(log.ipaddr, log.date, log.request, log.code.to_i, log.size.to_i, log.referer, log.agent)
  end

  def fetch(query)
    logarray = []
    sth = @dbh.prepare("SELECT * FROM weblogs WHERE #{query}")
    sth.execute.each do |row|
      w = Weblog.new(ipaddr: row['ipaddr'], date: row['date'], request: row['request'],
                     code: row['code'], size: row['size'], referer: row['referer'],
                     agent: row['agent'])
      logarray.push(w)
    end
    logarray
  end

  def fetch_all(limit = 50)
    logarray = []
    sth = @dbh.prepare("SELECT * FROM weblogs LIMIT ?")
    sth.execute(limit).each do |row|
      w = Weblog.new(ipaddr: row['ipaddr'], date: row['date'], request: row['request'],
                     code: row['code'], size: row['size'], referer: row['referer'],
                     agent: row['agent'])
      logarray.push(w)
    end
    logarray
  end

  def create_tables
    @dbh.execute("CREATE TABLE weblogs(" \
                 "ipaddr varchar(50) not null," \
                 "date varchar(50) not null," \
                 "request varchar(255) not null," \
                 "code int not null," \
                 "size int not null default 0," \
                 "referer varchar(255) not null," \
                 "agent varchar(255) not null, " \
                 "primary key (ipaddr, date) )")
  end
end
