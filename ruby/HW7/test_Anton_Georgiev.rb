require 'csv'

CSV.open("result.csv","w") do |csv|
	Dir.glob("*1.rb") do |file|
		`ruby #{file} 28.srt`
		result=`diff #{file} 28_test.txt`
		result = result.gsub(/[\n\r]/," ")
		csv << [file,result==" "]
	end
end
