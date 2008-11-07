import java.net.*;

public class tokenring
{
	public static void main(String[] args) throws Exception
	{
		/* create Server Sockets for each node */
		ServerSocket s1 = new ServerSocket(GlobalDataStore.netport_base+1);
		ServerSocket s2 = new ServerSocket(GlobalDataStore.netport_base+2);
		ServerSocket s3 = new ServerSocket(GlobalDataStore.netport_base+3);
		ServerSocket s4 = new ServerSocket(GlobalDataStore.netport_base+4);
		ServerSocket s5 = new ServerSocket(GlobalDataStore.netport_base+5);

		/* create Client Nodes for the Token Ring; these wont have the initial 
		 * token for sending
		 */
		ClientNode node2 = new ClientNode(s2, GlobalDataStore.netport_base+3, false);
		ClientNode node3 = new ClientNode(s3, GlobalDataStore.netport_base+4, false);
		ClientNode node4 = new ClientNode(s4, GlobalDataStore.netport_base+5, false);
		ClientNode node5 = new ClientNode(s5, GlobalDataStore.netport_base+1, false);
		
		/* This client Node will be the initial holder of the token */
		ClientNode node1 = new ClientNode(s1, GlobalDataStore.netport_base+2, true);

		/* check if Node One is still alive and continue */
		while(node1.isAlive()){}
		node2.exit();
		node3.exit();
		node4.exit();
		node5.exit();
	}
}


