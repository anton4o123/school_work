require 'csv'
bank=[]
bank2=[]
i=0

CSV.foreach(ARGV[0]) do |row|
	if row[5]==ARGV[1]
		j=1
		if i>0
			bank.each do |element|
				if row[1]==element[1]
					j=0
					break
				end
			end
			if j>0
				bank << row
			end
		else
			bank << row
			i+=1
		end
	end
end

bank=bank.sort {|a,b| DateTime.parse(a[1]) <=> DateTime.parse(b[1])}

bank.each do |e|
	bank2 << e[1].split("/")
end

CSV.open(ARGV[2],"w") do |csv|
	bank2.each do |element|
		csv << element
	end
end
