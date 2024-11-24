package task13_3;

import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

import javax.imageio.ImageIO;
import javax.swing.JPanel;

public class GraphPanel extends JPanel {

    private int[] padding = {75, 30, 30, 30};  // left, right, top, and bottom
    private Color grid_color = new Color(200, 200, 200, 200);
    private Color line_color = new Color(44, 102, 230, 180);
    private Color point_color = Color.red;
    private int point_width = 4;
    private int margin = 8;
    private int num_x_divisions = 10;
    private int num_y_divisions = 10;
    private Stroke graph_stroke = new BasicStroke(2f);
    private Matrix points;
    private Matrix interpolated_points;

    public GraphPanel() {
        this(600, 600);
    }

    public GraphPanel(int width, int height) {
        super();
        setPreferredSize(new Dimension(width, height));
    }

    public GraphPanel(Matrix points, int approximation, int n) {  	 	
        this();
        
        // 1. copy the argument "points" to "this.points".
        this.points = points;

        // 2. calculate minmum and maximum x values of the points
        double min_x = Double.MAX_VALUE, max_x = Double.MIN_VALUE;

        double a;
        for(int i = 0; i < points.data.length; i++) {
        	a = points.data[i][0];
        	if(a <= min_x) {
        		min_x = a;
        	}
        	if(a >= max_x) {
        		max_x = a;
        	}
        }
        
        Vector coeffs = new Vector(approximation + 1);
        coeffs = LeastSquares.minimize(points, approximation);

        interpolated_points = new Matrix(n, 2);
        for (int i = 0; i < n; ++i) {
        	double x = min_x + (double) i * (max_x - min_x) / (double) (n - 1);
        	double f = 0.0;
        	for(int j = 0; j < approximation + 1; j++) {
        		 f += coeffs.get(j) * Math.pow(x, j) ;
        	}
        	interpolated_points.at(i, 0, x);
            interpolated_points.at(i, 1, f);
        }
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2 = (Graphics2D) g;
        g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
        
        double min_x = Double.MAX_VALUE, max_x = Double.MIN_VALUE;
        double min_y = Double.MAX_VALUE, max_y = Double.MIN_VALUE;

        // 3. calculate minimum and maximum values for *all points* on each axis
        for(int i = 0; i < points.rows(); i++) {
        	double x_points = points.data[i][0];
        	double y_points = points.data[i][1];
        	
        	if(x_points <= min_x) {
        		min_x = x_points;
        	}
        	if(x_points >= max_x) {
        		max_x = x_points;
        	}
        	if(y_points <= min_y) {
        		min_y = y_points;
        	}
        	if(y_points >= max_y) {
        		max_y = y_points;
        	}
        }
        for(int i = 0; i < interpolated_points.rows(); i++) {
        	double x_lines = interpolated_points.data[i][0];
        	double y_lines = interpolated_points.data[i][1];
        	
        	if(x_lines <= min_x) {
        		min_x = x_lines;
        	}
        	if(x_lines >= max_x) {
        		max_x = x_lines;
        	}
        	if(y_lines <= min_y) {
        		min_y = y_lines;
        	}
        	if(y_lines >= max_y) {
        		max_y = y_lines;
        	}
        }
        
        double x_scale = ((double) getWidth() - (padding[0] + padding[1])) / (max_x - min_x);
        double y_scale = ((double) getHeight() - (padding[2] + padding[3])) / (max_y - min_y);
        
        ArrayList<Point> graph_points = new ArrayList<Point>();
        for (int i = 0; i < points.rows(); i++) {
            int x = (int)Math.round(getWidth() - padding[1] - (max_x - points.at(i, 0)) * x_scale);
            int y = (int)Math.round((max_y - points.at(i, 1)) * y_scale) + padding[2];
            graph_points.add(new Point(x, y));
        }

        ArrayList<Point> line_points = new ArrayList<Point>();
        for (int i = 0; i < interpolated_points.rows(); i++) {
            int x = (int)Math.round(getWidth() - padding[1] - (max_x - interpolated_points.at(i, 0)) * x_scale);
            int y = (int)Math.round((max_y - interpolated_points.at(i, 1)) * y_scale) + padding[2];
            line_points.add(new Point(x, y));
        }

        // draw white background
        g2.setColor(Color.WHITE);
        g2.fillRect(padding[0], padding[2], getWidth() - (padding[0] + padding[1]), getHeight() - (padding[2] + padding[3]));

        // draw grid and label
        for (int i = 0; i < num_y_divisions + 1; i++) {
            int x = padding[0];
            int y = (int)Math.round(getHeight() - (double)i * (getHeight() - (padding[2] + padding[3])) / num_y_divisions) - padding[2];

            g2.setColor(grid_color);
            g2.drawLine(x, y, getWidth() - padding[1], y);

            g2.setColor(Color.BLACK);
            String y_label = String.format("%.1f", min_y + (max_y - min_y) * (double) i / num_y_divisions);
            FontMetrics metrics = g2.getFontMetrics();
            int label_width = metrics.stringWidth(y_label);
            g2.drawString(y_label, x - label_width - margin, y + metrics.getHeight() / 2);
        }

        for (int i = 0; i < num_x_divisions + 1; i++) {
            int x = padding[0] + i * (getWidth() - (padding[0] + padding[1])) / num_x_divisions;
            int y = getHeight() - padding[3];

            g2.setColor(grid_color);
            g2.drawLine(x, getHeight() - padding[3], x, padding[3]);

            g2.setColor(Color.BLACK);
            String x_label = String.format("%.1f", min_x + (max_x - min_x) * (double) i / num_x_divisions);
            FontMetrics metrics = g2.getFontMetrics();
            int label_width = metrics.stringWidth(x_label);
            g2.drawString(x_label, x - label_width / 2, y + metrics.getHeight() + margin);
        }

        // draw axes
        g2.setColor(Color.BLACK);
        g2.drawLine(padding[0], getHeight() - padding[3], padding[0], padding[3]);
        g2.drawLine(padding[0], getHeight() - padding[3], getWidth() - padding[1], getHeight() - padding[3]);

        // 4. plot point
        for(int i = 0; i < graph_points.size(); i++) {
			int px = graph_points.get(i).x;
			int x = px - point_width / 2;
			int py = graph_points.get(i).y;
			int y = py - point_width / 2;
			// 赤点を打つ
			g2.setColor(point_color);
			g2.fillOval(x, y, point_width, point_width);
		}

        // 5. draw lines
        g2.setStroke(graph_stroke);
		for(int i = 1; i < line_points.size(); i++) {
			int x1 = line_points.get(i - 1).x;
			int y1 = line_points.get(i - 1).y;
			int x2 = line_points.get(i).x;
			int y2 = line_points.get(i).y;
			g2.setColor(line_color);
			g2.drawLine(x1, y1, x2, y2);
		}
    }
    
    void saveImage(String name) {
        // 6. save the graph as an image
    	BufferedImage image = new BufferedImage(getWidth(), getHeight(), BufferedImage.TYPE_INT_ARGB);
    	Graphics2D g2 = image.createGraphics();
    	paint(g2);
    	try {
    		ImageIO.write(image, "png", new File(name));
    	}catch(IOException e){
    		System.err.println(e);
    		System.exit(1);
    	}
    }
}