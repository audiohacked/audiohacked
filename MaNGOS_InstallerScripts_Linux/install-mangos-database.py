#!/usr/bin/python
import re, os, sys
import optparse

match_dbline = re.compile('^<(?P<dbsrctree>\w+)(((:)(?P<dbname>\w+))|())(((:)(?P<rarfile>.+))|())>(?P<sqlfile>.+)', re.I | re.M | re.X);

def execute_sql_file(dbquery, args):
	if dbquery['dbsrctree'] == "mangos":
		exec_tree = "mangos"
	elif dbquery['dbsrctree'] == "scriptdev2":
		exec_tree = "mangos/src/bindings/ScriptDev2" 
	elif dbquery['dbsrctree'] == "acid":
		exec_tree = "sd2-acid"
	elif dbquery['dbsrctree'] == "udb":
		exec_tree = "unifieddb"
	else:
		exec_tree = "."

	if dbquery['dbname'] == None:
		dbname = ""
	else:
		dbname = " "+dbquery['dbname']

	execute_str = "mysql -u "+args.username+args.password+dbname+" < "+exec_tree+dbquery['sqlfile']
	
	if dbquery['rarfile'] != None:
		#print "Extracting rar: "+os.path.dirname(exec_tree+dbquery['sqlfile'])+"/"+dbquery['rarfile']
		home = os.getcwd()
		os.chdir(os.path.dirname(exec_tree+dbquery['sqlfile']))
		os.system("unrar e \""+dbquery['rarfile']+"\"")
		os.chdir(home)
	
	if args.testing:
		print execute_str
	else:
		print "Executing: "+execute_str
		os.system(execute_str)

def get_sql_entries(db_install_list):
	queries = [] 
	buffer = db_install_list.readlines()
	for line in buffer:
		db_files = match_dbline.match(line)
		if db_files != None:
			queries.append( db_files.groupdict() )
	return queries

def parse_password_callback(option, opt, value, parser):
		parser.values.password = " --password="+value

def parse_cmd_args():
	parser = optparse.OptionParser(version="%prog 1.0")
	
	parser.add_option("-t", "--test",
		action="store_true",
		dest="testing",
		default=True)

	parser.add_option("-x", "--exec", "--execute", 
		action="store_false",
		dest="testing",
		default=True)

	parser.add_option("--up", "--update", 
		action="store_true",
		dest="update")
	
	parser.add_option("-p", "--pass", "--password", 
		action="callback",
		type="string",
		callback=parse_password_callback,
		dest="password",
		default=" -p")
	
	parser.add_option("-u", "--user", "--username",
		action="store",
		dest="username",
		default="root")
	
	parser.add_option("--db", "--dbfile", 
		action="store",
		dest="filename",
		default="fresh.dbinst")

	(options, args) = parser.parse_args()
	return options

if __name__ == '__main__':
	my_args = parse_cmd_args()
	print my_args
	db_install_list = open(my_args.filename, 'rU')
	for query in get_sql_entries(db_install_list):
		execute_sql_file(query, my_args)

