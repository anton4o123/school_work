require 'csv'
top_players=[]

CSV.foreach(ARGV[0]) do |row|
	top_players << [row[0],row[1].to_i,row[2],row[3],row[4],row[5],row[6],row[7],row[8],row[9],row[10],row[11],row[12],row[13]]
end

top_players.sort_by! { |e| [e[1].to_i, e[0].to_i] }.reverse!
check = ARGV[1]==nil ? 5 : ARGV[1].to_i
i=0

CSV.open("top.csv","w") do |csv|
	top_players.each do |element|
		csv << element
		i+=1
		if i==check
			break
		end
	end
end
