require 'csv'
laptops=[]

CSV.foreach(ARGV[0]) do |row|
	if row[0]==ARGV[1]
		laptops << [row[0],row[1],row[2].to_i,row[3],row[4],row[5]]
	end
end

laptops=laptops.sort {|a,b| a[2] <=> b[2]}

CSV.open("laptops_processor_result.csv","w") do |csv|
	laptops.each do |element|
		csv << element
	end
end
