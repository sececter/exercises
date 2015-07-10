package com.company;

public class DataStructure {

    // Create an array
    private final static int SIZE = 15;
    private int[] arrayOfInts = new int[SIZE];

    public DataStructure() {
        // fill the array with ascending integer values
        for (int i = 0; i < SIZE; i++) {
            arrayOfInts[i] = i;
        }
    }

    public int getSize() {
        return this.SIZE;
    }

    public int[] getData() {
        return arrayOfInts;
    }

    public void printEven() {

        // Print out values of even indices of the array
        DataStructureIterator iterator = this.new EvenIterator();
        while (iterator.hasNext()) {
            System.out.print(iterator.next() + " ");
        }
        System.out.println();
    }

    interface DataStructureIterator extends java.util.Iterator<Integer> { }

    // Inner class implements the DataStructureIterator interface,
    // which extends the Iterator<Integer> interface

    private class EvenIterator implements DataStructureIterator {

        // Start stepping through the array from the beginning
        private int nextIndex = 0;

        public boolean hasNext() {

            // Check if the current element is the last in the array
            return (nextIndex <= SIZE - 1);
        }

        public Integer next() {

            // Record a value of an even index of the array
            Integer retValue = Integer.valueOf(arrayOfInts[nextIndex]);

            // Get the next even element
            nextIndex += 2;
            return retValue;
        }
    }

    public void print(DataStructureIterator iterator) {
        while (iterator.hasNext()) {
            System.out.print(iterator.next() + " ");
        }
        System.out.println();
    }

    public void print(java.util.Function<Integer, Boolean> iterator) {

    }

    public static void main(String s[]) {

        // Fill the array with integer values and print out only
        // values of even indices
        final DataStructure ds = new DataStructure();
        ds.printEven();
        ds.print(ds.new EvenIterator());
        ds.print(new DataStructureIterator() {
            private int nextIndex = 1;
            private int[] data = ds.getData();
            @Override
            public boolean hasNext() {
                return nextIndex <= ds.getSize()-1;
            }

            @Override
            public Integer next() {
                int res = data[nextIndex];
                nextIndex += 2;
                return res;
            }
        });
    }
}
