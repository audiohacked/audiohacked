import java.net.*;

public class tokenring
{
	public static void main(String[] args) throws Exception
	{
		/* create Server Sockets for each node */
		/* ring 0 */
		ServerSocket s0 = new ServerSocket(GlobalDataStore.netport_base+1);
		ServerSocket s1 = new ServerSocket(GlobalDataStore.netport_base+2);
		ServerSocket s2 = new ServerSocket(GlobalDataStore.netport_base+3);
		ServerSocket s3 = new ServerSocket(GlobalDataStore.netport_base+4);
		ServerSocket s4 = new ServerSocket(GlobalDataStore.netport_base+5);
		/* ring 1 */
		ServerSocket s5 = new ServerSocket(GlobalDataStore.netport_base+6);
		ServerSocket s6 = new ServerSocket(GlobalDataStore.netport_base+7);
		ServerSocket s7 = new ServerSocket(GlobalDataStore.netport_base+8);
		ServerSocket s8 = new ServerSocket(GlobalDataStore.netport_base+9);
		ServerSocket s9 = new ServerSocket(GlobalDataStore.netport_base+10);
		/* bridge */
		ServerSocket b0 = new ServerSocket(GlobalDataStore.netport_base);

		/* create the Bridge Node for Transparent routing between ring0 and ring1 */
		BridgeNode bridge = new BridgeNode(b0, s0.getLocalPort(), s5.getLocalPort());

		/* create Client Nodes for the Token Ring; these wont have the initial 
		 * token for sending: */
		/* ring 0 */
		new Ring0ClientNode(s1, s2.getLocalPort());
		new Ring0ClientNode(s2, s3.getLocalPort());
		new Ring0ClientNode(s3, s4.getLocalPort());
		new Ring0ClientNode(s4, b0.getLocalPort());
		
		/* ring 1 */
		new Ring1ClientNode(s6, s7.getLocalPort());
		new Ring1ClientNode(s7, s8.getLocalPort());
		new Ring1ClientNode(s8, s9.getLocalPort());
		new Ring1ClientNode(s9, b0.getLocalPort());
		
		/* Client Nodes that are the initial holder of the token in their respective rings */
		new Ring0ClientNode(s0, s1.getLocalPort(), true);
		new Ring1ClientNode(s5, s6.getLocalPort(), true);

		/* check if Node One is still alive and continue */
		while(bridge.isAlive()){}
	}
}
