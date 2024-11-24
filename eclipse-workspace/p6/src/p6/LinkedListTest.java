package p6;
import java.util.*;

public class LinkedListTest {

	public static void main(String[] args) {
		
		String[] days = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
		LinkedList<String>words = new LinkedList<>();
	
		for(String x :days) {
			words.add(x);
		}
		
		for(int i = 0; i < words.size(); i++) {
			System.out.println(words.get(i));
		}
		
		for(String x : words) {
			System.out.println(x);
		}

	}

}
