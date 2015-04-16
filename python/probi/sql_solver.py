import re

tables = []

LINE_STEP = 1
SPLIT_FIELDS = ':'

def create_task_one(file_lines):	
	table_statements = [item for item in file_lines if re.match('Create table', item)]

	for i in table_statements:
		line = [item for item in file_lines if re.match(i, item)][0]
		statement = line.split('with')[0] + '('
		statement += 'id int(11) auto_increment primary key,'
		statement += file_lines[file_lines.index(i) + LINE_STEP]
		
		change_list = list(statement)
		change_list[-1] = ')'
		statement = ''.join(change_list)
		
		statement = statement.replace(SPLIT_FIELDS, ' ')
		statement = statement.replace('\t', '')
		
		tables.append(statement.split(' ')[2])
		print(statement + ';')

def create_task_two(file_lines):
	index_of_second_task = [item for item in enumerate(file_lines) if re.match(r'2\.', item[1])][0][0]
	for i in range(index_of_second_task + 1, index_of_second_task + 4):
		words = file_lines[i].split(' ')
		if((words[3] == 'one' and words[5] == 'one') or (words[3] == 'one' and words[5] == 'many')):
			print('alter table ' + words[8] + ' add column ' + words[0] + '_id int(11);')
		if(words[3] == 'many' and words[5] == 'one'):
			print('alter table ' + words[0] + ' add column ' + words[8] + '_id int(11);')
		if(words[3] == 'many' and words[5] == 'many'):
			tables.append(words[0] + '_' + words[8])
			print('create table ' + words[0] + '_' + words[8] + '(id int(11) auto_increment primary key, ' + words[0] + '_id int(11), ' + words[8] + '_id int(11));')

def create_task_three():
	for i in tables:
		print('insert into ' + i + ' values();')
		print('insert into ' + i + ' values();')

with open('anton.txt') as f:
	file_content = f.read()

file_lines = file_content.split('\n')
create_task_one(file_lines)
print('')
create_task_two(file_lines)
print('')
create_task_three()
print(tables)
