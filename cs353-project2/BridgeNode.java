import java.io.*;
import java.net.*;

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
	
	private String f_input; /* string to build the input-file-{num} name */
	private String f_output; /* same as f_input but for output-file-{num} */
	
	private PrintWriter status;
	private String f_status;
	private QueueFile file;
	
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
		this.f_input = new String("bridge-input-file");
		this.f_output = new String("bridge-output-file");
		this.f_status = new String("bridge-status-file");

		/*
		try
		{
			// open the bridge-status-file
			this.status = new PrintWriter(new FileWriter(this.f_status));
		}
		catch (IOException io) // file io, so we catch exceptions
		{
			System.err.println(node_name+": client node: status, IO error, PrintWriter;" + io);
		}
		*/

		try /* try to build the transmit socket for a token ring node */
		{
			System.out.println(this.node_name+": client node: creating client socket.");
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

		/* if we are the initial holder of the token we just 
		 * run our thread, otherwise we start our thread; this
		 * isn't technically the right way, we could just start()
		 * the thread */
		this.file = new QueueFile();
		start();
	}
	
	public void run()
	{
		listen_state();
	}
	
	public void listen_state()
	{
		Socket conn = null;
		String data = null;
		while(true)
		{
			try
			{
				conn = this.recv_socket.accept();
				BufferedReader si = new BufferedReader(new InputStreamReader(conn.getInputStream()));
				data = si.readLine();/* in this implementation we send newlines */
			}
			catch (IOException io)
			{
				System.err.println(this.node_name+": Socket read error: "+io);
			}

			if (data != null)
			{
				BridgeTokenFrame frame = new BridgeTokenFrame(this.node_name, this.status);
				frame.from_input(data);
				if (frame.access_control() == 0)
				{
					transmit_state();
					return_token(frame);
				}
				else this.file.Ins(data);
			}
		}
	}
	
	public void transmit_state()
	{
		String str = null;

		System.out.println(this.node_name+": transmit");

		while (true)
		{
			if ((str = this.file.Del()) != null) /* check if we can read from file */
			{
				/*
				 * Need more code here
				 */
				BridgeTokenFrame frame = new BridgeTokenFrame(this.node_name, this.status);
				frame.from_input(str);
				transmit_packet(frame);
			}
			else
			{
				break;
			}
		}
	}

	public void return_token(BridgeTokenFrame frame)
	{
		Ring0TokenFrame r0frame = new Ring0TokenFrame(this.node_name, this.status);
		Ring1TokenFrame r1frame = new Ring1TokenFrame(this.node_name, this.status);

		System.out.println(this.node_name+": return token");
		if(routing.is_ring0(frame.src()))
		{
			r0frame = frame.convert_to_ring0();
			pass_to_ring0(r0frame);
		}
		else if (routing.is_ring1(frame.src()))
		{
			r1frame = frame.convert_to_ring1();
			pass_to_ring1(r1frame);
		}
	}
	
	public void transmit_packet(BridgeTokenFrame frame)
	{
		Ring0TokenFrame r0frame = new Ring0TokenFrame(this.node_name, this.status);
		Ring1TokenFrame r1frame = new Ring1TokenFrame(this.node_name, this.status);

		System.out.println(this.node_name+": transmit packet");
		if(routing.is_ring0(frame.dest()))
		{
			r0frame = frame.convert_to_ring0();
			pass_to_ring0(r0frame);
		}
		else if (routing.is_ring1(frame.dest()))
		{
			r1frame = frame.convert_to_ring1();
			pass_to_ring1(r1frame);
		}
	}
		
	/* if somehow the thread calls the exit() method we need to clean up */
	public void exit()
	{	
		cleanup_node();
	}

	void cleanup_node()
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
			System.err.println(this.node_name+": cleanup_node: IO Error, Unknown");
		}
	}

    void pass_to_ring0(Ring0TokenFrame frame)
	{
		/* check if we are passing the token to the next node */
		if (frame.access_control().equals(0))
		
		System.out.println(this.node_name+": send: trying to send frame");
		try
		{
			/* try to open a Write Buffer for writing frames received */
			PrintWriter so = new PrintWriter(this.ring0_socket.getOutputStream(), true);
			so.println(frame.print());/* print the frame as a line */
		}
		catch(IOException io)
		{
			System.err.println(this.node_name+": send: IO Error, DataOutputStream");
		}
		System.out.println(this.node_name+": send: frame sent");
	}
	
    void pass_to_ring1(Ring1TokenFrame frame)
	{
		/* check if we are passing the token to the next node */
		if (frame.access_control().equals(0))
		
		System.out.println(this.node_name+": send: trying to send frame");
		try
		{
			/* try to open a Write Buffer for writing frames received */
			PrintWriter so = new PrintWriter(this.ring1_socket.getOutputStream(), true);
			so.println(frame.print());/* print the frame as a line */
		}
		catch(IOException io)
		{
			System.err.println(this.node_name+": send: IO Error, DataOutputStream");
		}
		System.out.println(this.node_name+": send: frame sent");
	}

    void save_frame_to_output(BridgeTokenFrame frame)
	{
		System.out.println(this.node_name+": saving frame to output");
		try
		{
			/* try to open buffer for the printing frames to output file */
			PrintWriter outfile = new PrintWriter(new FileWriter(this.f_output, true));
			
			/* print frame to a line */
			outfile.println(frame.print());
			
			/* close buffer */
			outfile.close();
		}
		catch (IOException io)
		{
			System.err.println(this.node_name+": save frame to file: outfile, IO error, Writes");
		}
		System.out.println(this.node_name+": saved frame to output");
	}

}
