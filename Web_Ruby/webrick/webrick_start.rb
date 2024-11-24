# include webrick Web server
require 'webrick'
include WEBrick
require 'pathname'

port = 3000
document_root = Pathname.pwd + "httpd_root"
document_root = document_root.to_s

# fix problems in webrick itself
module WEBrick
  module HTTPServlet
    class ERBHandler < AbstractServlet
      def do_GET(req, res)
        unless defined?(ERB)
          @logger.warn "#{self.class}: ERB not defined."
          raise HTTPStatus::Forbidden, "ERBHandler cannot work."
        end
        begin
          # make sure encoding is UTF-8
          # data = File.open(@script_filename, &:read)
          data = File.open(@script_filename, 'r:utf-8', &:read)
          res.body = evaluate(ERB.new(data), req, res)
          res['content-type'] ||=
            HTTPUtils::mime_type(@script_filename, @config[:MimeTypes])
        rescue StandardError
          raise
        rescue Exception => ex
          @logger.error(ex)
          raise HTTPStatus::InternalServerError, ex.message
        end
      end
      private
      def evaluate(erb, servlet_request, servlet_response)
        Module.new.module_eval{
          # add next line so that students don't have to
          extend self
          servlet_request.meta_vars
          servlet_request.query
          erb.result(binding)
        }
      end      
    end
  end
end

# get path to ruby executable
begin # assume something like Linux
  ruby_executable = `which ruby`.chomp
  ruby_executable_version = `#{ruby_executable} -v`.chomp
rescue Exception
  begin
    document_root = document_root.gsub(/\//, "\\")
    ruby_executable = `where.exe ruby.exe`.each_line.first.chomp
    ruby_executable_version = `#{ruby_executable} -v`.chomp
  rescue Exception
  end
end
if ruby_executable
  puts "Ruby executable: #{ruby_executable}"
else
  puts "Ruby executable unclear."
end
if ruby_executable_version
  puts "Ruby executable version: #{ruby_executable_version}"
else
  puts "Ruby executable version unclear."
end
puts "Document root directory: #{document_root}"

module WEBrick::HTTPServlet
  FileHandler.add_handler("rb", CGIHandler)
  FileHandler.add_handler("erb", ERBHandler)
end

# create new server
server = HTTPServer.new(
  :Port           => port, 
  :DocumentRoot   => document_root, #Dir.pwd, #document_root.to_s, # directory is not present working directory
  :CGIInterpreter => ruby_executable
)

# show how to access this server
puts "Listening on port: #{port}."
puts "On your local machine, access with http://localhost:#{port}/."
puts "On the server, access with http://XXXX.sw.it.aoyama.ac.jp/,"
puts "where XXXX is your userid."

# make sure we can shut down the server with Ctrl-C
Signal.trap('SIGINT') { server.shutdown }

# actually start the server
server.start