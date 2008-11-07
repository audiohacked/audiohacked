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

		boolean flag = false; // initial token holder

		new ClientNode(s2, GlobalDataStore.netport_base+3, flag);
		new ClientNode(s3, GlobalDataStore.netport_base+4, flag);
		new ClientNode(s4, GlobalDataStore.netport_base+5, flag);
		new ClientNode(s5, GlobalDataStore.netport_base+1, flag);

		flag = true; // node1 should be the initial token holder
		ClientNode node1 = new ClientNode(s1, GlobalDataStore.netport_base+2, flag);

		while(node1.isAlive()){}
	}
}


