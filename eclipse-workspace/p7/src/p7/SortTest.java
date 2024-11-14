package p7;

import java.util.*;
import java.util.Map.Entry;

//Practice 7-3
public class SortTest {

	public static void main(String[] args) {
		Map<String, Integer> map = new HashMap<>();
		map.put("apple", 10);
		map.put("banana", 7);
		map.put("lemon", 20);
		List<Entry<String, Integer>> entries = new  ArrayList<>(map.entrySet());
		Collections.sort(entries, new Comparator<>() {
			public int compare(Entry<String, Integer> obj1, Entry<String, Integer> obj2) {
				return obj2.getValue().compareTo(obj1.getValue());
			}
		});
		for(Entry<String, Integer> entry : entries) {
			System.out.printf("%s (%d)\n", entry.getKey(), entry.getValue());
		}
	}

}
