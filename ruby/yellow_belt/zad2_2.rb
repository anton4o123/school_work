require 'csv'

all=[]
CSV.foreach(ARGV[0]) do |row|
	i=0
	all.each do |element|
		if element[0]==row[4].split(" ")[0]
			element[1]+=row[2].to_i
			i=1
			break
		end
	end
	if i!=1
		if row[4].split(" ")[0].length==3
			all << [row[4].split(" ")[0],row[2].to_i]
		end
	end
end

all=all.sort {|a,b| a[1]<=>b[1]}
CSV.open("#{ARGV[0].chomp(".csv")}_result.csv","w") do |csv|
	all.each do |element|
		csv << element
	end
end
