package jp.aoyama.a5822108.hdaudioplayer;

import android.Manifest;
import android.content.pm.PackageManager;
import android.media.MediaPlayer;
import android.media.MediaRecorder;
import android.net.Uri;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

public class MainActivity extends AppCompatActivity {

    private TextView textView;
    private MediaPlayer mediaPlayer;
    private MediaRecorder mediaRecorder;
    private String recordedFilePath;
    private String audioFilePath;
    private int pausePosition = 0;
    private int mediaDuration = 0;
    private static final int REQUEST_RECORD_AUDIO_PERMISSION = 200;
    private boolean permissionToRecordAccepted = false;
    private String[] permissions = {Manifest.permission.RECORD_AUDIO, Manifest.permission.WRITE_EXTERNAL_STORAGE};

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.layout_image);

        ActionBar actionBar = getSupportActionBar();
        if (actionBar != null) {
            actionBar.setDisplayHomeAsUpEnabled(true);
            actionBar.setHomeButtonEnabled(true);
            actionBar.setDisplayShowHomeEnabled(true);
            actionBar.setIcon(R.mipmap.ic_launcher);
        }

        ActivityCompat.requestPermissions(this, permissions, REQUEST_RECORD_AUDIO_PERMISSION);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.menu_action_bar, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int id = item.getItemId();
        textView = findViewById(R.id.btn_tv_id);

        if (id == R.id.action_settings) {
            textView.append("\nSettings clicked");
            return true;
        } else if (id == R.id.action_edit) {
            textView.append("\nEdit clicked");
            return true;
        } else if (id == R.id.action_preview) {
            textView.append("\nPreview clicked");
            return true;
        } else if (id == R.id.action_save) {
            textView.append("\nSave content");
            return true;
        } else if (id == android.R.id.home) {
            textView.append("\nHome clicked");
            return true;
        } else {
            return super.onOptionsItemSelected(item);
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        permissionToRecordAccepted = requestCode == REQUEST_RECORD_AUDIO_PERMISSION &&
                grantResults[0] == PackageManager.PERMISSION_GRANTED;
    }

    public void myBtnClick(View v) {
        textView = findViewById(R.id.btn_tv_id);
        if (v.getId() == R.id.play_btn) {
//            playMediaFromResource();
//            playMediaFromUrl();
            playRecordedMedia();
        } else if (v.getId() == R.id.stop_btn) {
            stopMedia();
        } else if (v.getId() == R.id.pause_btn) {
            pauseMedia();
        } else if (v.getId() == R.id.record_btn) {
            if (mediaRecorder == null) {
                startRecording();
                textView.setText("Recording");
            } else {
                stopRecording();
                textView.setText("Stop Recording");
            }
        }
    }

    private void playRecordedMedia() {
        if (recordedFilePath == null || recordedFilePath.isEmpty()) {
            textView.setText("No recording found");
            Toast.makeText(this, "No recording found", Toast.LENGTH_SHORT).show();
            return;
        }

        if (mediaPlayer != null) {
            mediaPlayer.release();
        }
        mediaPlayer = new MediaPlayer();
        try {
            mediaPlayer.setDataSource(recordedFilePath);
            mediaPlayer.prepare();
            mediaPlayer.start();
            mediaDuration = mediaPlayer.getDuration();
            textView.setText("Playing recorded media\nMedia duration is " + formatTime(mediaDuration));
            Toast.makeText(this, "Playing recorded media", Toast.LENGTH_SHORT).show();

            updateMediaTime();

            mediaPlayer.setOnCompletionListener(mp -> {
                textView.setText("Recorded media completed");
                pausePosition = 0;
                Toast.makeText(this, "Recorded media completed", Toast.LENGTH_SHORT).show();
            });

        } catch (IOException e) {
            e.printStackTrace();
            textView.setText("Error playing recorded media");
            Toast.makeText(this, "Error playing recorded media", Toast.LENGTH_SHORT).show();
        }
    }

    private void playMediaFromResource() {
        if (mediaPlayer != null) {
            mediaPlayer.release();
        }
        mediaPlayer = MediaPlayer.create(this, R.raw.kalimba); // your_media_fileにはres/rawに追加したメディアファイル名（拡張子なし）
        mediaPlayer.start();
        textView.setText("Playing media from resource");
        Toast.makeText(this, "Playing media from resource", Toast.LENGTH_SHORT).show();

        // 3秒後に停止する
        new Thread(() -> {
            try {
                Thread.sleep(3000);
                if (mediaPlayer != null) {
                    mediaPlayer.stop();
                    mediaPlayer.release();
                    mediaPlayer = null;
                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }).start();
    }

    private void playMediaFromUrl() {
        if (mediaPlayer != null) {
            mediaPlayer.release();
        }
        mediaPlayer = new MediaPlayer();
        try {
            mediaPlayer.setDataSource("http://sc21vlweb01.cc.ag.aoyama.ac.jp/user/t23428/sleep_away.mp3");
            mediaPlayer.prepare();
            mediaPlayer.start();
            textView.setText("Playing media from URL");
            Toast.makeText(this, "Playing media from URL", Toast.LENGTH_SHORT).show();

            // 3秒後に停止する
            new Thread(() -> {
                try {
                    Thread.sleep(3000);
                    if (mediaPlayer != null) {
                        mediaPlayer.stop();
                        mediaPlayer.release();
                        mediaPlayer = null;
                    }
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }).start();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void stopMedia() {
        if (mediaPlayer != null) {
            mediaPlayer.stop();
            mediaPlayer.release();
            mediaPlayer = null;
            pausePosition = 0;
            textView.setText("Media stopped");
            Toast.makeText(this, "Media stopped", Toast.LENGTH_SHORT).show();
        }
    }

    private void pauseMedia() {
        if (mediaPlayer != null && mediaPlayer.isPlaying()) {
            pausePosition = mediaPlayer.getCurrentPosition();
            mediaPlayer.pause();
            textView.append("\nMedia paused at " + formatTime(pausePosition));
            Toast.makeText(this, "Media paused", Toast.LENGTH_SHORT).show();
        }
    }

    private void startRecording() {
        audioFilePath = getExternalCacheDir().getAbsolutePath() + "/" + new SimpleDateFormat("yyyyMMdd_HHmmss", Locale.getDefault()).format(new Date()) + ".3gp";
        recordedFilePath = audioFilePath;
        mediaRecorder = new MediaRecorder();
        mediaRecorder.setAudioSource(MediaRecorder.AudioSource.MIC);
        mediaRecorder.setOutputFormat(MediaRecorder.OutputFormat.THREE_GPP);
        mediaRecorder.setAudioEncoder(MediaRecorder.AudioEncoder.AMR_NB);
        mediaRecorder.setOutputFile(audioFilePath);
        try {
            mediaRecorder.prepare();
            mediaRecorder.start();
            textView.setText("Recording started");
            Toast.makeText(this, "Recording started", Toast.LENGTH_SHORT).show();
        } catch (IOException e) {
            e.printStackTrace();
            textView.setText("Recording failed");
            Toast.makeText(this, "Recording failed", Toast.LENGTH_SHORT).show();
        }
    }

    private void stopRecording() {
        if (mediaRecorder != null) {
            mediaRecorder.stop();
            mediaRecorder.release();
            mediaRecorder = null;
            textView.setText("Recording stopped. File saved at: " + recordedFilePath);
            Toast.makeText(this, "Recording stopped", Toast.LENGTH_SHORT).show();
        }
    }

    private void updateMediaTime() {
        new Thread(() -> {
            while (mediaPlayer != null && mediaPlayer.isPlaying()) {
                runOnUiThread(() -> {
                    int currentPosition = mediaPlayer.getCurrentPosition();
                    textView.setText("Media duration is " + formatTime(mediaDuration) + "\nPlaying at " + formatTime(currentPosition));
                });
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }).start();
    }

    private String formatTime(int milliseconds) {
        int minutes = (milliseconds / 1000) / 60;
        int seconds = (milliseconds / 1000) % 60;
        return String.format(Locale.getDefault(), "%02d:%02d", minutes, seconds);
    }

}