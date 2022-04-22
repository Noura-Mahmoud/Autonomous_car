import cv2
from Lib.utils import show_image, compute_angle, detect_direction, show_heading_line
# from Line_detection.Lib.utils import show_image, compute_angle, detect_direction, show_heading_line
import warnings
warnings.filterwarnings('ignore')

def detect():
        
    # frame = cv2.imread('../images/image5.jpg')
    frame = cv2.imread('../image1.jpg')
    show_image("Original image", frame)
    
    angle = compute_angle(frame)
    print('-----------------------------------------------------')
    print('Steering angle: ', angle)
    
    direction = detect_direction(frame)
    print('direction: ', direction)
    
    finalImage = show_heading_line(frame)
    show_image("finalImage", finalImage)
    
    return angle, direction

detect()