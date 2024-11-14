package task13_3;

import java.awt.*;
import java.awt.event.*;
import java.awt.font.*;
import java.awt.geom.*;
import java.io.*;
import javax.swing.*;

public class DataPanel {
	
	JPanel commandPanel;
	JButton openButton;
	JButton plotButton;
	JButton quitButton;
	
	public DataPanel() {
		
		commandPanel = new JPanel(new FlowLayout());
		openButton = new JButton("Open Ctrl-O");
		plotButton = new JButton("Plot Ctrl-P");
		quitButton = new JButton("Quit Ctrl-Q");
		quitButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				System.exit(0);
			}
		});
		commandPanel.registerKeyboardAction(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				System.exit(0);
			}
		}, KeyStroke.getKeyStroke("control Q"), JComponent.WHEN_IN_FOCUSED_WINDOW);
		commandPanel.add(openButton);
		commandPanel.add(plotButton);
		commandPanel.add(quitButton);
		Container container = new Container();
		container.add(commandPanel, "North");
		
		
		
	}
	// GraphicPanel
	private boolean display_plot;
	private DataPanel d;
	
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		Graphics2D g2d = (Graphics2D) g;
		g2d.setPaint(Color.black);
		g2d.setStroke(new BasicStroke());
		g2d.setFont(new Font("Century Schoolbook", Font.PLAIN, 12));
		if(d.isInitialized() && display_plot) {
			d.refreshData();
            Float xLower = d.getXLower();
            Float xUpper = d.getXUpper();
            Float xInterval = d.getXInterval();
            Float yLower = d.getYLower();
            Float yUpper = d.getYUpper();
            Float yInterval = d.getYInterval();
            Float dx = xUpper - xLower;
            Float dy = yUpper - yLower;

            drawCenteredString(g2d, d.getTitle(), 250, 25, (float) 0.);
            drawCenteredString(g2d, d.getXTitle(), 250, 475, (float) 0.);
            drawCenteredString(g2d, d.getYTitle(), 25, 250, (float) -Math.PI / 2);
            drawCenteredString(g2d, xLower.toString(), 50, 475, (float) 0);
            drawCenteredString(g2d, xUpper.toString(), 450, 475, (float) 0);
            drawCenteredString(g2d, yLower.toString(), 25, 450, (float) 0);
            drawCenteredString(g2d, yUpper.toString(), 25, 50, (float) 0);

            g2d.setPaint(Color.gray);
            for (Float x = 50f; x <= 450; x += 400 * xInterval / dx)
                g2d.draw(new Line2D.Float(x, 450, x, 50));
            for (Float y = 50f; y <= 450; y += 400 * yInterval / dy)
                g2d.draw(new Line2D.Float(45, y, 450, y));

            g2d.setPaint(Color.red);
            Float diam = 8f;
            int num_points = d.getNumberOfPoints();
            
            for (int i = 0; i < num_points; i++) {
                Float ex = 400 * (d.getPoint(i).x - xLower) / dx + 50;
                ex -= diam / 2;
                Float ey = -400 * (d.getPoint(i).y - yLower) / dy + 450;
                ey -= diam / 2;
                g2d.fill(new Ellipse2D.Float(ex, ey, diam, diam));
            }
            
            for (int i = 0; i < num_points - 1; i++) {
            	Float ex1 = 400 * (d.getPoint(i).x - xLower) / dx + 50;
                Float ey1 = -400 * (d.getPoint(i).y - yLower) / dy + 450;
                Float ex2 = 400 * (d.getPoint(i+1).x - xLower) / dx + 50;
                Float ey2 = -400 * (d.getPoint(i+1).y - yLower) / dy + 450;
                g2d.draw(new Line2D.Float(ex1, ey1, ex2, ey2));
            }
		}
	}
	
	void setDataPanel(DataPanel new_d) {
        d = new_d;
    }

    void setDisplayPlot(boolean new_display) {
        display_plot = new_display;
    }

    private void drawCenteredString(Graphics2D g2d, String string,
                                    int x0, int y0, float angle) {
        FontRenderContext frc = g2d.getFontRenderContext();
        Rectangle2D bounds = g2d.getFont().getStringBounds(string, frc);
        LineMetrics metrics = g2d.getFont().getLineMetrics(string, frc);
        if (angle == 0) {
            g2d.drawString(string, x0 - (float) bounds.getWidth() / 2,
                y0 + metrics.getHeight() / 2);
        } else {
            g2d.rotate(angle, x0, y0);
            g2d.drawString(string, x0 - (float) bounds.getWidth() / 2,
                y0 + metrics.getHeight() / 2);
            g2d.rotate(-angle, x0, y0);
        }
    }
    
    private boolean initialized;
    private int titleIndex, xTitleIndex, yTitleIndex;
    private int xLowerIndex, xUpperIndex, xIntervalIndex;
    private int yLowerIndex, yUpperIndex, yIntervalIndex;
    private JFrame frame;
    private JPanel panel;
    private String title;
    private String xTitle;
    private String yTitle;
    private float xLower, xUpper, xInterval;
    private float yLower, yUpper, yInterval;
    private Point2D.Float[] points;
    private JLabel[] paramLabels;
    private JTextField[] paramFields;
    private JTextField[] dataFields;

    DataPanel(JFrame newFrame) {
        initialized = false;
        titleIndex = 0;
        xTitleIndex = 1;
        xLowerIndex = 2;
        xUpperIndex = 3;
        xIntervalIndex = 4;
        yTitleIndex = 5;
        yLowerIndex = 6;
        yUpperIndex = 7;
        yIntervalIndex = 8;
        paramLabels = new JLabel[9];
        paramLabels[titleIndex] = new JLabel("Title");
        paramLabels[xTitleIndex] = new JLabel("X Axis Title");
        paramLabels[yTitleIndex] = new JLabel("Y Axis Title");
        paramLabels[xLowerIndex] = new JLabel("X lower bound");
        paramLabels[xUpperIndex] = new JLabel("X upper bound");
        paramLabels[xIntervalIndex] = new JLabel("X tick interval");
        paramLabels[yLowerIndex] = new JLabel("Y lower bound");
        paramLabels[yUpperIndex] = new JLabel("Y upper bound");
        paramLabels[yIntervalIndex] = new JLabel("Y tick interval");
        paramFields = new JTextField[9];
        paramFields[titleIndex] = new JTextField("Test Title");
        paramFields[xTitleIndex] = new JTextField("X");
        paramFields[yTitleIndex] = new JTextField("Y");
        paramFields[xLowerIndex] = new JTextField("0");
        paramFields[xUpperIndex] = new JTextField("10");
        paramFields[xIntervalIndex] = new JTextField("1");
        paramFields[yLowerIndex] = new JTextField("0");
        paramFields[yUpperIndex] = new JTextField("10");
        paramFields[yIntervalIndex] = new JTextField("1");
        frame = newFrame;
        panel = new JPanel(new FlowLayout());
        frame.getContentPane().add(panel, "West");
    }

    public void actionPerformed(ActionEvent e) {
        JFrame fileFrame = new JFrame();
        JPanel filePanel = new JPanel();
        JFileChooser fileChooser = new JFileChooser();
        fileFrame.getContentPane().add(filePanel);
        filePanel.add(fileChooser);
        fileChooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
        int result = fileChooser.showOpenDialog(filePanel);
        if (result != JFileChooser.APPROVE_OPTION) {
            JLabel msg = new JLabel("No file selected");
            panel.add(msg);
            return;
        }

        File datafile = fileChooser.getSelectedFile();
        initialized = readFile(datafile);
        panel.update(panel.getGraphics());
        frame.pack();
        frame.setVisible(true);
    }

	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

}
