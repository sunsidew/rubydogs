#encoding: UTF-8

require "google_drive"
require "open-uri"
require "nokogiri"

class KctController < ApplicationController
	def input
	end

	def webparse()
	end

	def putdata
            session = GoogleDrive.login("", "")
            file = session.file_by_title("code.c")
            file.download_to_file("public/code")
            
            file = File.new("public/code", "r")
            file_w = File.new("public/code_convert","w")
            
            while (line = file.gets)
                line.gsub!("&nbsp;","")
                line.gsub!("&ldquo;","&quot;")
                line.gsub!("&rdquo;","&quot;")
                line.gsub!("</p>","</p>\n")
                file_w.syswrite(line)
            end
            
            file.close
            file_w.close

            doc = Nokogiri::HTML(open("public/code_convert"))
            
            log_flag = 0

            codewrite = File.new("public/real_code.c", "w")
            file_w = File.new("public/final_output.txt","w")
            
            doc.xpath('//body[@class]/p/span').each do |a|
                if a.content == "##"
                    if log_flag == 0
                        log_flag = 1
                    else
                        log_flag = 0
                    end
                elsif log_flag == 1
                    codewrite.syswrite(a.content)
                    codewrite.syswrite("\n")
                end
                file_w.syswrite(a.content);
                file_w.syswrite("\n")
            end
            
            codewrite.close

            system("gcc -o public/a.out public/real_code.c")
            system("./public/a.out > public/c_compile")

            result_file = File.open("public/c_compile","r");
            result_string = result_file.read
            file_w.syswrite("// print start \n")
            file_w.syswrite(result_string+"\n")
            file_w.syswrite("// print end \n\n")
            result_file.close
            file_w.close

            file = session.file_by_title("code.c")
            file.update_from_file("public/final_output.txt")

            #system("./public/a.out > app/views/kct/putdata.html.erb")

            #system("rm public/real_code.c public/c_compile public/a.out public/final_output public/code public/code_convert")
    end
end
