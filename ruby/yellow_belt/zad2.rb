require 'csv'
valuta = []
result = []

CSV.foreach(ARGV[0]) do |row|
     row_ch=row[4].split(" ")[0]
     row_d=row[2].to_i
     if row_ch.length==3 
       valuta << [row_ch,row_d]
       result << [0, 0]
     end
end

valuta.each do |e|
  result.each do |element|
    if element[0]==0 && element[0]!=e[0]
      element[0]=e[0]
      element[1]=e[1].to_i
      break
    elsif element[0]==e[0]
      element[1]+=e[1]
      break
    end
  end
end

result=result.sort {|a,b| a[1] <=> b[1]}

name=ARGV[0].chomp(".csv")
CSV.open("#{name}_result.csv","w") do |csv|
  result.each do |element|
	if element[0]!=0
    	csv << element
	end
  end
end
