def check_if_prime(n)
	if(n<1)
		return false
	end
	
	for i in 2..n-1
		if n%i==0
			return false
		end
	end
	return true
end

def get_prime_number(bound, precise)
	while(true)
		n=rand(bound)+precise
		if check_if_prime(n)==true
			return n
		end
	end
end

p=get_prime_number(384, 128)
begin
	q=get_prime_number(384, 128)
end until p!=q

n=p*q
fn=(p-1)*(q-1)

begin
	e=get_prime_number(fn-3, 2)
end until fn.gcd(e)==1

i=1
while(true)
	if (fn*i+1)%e==0
		d=(fn*i+1)/e
		break
	end
	i+=1
end

printf("%d %d\n", n, e)
printf("%d %d\n", n, d)
