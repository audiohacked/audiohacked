import java.lang.String;
import java.util.HashMap;
import java.net.ServerSocket;

/*
	bridge_routing_table = 
	{
		ring0 = {n0, n1, n2, n3, n4},
		ring1 = {n5, n6, n7, n8, n9}
	}
*/

public class RoutingTable
{
	public HashMap< String, HashMap<String,ServerSocket> > rt;
	RoutingTable()
	{
		this.rt = new HashMap< String, HashMap<String,ServerSocket> >();

		HashMap<String,ServerSocket> ring0_list = new HashMap<String,ServerSocket>();
		HashMap<String,ServerSocket> ring1_list = new HashMap<String,ServerSocket>();

		ring0_list.put("n0", null);
		ring0_list.put("n1", null);
		ring0_list.put("n2", null);
		ring0_list.put("n3", null);
		ring0_list.put("n4", null);

		ring1_list.put("n5", null);
		ring1_list.put("n6", null);
		ring1_list.put("n7", null);
		ring1_list.put("n8", null);
		ring1_list.put("n9", null);
		
		this.rt.put("ring0", ring0_list);
		this.rt.put("ring1", ring1_list);
	}
	
	public boolean is_ring0(Integer dest)
	{
		return this.rt.get("ring0").containsKey("n"+dest.toString());
	}
	
	public boolean is_ring1(Integer dest)
	{
		return this.rt.get("ring1").containsKey("n"+dest.toString());
	}
	
	public boolean same_ring(Integer token_src, Integer frame_dest)
	{
		for (Object o: this.rt.keySet())
		{
			if ( this.rt.get(o).containsKey("n"+token_src.toString()) 
				&& this.rt.get(o).containsKey("n"+frame_dest.toString()) )
			{
				return true;
			}
		}
		return false;
		//this.rt.get(ring).containsKey("n"+frame_dest.toString());
	}	
}
