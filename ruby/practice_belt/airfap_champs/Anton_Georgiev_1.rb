require 'csv'
champs=[]

CSV.foreach(ARGV[0]) do |row|
	if row[1]==ARGV[1]
		champs << [row[0].gsub("champ_","").gsub("_",' '),row[3]]
	end
end

champs=champs.sort {|a,b| a[1] <=> b[1]}
CSV.open("#{ARGV[0].chomp(".csv")}_result.csv","w") do |csv|
	champs.each do |element|
		csv << element
	end
end
