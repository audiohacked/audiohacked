import java.io.*;
import java.util.*;
import java.util.concurrent.*;

class QueueFile
{
	private LinkedBlockingQueue<String> q;
	private String filename;
	private String node_name;

	QueueFile(String filename)
	{
		this.filename = filename;
		q = new LinkedBlockingQueue<String>();
		try
		{
			Load();
		}
		catch (IOException io)
		{
			System.err.println("QueueFile: QueueFile-Load error, "+io);
		}
	}

	QueueFile()
	{
		this("bridge-input-file");
	}

	/*
	 * Public Functions
	 */
	public String Del()
	{
		String ret = null;
		if ((ret = q.poll()) != null)
		{
			try
			{
				Save();
			}
			catch (IOException io)
			{
				System.err.println("QueueFile: Ins-Save error, "+io);
			}
		}
		Debug();
		return ret;
	}

	public void Ins(String str)
	{
		try
		{
			q.put(str);
		}
		catch (InterruptedException irq)
		{
			System.err.println("QueueFile: Ins interrupt error, "+irq);
		}
		
		try
		{
			Save();
		}
		catch (IOException io)
		{
			System.err.println("QueueFile: Ins-Save error, "+io);
		}
		Debug();
	}

	public void Close()
	{
		try
		{
			Save();
		}
		catch (IOException io)
		{
			System.err.println("QueueFile: Close-Save error, "+io);
		}
	}

	/*
	 * Private Functions
	 */
	private void Load() throws IOException
	{
		String str = null;
		BufferedReader in = new BufferedReader(new FileReader(this.filename));
		while ((str = in.readLine()) != null)
		{
			//if (! in.ready()) break;
			try
			{
				q.put(str);
			}
			catch (InterruptedException irq)
			{
				System.err.println("QueueFile: Load interrupt error, "+irq);
			}
		}
		in.close();
	}
	
	private void Save() throws IOException
	{
		String str = null;
		Iterator<String> i = q.iterator();
		PrintWriter out = new PrintWriter(new FileWriter(this.filename, true), true);

		while (i.hasNext())
		{
			str = i.next();
			out.println(str);
		}

		out.close();
	}
	
	private void Debug()
	{
		String str = null;
		Iterator<String> i = q.iterator();
		while (i.hasNext())
		{
			str = i.next();
			System.out.println(str);
		}
	}
}

/*
class ReceiveFrame
{
	public void get_frame()
	{
		
	}
	
	public void write_frame_to_file()
	{
		
	}
}

class SendFrame
{
	public void read_frame_from_file()
	{
		
	}
	
	public void send_frame()
	{
		
	}
}
*/
