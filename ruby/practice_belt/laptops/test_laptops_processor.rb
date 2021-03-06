is_ok = false

Dir.glob(ARGV[0]) do |file|
	`mkdir test_execution`
	`cp laptops_processor_expected.csv test_execution`
	`cp #{file} test_execution`
	`cp laptops.csv test_execution`

	begin		
		Dir.chdir "test_execution"
		`ruby #{file} laptops.csv iNtEl`
		result = `diff laptops_processor_expected.csv laptops_processor_result.csv`
	rescue Exception => e
		p false
	else
		is_ok = true if result == ""
	end	

	puts is_ok
	Dir.chdir ".."
	`rm -rf test_execution`
end
