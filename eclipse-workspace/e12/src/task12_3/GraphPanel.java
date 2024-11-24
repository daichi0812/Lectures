//15822108 情報テクノロジー　堀田大智
package task12_3;

import java.awt.*;
import java.awt.image.BufferedImage;
import java.util.*;
import java.io.*;
import javax.imageio.ImageIO;
import javax.swing.*;

public class GraphPanel extends JPanel {
	// Member variable to store 2D point coordinates
	private Matrix points;
	double[][] x_intercept;

	// Setting
	private int padding = 30;
	private int label_padding = 30;
	private Color line_color = new Color(30, 30, 30, 180);
	private Color line_color_cross = new Color(140, 40, 140, 255);
	private Color point_color_positive = Color.red;
	private Color point_color_negative = Color.blue;
	private Color point_color_solution = Color.green;
	private Color grid_color = new Color(200, 200, 200, 200);
	private Color x_axis_color = new Color(35, 75, 35, 255);
	private Stroke graph_stroke = new BasicStroke(2f);
	private Stroke x_axis_stroke = new BasicStroke(1f);
	private int point_width = 4;
	private int num_x_divisions = 10;
	private int num_y_divisions = 10;

	public GraphPanel(double x1, double x2, int division) {
		super();

		// Set the panel size to 600 x 600
		setPreferredSize(new Dimension(600, 600));
		
		NonLinearSolver solver = new NonLinearSolver();
		
		//曲線上の点を求める
		int count;
		double i, h;
		points = new Matrix(division, 2);
		double[][] XY = new double[division][2];
		
		h = (x2 - x1) / (division - 1);
		count = 0;
		int c2 = 0;
		
		try {
			for(i = x1; i <= x2 ; i += h) {
				double y = solver.f(i);
				XY[count][0] = i;
				XY[count][1] = y;
				count++;
			}
		}catch(Exception e) {
			System.err.println(e);
			System.exit(1);
		}
		
		// Set the argument "points" to "this.points"
		for(int j = 0; j < division; j++) {
			this.points.data[j][0] = XY[j][0];
			this.points.data[j][1] = XY[j][1];
		}
		
		//x切片を求める
		double[] x_i;
		int h2, j, k;
		int count2;
		double root;
		
		count2 = 1;
		h2 = ((int)x2 - (int)x1) / 5;
		x_i = new double[10];
		
		x_i[0] = solver.solveNewton(3.0);
		for(j = (int)x1; j <= (int)x2; j += h2 ) {
			root = solver.solveNewton(j);
			if(x1 <= root && root <= x2 && Math.round(root * 1000.0) / 1000.0 != Math.round(x_i[count2 - 1] * 1000.0) / 1000.0) {
				x_i[count2] = root;
				count2++;
			}
		}
		
		x_intercept = new double[count2][2];
		
		for(j = 0; j < count2; j ++) {
			x_intercept[j][0] = x_i[j];
			x_intercept[j][1] = 0.0;
		}
		
	}

	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		Graphics2D g2 = (Graphics2D) g;

		// Set antialiasing to remove artifacts (VALUE_ANTIALIAS_ON)
		g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

		// Calculate the minimum and maximum values of x and y coordinates
		double min_x = Double.MAX_VALUE, max_x = Double.MIN_VALUE;
		double min_y = Double.MAX_VALUE, max_y = Double.MIN_VALUE;

		for (int i = 0; i < points.rows(); i++) {
			double x = points.data[i][0];
			double y = points.data[i][1];

			if (x < min_x) {
				min_x = points.data[i][0];
			}
			if (x > max_x) {
				max_x = points.data[i][0];
			}
			if (y < min_y) {
				min_y = points.data[i][1];
			}
			if (y > max_y) {
				max_y = points.data[i][1];
			}
		}

		// Draw white background (hint: fillRect)
		g2.setColor(Color.WHITE);
		g2.fillRect(padding + label_padding, padding, getWidth() - 2 * padding - label_padding,
				getHeight() - 2 * padding - label_padding);

		// Draw grid, label, and tick along y axis (hint: drawLine, drawString)
		for (int i = 0; i < num_y_divisions + 1; i++) {
			int y = (int) ((getHeight() - 2 * padding - label_padding) * i 
					/ (double) num_y_divisions) + padding;
			//グリッド線を書く
			g2.setColor(grid_color);
			g2.drawLine(padding + label_padding, y, getWidth() - padding, y);
			//軸充実させる
			g2.setColor(Color.BLACK);
			String yLabel = String.format("%.1f", max_y - (i * (max_y - min_y) / num_y_divisions));
			FontMetrics metrics = g2.getFontMetrics();
			int labelWidth = metrics.stringWidth(yLabel);
			//横に短い黒線
			g2.drawLine(padding + label_padding, y, 
					padding + label_padding + point_width, y);
			//目盛りの値
			g2.drawString(yLabel, padding + label_padding - labelWidth - 5, 
					y + (metrics.getHeight() / 2) - 3);
		}

