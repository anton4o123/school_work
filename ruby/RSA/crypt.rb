print "Molq vavedete 'n': "
n=gets.chomp.to_i
print "Molq vavedete 'e': "
e=gets.chomp.to_i
print "Molq vavedete 'd': "
d=gets.chomp.to_i
print "Molq vavedete suobshtenie: "
m=gets.chomp.to_i
print "Molq izberete 'crypt' ili 'decrypt': "
check=gets.chomp

if check=="crypt"
	c=m**e%n
	puts c
elsif check=="decrypt"
	dm=m**d%n
	puts dm
else
	puts "Wrong choice!"
end
