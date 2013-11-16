require 'date'

dead=0
noSuccess=1

jiv=365*24*60*60

d1=DateTime.now
while noSuccess
	dead+=1

	if dead==jiv
		break
	end
end
d2=DateTime.now
puts d2-d1
