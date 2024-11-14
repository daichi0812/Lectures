package test;

public class PrintPrice {

	public static void main(String[] args) {
		
		int i, total;
		int[][] price= {{0,10}, {1,20}, {2,30}, {3,20}};
		String[] item= {"milk", "coffee", "bread", "tea"};
		
		for(i=0, total=0; i<price.length; i++) {
			total += price[i][1];
			System.out.println(item[price[i][0]] + ":" +price[i][1]);
		}
		System.out.println("total: " + total);
	}

}