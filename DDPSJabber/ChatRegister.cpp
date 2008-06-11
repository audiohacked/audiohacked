void ChatRegisterUser::NewAccount()
{
	j = new Client( "localhost" );
	j->disableRoster();
	j->registerConnectionListener( this );

	m_reg = new Registration( j );
	m_reg->registerRegistrationHandler( this );

	j->connect();

	delete( m_reg );
	delete( j );
}

void ChatRegisterUser::onConnect()
{
	m_reg->fetchRegistrationFields();
}

void ChatRegisterUser::handleRegistrationFields( const JID& from, int fields, std::string instructions )
{
	printf( "fields: %d\ninstructions: %s\n", fields, instructions.c_str() );
	RegistrationFields vals;
	vals.username = "ddps";
	vals.password = "letmein";
	m_reg->createAccount( fields, vals );
}

void ChatRegisterUser::handleRegistrationResult( const JID& from, RegistrationResult result )
{
	printf( "result: %d\n", result );
	j->disconnect();
}

void ChatRegisterUser::handleAlreadyRegistered( const JID& from )
{ 
	printf( "the account already exists.\n" ); 
}

void ChatRegisterUser::handleDataForm( const JID& from, const DataForm& form )
{ 
	printf( "datForm received\n" ); 
}

void ChatRegisterUser::handleOOB( const JID& from, const OOB& oob )
{
	printf( "OOB registration requested. %s: %s\n", oob.desc().c_str(), oob.url().c_str() );
}
