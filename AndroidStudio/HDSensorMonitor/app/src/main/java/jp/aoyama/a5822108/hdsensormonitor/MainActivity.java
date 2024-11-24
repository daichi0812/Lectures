package jp.aoyama.a5822108.hdsensormonitor;

import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.os.Environment;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

public class MainActivity extends AppCompatActivity implements SensorEventListener {

    private SensorManager sensorManager;
    private Sensor accelerometer;
    private TextView accelerationView;
    private TextView sensorDetailsView;
    private FileWriter fileWriter;
    private boolean isRecording = false;
    private Spinner activitySpinner;
    private GraphView graphView;
    private long lastUpdateTime = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            v.setPadding(insets.getSystemWindowInsetLeft(),
                    insets.getSystemWindowInsetTop(),
                    insets.getSystemWindowInsetRight(),
                    insets.getSystemWindowInsetBottom());
            return WindowInsetsCompat.CONSUMED;
        });

        accelerationView = findViewById(R.id.acceleration);
        sensorDetailsView = findViewById(R.id.sensor_details);
        activitySpinner = findViewById(R.id.activity_spinner);
        graphView = findViewById(R.id.graphView);
        Button startButton = findViewById(R.id.start_button);
        Button stopButton = findViewById(R.id.stop_button);

        // スピナーの設定
        ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(this,
                R.array.activities_array, android.R.layout.simple_spinner_item);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        activitySpinner.setAdapter(adapter);

        sensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
        if (sensorManager != null) {
            accelerometer = sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
            if (accelerometer != null) {
                displaySensorDetails(accelerometer);
            }
        }

        startButton.setOnClickListener(v -> startRecording());
        stopButton.setOnClickListener(v -> stopRecording());
    }

    @Override
    protected void onResume() {
        super.onResume();
        if (accelerometer != null) {
            sensorManager.registerListener(this, accelerometer, SensorManager.SENSOR_DELAY_NORMAL);
        }
    }

    @Override
    protected void onPause() {
        super.onPause();
        sensorManager.unregisterListener(this);
    }

    @Override
    public void onSensorChanged(SensorEvent event) {
        if (event.sensor.getType() == Sensor.TYPE_ACCELEROMETER) {
            long currentTime = System.currentTimeMillis();
            if (isRecording && (currentTime - lastUpdateTime) >= 200) {
                float x = event.values[0];
                float y = event.values[1];
                float z = event.values[2];
                String accelerationText = String.format("Acceleration\nx: %.4f\ny: %.4f\nz: %.4f", x, y, z);
                accelerationView.setText(accelerationText);

                displaySensorDetails(accelerometer);
                writeSensorData(currentTime, x, y, z);
                graphView.addData(x, y, z);

                lastUpdateTime = currentTime;
            }
        }
    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) {
        // 特に処理は不要
    }

    private void displaySensorDetails(Sensor sensor) {
        String details = String.format(
                "Sensor Details:\n" +
                        "Type: %d\n" +
                        "Name: %s\n" +
                        "Vendor: %s\n" +
                        "Version: %d\n" +
                        "Resolution: %f\n" +
                        "Maximum Range: %f\n" +
                        "Power: %f mA\n" +
                        "Sampling Interval: %d ms",
                sensor.getType(),
                sensor.getName(),
                sensor.getVendor(),
                sensor.getVersion(),
                sensor.getResolution(),
                sensor.getMaximumRange(),
                sensor.getPower(),
                200
        );
        sensorDetailsView.setText(details);
    }

    private void startRecording() {
        if (!isRecording) {
            String selectedActivity = activitySpinner.getSelectedItem().toString();
            File file = new File(getExternalFilesDir(Environment.DIRECTORY_DOCUMENTS),
                    selectedActivity + "_sensor_data_" + new SimpleDateFormat("yyyyMMdd_HHmmss", Locale.getDefault()).format(new Date()) + ".csv");
            try {
                fileWriter = new FileWriter(file);
                isRecording = true;
                Toast.makeText(this, "Recording started: " + file.getAbsolutePath(), Toast.LENGTH_LONG).show();
            } catch (IOException e) {
                e.printStackTrace();
                Toast.makeText(this, "Failed to start recording", Toast.LENGTH_SHORT).show();
            }
        }
    }

    private void stopRecording() {
        if (isRecording) {
            try {
                fileWriter.close();
                isRecording = false;
                Toast.makeText(this, "Recording stopped", Toast.LENGTH_SHORT).show();
            } catch (IOException e) {
                e.printStackTrace();
                Toast.makeText(this, "Failed to stop recording", Toast.LENGTH_SHORT).show();
            }
        }
    }

    private void writeSensorData(long timestamp, float x, float y, float z) {
        try {
            String formattedDate = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss.SSS", Locale.getDefault()).format(new Date(timestamp));
            String data = String.format(Locale.getDefault(), "%s,%f,%f,%f\n", formattedDate, x, y, z);
            fileWriter.write(data);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}