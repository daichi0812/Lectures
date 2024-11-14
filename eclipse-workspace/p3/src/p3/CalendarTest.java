package p3;
import java.util.*;
//import the package containing the classes Date and Calendar

public class CalendarTest {

	public static void main(String[] args) {
		Date today = new Date();
		Calendar now = Calendar.getInstance();
		int year = now.get(Calendar.YEAR);
		int month = now.get(Calendar.MONTH);
		int day = now.get(Calendar.DATE);
		int hour = now.get(Calendar.HOUR);
		int minute = now.get(Calendar.MINUTE);
		int second = now.get(Calendar.SECOND);
		
		System.out.printf("%d/%d/%d %d:%d:%d\n", year, month+1, day, hour, minute, second);
		System.out.println(today);

	}

}
