require 'csv'
iz=[]

CSV.foreach(ARGV[0]) do |row|
	if row[4][0..2]==ARGV[1]
		iz << [row[0],row[1],row[2].to_i,row[3],row[4],row[5]]
	end
end

iz=iz.sort {|a,b| a[2] <=> b[2]}
CSV.open("#{ARGV[0].chomp(".csv")}_result.csv","w") do |csv|
	iz.each do |element|
		csv << element
	end
end
