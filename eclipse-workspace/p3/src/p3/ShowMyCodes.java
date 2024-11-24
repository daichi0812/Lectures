package p3;

public class ShowMyCodes {

	public static void main(String[] args) {
		StringBuffer name = new StringBuffer("Daichi");
		name.append(" Hotta");
		
		for(int i = 0; i < name.length(); i++)
			System.out.printf("[%c]=%d", name.charAt(i), (int)name.charAt(i));
	}

}
