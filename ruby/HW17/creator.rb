require 'csv'

all=[]

all << [1,2]
i=3
while i<21
	for j in 1..i-1
		all << [i,j]
	end
	i+=1
end

CSV.open("cab.csv","w") do |csv|
	all.each do |element|
		csv << element
	end
end
