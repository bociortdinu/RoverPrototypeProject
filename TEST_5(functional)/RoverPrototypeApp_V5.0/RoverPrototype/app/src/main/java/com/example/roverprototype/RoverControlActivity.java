package com.example.roverprototype;

import android.app.ProgressDialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.CompoundButton;
import android.widget.ImageView;
import android.widget.Switch;
import android.widget.Toast;
import android.widget.ToggleButton;

import java.io.IOException;
import java.io.InputStream;
import java.util.UUID;

public class RoverControlActivity extends AppCompatActivity {


    //Bluetooth
    private static final String TAG = "BlueTest5-MainActivity";
    private int mMaxChars = 50000;//Default
    private UUID mDeviceUUID;
    private BluetoothSocket mBTSocket;
    private ReadInput mReadThread = null;

    private boolean mIsUserInitiatedDisconnect = false;

    private boolean mIsBluetoothConnected = false;

    private BluetoothDevice mDevice;

    private ProgressDialog progressDialog;


    // Switch intre panouri de comanda
    Switch switch_roti_brat;


    // Butoane control Rover
            // brat
    ImageView arrow_Z_LEFT;
    ImageView arrow_Z_RIGHT;
    ImageView arrow_X_FRONT;
    ImageView arrow_X_BACK;
    ImageView arrow_Y_UP;
    ImageView arrow_Y_DOWN;

            // roti
    ImageView arrow_FRONT;
    ImageView arrow_BACK;
    ImageView arrow_LEFT;
    ImageView arrow_RIGHT;

          //cleste
    ImageView cleste_brat;

         // ENABLE toggle button
    ToggleButton brat_on_off_EN;
    ToggleButton roti_on_off_EN;

    // falguri ca sa nu se trimita decat o singura comanda ( s-ar putea sa fie degeaba )
    boolean Roti_stateEN = false;
    boolean Brat_stateEN = false;

