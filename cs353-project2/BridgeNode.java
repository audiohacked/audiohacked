import java.io.*;
import java.net.*;
import java.util.HashMap;

class RoutingTable
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
}

class BridgeTokenFrame
{
	private String this_node_name; /* name of Node for logging */
	private Integer access_control; /* AC: 0=token, 1=data */
	private Integer data_size; /* data size in multiples of 50 */
	private Integer dest; /* destination node for frame */
	private Integer src; /* source node of frame */
	private String data; /* data string of frame */
	private Integer frame_status; /* frame status: */

	/* access methods */
	public Integer access_control() {return this.access_control;}
	public Integer data_size(){return this.data_size;}
	public Integer dest(){return this.dest;}
	public Integer src(){return this.src;}
	public String data(){return this.data;}
	public Integer frame_status(){return this.frame_status;}

	/* access methods for setting variables */
	public void set_access_control(int ac) {this.access_control= new Integer(ac);}
	public void set_dest(int da){this.dest=new Integer(da);}
	public void set_src(int sa){this.src=new Integer(sa);}
	public void set_data(String input){this.data=input;}
	public void set_frame_status(int fs){this.frame_status=new Integer(fs);}
	public void set_data_size()
	{
		if (this.data.length() != 0)
		{
				int ret = multiple_of_fifty(this.data.length(), 50);
				this.data_size = new Integer(ret);
		}
	}
	private int multiple_of_fifty(int num, int check)
	{
		if (num < check)
			return check;
		else if ((num%check) != 0)
			return multiple_of_fifty(num, check+50);
		else return 0;
	}

	/* method for populating data from input string */
	public void from_input(String input)
	{
		System.out.println(this.this_node_name+": Populating TokenFrame from input");
		System.out.println(this.this_node_name+": FRAME: "+input);
		log_frame(this.this_node_name, input);
		try {
			String[] list = input.split(",");
			this.access_control = new Integer(list[0]);
			this.data_size = new Integer(list[1]);
			this.dest = new Integer(list[2]);
			this.src = new Integer(list[3]);
			this.data = new String(list[4]);
			this.frame_status = new Integer(0);
		}
		catch (ArrayIndexOutOfBoundsException index)
		{
			System.err.println(this.this_node_name+": from input: Array Index Bound Exceeded");
			this.access_control = new Integer(1); 
		}
	}

	/* method for populating data from a received frame */
	public void from_existing(String input)
	{
		System.out.println(this.this_node_name+": Populating TokenFrame from incoming Frame");
		System.out.println(this.this_node_name+": FRAME: "+input);
		log_frame(this.this_node_name, input);
		try {
			String[] list = input.split(",");
			this.access_control = new Integer(list[0]);
			this.data_size = new Integer(list[1]);
			this.dest = new Integer(list[2]);
			this.src = new Integer(list[3]);
			this.data = new String(list[4]);
			this.frame_status = new Integer(0);
		}
		catch (ArrayIndexOutOfBoundsException index)
		{
			System.err.println(this.this_node_name+": from input: Array Index Bound Exceeded");
			this.access_control = new Integer(1); 
		}
	}
	
	public void convert_from_ring0(Ring0TokenFrame frame)
	{
		this.access_control = frame.access_control();
		this.data_size = frame.data_size();
		this.dest = frame.dest();
		this.src = frame.src();
		this.data = frame.data();
		this.frame_status = frame.frame_status();
	}
	
	public void convert_from_ring1(Ring1TokenFrame frame)
	{
		this.access_control = frame.access_control();
		this.data_size = frame.data_size();
		this.dest = frame.dest();
		this.src = frame.src();
		this.data = frame.data();
		this.frame_status = frame.frame_status();
	}
	
	public Ring0TokenFrame convert_to_ring0()
	{
		Ring0TokenFrame new_ret = new Ring0TokenFrame(this.this_node_name);
		from_existing(print());
		return new_ret;
	}
	
	public Ring1TokenFrame convert_to_ring1()
	{
		Ring1TokenFrame new_ret = new Ring1TokenFrame(this.this_node_name);
		from_existing(print());
		return new_ret;
	}
	/* method for logging each frame received to a file */
	void log_frame(String node_name, String frame)
	{
		try
		{
			PrintWriter log = new PrintWriter(new FileWriter("log-file-"+node_name, true));
			//log.println(this.this_node_name+": FRAME: "+input);
			log.println(frame);
			log.close();
		}
		catch (IOException io)
		{
			System.err.println("log frame: IO Error, Write");
		}
	}
	
	/* method for creating a string from the object data */
	public String print()
	{
		return this.access_control.toString()+","
			+this.data_size.toString()+","
			+this.dest.toString()+","
			+this.src.toString()+","
			+this.data;
	}

	/* method for printing that includes a newline */
	public String println()
	{
		return print()+"\n";
	}

	/* object constructor for a Token Frame */
	BridgeTokenFrame(String node_name)
	{
		this.this_node_name = node_name;
		this.access_control = new Integer(0);
		this.data_size = new Integer(0);
		this.dest = new Integer(0);
		this.src = new Integer(0);
		this.data = new String("");
		this.frame_status = new Integer(0);
	}
}

/* declare a new class that extends Thread for our Token Ring Node */
public class BridgeNode extends Thread 
{
	private RoutingTable routing;
	private ServerSocket recv_socket; /* declare a listening socket */
	private Socket ring0_socket; /* declare our socket for sending frames: ring0 */
	private Socket ring1_socket; /* declare our socket for sending frames: ring1 */

