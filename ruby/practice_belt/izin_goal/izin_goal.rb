require 'csv'
teams=[]
goal_difference=0

CSV.foreach("bpl.csv") do |row|
	if ARGV[0]==row[1]
		goal_difference=row[5].to_i
	end
end

CSV.foreach("bpl.csv") do |row|
	if goal_difference<row[5].to_f
		teams << [row[0].to_i,row[1],row[2],row[3],row[4],row[5],row[6]]
	end
end

teams=teams.sort {|a,b| a[0] <=> b[0]}
CSV.open("#{ARGV[0]}_result.csv","w") do |csv|
	teams.each do |element|
		csv << element
	end
end
