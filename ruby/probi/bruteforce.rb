require 'time'
def bruteforce pass_expect,pass="",len=1
	i=0
	while i<62
		if i<26
			c=(i+97).chr
		elsif i<52
			c=(i+39).chr
		else
			c=(i-4).chr
		end
		if pass_expect==pass+c
			puts pass+c
			i=101
			break
		end
		if (pass+c).length<len
			bruteforce pass_expect,pass+c,len
			puts 'ho'
			puts i
		end
		if i>100
			break
		end
		i+=1
	end
	return i
end

d=Time.now
bruteforce ARGV[0],"",ARGV[1].to_i
puts Time.now-d
