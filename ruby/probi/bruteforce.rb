require 'time'
def bruteforce pass_expect,pass="",len=1
	i=0
	while i<26
		if pass_expect==pass+(i+97).chr
			puts pass+(i+97).chr
			break
		end
		if (pass+(i+97).chr).length<len
			bruteforce pass_expect,pass+(i+97).chr,len
		end
		i+=1
	end
end

d=Time.now
bruteforce ARGV[0],"",ARGV[1].to_i
puts Time.now-d
