/* *
 * INPUT:
 * 1. t : number of test cases; t test cases follow
 * 2. n : number of elements to consider in each test case
 * 3. ar[i] : n numbers, elements of considered array
 * */
 
import java.util.*;

public class Inversions1 {
	
	public static long[] ar;
	public static long[] buff;
	
	// Merges arrays left[] and right[] into ar[], returns number of
	// inversions found in the process
	public static long merge(int low, int middle, int high) {
		int i = low;
		int j = middle + 1;
		int k = low;
		long count = 0;
		
		for(int l = low; l <= high; l++) {
				buff[l] = ar[l];
		}
		
		while (i <= middle && j <= high) {
			if (buff[i] <= buff[j]) {
				ar[k] = buff[i];
				i++;
			} else {
				ar[k] = buff[j];
				j++;
				count += middle-i+1;
			}
				k++;
		}
		
		while (i <= middle) {
			ar[k] = buff[i];
			i++; k++;
		}
		while(j <= high) {
			ar[k] = buff[j];
			j++; k++; 
		}
		return count;
	}

	// Traditional merge sort on arr[], returns number of inversions
	public static long invCount(int low, int high) {
		if(low < high) {

			int middle = low + (high - low)/2;
			
			return invCount(low, middle) + invCount(middle+1,high) + merge(low, middle, high);
		}
		return 0;
	}
	
	public static void main (String args[]) {
		int t, n;
		Scanner sc = new Scanner(System.in);
		t = sc.nextInt();
		while(t-- > 0) {
			n = sc.nextInt();
			ar = new long[n];
			buff = new long[n];
			for(int i = 0; i < n; i++) {
				ar[i] = sc.nextLong();
			}
			System.out.println(invCount(0,n-1));
		}
	}
}

