require 'csv'
numbers = []


CSV.foreach(ARGV[0]) do |row|
   numbers << [row[0].to_i,row[1].to_i,0]
end

numbers.each do |element|
   element[2]=rand(element[1]/2)
end

CSV.open("#{ARGV[0]}_result.csv","w") do |csv|
   numbers.each do |element|
   csv << element
end
end
