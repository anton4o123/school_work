require 'csv'
control = ARGV[1].to_f
all=[]

CSV.foreach(ARGV[0]) do |row|
	if row[2].to_f>control
		all << [row[0],row[1],row[2],row[3],row[4],row[5]]
	end
end

all=all.sort {|a,b| b[2] <=> a[2]}
CSV.open("#{ARGV[0].chomp(".csv")}_result.csv","w") do |csv|
	all.each do |element|
		csv << element
	end
end
