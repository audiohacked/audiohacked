#!/usr/bin/python
import re, os, sys, subprocess
import optparse
import _mysql
sys.path.insert( 0, os.path.abspath("libs"))

import dep_check

if os.name == "nt":
    os.environ['path'] += ";C:\\Program Files\\WinRAR\\"
    
match_dbline = re.compile('^<(?P<dbsrctree>\w+)(((:)(?P<dbname>\w+))|())(((:)(?P<rarfile>.+))|())>(?P<sqlfile>.+)', re.I | re.M | re.X);
mangos_dbversion_str = {'characters':'character_db_version',
                        'mangos':'db_version',
                        'realmd':'realmd_db_version',
                        'scriptdev2':'sd2_db_version'}
    
def delete_mangos_dbs(args, full_clean=False):
    conn = _mysql.connect(host="localhost",
                          port=3306,
                          user=args.username,
                          passwd=args.passwd)

    try:
        try:
            print "Dropping Database: mangos"
            conn.query("DROP DATABASE mangos;")
        except _mysql.OperationalError:
            pass
        
        try:
            print "Dropping Database: scriptdev2"
            conn.query("DROP DATABASE scriptdev2;")
        except _mysql.OperationalError:
            pass
        
        if full_clean:
            try:
                print "Dropping Database: characters"
                conn.query("DROP DATABASE characters;")
            except _mysql.OperationalError:
                pass
        
            try:
                print "Dropping Database: realmd"
                conn.query("DROP DATABASE realmd;")
            except _mysql.OperationalError:
                pass
    finally:
        conn.close()

 
def fresh_db_install(args):
    print "Performing a Fresh Install"
    delete_mangos_dbs(args, full_clean=True)
    db_install_list = open(args.filename, 'rU')
    for query in get_sql_entries(db_install_list):
        extract_sql_files(query, args)
        execute_sql_file(query, args)

def update_db_install(args):
    print "Performing an Update Install"
    delete_mangos_dbs(args)
    db_install_list = open(args.filename, 'rU')
    for query in get_sql_entries(db_install_list):
        extract_sql_files(query, args)
        execute_sql_file(query, args)
    
##def get_mangos_db_version(args, dbname="characters"):
##    conn = _mysql.connect(host="localhost",
##                          port=3306,
##                          user=args.username,
##                          passwd=args.passwd)
##    conn.query("SHOW COLUMNS FROM "+dbname+"."+mangos_dbversion_str[dbname])
##    result = conn.store_result()
##    print result.fetch_row()[0][0]

def extract_sql_files(dbquery, args):
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

    if dbquery['rarfile'] != None and not args.testing:
        print "Extracting rar: "+os.path.dirname(exec_tree+dbquery['sqlfile'])+"/"+dbquery['rarfile']
        home = os.getcwd()
        os.chdir(os.path.dirname(exec_tree+dbquery['sqlfile']))
        subprocess.call("unrar e -y \""+dbquery['rarfile']+"\"", shell=True)
        os.chdir(home)

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

    execute_str = "mysql -u "+args.username+args.cmd_passwd_str+dbname+" < "+exec_tree+dbquery['sqlfile']
    
    if args.testing:
        print execute_str
    else:
        print "Executing: ",execute_str
        try:
            retcode = subprocess.call(execute_str, shell=True)
            if retcode < 0:
                print >>sys.stderr, "Child was terminated by signal", -retcode
            #else:
            #   print >>sys.stderr, "Child returned", retcode
        except OSError, e:
            print >>sys.stderr, "Execution failed:", e
    

def get_sql_entries(db_install_list):
    queries = [] 
    buffer = db_install_list.readlines()
    for line in buffer:
        db_files = match_dbline.match(line)
        if db_files != None:
            queries.append( db_files.groupdict() )
    return queries

def parse_password_callback(option, opt, value, parser):
        parser.values.cmd_passwd_str = " --password="+value
        parser.values.passwd = value

def parse_update_callback(option, opt, value, parser):
        parser.values.update = True
        if parser.values.filename == "fresh.dbinst":
            parser.values.filename = "update.dbinst"
            
def parse_cmd_args():
    parser = optparse.OptionParser(version="%prog 1.0")

    parser.set_defaults(username="mangos", 
                        passwd="mangos",
                        filename="fresh.dbinst",
                        update=False)
    
    parser.add_option("-t", "--test", "--dry-run",
                      action="store_true",
                      dest="testing",
                      default=False)
    
    parser.add_option("-x", "--exec", "--execute",
                      action="store_false",
                      dest="testing",
                      default=False)

    parser.add_option("--up", "--update",
                      action="callback",
                      callback=parse_update_callback,                    
                      dest="update",
                      default=False)
    
    parser.add_option("-p", "--pass", "--password",
                      action="callback",
                      type="string",
                      callback=parse_password_callback,
                      dest="cmd_passwd_str",
                      default=" -p")
    
    parser.add_option("-u", "--user", "--username",
                      action="store",
                      dest="username")
    
    parser.add_option("--db", "--dbfile",
                      action="store",
                      dest="filename")

    (options, args) = parser.parse_args()
    return options

if __name__ == '__main__':
    my_args = parse_cmd_args()
    #print (my_args)
    if os.name == "nt":
        dep_check.win32()
    else:
        dep_check.linux()

    if my_args.update:
        update_db_install(my_args)
    else:
        fresh_db_install(my_args)
