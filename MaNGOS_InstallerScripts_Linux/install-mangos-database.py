#!/usr/bin/python
import re, os, sys

match_dbline = re.compile('^<(?P<dbsrctree>\w+)(((:)(?P<dbname>\w+))|())>(?P<sqlfile>.+)', re.I | re.M | re.X);

def execute_sql_file(dbname, tree, file, args):
	if tree == "mangos":
		exec_tree = "mangos"
	elif tree == "scriptdev2":
		exec_tree = "mangos/src/bindings/ScriptDev2" 
	elif tree == "acid":
		exec_tree = "sd2-acid"
	elif tree == "udb":
		exec_tree = "unifieddb"
	else:
		exec_tree = "."

	if dbname == None:
		dbname = ""
	else:
		dbname = " "+dbname

	execute_str = "mysql -u "+args['username']+args['password']+dbname+" < "+exec_tree+file
	if args['testing']:
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

def parse_cmd_args(cmd_args):
	d = dict(filename="mangos.dbinst", testing=True, password=" -p", update=False, username="root")
	cmd_args.remove(cmd_args[0])
	for cmd in cmd_args[:]:
		if cmd == "--test":
			d['testing'] = True
		elif cmd == "--execute":
			d['testing'] = False
		elif cmd.split('=')[0] == "--password":
			d['password'] = " --password=" + cmd.split('=')[1]
		elif cmd.split('=')[0] == "--user":
			d['username'] = cmd.split('=')[1]
		elif cmd == "--update":
			d['update'] = True;
		elif cmd.split('=')[0] == "--dbfile":
			d['filename'] = cmd.split('=')[1]
		cmd_args.remove(cmd)
	return d

if __name__ == '__main__':
	parsed_cmd_args = parse_cmd_args(sys.argv)
	db_install_list = open(parsed_cmd_args['filename'], 'rU')
	for query in get_sql_entries(db_install_list):
		execute_sql_file(query[1], query[0], query[2], parsed_cmd_args)

