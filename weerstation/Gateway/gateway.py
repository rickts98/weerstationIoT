from requests import *
import json
import os
import datetime
import time

token_file_write = open("token.txt", "a+")
token_file_read = open("token.txt", "r")

ip = "192.168.1.100"

def getNewToken():
	url =  "http://iot.jorgvisch.nl/token"
	header = {"Content-Type":"applicaton/x-www-form-urlencoded"}
	data = "grant_type=password&username=rens.aerts%40han.nl&password=Rensaerts1!"

	response = request("POST", url, headers=header, data=data)
	response_json = json.loads(response.text)
	new_token = response_json.get("access_token")

	print(new_token)

	os.remove("token.txt")
	temp_file = open("token.txt", "r+")
	temp_file.write(new_token)

	return new_token


def uploadData():
	url = "http://iot.jorgvisch.nl/api/Weather"
	header = {"Authorization":"Bearer " + token}
	timestamp = datetime.datetime.now().isoformat()

	t = request("GET", ip+"/temp")
	t_json = json.loads(t.text)
	data_json = t_json.get("data")
	temp = data_json.get("Temperatuur")

	l = request("GET", ip+"/lux")
	l_json = json.loads(l.text)
	data_lux_json = l_json.get("data")
	lux = data_lux_json.get("Lichtintensiteit")

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

	print(response.text)

	return response

def isTokenOnGeldig():
	valid_token = checkToken()

	json_valid_token = json.loads(valid_token.text)
	#print(json_valid_token)

	return (json_valid_token == "I don't know you")

if __name__ == "__main__":
	token = token_file_read.read()

	previousMillis = int(round(time.time()*1000))
	interval = 1000

	while(True):
		currentMillis = int(round(time.time()*1000))

		if (currentMillis - previousMillis >= interval):
			previousMillis = currentMillis
			if isTokenOnGeldig():			
				print("Getting new token")
				getNewToken()
			else:
				print("De data word geupload")
				uploadData()

	
	
	
