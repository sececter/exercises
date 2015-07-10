//import java.io.*;
import java.util.*;

public class offside {
	
	public static void main (String args[]) {
		Scanner sc = new Scanner(System.in);
		int a = -1;
		int b = -1;
		a = sc.nextInt();
		b = sc.nextInt();
		while(a != 0 && b != 0) {
			long n = 0;
			long aMin = Long.MAX_VALUE;
			long dMin = Long.MAX_VALUE;
			long gk = Long.MAX_VALUE;
			long temp = 0;
			while(a-- > 0) {
				n = sc.nextInt();
				if(n < aMin) aMin = n;
			}
			while(b-- > 0) {
				n = sc.nextInt();
				if(n < gk) {
					temp = gk;
					gk = n;
					dMin = temp;
				}
				else if(n < dMin) {
					dMin = n;
				}
			}
			//System.out.println("aMin = " + aMin);
			//System.out.println("dMin = " + dMin);
			//System.out.println("gk = " + gk);
			if(aMin < dMin) System.out.println("Y");
			else System.out.println("N");
			a = sc.nextInt();
			b = sc.nextInt();
		}
	}
}

