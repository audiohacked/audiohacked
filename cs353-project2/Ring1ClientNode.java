import java.io.*;
import java.net.*;
import java.util.Random;

/* declare a new class that extends Thread for our Token Ring Node */
public class Ring1ClientNode extends Thread 
{
	private ServerSocket recv_socket; /* declare a listening socket */
	private Socket send_socket; /* declare our socket for sending frames */
	private boolean flag; /* variable to tell if we hold the token or not */

	private Integer this_node_num; /* a simple way to know what node we are */
	private String node_name; /* this String holds the name we give ourselves
								* for cases when Exceptions and other errors
								* come up; makes it easier to figure who we
								* are by name */
	
	private String f_input; /* string to build the input-file-{num} name */
	private String f_output; /* same as f_input but for output-file-{num} */
	
	private BufferedReader infile_read; /* since we need to be able to read
										* from a file during the transmit state
										* we declare an always open buffer
										* and close it when we are finished
										* at end of program or when we exit */
	private String f_status;
	private PrintWriter status;
	
	/* this is the constructor used to make a Node in a tokenring */
	Ring1ClientNode(ServerSocket s_temp, int p_temp, boolean flag)
	{
		// initialize client stuff
		this.this_node_num = new Integer(s_temp.getLocalPort()-Ring1DataStore.netport_base-1);
		this.node_name = new String("Node-");
		this.node_name += this.this_node_num.toString();
		setName(this.node_name); /* we set the name to make debugging Threads
									* easier for us mere humans */

		this.recv_socket = s_temp; /* since in the main program loop we create
									* the server sockets, all we have to do is 
									* make sure the node remembers its 
									* ServerSocket object */
		this.flag = flag; /* we use this flag to figure out if we have the
							* the token or not, for the purpose of transmit */
		
		/* here we build the filename strings for output and input files */
		this.f_input = Ring1DataStore.infile_name + this.this_node_num.toString();
		this.f_output = Ring1DataStore.outfile_name + this.this_node_num.toString();
		this.f_status = Ring1DataStore.statusfile_name + this.this_node_num.toString();

		/*
		try
		{
			// open the status-file-{node_num}
			this.status = new PrintWriter(new FileWriter(this.f_status, true), true);
		}
		catch (IOException io) // file io, so we catch exceptions
		{
			System.err.println(node_name+": client node: status_file, IO error, Buffered Reads;" + io);
		}
		*/
		
		//System.out.println(this.node_name+": FILENAME: "+f_input);
		
		try /* try to build the transmit socket for a token ring node */
		{
			System.out.println(this.node_name+": client node: creating client socket.");
			this.send_socket = new Socket("localhost", p_temp);
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
			// generate frames if we need to during Debugging
			generate_frames("STR", 1); 
		}
		catch (IOException io) // since we do file io; catch Exception
		{
			System.err.println(node_name+": client node: generate_frames");
		}
		//*/

		try
		{
			/* open the input-file-{node_num} */
			this.infile_read = new BufferedReader(new FileReader(this.f_input));
		}
		catch (IOException io) /* file io, so we catch exceptions */
		{
			System.err.println(node_name+": client node: infile_read, IO error, Buffered Reads;" + io);
		}

		 /* if we are the initial holder of the token we just 
		* run our thread, otherwise we start our thread; this
		* isn't technically the right way, we could just start()
		* the thread */
		start();
	}
	
	Ring1ClientNode(ServerSocket s_temp, int p_temp)
	{
		this(s_temp, p_temp, false);
	}
	
	public void run()
	{
		try
		{
			/* if we have the token initially we have to start in 
			 * the transmit state; we do this through a special method
			 * called initialize_token */
			if(this.flag) initialize_token(this.node_name);
			/* otherwise we start in our listening state */
			else listen_state(this.node_name);
		}
		catch (IOException io)
		/* since we have initialize_token and listen_state
		 * throw execptions to use we need to handle them ourselfs */
		{
			System.err.println("thread run: IO Error, unknown");
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
			this.infile_read.close();
			this.recv_socket.close();
			this.send_socket.close();
		}
		catch (IOException io)
		/* for some reason java has problems from just closing sockets it owns
		* so we need to catch IO execptions */
		{
			System.err.println(node_name+": cleanup_node: IO Error, Unknown");
		}
	}