		// Draw grid, label, and tick along x axis (hint: drawLine, drawString)
		for (int i = 0; i < num_x_divisions + 1; i++) {
			int x = (int)((getWidth() - 2 * padding - label_padding) * i
					/ (double) num_x_divisions) + padding + label_padding;
			//グリッド線を書く
			g2.setColor(grid_color);
			g2.drawLine(x, padding, x, getHeight() - padding - label_padding);
			//軸を充実させる
			g2.setColor(Color.BLACK);
			String xLabel = String.format("%.1f",
					min_x + (i * (max_x - min_x) / num_x_divisions));
			FontMetrics metrics = g2.getFontMetrics();
			int labelWidth = metrics.stringWidth(xLabel);
			//縦に短い黒線
			g2.drawLine(x, getHeight() - padding - label_padding,
					x, getHeight() - padding - label_padding - point_width );
			//目盛りの値
			g2.drawString(xLabel, x - labelWidth / 2,
					getHeight() - padding - label_padding + metrics.getHeight() + 3 );
		}

		// Draw x and y axes (hint: drawLine)
		//縦の黒線
		g2.drawLine(padding + label_padding, padding, padding + label_padding,
				getHeight() - padding - label_padding);
		//横に黒線
		g2.drawLine(padding + label_padding, getHeight() - padding - label_padding,
				 getWidth() - padding, getHeight() - padding - label_padding);

		// Scale factors to point-panel coordinate conversion
		double x_scale = ((double) getWidth() - 2 * padding - label_padding) / (max_x - min_x);
		double y_scale = ((double) getHeight() - 2 * padding - label_padding) / (max_y - min_y);

		ArrayList<Point> graph_points = new ArrayList<Point>();
		// Scale the point coordinates into graph coordinates and store them in
		for(int i = 0; i < points.data.length; i++) {
			double x = (points.data[i][0] - min_x) * x_scale 
					+ padding + label_padding;
			double y = getHeight() - padding - label_padding 
					- (points.data[i][1] - min_y) * y_scale;
			graph_points.add(new Point((int)x, (int)y));
		}
		
		//x切片用の座標
		ArrayList<Point> graph_points2 = new ArrayList<Point>();
		for(int i = 0; i < x_intercept.length; i++) {
			double x = (x_intercept[i][0] - min_x) * x_scale 
					+ padding + label_padding;
			double y = getHeight() - padding - label_padding 
					- (x_intercept[i][1] - min_y) * y_scale;
			graph_points2.add(new Point((int)x, (int)y));
		}

		// Draw lines between points (hint: setStroke, drawLine)
		g2.setStroke(graph_stroke);
		for(int i = 1; i < graph_points.size(); i++) {
			int x1 = graph_points.get(i - 1).x;
			int y1 = graph_points.get(i - 1).y;
			int x2 = graph_points.get(i).x;
			int y2 = graph_points.get(i).y;
			//正負が入れ替わるところを紫
			if(points.data[i][1] * points.data[i - 1][1] < 0){
				g2.setColor(line_color_cross);
				g2.drawLine(x1, y1, x2, y2);
			}
			//正負がそのままのところを灰色
			if(points.data[i][1] * points.data[i - 1][1] > 0) {
				g2.setColor(line_color);
				g2.drawLine(x1, y1, x2, y2 );
			}	
		}
		
		// Plot points(hint: fillOval)
		for(int i = 0; i < graph_points.size(); i++) {
			int px = graph_points.get(i).x;
			int x = px - point_width / 2;
			int py = graph_points.get(i).y;
			int y = py - point_width / 2;
			// yが正のとき赤点を打つ
			if(points.data[i][1] > 0) {
				g2.setColor(point_color_positive);
			// yが負のとき青点をうつ
			}else{
				g2.setColor(point_color_negative);
			}
			g2.fillOval(x, y, point_width, point_width);
		}
		//x軸切片のプロット
		g2.setColor(point_color_solution);
		for(int i = 0; i < graph_points2.size(); i++) {
			int px = graph_points2.get(i).x;
			int x = px - point_width / 2;
			int py = graph_points2.get(i).y;
			int y = py - point_width / 2;
			g2.fillOval(x, y, point_width, point_width);
		}
		//y=0の線
		g2.setStroke(x_axis_stroke);
		g2.setColor(x_axis_color);
		int py = graph_points2.get(0).y;
		int y = py - point_width / 2;
		g2.drawLine(padding + label_padding, y + padding / 20,
				getWidth() - padding, y + padding / 20);
	}
	
	public void saveImage(String filename) {
		BufferedImage image = new BufferedImage(getWidth(), getHeight(), BufferedImage.TYPE_INT_ARGB);
		Graphics2D g2 = image.createGraphics();
		paint(g2);
		try {
			ImageIO.write(image, "png", new File(filename));
		}catch(IOException e) {
			System.err.println(e);
			System.exit(1);
		}
	}

	public static void main(String[] args) {
	}
}
