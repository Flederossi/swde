import cv2
import sys

filename = ""
charCount = 65
numZ = 0

def main():
	global filename, numZ, charCount

	vidcap = cv2.VideoCapture(sys.argv[1])
	success, image = vidcap.read()

	while success:
		filename = ""
		for z in range(1, numZ + 1):
			filename += "Z"
		filename += chr(charCount)
		
		charCount += 1

		if charCount > 90:
			charCount = 65
			numZ += 1

		cv2.imwrite(filename + ".png", image)
		success, image = vidcap.read()

if __name__ == "__main__":
	main()