import java.io.*;
import java.lang.*;
import java.util.*;

public class CustomStream {
	
	public static void main (String args[]) {
		try {
			BufferedReader bufferRead = new BufferedReader(new InputStreamReader(System.in));
			int x = bufferRead.read();
			System.out.println(x);
		} catch (IOException e) { }
	}
}

