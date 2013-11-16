require 'csv'
players=[]
searched_players=[]

CSV.foreach(ARGV[0]) do |row|
	players << row
end
i=0
players.sort_by! { |e| [e[1].to_i, e[0].to_i] }.reverse!
players.each do |e|
	i+=1
	if ARGV[1].to_i==e[0].to_i
		searched_players << e
		break
	end
end
j=0
players.each do |e|
	j+=1
	if (j>=i-5 && j<i) || (j>i && j<=i+5)
		searched_players << e
	end
end

searched_players.sort_by! {|e| [e[1].to_i,e[0].to_i]}

CSV.open(ARGV[2],"w") do |csv|
	searched_players.each do |e|
		csv << e
	end
end
