// 15822108 情報テクノロジー学科 堀田大智
package task11_3;

import java.io.*;

public class Vector {
	
	private double[] data;
	
	Vector(int columns) {
		data = new double[columns];
	}
	
	public double get(int i) {
		return data[i];
	}
	
	void set(int i, double num) {
		data[i] = num;
	}
	
	void replace(int i, double tmp) {
		data[i] = tmp;
	}
	
	static Vector sub(Vector a, Vector b) {
		if(a.data.length != b.data.length) {
			System.err.println("ベクトルのサイズがおかしいです");
			System.exit(1);
		}
		Vector result = new Vector(a.data.length);
		for(int i = 0; i < a.data.length; i++) {
			result.data[i] = a.data[i] - b.data[i];
		}
		return result;
	}
	
	 void show() {
		for(int i = 0; i < data.length; i++) {
			System.out.printf(data[i] + " ");
		}
		System.out.println();
	}
	
	void show(String description) {
		System.out.println(description);
		show();
	}
	
	void writeToFile(String filename) {
		writeToFile(filename, false);
	}
	
	void writeToFile(String filename, boolean append) {
		try {
			FileWriter fw = new FileWriter(filename);
			for(int i = 0; i < data.length; i++) {
				fw.write(data[i] + " ");
			}
			fw.close();
		}catch(IOException e){
			System.err.println(e);
			System.exit(1);
		}
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}
}
