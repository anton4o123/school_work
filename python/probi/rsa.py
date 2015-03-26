from random import randint

def is_prime(n):
	for i in range(2, n):
		if n % i == 0:
			return False
	return True

def generate_prime():
	n = randint(2**7, 2**8 - 1)
	while(not is_prime(n)):
		n = randint(2**7, 2**8 - 1)
	return n

p = generate_prime()
q = generate_prime()
while(p == q):
	q = generate_prime()

n = p * q
fn = (p - 1) * (q - 1)
e = 65537

i = 1
while True:
	if((fn * i + 1) % e == 0):
		d = (fn * i + 1) / e
		break
	i += 1

print(str(n) + " " + str(e))
print(str(n) + " " + str(d))

m = input("Enter message to encrypt: ")
c = m**e % n
print(c)
cd = c**d % n
print(cd)
