class ChatRegisterUser : public RegistrationHandler, ConnectionListener
{
	public:
		ChatRegisterUser(){}
		void NewAccount();
		virtual void onConnect();
		virtual void handleRegistrationFields( const JID& from, int fields, std::string instructions );
		virtual void handleRegistrationResult( const JID& from, RegistrationResult result );
		virtual void handleAlreadyRegistered( const JID& from );
		virtual void handleDataForm( const JID& from, const DataForm& form );
		virtual void handleOOB( const JID& from, const OOB& oob );

	  private:
	    Registration *m_reg;
	    Client *j;
	    
};
