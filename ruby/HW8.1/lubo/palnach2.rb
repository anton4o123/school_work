require 'csv'

a=[]
CSV.foreach("a.csv") do |row|
	a << [row[0],"",0.00]
end
puts a.size
a.each do |e|
	
end
