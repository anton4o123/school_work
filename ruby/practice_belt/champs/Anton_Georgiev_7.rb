require 'csv'
require 'csv'

small_date=DateTime.parse("9999-12-31")
big_date=DateTime.new
date=[]

CSV.foreach(ARGV[0]) do |row|
	if big_date<DateTime.parse(row[2].split("date_")[1])
		big_date=DateTime.parse(row[2].split("date_")[1])
	end
	if small_date>DateTime.parse(row[2].split("date_")[1])
		small_date=DateTime.parse(row[2].split("date_")[1])
	end
end

CSV.foreach(ARGV[0]) do |row|
	if small_date==DateTime.parse(row[2].split("date_")[1]) || big_date==DateTime.parse(row[2].split("date_")[1])
		date << [row[0].split("champ_")[1].gsub("_"," "),row[2].split("date_")[1]]
	end
end

date=date.sort {|a,b| a[1] <=> b[1]}

CSV.open("#{ARGV[0].chomp(".csv")}_result.csv","w") do |csv|
	date.each do |element|
		csv << element
	end
end
