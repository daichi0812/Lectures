package test;

public class ShowArray2 {

	public static void main(String[] args) {
		
		int i,j;
		int[][] price= {{0,10},{1,20},{2,30},{3,20}};
		
		FIRST: for(i=0; i<price.length; i++)
			for(j=0; j<price[i].length; j++) {
				if(i==0&&j==1) break;
				if(i==1&&j==0) continue;
				if(i==2&&j==0) continue FIRST;
				if(i==3&&j==1) break FIRST;
				System.out.printf("price[%d][%d]=%d\n", i, j, price[i][j]);
			}

	}

}
