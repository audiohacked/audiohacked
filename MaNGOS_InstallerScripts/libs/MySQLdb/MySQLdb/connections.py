"""
MySQLdb Connections
-------------------

This module implements connections for MySQLdb. Presently there is
only one class: Connection. Others are unlikely. However, you might
want to make your own subclasses. In most cases, you will probably
override Connection.default_cursor with a non-standard Cursor class.

"""

__revision__ = "$Revision: 592 $"[11:-2]
__author__ = "$Author: kylev $"[9:-2]


def defaulterrorhandler(connection, cursor, errorclass, errorvalue):
    """
    If cursor is not None, (errorclass, errorvalue) is appended to
    cursor.messages; otherwise it is appended to connection.messages. Then
    errorclass is raised with errorvalue as the value.

    You can override this with your own error handler by assigning it to the
    instance.
    """
    error = errorclass, errorvalue
    if cursor:
        cursor.messages.append(error)
    else:
        connection.messages.append(error)
    del cursor
    del connection
    raise errorclass(errorvalue)


class Connection(object):

    """MySQL Database Connection Object"""

    errorhandler = defaulterrorhandler
    
    from MySQLdb.exceptions import Warning, Error, InterfaceError, DataError, \
         DatabaseError, OperationalError, IntegrityError, InternalError, \
         NotSupportedError, ProgrammingError

    def __init__(self, *args, **kwargs):
        """
        Create a connection to the database. It is strongly recommended that
        you only use keyword parameters. Consult the MySQL C API documentation
        for more information.

        host
          string, host to connect
          
        user
          string, user to connect as

        passwd
          string, password to use

        db
          string, database to use

        port
          integer, TCP/IP port to connect to

        unix_socket
          string, location of unix_socket to use

        conv
          conversion dictionary, see MySQLdb.converters

        connect_timeout
          number of seconds to wait before the connection attempt
          fails.

        compress
          if set, compression is enabled

        named_pipe
          if set, a named pipe is used to connect (Windows only)

        init_command
          command which is run once the connection is created

        read_default_file
          file from which default client values are read

        read_default_group
          configuration group to use from the default file

        cursorclass
          class object, used to create cursors (keyword only)

        use_unicode
          If True, text-like columns are returned as unicode objects
          using the connection's character set.  Otherwise, text-like
          columns are returned as strings.  columns are returned as
          normal strings. Unicode objects will always be encoded to
          the connection's character set regardless of this setting.

        charset
          If supplied, the connection character set will be changed
          to this character set (MySQL-4.1 and newer). This implies
          use_unicode=True.

        sql_mode
          If supplied, the session SQL mode will be changed to this
          setting (MySQL-4.1 and newer). For more details and legal
          values, see the MySQL documentation.
          
        client_flag
          integer, flags to use or 0
          (see MySQL docs or constants/CLIENTS.py)

        ssl
          dictionary or mapping, contains SSL connection parameters;
          see the MySQL documentation for more details
          (mysql_ssl_set()).  If this is set, and the client does not
          support SSL, NotSupportedError will be raised.

        local_infile
          integer, non-zero enables LOAD LOCAL INFILE; zero disables
    
        There are a number of undocumented, non-standard methods. See the
        documentation for the MySQL C API for some hints on what they do.

        """
        from MySQLdb.constants import CLIENT, FIELD_TYPE
        from MySQLdb.converters import conversions
        from MySQLdb.cursors import Cursor
        import _mysql
        from weakref import proxy

        kwargs2 = kwargs.copy()

        if 'conv' in kwargs:
            conv = kwargs['conv']
        else:
            conv = conversions

        conv2 = {}
        for k, v in conv.items():
            if isinstance(k, int):
                if isinstance(v, list):
                    conv2[k] = v[:]
                else:
                    conv2[k] = v
        # TODO Remove this when we can do conversions in non-C space.
        kwargs2['conv'] = conv2

        self.cursorclass = kwargs2.pop('cursorclass', Cursor)
        charset = kwargs2.pop('charset', '')

        if charset:
            use_unicode = True
        else:
            use_unicode = False
            
        use_unicode = kwargs2.pop('use_unicode', use_unicode)
        sql_mode = kwargs2.pop('sql_mode', '')

        client_flag = kwargs.get('client_flag', 0)
        client_version = tuple(
            [ int(n) for n in _mysql.get_client_info().split('.')[:2] ])
        if client_version >= (4, 1):
            client_flag |= CLIENT.MULTI_STATEMENTS
        if client_version >= (5, 0):
            client_flag |= CLIENT.MULTI_RESULTS
            
        kwargs2['client_flag'] = client_flag

        self._db = _mysql.connection(*args, **kwargs2)

        self.encoders = dict(
            [ (k, v) for k, v in conv.items()
              if type(k) is not int ])
        
        self._server_version = tuple(
            [ int(n) for n in self._db.get_server_info().split('.')[:2] ])

        db = proxy(self)
        def _get_string_literal():
            def string_literal(obj, dummy=None):
                return self._db.string_literal(obj)
            return string_literal

        def _get_unicode_literal():
            def unicode_literal(u, dummy=None):
                return self.literal(u.encode(unicode_literal.charset))
            return unicode_literal

        def _get_string_decoder():
            def string_decoder(s):
                return s.decode(string_decoder.charset)
            return string_decoder
        
        string_literal = _get_string_literal()
        self.unicode_literal = unicode_literal = _get_unicode_literal()
        self.string_decoder = string_decoder = _get_string_decoder()
        if not charset:
            charset = self._db.character_set_name()
        self._db.set_character_set(charset)

        if sql_mode:
            self.set_sql_mode(sql_mode)

        #if use_unicode:
            #self._db.converter[FIELD_TYPE.STRING].append((None, string_decoder))
            #self._db.converter[FIELD_TYPE.VAR_STRING].append((None, string_decoder))
            #self._db.converter[FIELD_TYPE.VARCHAR].append((None, string_decoder))
            #self._db.converter[FIELD_TYPE.BLOB].append((None, string_decoder))

        self.encoders[str] = string_literal
        self.encoders[unicode] = unicode_literal
        string_decoder.charset = charset
        unicode_literal.charset = charset
        self._transactional = self._db.server_capabilities & CLIENT.TRANSACTIONS
        if self._transactional:
            # PEP-249 requires autocommit to be initially off
            self.autocommit(False)
        self.messages = []
    
    def autocommit(self, do_autocommit):
        return self._db.autocommit(do_autocommit)
    
    def commit(self):
        return self._db.commit()
    
    def rollback(self):
        return self._db.rollback()
    
    def close(self):
        return self._db.close()
    
    def cursor(self, cursorclass=None):
        """
        Create a cursor on which queries may be performed. The optional
        cursorclass parameter is used to create the Cursor. By default,
        self.cursorclass=cursors.Cursor is used.
        """
        return (cursorclass or self.cursorclass)(self)

    def __enter__(self):
        return self.cursor()
    
    def __exit__(self, exc, value, traceback):
        if exc:
            self.rollback()
        else:
            self.commit()
            
    def literal(self, obj):
        """
        If obj is a single object, returns an SQL literal as a string. If
        obj is a non-string sequence, the items of the sequence are converted
        and returned as a sequence.

        Non-standard. For internal use; do not use this in your applications.
        """
        return self._db.escape(obj, self.encoders)

    def _warning_count(self):
        """Return the number of warnings generated from the last query."""
        if hasattr(self._db, "warning_count"):
            return self._db.warning_count()
        else:
            info = self._db.info()
            if info:
                return int(info.split()[-1])
            else:
                return 0
    def character_set_name(self):
        return self._db.character_set_name()
    
    def set_character_set(self, charset):
        """Set the connection character set to charset. The character set can
        only be changed in MySQL-4.1 and newer. If you try to change the
        character set from the current value in an older version,
        NotSupportedError will be raised.
        
        Non-standard. It is better to set the character set when creating the
        connection using the charset parameter."""
        if self.character_set_name() != charset:
            try:
                self._db.set_character_set(charset)
            except AttributeError:
                if self._server_version < (4, 1):
                    raise self.NotSupportedError("server is too old to set charset")
                self._db.query('SET NAMES %s' % charset)
                self._db.store_result()
        self.string_decoder.charset = charset
        self.unicode_literal.charset = charset

    def set_sql_mode(self, sql_mode):
        """Set the connection sql_mode. See MySQL documentation for legal
        values.
        
        Non-standard. It is better to set this when creating the connection
        using the sql_mode parameter."""
        if self._server_version < (4, 1):
            raise self.NotSupportedError("server is too old to set sql_mode")
        self._db.query("SET SESSION sql_mode='%s'" % sql_mode)
        self._db.store_result()
        
    def _show_warnings(self):
        """Return detailed information about warnings as a sequence of tuples
        of (Level, Code, Message). This is only supported in MySQL-4.1 and up.
        If your server is an earlier version, an empty sequence is returned.
        
        Non-standard. This is invoked automatically after executing a query,
        so you should not usually call it yourself."""
        if self._server_version < (4, 1): return ()
        self._db.query("SHOW WARNINGS")
        result = self._db.store_result()
        warnings = result.fetch_row(0)
        return warnings
    
