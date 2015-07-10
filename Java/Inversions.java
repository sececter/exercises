/* *
 * INPUT:
 * 1. t : number of test cases; t test cases follow
 * 2. n : number of elements to consider in each test case
 * 3. n numbers, elements of considered array consecutively
 * */
 
import java.util.*;

public class Inversions {
	
	// Merges arrays left[] and right[] into ar[], returns number of
	// inversions found in the process
	public static long merge(long[] arr, long[] left, long[] right) {
		int i = 0, j = 0;
		long count = 0;
		while (i < left.length || j < right.length) {
			if (i == left.length) {
				arr[i+j] = right[j];
				j++;
			} else if (j == right.length) {
				arr[i+j] = left[i];
				i++;
			} else if (left[i] <= right[j]) {
				arr[i+j] = left[i];
				i++;                
			} else {
				arr[i+j] = right[j];
				// # inv. is curr. size of left array
				count += left.length-i;
				System.out.println("count = " + count);
				j++;
			}
		}
		return count;
	}

	// Traditional merge sort on arr[], returns number of inversions
	public static long invCount(long[] arr) {
		if (arr.length < 2)
			return 0;

		int m = (arr.length + 1) / 2;
		long left[] = Arrays.copyOfRange(arr, 0, m);
		long right[] = Arrays.copyOfRange(arr, m, arr.length);

		return invCount(left) + invCount(right) + merge(arr, left, right);
	}
	
	public static void main (String args[]) {
		int t, n;
		Scanner sc = new Scanner(System.in);
		t = sc.nextInt();
		while(t-- > 0) {
			n = sc.nextInt();
			long[] ar = new long[n];
			for(int i = 0; i < n; i++) {
				ar[i] = sc.nextLong();
			}
			System.out.println(invCount(ar));
		}
	}
}

