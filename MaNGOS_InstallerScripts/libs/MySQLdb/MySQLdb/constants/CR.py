"""
MySQL Connection Errors
-----------------------

Nearly all of these raise OperationalError. COMMANDS_OUT_OF_SYNC
raises ProgrammingError.

"""
__revision__ = "$Revision: 489 $"[11:-2]
__author__ = "$Author: adustman $"[9:-2]

MIN_ERROR = 2000
MAX_ERROR = 2999
UNKNOWN_ERROR = 2000
SOCKET_CREATE_ERROR = 2001
CONNECTION_ERROR = 2002
CONN_HOST_ERROR = 2003
IPSOCK_ERROR = 2004
UNKNOWN_HOST = 2005
SERVER_GONE_ERROR = 2006
VERSION_ERROR = 2007
OUT_OF_MEMORY = 2008
WRONG_HOST_INFO = 2009
LOCALHOST_CONNECTION = 2010
TCP_CONNECTION = 2011
SERVER_HANDSHAKE_ERR = 2012
SERVER_LOST = 2013
COMMANDS_OUT_OF_SYNC = 2014
NAMEDPIPE_CONNECTION = 2015
NAMEDPIPEWAIT_ERROR = 2016
NAMEDPIPEOPEN_ERROR = 2017
NAMEDPIPESETSTATE_ERROR = 2018
CANT_READ_CHARSET = 2019
NET_PACKET_TOO_LARGE = 2020