    //buton de configurare a modului de lucru
    ImageView config_settings;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_rover_control);
        ActivityHelper.initialize(this);
        this.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);

        Intent intent = getIntent();
        Bundle b = intent.getExtras();
        mDevice = b.getParcelable(ConnectionActivity.DEVICE_EXTRA);
        mDeviceUUID = UUID.fromString(b.getString(ConnectionActivity.DEVICE_UUID));
        mMaxChars = b.getInt(ConnectionActivity.BUFFER_SIZE);
        Log.d(TAG, "Ready");


        config_settings = findViewById(R.id.config_settings);

        switch_roti_brat = findViewById(R.id.switch_roti_brat);
        //brat
        brat_on_off_EN = findViewById(R.id.brat_on_off_EN);
        arrow_Y_UP = findViewById(R.id.arrow_X_UP);
        arrow_Y_DOWN = findViewById(R.id.arrow_X_DOWN);
        arrow_X_FRONT = findViewById(R.id.arrow_Y_FRONT);
        arrow_X_BACK = findViewById(R.id.arrow_Y_BACK);
        arrow_Z_LEFT = findViewById(R.id.arrow_Z_LEFT);
        arrow_Z_RIGHT = findViewById(R.id.arrow_Z_RIGHT);
        cleste_brat = findViewById(R.id.brat_claw);

        //roti
        roti_on_off_EN = findViewById(R.id.roti_on_off_EN);
        arrow_FRONT = findViewById(R.id.arrow_FRONT_R);
        arrow_BACK = findViewById(R.id.arrow_BACK_R);
        arrow_LEFT = findViewById(R.id.arrow_LEFT_R);
        arrow_RIGHT = findViewById(R.id.arrow_RIGHT_R);

        // initializare pentru a incepe in modul "ROTI"
        brat_on_off_EN.setVisibility(View.INVISIBLE);
        arrow_Z_LEFT.setVisibility(View.INVISIBLE);
        arrow_Z_RIGHT.setVisibility(View.INVISIBLE);
        arrow_X_FRONT.setVisibility(View.INVISIBLE);
        arrow_X_BACK.setVisibility(View.INVISIBLE);
        arrow_Y_UP.setVisibility(View.INVISIBLE);
        arrow_Y_DOWN.setVisibility(View.INVISIBLE);
        cleste_brat.setVisibility(View.INVISIBLE);

        roti_on_off_EN.setVisibility(View.VISIBLE);
        arrow_FRONT.setVisibility(View.VISIBLE);
        arrow_BACK.setVisibility(View.VISIBLE);
        arrow_LEFT.setVisibility(View.VISIBLE);
        arrow_RIGHT.setVisibility(View.VISIBLE);

        // buton de configurare a modului de lucru
        config_settings.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(getApplicationContext(), ConfigurationSettings.class);
                startActivity(intent);
            }
        });

        // switch intre controale  ROTI / BRAT
        switch_roti_brat.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if(isChecked) // BRAT ON
                {
                    roti_on_off_EN.setVisibility(View.INVISIBLE);
                    arrow_FRONT.setVisibility(View.INVISIBLE);
                    arrow_BACK.setVisibility(View.INVISIBLE);
                    arrow_LEFT.setVisibility(View.INVISIBLE);
                    arrow_RIGHT.setVisibility(View.INVISIBLE);

                    brat_on_off_EN.setVisibility(View.VISIBLE);
                    arrow_Z_LEFT.setVisibility(View.VISIBLE);
                    arrow_Z_RIGHT.setVisibility(View.VISIBLE);
                    arrow_X_FRONT.setVisibility(View.VISIBLE);
                    arrow_X_BACK.setVisibility(View.VISIBLE);
                    arrow_Y_UP.setVisibility(View.VISIBLE);
                    arrow_Y_DOWN.setVisibility(View.VISIBLE);
                    cleste_brat.setVisibility(View.VISIBLE);



                } else { // ROTI ON

                    brat_on_off_EN.setVisibility(View.INVISIBLE);
                    arrow_Z_LEFT.setVisibility(View.INVISIBLE);
                    arrow_Z_RIGHT.setVisibility(View.INVISIBLE);
                    arrow_X_FRONT.setVisibility(View.INVISIBLE);
                    arrow_X_BACK.setVisibility(View.INVISIBLE);
                    arrow_Y_UP.setVisibility(View.INVISIBLE);
                    arrow_Y_DOWN.setVisibility(View.INVISIBLE);
                    cleste_brat.setVisibility(View.INVISIBLE);

                    roti_on_off_EN.setVisibility(View.VISIBLE);
                    arrow_FRONT.setVisibility(View.VISIBLE);
                    arrow_BACK.setVisibility(View.VISIBLE);
                    arrow_LEFT.setVisibility(View.VISIBLE);
                    arrow_RIGHT.setVisibility(View.VISIBLE);

                }
            }
        });

        // controale pentru ROTI
        roti_on_off_EN.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if (isChecked) {
                    // The toggle is enabled
                    if(Roti_stateEN == false)
                    {
                        Roti_EN_On();
                        Roti_stateEN = true;
                    }
                } else {
                    // The toggle is disabled
                    if(Roti_stateEN == true)
                    {
                        Roti_EN_Off();
                        Roti_stateEN = false;
                    }
                }
            }
        });

        arrow_FRONT.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                RotiGoFront();
            }
        });
        arrow_BACK.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                RotiGoBack();
            }
        });
        arrow_LEFT.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                RotiGoLeft();
            }
        });
        arrow_RIGHT.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                RotiGoRight();
            }
        });

        // controale pentru BRAT
        brat_on_off_EN.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if (isChecked) {
                    // The toggle is enabled
                    if(Brat_stateEN == false)
                    {
                        Brat_EN_On();
                        Brat_stateEN = true;
                    }
                } else {
                    // The toggle is disabled
                    if(Brat_stateEN == true)
                    {
                        Brat_EN_Off();
                        Brat_stateEN = false;
                    }
                }
            }
        });

        arrow_Z_LEFT.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                BratGoLeft_Z();
            }
        });
        arrow_Z_RIGHT.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                BratGoRight_Z();
            }
        });
        arrow_X_FRONT.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                BratGoFront_X();
            }
        });
        arrow_X_BACK.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                BratGoBack_X();
            }
        });
        arrow_Y_UP.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                BratGoUp_Y();
            }
        });
        arrow_Y_DOWN.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                BratGoDown_Y();
            }
        });
        cleste_brat.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                BratOpenOrCloseClaw();
            }
        });


    }

    // controale pentru ROTI
    private void Roti_EN_On()
    {
        if (mBTSocket!=null)
        {
            try
            {
                mBTSocket.getOutputStream().write("rENon".toString().getBytes());

                Log.e("RotiGoFront","write : rENon");
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }
    private void Roti_EN_Off()
    {
        if (mBTSocket!=null)
        {
            try
            {
                mBTSocket.getOutputStream().write("rENoff".toString().getBytes());
                Log.e("RotiGoFront","write : rENoff");
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }
    private void RotiGoFront()
    {
        if (mBTSocket!=null)
        {
            try
            {
                mBTSocket.getOutputStream().write(RoverCommands.getInstance().getCommand_ROTI_arrow_FRONT().toString().getBytes());

                Log.e("RotiGoFront","write : " + RoverCommands.getInstance().getCommand_ROTI_arrow_FRONT().toString());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }
    private void RotiGoBack()
    {
        if (mBTSocket!=null)
        {
            try
            {
                mBTSocket.getOutputStream().write(RoverCommands.getInstance().getCommand_ROTI_arrow_BACK().toString().getBytes());
                Log.e("RotiGoBack","write : " + RoverCommands.getInstance().getCommand_ROTI_arrow_BACK().toString());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }
    private void RotiGoLeft()
    {
        if (mBTSocket!=null)
        {
            try
            {
                mBTSocket.getOutputStream().write(RoverCommands.getInstance().getCommand_ROTI_arrow_LEFT().toString().getBytes());
                Log.e("RotiGoLeft","write : " + RoverCommands.getInstance().getCommand_ROTI_arrow_LEFT().toString());
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }
    private void RotiGoRight()
    {
        if (mBTSocket!=null)
        {
            try
            {
                mBTSocket.getOutputStream().write(RoverCommands.getInstance().getCommand_ROTI_arrow_RIGHT().toString().getBytes());
                Log.e("RotiGoRight","write : " + RoverCommands.getInstance().getCommand_ROTI_arrow_RIGHT().toString());

            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }

    // controale pentru BRAT
    private void Brat_EN_On()
    {
        if (mBTSocket!=null)
        {
            try
            {
                mBTSocket.getOutputStream().write("bENon".toString().getBytes());
                Log.e("RotiGoFront","write : bENon");
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }
    private void Brat_EN_Off()
    {
        if (mBTSocket!=null)
        {
            try
            {
                mBTSocket.getOutputStream().write("bENoff".toString().getBytes());
                Log.e("RotiGoFront","write : bENoff");
            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }
    private void BratGoLeft_Z()
    {
        if (mBTSocket!=null)
        {
            try
            {
                mBTSocket.getOutputStream().write(RoverCommands.getInstance().getCommand_BRAT_arrow_Z_LEFT().toString().getBytes());
                Log.e("BratGoLeft_Z","write : " + RoverCommands.getInstance().getCommand_BRAT_arrow_Z_LEFT().toString());

            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }
    private void BratGoRight_Z()
    {
        if (mBTSocket!=null)
        {
            try
            {
                mBTSocket.getOutputStream().write(RoverCommands.getInstance().getCommand_BRAT_arrow_Z_RIGHT().toString().getBytes());
                Log.e("BratGoRight_Z","write : " + RoverCommands.getInstance().getCommand_BRAT_arrow_Z_RIGHT().toString());

            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }
    private void BratGoFront_X()
    {
        if (mBTSocket!=null)
        {
            try
            {
                mBTSocket.getOutputStream().write(RoverCommands.getInstance().getCommand_BRAT_arrow_X_FRONT().toString().getBytes());
                Log.e("BratGoFront_X","write : " + RoverCommands.getInstance().getCommand_BRAT_arrow_X_FRONT().toString());

            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }
    private void BratGoBack_X()
    {
        if (mBTSocket!=null)
        {
            try
            {
                mBTSocket.getOutputStream().write(RoverCommands.getInstance().getCommand_BRAT_arrow_X_BACK().toString().getBytes());
                Log.e("BratGoBack_X","write : " + RoverCommands.getInstance().getCommand_BRAT_arrow_X_BACK().toString());

            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }
    private void BratGoUp_Y()
    {
        if (mBTSocket!=null)
        {
            try
            {
                mBTSocket.getOutputStream().write(RoverCommands.getInstance().getCommand_BRAT_arrow_Y_UP().toString().getBytes());
                Log.e("BratGoUp_Y","write : " + RoverCommands.getInstance().getCommand_BRAT_arrow_Y_UP().toString());

            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }
    private void BratGoDown_Y()
     {
        if (mBTSocket!=null)
        {
            try
            {
                mBTSocket.getOutputStream().write(RoverCommands.getInstance().getCommand_BRAT_arrow_Y_DOWN().toString().getBytes());
                Log.e("BratGoDown_Y","write : " + RoverCommands.getInstance().getCommand_BRAT_arrow_Y_DOWN().toString());

            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }
    // cleste
    private void BratOpenOrCloseClaw()
    {
        if (mBTSocket!=null)
        {
            try
            {
                mBTSocket.getOutputStream().write("bCLAW".toString().getBytes());
                Log.e("BratOpenOrCloseClaw","write : bCLAW");

            }
            catch (IOException e)
            {
                msg("Error");
            }
        }
    }



    private class ReadInput implements Runnable {

        private boolean bStop = false;
        private Thread t;

        public ReadInput() {
            t = new Thread(this, "Input Thread");
            t.start();
        }

        public boolean isRunning() {
            return t.isAlive();
        }

        @Override
        public void run() {
            InputStream inputStream;

            try {
                inputStream = mBTSocket.getInputStream();
                while (!bStop) {
                    byte[] buffer = new byte[256];
                    if (inputStream.available() > 0) {
                        inputStream.read(buffer);
                        int i = 0;
                        /*
                         * This is needed because new String(buffer) is taking the entire buffer i.e. 256 chars on Android 2.3.4 http://stackoverflow.com/a/8843462/1287554
                         */
                        for (i = 0; i < buffer.length && buffer[i] != 0; i++) {
                        }
                        final String strInput = new String(buffer, 0, i);

                        /*
                         * If checked then receive text, better design would probably be to stop thread if unchecked and free resources, but this is a quick fix
                         */



                    }
                    Thread.sleep(1000);
                }
            } catch (IOException e) {
// TODO Auto-generated catch block
                e.printStackTrace();
            } catch (InterruptedException e) {
// TODO Auto-generated catch block
                e.printStackTrace();
            }

        }

        public void stop() {
            bStop = true;
        }

    }


    private class DisConnectBT extends AsyncTask<Void, Void, Void> {

        @Override
        protected void onPreExecute() {
        }

        @Override
        protected Void doInBackground(Void... params) {

            if (mReadThread != null) {
                mReadThread.stop();
                while (mReadThread.isRunning())
                    ; // Wait until it stops
                mReadThread = null;

            }

            try {
                mBTSocket.close();
            } catch (IOException e) {
// TODO Auto-generated catch block
                e.printStackTrace();
            }

            return null;
        }

        @Override
        protected void onPostExecute(Void result) {
            super.onPostExecute(result);
            mIsBluetoothConnected = false;
            if (mIsUserInitiatedDisconnect) {
                finish();
            }
        }

    }

    private void msg(String s) {
        Toast.makeText(getApplicationContext(), s, Toast.LENGTH_SHORT).show();
    }

    @Override
    protected void onPause() {
        if (mBTSocket != null && mIsBluetoothConnected) {
            new DisConnectBT().execute();
        }
        Log.d(TAG, "Paused");
        super.onPause();
    }

    @Override
    protected void onResume() {
        if (mBTSocket == null || !mIsBluetoothConnected) {
            new ConnectBT().execute();
        }
        Log.d(TAG, "Resumed");
        super.onResume();
    }

    @Override
    protected void onStop() {
        Log.d(TAG, "Stopped");
        super.onStop();
    }

    @Override
    protected void onSaveInstanceState(Bundle outState) {
// TODO Auto-generated method stub
        super.onSaveInstanceState(outState);
    }

    private class ConnectBT extends AsyncTask<Void, Void, Void> {
        private boolean mConnectSuccessful = true;

        @Override
        protected void onPreExecute() {
            progressDialog = ProgressDialog.show(RoverControlActivity.this, "Hold on", "Connecting");// http://stackoverflow.com/a/11130220/1287554
        }

        @Override
        protected Void doInBackground(Void... devices) {

            try {
                if (mBTSocket == null || !mIsBluetoothConnected) {
                    mBTSocket = mDevice.createInsecureRfcommSocketToServiceRecord(mDeviceUUID);
                    BluetoothAdapter.getDefaultAdapter().cancelDiscovery();
                    mBTSocket.connect();
                }
            } catch (IOException e) {
// Unable to connect to device
                e.printStackTrace();
                mConnectSuccessful = false;
            }
            return null;
        }

        @Override
        protected void onPostExecute(Void result) {
            super.onPostExecute(result);

            if (!mConnectSuccessful) {
                Toast.makeText(getApplicationContext(), "Could not connect to device. Is it a Serial device? Also check if the UUID is correct in the settings", Toast.LENGTH_LONG).show();
                finish();
            } else {
                msg("Connected to device");
                mIsBluetoothConnected = true;
                mReadThread = new ReadInput(); // Kick off input reader
            }

            progressDialog.dismiss();
        }

    }


}