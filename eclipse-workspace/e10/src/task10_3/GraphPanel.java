//15822108 情報テクノロジー　堀田大智
package task10_3;

import java.awt.*;
import java.awt.image.BufferedImage;
import java.util.*;
import java.io.*;
import javax.imageio.ImageIO;
import javax.swing.*;

public class GraphPanel extends JPanel {
	// Member variable to store 2D point coordinates
	private Matrix points;

	// Setting
	private int padding = 30;
	private int label_padding = 30;
	private Color line_color = new Color(44, 102, 230, 180);
	private Color point_color = new Color(100, 100, 100, 180);
	private Color grid_color = new Color(200, 200, 200, 200);
	private Stroke graph_stroke = new BasicStroke(2f);
	private int point_width = 4;
	private int num_x_divisions = 10;
	private int num_y_divisions = 10;

	public GraphPanel(Matrix points) {
		super();

		// Set the panel size to 800 x 400
		setPreferredSize(new Dimension(800, 400));

		// Set the argument "points" to "this.points"
		this.points = points;
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

		// Draw lines between points (hint: setStroke, drawLine)
		g2.setStroke(graph_stroke);
		g2.setColor(line_color);
		for(int i = 1; i < graph_points.size(); i++) {
			int x1 = graph_points.get(i - 1).x;
			int y1 = graph_points.get(i - 1).y;
			int x2 = graph_points.get(i).x;
			int y2 = graph_points.get(i).y;
			g2.drawLine(x1, y1, x2, y2 );
		}
		
		// Plot points(hint: fillOval)
		g2.setColor(point_color);
		for(int i = 0; i < graph_points.size(); i++) {
			int px = graph_points.get(i).x;
			int x = px - point_width / 2;
			int py = graph_points.get(i).y;
			int y = py - point_width / 2;
			g2.fillOval(x, y, point_width, point_width);
		}
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
