# IOT Task_2

## Team members
| Name  | Section| BN |
| ------------- | ------------- |------------- |
|Dalia Lotfy| 01| 30|
|Marwa AbdelAal| 02| 23|
|Nada Ezzat |02 |38  |
|Noura Mahmoud |02 |39|


## 1- Get your own IP address by using cmd of your device and type 
```
ipconfig
```

then make sure to change the existing IP in 'esp.ino', 'ard.ino' and 'AutoMode.js', 'Home.js', 'ManualMode.js' in folder (\front\Components)

- Make sure to change IP adress and SSID & password in the arduino code first

#### install *IP Webcam* and start the server inside it for the automatic mode. Be sure to change the ip in \App\Camera.py


<!-- ## 1- Create virtual Enviironment  -->
<!-- 
```
pip install virtualenv
virtualenv venv  
```

#### PS Don't forget to activate your virtual environment

#### In case working with windows activation may fail so check next link

[Activation](https://stackoverflow.com/questions/18713086/virtualenv-wont-activate-on-windows) -->

## 2- Make sure to be in *\App* then run web_cam.py to run server 

> install requirements first : 
> ```
> python -m pip install -r requirements.txt
> ```

```
python web_cam.py
```

- For the model used in the automatic mode we used *https://teachablemachine.withgoogle.com/train/image* and trained it on the lane 

## 3- Make sure to be in *front_* directory then run following commands

```
npm init
npm install
npm start
```

<!-- ### existing in hall-way two
![](/images/hallway2.png) -->

## 4- To run the mobile app

- Be sure to have *expoGo* application on your phone
- You can use the first link in the terminal after ruuning the front, then choose *Tunnel* and scan the QR code in the link