	private Integer this_node_num; /* a simple way to know what node we are */
	private String node_name;  /* this String holds the name we give ourselves
								* for cases when Exceptions and other errors
								* come up; makes it easier to figure who we
								* are by name */
	
	//private String f_input; /* string to build the input-file-{num} name */
	private String f_output; /* same as f_input but for output-file-{num} */
	
	/* since we need to be able to read
	 * from a file during the transmit state
	 * we declare an always open buffer
	 * and close it when we are finished
	 * at end of program or when we exit */
	//private BufferedReader infile_read; 

	private PrintWriter status;
	//private String f_status;
	
	/* this is the constructor used to make a Node in a tokenring */
	BridgeNode(ServerSocket s_temp, int r0_temp, int r1_temp)
	{
		this.routing = new RoutingTable();
		
		// initialize client stuff
		this.this_node_num = new Integer(0);
		this.node_name = new String("Bridge-");
		this.node_name += this.this_node_num.toString();
		setName(this.node_name); /* we set the name to make debugging Threads
								  * easier for us mere humans */

		this.recv_socket = s_temp; /* since in the main program loop we create
									* the server sockets, all we have to do is 
									* make sure the node remembers its 
									* ServerSocket object */
		
		/* here we build the filename strings for output and input files */
		//f_input = new String("bridge-input-file");
		f_output = new String("bridge-output-file");
		//f_status = new String("bridge-status-file");

		try
		{
			/* open the bridge-input-file */
			this.status = new PrintWriter(new FileWriter(this.f_output));
		}
		catch (IOException io) /* file io, so we catch exceptions */
		{
			System.err.println(node_name+": client node: infile_read, IO error, Buffered Reads;" + io);
		}

		try /* try to build the transmit socket for a token ring node */
		{
			this.status.println(this.node_name+": client node: creating client socket.");
			this.ring0_socket = new Socket("localhost", r0_temp);
			this.ring1_socket = new Socket("localhost", r1_temp);
		}
		catch(UnknownHostException host)
		/* catch to see if we are unable to find the localhost, for any reason */
		{
			System.err.println(node_name+": client node: Unkown Host used for client Socket.");
		}
		catch(IOException io)
		/* catch if we have an socket io error for any reason */
		{
			System.err.println(node_name+": client node: IO error, client Socket.");
		}

		/*
		try
		{
			// open the bridge-input-file
			this.infile_read = new BufferedReader(new FileReader(this.f_input));
		}
		catch (IOException io) // file io, so we catch exceptions
		{
			System.err.println(node_name+": client node: infile_read, IO error, Buffered Reads;" + io);
		}
		*/

		/* if we are the initial holder of the token we just 
		 * run our thread, otherwise we start our thread; this
		 * isn't technically the right way, we could just start()
		 * the thread */
		start();
	}
	
	public void run()
	{
		Socket conn = null;
		String data = null;
		BridgeTokenFrame frame = new BridgeTokenFrame(this.node_name);
		Ring0TokenFrame r0frame = new Ring0TokenFrame(this.node_name);
		Ring1TokenFrame r1frame = new Ring1TokenFrame(this.node_name);
		while(true)
		{
			try
			{
				conn = this.recv_socket.accept();
				BufferedReader si = new BufferedReader(new InputStreamReader(conn.getInputStream()));
				data = si.readLine();/* in this implementation we send newlines */
			}
			catch (IOException io){}

			if (data != null)
			{
				frame.from_existing(data);

				if(routing.is_ring0(frame.dest()))
				{
					r0frame = frame.convert_to_ring0();
					pass_to_ring0(this.node_name, r0frame);
				}
				else if (routing.is_ring1(frame.dest()))
				{
					r1frame = frame.convert_to_ring1();
					pass_to_ring1(this.node_name, r1frame);
				}
			}
			
		}
	}
	
	/* if somehow the thread calls the exit() method we need to clean up */
	public void exit()
	{	
		cleanup_node(this.node_name);
	}

	void cleanup_node(String node_name)
	{
		try
		{
			/* the input read file and the node's socket are the only things
			 * kept open during the life of the node; when the node "bows out"
			 * these need to be closed */
			//this.infile_read.close();
			this.recv_socket.close();
			this.ring0_socket.close();
			this.ring1_socket.close();
		}
		catch (IOException io)
		/* for some reason java has problems from just closing sockets it owns
		 * so we need to catch IO execptions */
		{
			System.err.println(node_name+": cleanup_node: IO Error, Unknown");
		}
	}

    void pass_to_ring0(String node_name, Ring0TokenFrame frame)
	{
		/* check if we are passing the token to the next node */
		if (frame.access_control().equals(0))
		
		this.status.println(node_name+": send: trying to send frame");
		try
		{
			/* try to open a Write Buffer for writing frames received */
			PrintWriter so = new PrintWriter(this.ring0_socket.getOutputStream(), true);
			so.println(frame.print());/* print the frame as a line */
		}
		catch(IOException io)
		{
			System.err.println(node_name+": send: IO Error, DataOutputStream");
		}
		this.status.println(node_name+": send: frame sent");
	}
	
    void pass_to_ring1(String node_name, Ring1TokenFrame frame)
	{
		/* check if we are passing the token to the next node */
		if (frame.access_control().equals(0))
		
		this.status.println(node_name+": send: trying to send frame");
		try
		{
			/* try to open a Write Buffer for writing frames received */
			PrintWriter so = new PrintWriter(this.ring1_socket.getOutputStream(), true);
			so.println(frame.print());/* print the frame as a line */
		}
		catch(IOException io)
		{
			System.err.println(node_name+": send: IO Error, DataOutputStream");
		}
		this.status.println(node_name+": send: frame sent");
	}
}
