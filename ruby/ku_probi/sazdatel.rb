# encoding: utf-8
require 'csv'
all=[]
all2=[]
i=0
while i<880
	x1=rand(21)-10
	x2=rand(21)-10
	if i>0
		j=0;
		while j<i
			if (all[0][i]==x1)&&(all[1][i]==x2)
				x1=rand(21)-10
				x2=rand(21)-10
				j=0
				next
			end
			j+=1
		end
	end
	all << [x1+x2,x1*x2]
	i+=1
end

all.each do |e|
	e1=rand(5)+1
	e[0]*=e1
	e[1]*=e1
	a=-e[0]>=0 ? "+" : 0
	b=e[1]>0 ? "+" : 0
	e[0]=-e[0]!=1 ? -e[0] : ""
	e[1]=e[1]!=0 ? e[1] : ""
	if a=="+" && b=="+"
		all2 << ["#{e1==1 ? "" : e1}x\u00B2#{e[0]!=0 ? a+e[0].to_s+"x" : ""}#{b}#{e[1]}=0\n"]
	elsif a=="+"
		all2 << ["#{e1==1 ? "" : e1}x\u00B2#{e[0]!=0 ? a+e[0].to_s+"x" : ""}#{e[1]}=0\n"]
	elsif b=="+"
		all2 << ["#{e1==1 ? "" : e1}x\u00B2#{e[0]!=0 ? e[0].to_s+"x" : ""}#{b}#{e[1]}=0\n"]
	else
		all2 << ["#{e1==1 ? "" : e1}x\u00B2#{e[0]!=0 ? e[0].to_s+"x" : ""}#{e[1]}=0\n"]
	end
end

File.open("uravnenia.txt","w") do |file|
	all2.each do |element|
		file.write(element[0])
	end
end
