package test;

public class ShowArray {

	public static void main(String[] args) {
		
		int i, j;
		int[][] price= {{0,10},{1,20},{2,30},{3,20}};
		
		for(i=0; i<price.length; i++)
			for(j=0; j<price[i].length; j++)
				System.out.printf("price[%d][%d]=%d\n", i, j, price[i][j]);
	}

}
