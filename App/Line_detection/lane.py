import cv2
from PIL import Image, ImageOps
from keras.models import load_model
import numpy as np
from Line_detection.Lib.utils import show_image, compute_angle, detect_direction, show_heading_line
import warnings
warnings.filterwarnings('ignore')

model = load_model('C:/Users/noura/Downloads/Autonomous-Driving-Car-master/App/model6/keras_model.h5')

def detect():
        
    # frame = cv2.imread('../images/image5.jpg')
    frame = cv2.imread('./image.jpg')
    # show_image("Original image", frame)
    
    angle = compute_angle(frame)
    print('-----------------------------------------------------')
    print('Steering angle: ', angle)
    
    direction = detect_direction(frame)
    # print('direction: ', direction)
    
    # finalImage = show_heading_line(frame)
    # show_image("finalImage", finalImage)
    
    return angle, direction


def prediction ():
        
                    # Create the array of the right shape to feed into the keras model
              # The 'length' or number of images you can put into the array is
              # determined by the first position in the shape tuple, in this case 1.
              data = np.ndarray(shape=(1, 224, 224, 3), dtype=np.float32)
              # Replace this with the path to your image
            #   image = Image.open('C:/Users/noura/Downloads/Autonomous-Driving-Car-master/App/model/image35.jpg')
              image = Image.open('./image.jpg')
              #resize the image to a 224x224 with the same strategy as in TM2:
              #resizing the image to be at least 224x224 and then cropping from the center
              size = (224, 224)
              image = ImageOps.fit(image, size, Image.ANTIALIAS)

              #turn the image into a numpy array
              image_array = np.asarray(image)
              # Normalize the image
              normalized_image_array = (image_array.astype(np.float32) / 127.0) - 1
              # Load the image into the array
              data[0] = normalized_image_array
              
              # run the inference
              prediction = model.predict(data)
              max_item = max(prediction[0])
              max_probabilty = prediction[0].tolist().index(max_item)

              dict = {"0": "F",
                        "1": "R",
                        "2": "L"}

              direction = dict[str(max_probabilty)]
              print(direction)
              return(direction)