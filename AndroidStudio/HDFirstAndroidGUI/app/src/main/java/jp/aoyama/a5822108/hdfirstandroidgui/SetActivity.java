package jp.aoyama.a5822108.hdfirstandroidgui;

import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.Spinner;
import android.widget.Toast;

import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;

import com.google.android.material.floatingactionbutton.FloatingActionButton;

import java.io.FileOutputStream;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class SetActivity extends AppCompatActivity {

    private static final String PREFS_NAME = "user_prefs";
    private static final String KEY_NAME = "key_name";
    private static final String KEY_STUDENT_NUMBER = "key_student_number";
    private static final String KEY_EMAIL = "key_email";
    private static final String KEY_PHONE_NUMBER = "key_phone_number";
    private static final String KEY_PHONE_TYPE = "key_phone_type";
    private static final String KEY_MOBILITY = "key_mobility";

    private EditText nameInput, studentNumberInput, emailInput, phoneNumberInput;
    private Spinner phoneTypeSpinner;
    private RadioGroup mobilityRadioGroup;

    private static Bundle savedDataBundle = new Bundle();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_set);

        ActionBar actionBar = getSupportActionBar();
        if (actionBar != null) {
            actionBar.setDisplayHomeAsUpEnabled(true);
            actionBar.setHomeButtonEnabled(true);
            actionBar.setDisplayShowHomeEnabled(true);
            actionBar.setTitle("Settings");
        }

        nameInput = findViewById(R.id.name_input);
        studentNumberInput = findViewById(R.id.student_number_input);
        emailInput = findViewById(R.id.email_input);
        phoneNumberInput = findViewById(R.id.phone_number_input);
        phoneTypeSpinner = findViewById(R.id.phone_type_spinner);
        mobilityRadioGroup = findViewById(R.id.mobility_radio_group);

        FloatingActionButton saveButton = findViewById(R.id.save_button);
        saveButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                saveData();
                saveDataToFile();
                Toast.makeText(SetActivity.this, "Data saved", Toast.LENGTH_SHORT).show();
            }
        });

        loadDataFromBundle();
        loadData();

        phoneTypeSpinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                String phoneType = parent.getItemAtPosition(position).toString();
                Toast.makeText(SetActivity.this, "Selected: " + phoneType, Toast.LENGTH_SHORT).show();
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {
            }
        });

        mobilityRadioGroup.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(RadioGroup group, int checkedId) {
                RadioButton selectedRadioButton = findViewById(checkedId);
                String selectedMobility = selectedRadioButton.getText().toString();
                Toast.makeText(SetActivity.this, "Selected: " + selectedMobility, Toast.LENGTH_SHORT).show();
            }
        });
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        if (item.getItemId() == android.R.id.home) {
            saveData();
            finish();
            return true;
        }
        return super.onOptionsItemSelected(item);
    }

    private void saveData() {
        SharedPreferences sharedPreferences = getSharedPreferences(PREFS_NAME, MODE_PRIVATE);
        SharedPreferences.Editor editor = sharedPreferences.edit();

        editor.putString(KEY_NAME, nameInput.getText().toString());
        editor.putString(KEY_STUDENT_NUMBER, studentNumberInput.getText().toString());
        editor.putString(KEY_EMAIL, emailInput.getText().toString());
        editor.putString(KEY_PHONE_NUMBER, phoneNumberInput.getText().toString());
        editor.putString(KEY_PHONE_TYPE, phoneTypeSpinner.getSelectedItem().toString());

        int mobilityId = mobilityRadioGroup.getCheckedRadioButtonId();
        RadioButton selectedRadioButton = findViewById(mobilityId);
        String mobility = selectedRadioButton != null ? selectedRadioButton.getText().toString() : "";
        editor.putString(KEY_MOBILITY, mobility);

        editor.apply();

        saveDataToBundle();
    }

    private void saveDataToBundle() {
        savedDataBundle.putString(KEY_NAME, nameInput.getText().toString());
        savedDataBundle.putString(KEY_STUDENT_NUMBER, studentNumberInput.getText().toString());
        savedDataBundle.putString(KEY_EMAIL, emailInput.getText().toString());
        savedDataBundle.putString(KEY_PHONE_NUMBER, phoneNumberInput.getText().toString());
        savedDataBundle.putString(KEY_PHONE_TYPE, phoneTypeSpinner.getSelectedItem().toString());

        int mobilityId = mobilityRadioGroup.getCheckedRadioButtonId();
        RadioButton selectedRadioButton = findViewById(mobilityId);
        String mobility = selectedRadioButton != null ? selectedRadioButton.getText().toString() : "";
        savedDataBundle.putString(KEY_MOBILITY, mobility);
    }

    private void saveDataToFile() {
        String filename = getFilename("setactivity_pref");
        String bundleContent = savedDataBundle.toString();
        writeToFile(filename, bundleContent);
    }

    private String getFilename(String prefix) {
        String nameInitials = "hd"; // 自分の名前の頭文字
        String timestamp = new SimpleDateFormat("yyyyMMdd_HHmmss").format(new Date());
        return nameInitials + prefix + "-" + timestamp + ".txt";
    }

    private void writeToFile(String filename, String content) {
        try (FileOutputStream fos = openFileOutput(filename, MODE_PRIVATE)) {
            fos.write(content.getBytes());
            Toast.makeText(this, "File saved: " + filename, Toast.LENGTH_SHORT).show();
        } catch (IOException e) {
            Toast.makeText(this, "Error saving file: " + e.getMessage(), Toast.LENGTH_SHORT).show();
        }
    }

    private void loadData() {
        SharedPreferences sharedPreferences = getSharedPreferences(PREFS_NAME, MODE_PRIVATE);

        nameInput.setText(sharedPreferences.getString(KEY_NAME, ""));
        studentNumberInput.setText(sharedPreferences.getString(KEY_STUDENT_NUMBER, ""));
        emailInput.setText(sharedPreferences.getString(KEY_EMAIL, ""));
        phoneNumberInput.setText(sharedPreferences.getString(KEY_PHONE_NUMBER, ""));

        String phoneType = sharedPreferences.getString(KEY_PHONE_TYPE, "");
        if (!phoneType.isEmpty()) {
            ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(this, R.array.phone_type_array, android.R.layout.simple_spinner_item);
            adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
            phoneTypeSpinner.setAdapter(adapter);
            int spinnerPosition = adapter.getPosition(phoneType);
            phoneTypeSpinner.setSelection(spinnerPosition);
        }

        String mobility = sharedPreferences.getString(KEY_MOBILITY, "");
        if (!mobility.isEmpty()) {
            for (int i = 0; i < mobilityRadioGroup.getChildCount(); i++) {
                RadioButton radioButton = (RadioButton) mobilityRadioGroup.getChildAt(i);
                if (radioButton.getText().toString().equals(mobility)) {
                    radioButton.setChecked(true);
                    break;
                }
            }
        }
    }

    private void loadDataFromBundle() {
        if (savedDataBundle != null) {
            nameInput.setText(savedDataBundle.getString(KEY_NAME, ""));
            studentNumberInput.setText(savedDataBundle.getString(KEY_STUDENT_NUMBER, ""));
            emailInput.setText(savedDataBundle.getString(KEY_EMAIL, ""));
            phoneNumberInput.setText(savedDataBundle.getString(KEY_PHONE_NUMBER, ""));

            String phoneType = savedDataBundle.getString(KEY_PHONE_TYPE, "");
            if (!phoneType.isEmpty()) {
                ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(this, R.array.phone_type_array, android.R.layout.simple_spinner_item);
                adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
                phoneTypeSpinner.setAdapter(adapter);
                int spinnerPosition = adapter.getPosition(phoneType);
                phoneTypeSpinner.setSelection(spinnerPosition);
            }

            String mobility = savedDataBundle.getString(KEY_MOBILITY, "");
            if (!mobility.isEmpty()) {
                for (int i = 0; i < mobilityRadioGroup.getChildCount(); i++) {
                    RadioButton radioButton = (RadioButton) mobilityRadioGroup.getChildAt(i);
                    if (radioButton.getText().toString().equals(mobility)) {
                        radioButton.setChecked(true);
                        break;
                    }
                }
            }
        }
    }
}