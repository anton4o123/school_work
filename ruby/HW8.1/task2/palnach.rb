require 'csv'

masiv=[]
i=0
while i<1000
	d=rand(28)+1
	if d<10
		d="0"+d.to_s
	else
		d=d.to_s
	end
	m=rand(12)+1
	if m<10
		m="0"+m.to_s
	else
		m=m.to_s
	end
	s=d + "/" + m + "/" + (rand(151)+1900).to_s
	s1=rand(201).to_f.round(2)
	s2=rand(2001).to_f.round(2)
	while s1>s2
		s2=rand(2001).to_f.round(2)
	end 
	masiv << [s,s1,s2]
	i+=1
end

CSV.open("task2.csv","w") do |csv|
	masiv.each do |element|
		csv << element
	end
end
