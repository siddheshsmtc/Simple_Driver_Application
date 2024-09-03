package com.example.myapplication;

import android.os.Bundle;
import android.util.Log;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("native-lib");
    }

    private int deviceFd = -1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button openButton = findViewById(R.id.open_button);
        Button closeButton = findViewById(R.id.close_button);
        Button readButton = findViewById(R.id.read_button);
        Button writeButton = findViewById(R.id.write_button);
        EditText writeInput = findViewById(R.id.write_input);
        TextView readOutput = findViewById(R.id.read_output);

        openButton.setOnClickListener(v -> {
            deviceFd = openDevice();
            Log.i("KernelModuleApp", "Device opened with FD: " + deviceFd);
        });

        closeButton.setOnClickListener(v -> {
            if (deviceFd != -1) {
                closeDevice(deviceFd);
                deviceFd = -1;
            }
        });

        readButton.setOnClickListener(v -> {
            if (deviceFd != -1) {
                String data = readFromDevice(deviceFd, 1024);
                readOutput.setText(data);
            }
        });

        writeButton.setOnClickListener(v -> {
            if (deviceFd != -1) {
                String data = writeInput.getText().toString();
                writeToDevice(deviceFd, data);
            }
        });
    }

    public native int openDevice();

    public native int closeDevice(int fd);

    public native int writeToDevice(int fd, String data);

    public native String readFromDevice(int fd, int length);
}
