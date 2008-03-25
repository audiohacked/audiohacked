# Copyright 1999-2008 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Header: $

inherit subversion eutils flag-o-matic

DESCRIPTION="dotmac Server hosted on GoogleCode - Perl-based dotMac server; use
this to easily install everything needed for a dotmac server"
HOMEPAGE="http://dotmac.googlecode.com/"

ESVN_UPDATE_CMD="svn up"
ESVN_FETCH_CMD="svn co"
ESVN_REPO_URI="http://dotmac.googlecode.com/svn/branches/iLife"
ESVN_STORE_DIR="${S}"
MY_S="${S}/dotmac/iLife"

LICENSE="GPL-2"

SLOT="0"
KEYWORDS="~alpha ~amd64 ~hppa ~ia64 ~mips ~ppc ~ppc64 ~sparc ~x86"
IUSE="sqlite mysql postgres iLife dbi-dotmac"

RDEPEND="
	>=www-servers/apache-2.2.8
	www-apache/mod_perl
	dev-perl/XML-DOM
	dev-perl/XML-Parser
	dev-perl/XML-LibXML
	dev-perl/DBI
	dev-perl/Compress-Raw-Zlib
	perl-core/Digest-MD5
	dev-perl/MD5
	dev-perl/HTTPD-User-Manage
	sqlite? (
		dev-perl/DBD-SQLite
		dev-db/sqlite
	)
	dbi-dotmac? (
		postgres? (
			dev-db/postgresql
			dev-perl/DBD-Pg
		)
		mysql? ( 
			dev-db/mysql
			dev-db/DBD-mysql
		)
	)"

src_unpack() {
	if use dbi-dotmac; then
		if ! use mysql; then
			eerror "dbi-dotmac supports only mysql"
			die "Enable mysql use flag"
		else
			ESVN_REPO_URI="http://dotmac.googlecode.com/svn/branches/dbi-dotmac"
		fi
	fi

	
	if ! use sqlite; then
		eerror "sqlite is currently required to run dotmac."
		eerror "You do not need sqlite only if you're going"
		eerror "to use dbi-dotmac."
		die "Enable sqlite use flag"
	else
		if use iLife; then
			ESVN_REPO_URI="http://dotmac.googlecode.com/svn/branches/iLife"
			einfo "the iLife branch is where all current work is being done to"
			einfo "add support for iLife '08. After work is complete on iLife"
			einfo "support, the branch will be migrated into the trunk."
		else
			ESVN_REPO_URI="http://dotmac.googlecode.com/svn/trunk"
		fi
	fi
	subversion_src_unpack
}

src_install() {

	dodir /usr/lib/apache2/logs

	insinto /var/www
	doins -r ${MY_S}/server/var/www/dotmac
	fowners -R apache /var/www/dotmac
	
	insinto /etc/apache2/vhosts.d
	newins ${MY_S}/Configuration/Apache/dotmac.conf 05_dotmac.conf
	fowners -R apache /etc/apache2/vhosts.d/05_dotmac.conf
}
