from requests import *
import json
import os
import datetime
import time

ip = "http://192.168.1.100"

def getNewToken():
	url =  "http://iot.jorgvisch.nl/token"
	header = {"Content-Type":"applicaton/x-www-form-urlencoded"}
	data = "grant_type=password&username=rens.aerts%40han.nl&password=Rensaerts1!"

	response = request("POST", url, headers=header, data=data)
	response_json = json.loads(response.text)
	new_token = response_json.get("access_token")

	os.remove("token.txt")
	temp_file = open("token.txt", "a+")
	temp_file.write(new_token)

	return new_token


def uploadData():
	url = "http://iot.jorgvisch.nl/api/Weather"
	header = {"Authorization":"Bearer " + token}
	timestamp = datetime.datetime.now().isoformat()

	temp_raw = request("GET", ip+"/temp")
	temp_json = json.loads(temp_raw.text)
	temp = temp_json.get('Temperatuur')

	lux_raw = request("GET", ip+"/lux")
	lux_json = json.loads(lux_raw.text)
	lux = lux_json.get('Lichtintensiteit')

	print(lux)
	print(temp)

	data = {
  		"Weatherstation": "123",
  		"Timestamp": timestamp,
  		"Temperature": temp,
  		"Illuminance": lux
	}

	send = request("POST", url, headers=header, data=data)

	response = send.text

	return response


def checkToken():
	url = "http://iot.jorgvisch.nl/api/greetings"
	header = {"Authorization":"Bearer " + token}

	response = request("GET", url, headers=header)

	return response

def isTokenOnGeldig():
	valid_token = checkToken()

	json_valid_token = json.loads(valid_token.text)

	return (json_valid_token == "I don't know you")

if __name__ == "__main__":
	previousMillis = int(round(time.time()*1000))
	interval = 60000

	while(True):
		currentMillis = int(round(time.time()*1000))

		token_file_write = open("token.txt", "a+")
		token_file_read = open("token.txt", "r")
		token = token_file_read.read()

		if (currentMillis - previousMillis >= interval):
			previousMillis = currentMillis
			
			if isTokenOnGeldig():			
				print("Getting new token")
				getNewToken()
			else:
				print("De data word geupload")
				uploadData()

	
	
	
