import java.util.*;

public class Beehive {
	
	public static void main (String args[]) {
		Map<Long,Long> m = new HashMap<Long,Long>();
		Scanner sc = new Scanner(System.in);
		long n = 0;
		long a = 0;
		while((n = sc.nextInt()) != -1) {
			a = 1;
			for(int i = 1; a < n; i++) {
				a = 1+3*i*(i-1);
			}
			if(a == n) System.out.println("Y");
			else System.out.println("N");
		}
	}
}

