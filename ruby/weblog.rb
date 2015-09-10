# Weblog.rb
# Define a class for holding a weblog object
# @Author FoxBoxPDX
class Weblog
  # Declare attrs
  attr_accessor :ipaddr
  attr_accessor :date
  attr_accessor :request
  attr_accessor :code
  attr_accessor :size
  attr_accessor :referer
  attr_accessor :agent

  # Initialization
  def initialize(params)
    @ipaddr  = params[:ipaddr]
    @date    = params[:date]
    @request = params[:request]
    @code    = params[:code]
    @size    = params[:size]
    @referer = params[:referer]
    @agent   = params[:agent]
  end

  # Define a way to print this thing
  def to_s
    Kernel.sprintf("%-20s %-30s %-40s", @ipaddr, @date, @request)
  end

  # Hurt me beat me treat me like a String
  def to_str
    to_s
  end
end
