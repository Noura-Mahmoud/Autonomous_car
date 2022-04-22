from flask import Flask , request , Response
from flask_cors import CORS
from flask import jsonify
from Camera import VideoCamera
from Line_detection.lane import detect ,prediction
from joblib import load


# Create flask & cors instance 
app = Flask(__name__)
cors = CORS()
frame = VideoCamera()
cors.init_app(app)

# clf = load('model.joblib')

directions=[]
dir = ["None"]
mod = ["None"]
# state ={"mode":"mode", "direction": "direction"}

@app.route('/video_feed',methods=['POST'])
def video_feed():

     request_data = request.get_json()
     mode= request_data["mode"]
     direction=request_data["direction"]
     mod[0] = mode

     if mode == "Automatic" :
          frame.get_frame()
          direction= prediction()
          # direction= detect()
          print(direction)
          # directions.append(direction) 
          dir[0] = direction
          state= {"mode":mode, "direction":dir[0]}

     else:
          if mode == "Manual":
               state= {"mode":mode,"direction":direction}
               dir[0] = direction
     print(state)  
     return state 

# Serving ESP GET request 
@app.route('/direction',methods=["GET"])
def send_direction():
     # state= {"mode":mod[0],"direction":dir[0]}
     state= (mod[0],dir[0])
     print(state)
     print("ESP server") 
     return jsonify(state)

if __name__ == "__main__":
    app.run(host='0.0.0.0', port= 8090,debug=True)
    	
