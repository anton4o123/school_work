require 'csv'

CSV.open("task5.csv","w") do |csv|
	i=0
	while i<1000
		b=rand(604)+1
		h=rand(24)
		if h<10
			h1="0"+h.to_s
		else h1=h.to_s
		end
		m=rand(60)
		if m<10
			m1="0"+m.to_s
		else m1=m.to_s
		end
		t=h1+":"+m1
		csv << [b,t]
		i+=1
	end
end
