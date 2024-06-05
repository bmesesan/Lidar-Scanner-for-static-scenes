package Lidar3D;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class Files_Processor {

	public BufferedWriter writer1;
	public BufferedWriter writer2;
	public BufferedWriter writer3;
	public BufferedReader br1;
	public BufferedReader br2;
	public BufferedReader br3;
	String path1;
	String path2;
	String path3;
	int dim_buff;
	
	public Files_Processor() {
		path1 = new String();
		path2 = new String();
		path3 = new String();
		dim_buff = 0;
	}

	public void set_Path(int num, String path)
	{
		if (num == 1)
			path1 = path;
		if (num == 2)
			path2 = path;
		if (num == 3)
			path3 = path;
	}
	
	
	public void setup_Writer(int num) throws IOException
	{
		if (num == 1)
			writer1 = new BufferedWriter(new FileWriter(path1));
		if (num == 2)
			writer2 = new BufferedWriter(new FileWriter(path2));
		if (num == 3)
			writer3 = new BufferedWriter(new FileWriter(path3));
	}
	
	public void setup_all_Writers() throws IOException
	{
		writer1 = new BufferedWriter(new FileWriter(path1));
		writer2 = new BufferedWriter(new FileWriter(path2));
		writer3 = new BufferedWriter(new FileWriter(path3));
	}
	
	public void close_Writer(int num) throws IOException
	{
		if (num == 1)
			writer1.close();
		if (num == 2)
			writer2.close();
		if (num == 3)
			writer3.close();
	}
	
	public void setup_Reader(int num) throws IOException
	{
		if (num == 1)
			br1 = new BufferedReader(new FileReader(path1));
		if (num == 2)
			br2 = new BufferedReader(new FileReader(path2));
		if (num == 3)
			br3 = new BufferedReader(new FileReader(path3));
	}
	
	public void setup_all_Readers() throws IOException
	{
		br1 = new BufferedReader(new FileReader(path1));
		br2 = new BufferedReader(new FileReader(path2));
		br3 = new BufferedReader(new FileReader(path3));
	}
	
	public void close_Reader(int num) throws IOException
	{
		if (num == 1)
			br1.close();
		if (num == 2)
			br2.close();
		if (num == 3)
			br3.close();
	}
	
	// Writes a single character on the serial line
	public void write_char(BufferedWriter writer, char x) throws IOException {
		writer.write((byte) (x));
	}

	// displays an integer number on the serial port
	public void write_int(BufferedWriter writer, int num) throws IOException {
		int val;
		int cif;
		// in case the number is negative
		if (num < 0) {
			write_char(writer, '-');
			num = num * (-1);
		}

		// we send the digits in reverse order
		val = mirr_number(num);
		// in case the number ends with a 0 we need to know the number of digits it has
		cif = nr_cif(num);

		while (val > 0) {
			// write digit by digit
			write_char(writer, (char) (val % 10 + 48));
			val = val / 10;
			cif--;
		}
		if (cif > 0 || num == 0) {
			// case in which the original number ends with a '0' digit, we send out one more
			// '0'
			write_char(writer, '0');
			if (cif > 0)
				cif--;
			while (cif > 0) {
				write_char(writer, '0');
				cif--;
			}
		}
	}

	// returns the mirrored number of the input
	private int mirr_number(int num) {
		int val = 0;
		while (num > 0) {
			val = val * 10 + num % 10;
			num = num / 10;
		}
		return (val);
	}

	// returns the number of digits in a given number
	private int nr_cif(int num) {
		int sum = 0;

		while (num > 0) {
			sum++;
			num = num / 10;
		}

		return (sum);
	}

	private void reverse_array(int buff[], int dim) {
		int i, aux;

		for (i = 0; i < dim / 2; i++) {
			aux = buff[i];
			buff[i] = buff[dim - 1 - i];
			buff[dim - 1 - i] = aux;
		}
	}
	
	public void set_DimBuff(int dim)
	{
		dim_buff = dim;
	}
	
	public void Process_Data() throws IOException
	{
		String st1, st2;
		int[] buff = new int[dim_buff];
		
		int i = 0;
		int j = 0;
		boolean flag = true;
		
		while (flag == true)
		{
			st1 = br1.readLine();
			st2 = br2.readLine();
			
			if ((st1 == null) && (st2 == null))
			{
				flag = false;
			}
			
			if (st1 != null)
			{
				writer3.write(st1);
				write_char(writer3, (char)(13));
				write_char(writer3, '\n');
			}
			
			if (st2 != null)
			{
				char string_buf[] = st2.toCharArray();
				for (i= 0; i < 4096; i++)
				{
					buff[i] = 0;
				}
				i = 0;
				for (char c: string_buf)
				{
					byte aux = (byte) c;
					if (aux != ' ')
					{
						buff[i] = (buff[i] * 10 + (aux - 48));
					}
					else
					{
						i++;
					}
				}
				reverse_array(buff, i);
				
				for (j = 0; j < i; j++)
				{
					write_int(writer3, buff[j]);
					write_char(writer3, ' ');
				}
				write_char(writer3, (char)(13));
				write_char(writer3, '\n');
			}
		}
	}
}