	/* each node has two states:
	 * a listen node where we receive frames, and either keep/save or pass on */
	void listen_state(String node_name)
	{
		/* if somehow we stumble into the listen state when we should be 
		 * the the transmit state, we need to return to the transmit_state
		 * idealistically we should never be here if we still have the rights
		 * to continue transmitting */
		if (this.flag)
		{
			System.out.println(node_name+": We Still have the Token!");
			transmit_state(node_name);
			return;
		}

		System.out.println(node_name+": Starting Listening State...");
		Socket conn = null;
		String data = null;
		Random rand = new Random();
		Ring1TokenFrame frame = new Ring1TokenFrame(node_name, this.status);
		
		try
		{
			/*
			 * we block execution till we get a connection from our neighbor 
			 */
			conn = this.recv_socket.accept();
			/* once we do get a connection we must open a Buffer for the data
			 * being received */
			BufferedReader si = new BufferedReader(new InputStreamReader(conn.getInputStream()));
			data = si.readLine();/* in this implementation we send newlines */
			
			if(data != null) 
			/* if for some reason we don't get data we move on
			 * but if the data is good we process the data */
			{
				System.out.println(node_name+": Intercepted Packet...");
				frame.from_existing(data);/* we create a Token Frame object
											* from the incoming data frame */
				conn.close(); /* since we have what we need, we can close the
								* connection */

				if (frame.access_control().equals(0))
				{
					/*
					 * if the incoming packet is a access control packet
					 * it means that the previous node is passing the
					 * token to us. And we move into our transmit state
					 */
					System.out.println(node_name+": Got Token!");
					this.flag = true;
					transmit_state(node_name);
				}
				else /* otherwise we either pass or keep */
				{
					if (frame.dest().equals(this.this_node_num))
					/* if we are the recipient, we process */
					{
						/* we determine if the frame is good or bad */
						frame.set_frame_status(rand.nextInt(2));
						
						/* we have corruption, we pass it? */
						if (frame.frame_status().equals(0))
							send_frame(node_name, frame);
						else
						{
							/* if we find out the frame is good we save it */
							save_frame_to_output(node_name, frame);
						}
					}
					else
					{
						/* if the frame is not for us:
						 * if we're the sender we either drop or reTx later
						 * otherwise we, we pass it
						 */
						System.out.println(node_name+": We are not the recipent");
						if (frame.src().equals(this.this_node_num))
						{
							if (frame.frame_status().equals(1))
								System.out.println(node_name+": listen: draining frame");
							else 
							{
								/* if the frame status is 0, then we have an
								 * orphaned frame; right now we ignore this
								 * case
								 */
								System.out.println(node_name+": listen: reTx, when we have Token");
								if (this.flag)
								{
									send_frame(node_name, frame);
								}
							}
						}
						else /* if the source is not use we just pass it */
							send_frame(node_name, frame);
					}
				}
			}
		}
		catch(IOException io)/* catch IO Exception errors from BufferedReader */
		{
			System.err.println(node_name+": listen state: IO Error, Buffered Reader");
		}

		/* decision for next state: continue or switch states */
		if (this.flag) transmit_state(node_name);
		else listen_state(node_name);
	}
	
	void transmit_state(String node_name)
	{
		/* if we somehow stumble into the transmit state by mistake,
		 * we switch to the listen state if need be
		 */
		if (!this.flag){
			System.out.println(node_name+": We Don't have the Token!");
			listen_state(node_name);
			return;
		}
		
		/* create Token Frame object */
		Ring1TokenFrame frame = new Ring1TokenFrame(node_name, this.status);
		Integer tht = new Integer(0);
		String str = null;
		System.out.println(node_name+": transmit");
		try
		{
			if ((str = this.infile_read.readLine()) != null) /* check if we can read from file */
			{
				/* read next frame from the file */
				frame.from_input(str);
				
				/* calculate frame THT size */
				tht = tht + frame.data_size();
				
				/* check if we are over the frame size limit */
				if (tht > Ring1DataStore.tht_byte_count) /* Yes */
				{
					/* Release the Token to right neighbor and go to listen state. */
					pass_token(node_name, frame);
					listen_state(node_name);
				}
				else /* No */ 
				{
					/* send current frame */
					send_frame(node_name, frame);
					
					/* and continue transmitting */
					transmit_state(node_name);
				}
			}
			else
			{
				/* Release the Token to right neighbor and go to listen state. */
				pass_token(node_name, frame);
				listen_state(node_name);
			}
		}
		catch (IOException io)
		{
			System.err.println(node_name+": transmit: infile_read, IO Error, Unknown");
		}
	}
	
