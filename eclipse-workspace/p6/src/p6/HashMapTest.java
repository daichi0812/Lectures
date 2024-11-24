package p6;
import java.util.*;

public class HashMapTest {

	public static void main(String[] args) {
		String [] days = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
		int [] classes = {0, 2, 0, 2, 1, 3, 0};
		HashMap<String, Integer>weekly_class = new HashMap<>();
		
		for(int i = 0; i < days.length; i++) {
			weekly_class.put(days[i], classes[i]);
		}
		
		for(String x: days) {
			System.out.printf("Number of classes on %s: %d\n", x, weekly_class.get(x));
		}
		
		weekly_class.put("Mon", 0);
		System.out.printf("Updated number of classes on Mon: %d\n", weekly_class.get("Mon"));
		
		for(String key : weekly_class.keySet()) {
			System.out.printf("Number of classes on %s: %d\n", key, weekly_class.get(key));
		}

	}

}
