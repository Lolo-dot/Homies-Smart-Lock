# @author:Gurarshdeep Singh
# @Date:February 12,2021

import time
import pyrebase

# Configuring datbase settings 
config = {
  "apiKey": "Enter_your_api_key",
  "authDomain": "Enter_your_authdomain.firebaseapp.com",
  "databaseURL": "https://Enter_your_datbaseurl.firebaseio.com",
  "storageBucket": "Enter_your_storagebuckeykey"
}

firebase = pyrebase.initialize_app(config)
db = firebase.database()


# Code for button
def button():
    # asking user to enter value
    user_value = input("Please Type l/lock or u/unlock: ")
    value = True
  
    # depending upon what user has entered change the value variable status
    if(user_value == "l" or user_value=="lock"):
        value=True
    elif(user_value == "u" or user_value == "unlock"):
        value=False
    else:
        return "Invalid input"
    # Depending upon value set database variable value to True/False
    try:
        if(value):
            data = {
                "lock_status": value
            }   
            db.child("Homies-Lock").child("status").set(data)
            print("Lock successfull")
        else:
            data = {
                    "lock_status": value
                    }
            db.child("Homies-Lock").child("status").set(data)
            print("Unlock successfull")
    except:
        print("Please try again")

# running the function
button()
