from crypt import crypt
from itertools import product
from sys import exit
#try:
#	index_num = int(raw_input("Enter index to start: "))
#except ValueError:
#	print("Not a number")

pass_to_crack = raw_input("Enter password to crack: ")
#raw_input("Enter salt for iterations: ")
salt = "$6$I0F5LtVX$"
dictionary = product("abcdefghijklmnopqrstuvwxyz", repeat=3)
expected = crypt(pass_to_crack, salt)

pass_dict = []

for i in dictionary:
	pass_dict.append(''.join(i))

for pass_try in pass_dict:
	if expected == crypt(pass_try, salt):
		print(pass_try)
		exit(0)

print("Sorry")
exit(1)