    void send_frame(String node_name, Ring1TokenFrame frame)
	{
		/* check if we are passing the token to the next node */
		if (frame.access_control().equals(0))
			/* set our token flag and remember we no longer have it */
			this.flag = false;
		
		System.out.println(node_name+": send: trying to send frame");
		try
		{
			/* try to open a Write Buffer for writing frames received */
			PrintWriter so = new PrintWriter(this.send_socket.getOutputStream(), true);
			so.println(frame.print());/* print the frame as a line */
		}
		catch(IOException io)
		{
			System.err.println(node_name+": send: IO Error, DataOutputStream");
		}
		System.out.println(node_name+": send: frame sent");
	}
	
	void pass_token(String node_name, Ring1TokenFrame frame)
	{
		/* we're passing the token to the neightbor, so insure the AC is 0 */
		frame.set_access_control(0);

		/* change for logging */
		frame.set_data("Pass Token");

		/* make sure we have the size correct */
		frame.set_data_size();

		/* now send the token */
		send_frame(node_name, frame);
	}
	
	void save_frame_to_output(String node_name, Ring1TokenFrame frame)
	{
		System.out.println(node_name+": saving frame to output");
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
			System.err.println("save frame to file: outfile, IO error, Writes");
		}
		System.out.println(node_name+": saved frame to output");
	}
		
	void initialize_token(String node_name) throws IOException
	{
		String current_line; /* storage for line read from a file */
		
		/* create a new Token Frame object */
		Ring1TokenFrame frame = new Ring1TokenFrame(node_name, this.status);

		try
		{
			/* try to grab a line from file and store */
			current_line = this.infile_read.readLine();

			/* if the string length is 0, we can be sure it's safe to populate
			 * the frame object
			 */
			if (current_line.length() != 0) frame.from_input(current_line);

			/* check if we are the source/creator of the frame */
			if (frame.src().equals(this.this_node_num))
			{
				System.out.println(node_name+": initialize: send frame token");

				/* we can send the frame, its safe */
				send_frame(node_name, frame);	
			}
		}
		catch(IOException io)
		{
			System.err.println("initialize_token: IO Error," + io + this.infile_read.toString());
			throw io;
		}

		/* decision for next state: continue or switch states */
		if (this.flag) transmit_state(node_name);
		else listen_state(node_name);
	}

	/* generate frame for debugging and testing */
	void generate_frames(String str, int count) throws IOException
	{
		/* if we are not the last frame to be created we call ourself */
		if (count > 0) generate_frames(str, count-1);
		
		/* create a Frame object */
		Ring1TokenFrame frame = new Ring1TokenFrame(node_name, this.status);
		
		/* initialize a random generator */
		Random rand = new Random();
		
		/* generate a random node to send the frame */
		Integer dest = rand.nextInt(10);

		/* set the data String to someting */
		frame.set_data(
			" This MAC STR frame sent from node "
			+this.this_node_num.toString()
			+" to node "
			+dest.toString()+" ");

		/* generate if we make a token for passing; or if its a data frame */
		frame.set_access_control(rand.nextInt(2));

		/* set the data frame size automatically */
		frame.set_data_size();
		
		/* set the destination node for the frame */
		frame.set_dest(dest);
		
		/* set the source node */
		frame.set_src(this.this_node_num);

		if (frame.dest() == frame.src())
		{
			generate_frames(str,count);
		}
		else
		{
			/* open the input file for writing and saving each frame */
			PrintWriter infile_write = new PrintWriter(new FileWriter(this.f_input, true));
			infile_write.println(frame.print()); /* print frame to input file */
			infile_write.close(); /* close buffer */
		}
	}
}
