package com.example.camerapreviewrecorder;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.Manifest;
import com.example.camerapreviewrecorder.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'camerapreviewrecorder' library on application startup.
    static {
        System.loadLibrary("camerapreviewrecorder");
    }

    private ActivityMainBinding binding;
    private Button start_preview_btn;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
        start_preview_btn = binding.startPreview;
        start_preview_btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (ContextCompat.checkSelfPermission(MainActivity.this, Manifest.permission.CAMERA)
                        == PackageManager.PERMISSION_GRANTED) {
                    Intent intent = new Intent(MainActivity.this, CameraPreviewActivity.class);
                    startActivity(intent);
                }else {
                    ActivityCompat.requestPermissions(MainActivity.this,new String[]{ Manifest.permission.CAMERA},1024);
                }
            }
        });
        stringFromJNI();
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        if (requestCode==1024 && grantResults[0]==PackageManager.PERMISSION_GRANTED){
            Intent intent = new Intent(MainActivity.this, CameraPreviewActivity.class);
            startActivity(intent);
        }
    }

    /**
     * A native method that is implemented by the 'camerapreviewrecorder' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}