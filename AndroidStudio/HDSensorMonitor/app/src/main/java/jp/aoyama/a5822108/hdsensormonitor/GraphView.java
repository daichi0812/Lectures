package jp.aoyama.a5822108.hdsensormonitor;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.view.View;

import java.util.ArrayList;
import java.util.List;

public class GraphView extends View {
    private Paint paintX, paintY, paintZ;
    private List<Float> dataX, dataY, dataZ;
    private int maxDataPoints = 100;

    public GraphView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    private void init() {
        paintX = new Paint();
        paintX.setColor(Color.RED);
        paintX.setStrokeWidth(5);

        paintY = new Paint();
        paintY.setColor(Color.GREEN);
        paintY.setStrokeWidth(5);

        paintZ = new Paint();
        paintZ.setColor(Color.BLUE);
        paintZ.setStrokeWidth(5);

        dataX = new ArrayList<>();
        dataY = new ArrayList<>();
        dataZ = new ArrayList<>();
    }

    public void addData(float x, float y, float z) {
        if (dataX.size() >= maxDataPoints) {
            dataX.remove(0);
            dataY.remove(0);
            dataZ.remove(0);
        }
        dataX.add(x);
        dataY.add(y);
        dataZ.add(z);
        invalidate(); // 再描画を要求
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        float width = getWidth();
        float height = getHeight();
        float xInterval = width / (maxDataPoints - 1);

        drawGraph(canvas, dataX, paintX, height, xInterval);
        drawGraph(canvas, dataY, paintY, height, xInterval);
        drawGraph(canvas, dataZ, paintZ, height, xInterval);
    }

    private void drawGraph(Canvas canvas, List<Float> data, Paint paint, float height, float xInterval) {
        float previousX = 0;
        float previousY = height / 2;
        for (int i = 0; i < data.size(); i++) {
            float currentX = i * xInterval;
            float currentY = height / 2 - (data.get(i) * 50); // スケーリング係数
            canvas.drawLine(previousX, previousY, currentX, currentY, paint);
            previousX = currentX;
            previousY = currentY;
        }
    }
}