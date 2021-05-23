package com.liu.opencvdemo;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Bitmap;
import android.os.Bundle;
import android.widget.ImageView;
import android.widget.TextView;

import com.bumptech.glide.Glide;
import com.bumptech.glide.request.FutureTarget;
import com.liu.opencvdemo.utils.NativeUtils;

public class MainActivity extends AppCompatActivity {

private ImageView imv;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(NativeUtils.stringFromJNI());

        imv=findViewById(R.id.imv);



        final FutureTarget<Bitmap> bitmap = Glide.with(this)
                .asBitmap()
                .load("https://ss2.bdstatic.com/70cFvnSh_Q1YnxGkpoWK1HF6hhy/it/u=3544668655,3879675809&fm=26&gp=0.jpg")
                .submit();
        new Thread(new Runnable() {
            @Override
            public void run() {
                try{
                     Bitmap  b = bitmap.get();
                    final Bitmap c= (Bitmap) NativeUtils.testPio(b);
                    runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            imv.setImageBitmap(c);
                        }
                    });
                }catch (Exception e){
                    e.printStackTrace();
                }
            }
        }).start();

    }

}
