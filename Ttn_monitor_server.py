import sys
import time
import base64
import json
import struct
import ttn
import pyodbc

#VERANDER DEZE KEYS IN JE EIGEN KEYS GEMAAKT IN TTN.
app_id = "gloomi"
access_key = "ttn-account-v2.K3bzc1jjNCFuvetH8g4Llx8O7u-KKT_HwrR-oPpWM0k"

global conn
#VERANDER SERVER IN DE NAAM VAN JE EIGEN MYSQL SERVER.
conn = pyodbc.connect('Driver={SQL Server};'
                      'Server=DESKTOP-SPGGB7R;'
                      'Database=gloomi;'
                      'Trusted_Connection=yes;')
print("connected to db")


# The callback for when a PUBLISH message is received from the server.
def uplink_callback(msg, client):
    # Decode message and print
    payload_raw = msg.payload_raw
    payload_plain = base64.b64decode(payload_raw)
    vals = struct.unpack("bbbb", payload_plain)
    print(f"@%s client={msg.dev_id}>> temp={vals[0]} hum={vals[1]} lux={vals[2]} movement={vals[3]}" % (time.strftime("%H:%M:%S")))

    # Send Downlink to regulate light intensity of LED for when this feature is added.
    # mqtt_client.send(dev_id=msg.dev_id, pay=base64.encodebytes(bytes([120])).decode(), port=1, conf=True, sched="replace")

    # update info in database
    cursor = conn.cursor()
    cursor.execute('SELECT * FROM gloomi.dbo.lampen')
    cursor.execute(f"UPDATE gloomi.dbo.lampen SET temperatuur={vals[0]}, vochtigheidsgraad={vals[1]}, luxgraad={vals[2]} WHERE apparaatid='{msg.dev_id}';")
    conn.commit()


handler = ttn.HandlerClient(app_id, access_key)

mqtt_client = handler.data()
mqtt_client.set_uplink_callback(uplink_callback)
mqtt_client.connect()
time.sleep(60)
#JE KAN DEZE LOOP NOG ONEINDIG DOOR LATEN GAAN
mqtt_client.close()