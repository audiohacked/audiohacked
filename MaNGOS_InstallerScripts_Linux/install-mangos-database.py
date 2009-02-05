#!/usr/bin/python
import re, os, sys

username = "root"
password = " -p"
match_dbline = re.compile('^<(?P<dbsrctree>\w+)(((:)(?P<dbname>\w+))|())>(?P<sqlfile>.+)', re.I | re.M | re.X);
filename = "mangos.dbinst"

def execute_sql_file(dbname, tree, file, noexec):
	if tree == "mangos":
		exec_tree = "mangos"
	elif tree == "scriptdev2":
		exec_tree = "mangos/src/bindings/ScriptDev2" 
	elif tree == "acid":
		exec_tree = "sd2-acid"
	elif tree == "udb":
		exec_tree = "unifieddb/trunk"
	else:
		exec_tree = ""

	if dbname == None:
		dbname = ""
	else:
		dbname = " "+dbname

	execute_str = "mysql -u "+username+password+dbname+" < "+exec_tree+file
	if noexec:
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
			queries.append( list(db_files.group('dbsrctree', 'dbname', 'sqlfile')) )
	return queries

if __name__ == '__main__':
	testing = 1;
	for cmd_arg in sys.argv[1:]:
		if cmd_arg == "--test":
			testing = 1
		elif cmd_arg == "--execute":
			testing = 0
		elif cmd_arg.split('=')[0] == "--password":
			password = " --password=" + cmd_arg.split('=')[1]
		elif cmd_arg.split('=')[0] == "--user":
			username = cmd_arg.split('=')[1]
		else:
			filename = cmd_arg
	db_install_list = open(filename, 'rU')
	for query in get_sql_entries(db_install_list):
		execute_sql_file(query[1], query[0], query[2], testing)

