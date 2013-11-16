require 'csv'
all=[]

CSV.foreach(ARGV[0]) do |row|
	if ARGV[1].to_i<=row[5].to_i
		all << [row[0],row[1],row[2],row[3],row[4],row[5].to_i]
	end
end

all=all.sort {|a,b| a[5] <=> b[5]}
CSV.open("laptops_price_result.csv","w") do |csv|
	all.each do |e|
		csv << e
	end
end
