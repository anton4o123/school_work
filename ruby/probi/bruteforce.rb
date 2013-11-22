require 'time'
def bruteforce pass_expect,pass="",len=1
	i=0
	j=0
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
			j=101
			break
		end
		if (pass+c).length<len
			j=bruteforce pass_expect,pass+c,len
		end
		if j>100
			break
		end
		i+=1
	end
	return j
end

d=Time.now
j=bruteforce ARGV[0],"",ARGV[1].to_i
puts Time.now-d
