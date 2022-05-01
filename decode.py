import serial
import json

MORSE_CODE_DICT = { 'A':'.-', 'B':'-...',
                    'C':'-.-.', 'D':'-..', 'E':'.',
                    'F':'..-.', 'G':'--.', 'H':'....',
                    'I':'..', 'J':'.---', 'K':'-.-',
                    'L':'.-..', 'M':'--', 'N':'-.',
                    'O':'---', 'P':'.--.', 'Q':'--.-',
                    'R':'.-.', 'S':'...', 'T':'-',
                    'U':'..-', 'V':'...-', 'W':'.--',
                    'X':'-..-', 'Y':'-.--', 'Z':'--..',
                    '.':'.-.-.-', ' ':'/' }

def decrypt(message):
    
    message += ' '
    
    decipher = ''
    citext =''
    for letter in message:
        if (letter != ' '):
            i = 0
            citext += letter
        else:
            i += 1
            if i == 2:
                decipher += ' '
            else:
                decipher += list(MORSE_CODE_DICT.keys())[list(MORSE_CODE_DICT.values()).index(citext)]
                citext = ''
                
    return decipher



if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    ser.reset_input_buffer()
    message = ""
    
    while True:
        
        if ser.in_waiting > 0:
            line = ser.readline()
            if (line == b' \r\n'):
                pass
            else:
                line = line.decode('utf-8').rstrip()
                message += line + ' '
                x = json.dumps({'encrypted': message, 'decrypted':decrypt(message)})
                print(x, end='', flush=True)
            
    
