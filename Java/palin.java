import java.util.Scanner;
import java.math.*;
public class palin {
	public static void main(String[] args) {

		Scanner sc = new Scanner(System.in);
		
		
		while(true) {
			try {
				BigInteger t = new BigInteger(sc.next());
				if(!t.equals(BigInteger.ONE)){
					System.out.println(BigInteger.valueOf(2).multiply(t).add(BigInteger.valueOf(-2)));
				} else {
					System.out.println(1);
				}
			} catch(Exception e) {
				break;
			}
		}
	}
}
