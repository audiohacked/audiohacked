import java.io.*;
import java.net.*;
import java.util.Random;

public class ClientNode extends Thread
{
	private ServerSocket recv_socket;
	private Socket send_socket;
	private boolean flag;

	private Integer this_node_num;
	private String node_name;
	
	private String f_input;
	private String f_output;
	
	private BufferedReader infile_read;

	ClientNode(ServerSocket s_temp, int p_temp, boolean flag)
	{
		// initialize client stuff
		this.this_node_num = new Integer(s_temp.getLocalPort()-GlobalDataStore.netport_base);
		this.node_name = new String("Node-");
		this.node_name += this.this_node_num.toString();
		setName(this.node_name);

		this.recv_socket = s_temp;
		this.flag = flag;
		
		f_input = GlobalDataStore.infile_name + this.this_node_num.toString();
		f_output = GlobalDataStore.outfile_name + this.this_node_num.toString();

		try
		{
			System.out.println(this.node_name+": client node: creating client socket.");
			this.send_socket = new Socket("localhost", p_temp);
		}
		catch(UnknownHostException host)
		{
			System.err.println(node_name+": client node: Unkown Host used for client Socket.");
		}
		catch(IOException io)
		{
			System.err.println(node_name+": client node: IO error, client Socket.");
		}

		///*
		try
		{
			generate_frames("STR", 3);
		}
		catch (IOException io)
		{
			System.err.println(node_name+": client node: generate_frames");
		}
		//*/

		try
		{
			this.infile_read = new BufferedReader(new FileReader(this.f_input));
		}
		catch (IOException io)
		{
			System.err.println(node_name+": client node: infile_read, IO error, Buffered Reads;" + io);
		}

		if (flag) run();
		else start();
	}
	
	public void run()
	{
		try
		{
			if(this.flag) initialize_token(this.node_name);
			else listen_state(this.node_name);
		}
		catch (IOException io)
		{
			System.err.println("thread run: IO Error, unknown");
		}
	}
	
	public void exit()
	{	
		cleanup_node(this.node_name);
	}

	void cleanup_node(String node_name)
	{
		try
		{
			this.infile_read.close();
			this.recv_socket.close();
			this.send_socket.close();
		}
		catch (IOException io)
		{
			System.err.println(node_name+": cleanup_node: IO Error, Unknown");
		}
	}

	void listen_state(String node_name)
	{
		/*if (this.flag)
		{
			System.out.println(node_name+": We Still have the Token!");
			transmit_state(node_name);
			return;
		}*/

		System.out.println(node_name+": Starting Listening State...");
		Socket conn = null;
		String data = null;
		Random rand = new Random();
		TokenFrame frame = new TokenFrame(node_name);
		
		try
		{
			conn = this.recv_socket.accept();
			BufferedReader si = new BufferedReader(new InputStreamReader(conn.getInputStream()));
			data = si.readLine();
			
			if(data != null)
			{
				System.out.println(node_name+": Intercepted Packet...");
				frame.from_existing(data);
				conn.close();

				if (frame.access_control().equals(0))
				{
					/*
					 * if the incoming packet is a access control packet
					 * it means that the previous node is passing the
					 * token to us.
					 */
					System.out.println(node_name+": Got Token!");
					this.flag = true;
					transmit_state(node_name);
				}
				else //
				{
					if (frame.dest().equals(this.this_node_num)) // if we are the recipient
					{
						frame.set_frame_status(rand.nextInt(2));
						if (frame.frame_status().equals(0))
							send_frame(node_name, frame);
						else
						{
							save_frame_to_output(node_name, frame);
						}
					}
					else
					{
						System.out.println(node_name+": We are not the recipent");
						if (frame.src().equals(this.this_node_num))
						{
							if (frame.frame_status().equals(1))
								System.out.println(node_name+": listen: draining frame");
							else 
							{
								System.out.println(node_name+": listen: reTx, when we have Token");
								if (this.flag)
								{
									send_frame(node_name, frame);
								}
							}
						}
						else
							send_frame(node_name, frame);
					}
				}
			}
		}
		catch(IOException io)
		{
			System.err.println(node_name+": listen state: IO Error, Buffered Reader");
		}

		if (this.flag) transmit_state(node_name);
		else listen_state(node_name);
	}
	
	void transmit_state(String node_name)
	{
		/*if (!this.flag){
			System.out.println(node_name+": We Don't have the Token!");
			listen_state(node_name);
			return;
		}*/
		TokenFrame frame = new TokenFrame(node_name);
		Integer tht = new Integer(0);
		System.out.println(node_name+": transmit");
		try
		{
			if (this.infile_read.ready())
			{
				frame.from_input(this.infile_read.readLine());
				tht = tht + frame.data_size();
				if (tht > GlobalDataStore.tht_byte_count)
				{
					pass_token(node_name, frame);
					listen_state(node_name);
				}
				else 
				{
					send_frame(node_name, frame);
				}
			}
			else
			{
			//	if (this.flag)
					this.exit();
			//	else
			//		pass_token(node_name, frame);
			}
		}
		catch (IOException io)
		{
			System.err.println(node_name+": transmit: infile_read, IO Error, Unknown");
		}

		//if (this.flag) transmit_state(node_name);
		//else listen_state(node_name);
	}
	
    void send_frame(String node_name, TokenFrame frame)
	{
		System.out.println(node_name+": send: trying to send frame");
		try
		{
			PrintWriter so = new PrintWriter(this.send_socket.getOutputStream(), true);
			so.println(frame.print());
		}
		catch(IOException io)
		{
			System.err.println(node_name+": send: IO Error, DataOutputStream");
		}
		System.out.println(node_name+": send: frame sent");

		if (frame.access_control().equals(0))
			this.flag = false;
	}
	
	void pass_token(String node_name, TokenFrame frame)
	{
		frame.set_access_control(0);
		send_frame(node_name, frame);
	}
	
	void save_frame_to_output(String node_name, TokenFrame frame)
	{
		System.out.println(node_name+": saving frame to output");
		try
		{
			PrintWriter outfile = new PrintWriter(new FileWriter(this.f_output, true));			
			outfile.println(frame.print());
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
		String current_line;
		TokenFrame frame = new TokenFrame(node_name);

		try
		{
			current_line = this.infile_read.readLine();

			if (current_line.length() != 0) frame.from_input(current_line);

			if (frame.src().equals(this.this_node_num))
			{
				System.out.println(node_name+": initialize: send frame token");
				send_frame(node_name, frame);	
			}
		}
		catch(IOException io)
		{
			System.err.println("initialize_token: IO Error," + io + this.infile_read.toString());
			throw io;
		}
		
		if (this.flag) transmit_state(node_name);
		else listen_state(node_name);
	}

	void generate_frames(String str, int count) throws IOException
	{
		
		if (count >= 0) generate_frames(str, count-1);
		
		TokenFrame frame = new TokenFrame(node_name);
		Random rand = new Random();
		Integer dest = rand.nextInt(5)+1;
		frame.set_data(
			" This MAC STR frame sent from node "
			+this.this_node_num.toString()
			+" to node "
			+dest.toString()+" ");
		frame.set_access_control(1/*rand.nextInt(2)*/);
		frame.set_data_size();
		frame.set_dest(dest);
		frame.set_src(this.this_node_num);

		PrintWriter infile_write = new PrintWriter(new FileWriter(this.f_input, true));
		infile_write.println(frame.print());
		infile_write.close();
	}
}
