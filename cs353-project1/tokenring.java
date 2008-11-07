import java.net.*;

public class tokenring
{
	public static void main(String[] args) throws Exception
	{
		ServerSocket s1 = new ServerSocket(GlobalDataStore.netport_base+1);
		ServerSocket s2 = new ServerSocket(GlobalDataStore.netport_base+2);
		ServerSocket s3 = new ServerSocket(GlobalDataStore.netport_base+3);
		ServerSocket s4 = new ServerSocket(GlobalDataStore.netport_base+4);
		ServerSocket s5 = new ServerSocket(GlobalDataStore.netport_base+5);

		new ClientNode(s2, GlobalDataStore.netport_base+3, false);
		new ClientNode(s3, GlobalDataStore.netport_base+4, false);
		new ClientNode(s4, GlobalDataStore.netport_base+5, false);
		new ClientNode(s5, GlobalDataStore.netport_base+1, false);
		ClientNode node1 = new ClientNode(s1, GlobalDataStore.netport_base+2, true);

		while(node1.isAlive()){}
	}
}


