package jp.aoyama.a5822108.hdfirstandroidgui;

import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import com.google.android.material.floatingactionbutton.FloatingActionButton;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    private TextView textView;
    private ListView fileListView;
    private String selectedFileName;

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
            actionBar.setDisplayHomeAsUpEnabled(true);
            actionBar.setHomeButtonEnabled(true);
        }

        FloatingActionButton fab = findViewById(R.id.floatingActionButton);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(MainActivity.this, SetActivity.class);
                startActivity(intent);
                Toast.makeText(MainActivity.this, "opening user setting", Toast.LENGTH_SHORT).show();
            }
        });

        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });
    }

    public boolean onCreateOptionsMenu(Menu menu){
        //Inflate（膨らます）the menu. This adds items to teh action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_action_bar, menu);

        return true;
    }

    public boolean onOptionsItemSelected(MenuItem item) {
        int id = item.getItemId();
        TextView textView = findViewById(R.id.btn_tv_id);

        if (id == R.id.action_settings) {
            textView.append("\nSettings clicked");
            return true;
        } else if (id == R.id.action_edit) {
            readFileContent(selectedFileName);
            return true;
        } else if (id == R.id.action_open) {
            setContentView(R.layout.open_layout);
            displayFileList();
            return true;
        } else if (id == R.id.action_save) {
            textView.append("\nSave content");
            saveTextViewContentToFile();
            return true;
        } else if (id == android.R.id.home) {
            textView.append("\nHome clicked");
            return true;
        } else {
            return super.onOptionsItemSelected(item);
        }
    }

    public void myBtnClick(View v) {
        textView = findViewById(R.id.btn_tv_id);
        if (v.getId() == R.id.play_btn) {
            textView.setText("Let's Play!");
        } else if (v.getId() == R.id.stop_btn) {
            textView.setText("Stop playing");
        }
    }

    private void saveTextViewContentToFile() {
        String content = textView.getText().toString();
        String filename = getFilename("inputactivity_content");
        writeToFile(filename, content);
    }

    private String getFilename(String prefix) {
        String nameInitials = "hd"; // 自分の名前の頭文字
        String timestamp = new SimpleDateFormat("yyyyMMdd_HHmmss").format(new Date());
        return nameInitials + prefix + "-" + timestamp + ".txt";
    }

    private void writeToFile(String filename, String content) {
        File directory = getFilesDir();
        if (!directory.exists()) {
            directory.mkdirs();
        }
        try (FileOutputStream fos = openFileOutput(filename, MODE_PRIVATE)) {
            fos.write(content.getBytes());
            Toast.makeText(this, "File saved: " + filename, Toast.LENGTH_SHORT).show();
        } catch (IOException e) {
            Toast.makeText(this, "Error saving file: " + e.getMessage(), Toast.LENGTH_SHORT).show();
        }
    }

    private void displayFileList() {
        fileListView = findViewById(R.id.file_list_view);
        List<String> fileList = getFileList();
        ArrayAdapter<String> adapter = new ArrayAdapter<>(this, android.R.layout.simple_list_item_1, fileList);
        fileListView.setAdapter(adapter);
        fileListView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                selectedFileName = fileList.get(position);
                setContentView(R.layout.layout_image);
                textView = findViewById(R.id.btn_tv_id);
                textView.setText("Selected file: " + selectedFileName);
            }
        });
    }

    private List<String> getFileList() {
        List<String> fileList = new ArrayList<>();
        File directory = getFilesDir();
        File[] files = directory.listFiles();
        if (files != null) {
            for (File file : files) {
                fileList.add(file.getName());
            }
        }
        return fileList;
    }

    private void readFileContent(String filename) {
        if (filename == null) {
            Toast.makeText(this, "No file selected", Toast.LENGTH_SHORT).show();
            return;
        }
        File file = new File(getFilesDir(), filename);
        StringBuilder content = new StringBuilder();
        try (FileInputStream fis = new FileInputStream(file);
             BufferedReader reader = new BufferedReader(new InputStreamReader(fis))) {
            String line;
            while ((line = reader.readLine()) != null) {
                content.append(line).append("\n");
            }
        } catch (IOException e) {
            Toast.makeText(this, "Error reading file: " + e.getMessage(), Toast.LENGTH_SHORT).show();
            return;
        }
        textView.setText(content.toString());
    }
}