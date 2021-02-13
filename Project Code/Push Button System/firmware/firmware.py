
import time
import pyrebase

# Configuring datbase settings 
config = {
  "apiKey": "dyl5awrdSIeX43UEEloKwR3h88GcFINwxkR2nkUX",
  "authDomain": "homies-smart-lock.firebaseapp.com",
  "databaseURL": "https://homies-smart-lock-default-rtdb.firebaseio.com",
  "storageBucket": "homies-smart-lock.appspot.com"
}

firebase = pyrebase.initialize_app(config)
db = firebase.database()


# Code for button
def button():
    user_value = input("Please Type l/lock or u/unlock: ")
    value = True

    if(user_value == "l" or user_value=="lock"):
        value=True
    elif(user_value == "u" or user_value == "unlock"):
        value=False
    else:
        return "Invalid input"
    
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
