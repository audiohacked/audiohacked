import java.io.*;

public class TokenFrame
{
	private String this_node_name;
	private Integer access_control;
	private Integer data_size;
	private Integer dest;
	private Integer src;
	private String data;
	private Integer frame_status;

	public Integer access_control() {return this.access_control;}
	public Integer data_size(){return this.data_size;}
	public Integer dest(){return this.dest;}
	public Integer src(){return this.src;}
	public String data(){return this.data;}
	public Integer frame_status(){return this.frame_status;}

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
	

	public String print()
	{
		return this.access_control.toString()+","
			+this.data_size.toString()+","
			+this.dest.toString()+","
			+this.src.toString()+","
			+this.data;
	}

	public String println()
	{
		return print()+"\n";
	}

	TokenFrame(String node_name)
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

