package p6;
import java.util.*;

public class ArrayListTest {

	public static void main(String[] args) {
		
		String[] days = { "Sun", "Mon", "Tue", "Fri", "Sat" };
		ArrayList<String>words = new ArrayList<>();
		
		for(int i = 0; i < days.length; i++) {
			words.add(days[i]);
		}
		
		/*for(int i = 0; i < words.size(); i++) {
			System.out.println(words.get(i));
		}*/
		
		System.out.println("Remove Tuesday");
		words.remove("Tue");
		
		for(String x : words) {
			System.out.println(x);
		}
	}

}
