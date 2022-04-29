# Janus
### Team Members: 
#### Oliver Bunner (Section A) and Gino Doumit (Section B)
### Georgia Institute of Technology


#### Project Overview
##### Idea
Janus is a robot car that is easy to setup and use.
The device aims to provide a smooth experience for any person who wants to operate a 

##### Features
- Control the car's movement using the Bluetooth app
- Control the car's movement using sound
- Control the car's speakers using the Bluetooth app
- View the state the car is in on the LCD

##### Video


##### Controls
Arrows: 
- Move the car in the direction the arrows are pointed in.

Buttons:
- 1 - Play a honk sound on the speaker
- 2 - Spins the car in place
- 3 - Voice controlled forwards
- 4 - Voice controlled backwards

##### Future Additions
- Self-drive mode
- Selecting songs to play from an online library
- Developping a dedicated mobile app
- Adding cameras onto the car and being able to see from the car's perspective

#### Setup

##### Parts Used
- [mBed](https://os.mbed.com/cookbook/Homepage)
- [uLCD](https://os.mbed.com/users/4180_1/notebook/ulcd-144-g2-128-by-128-color-lcd/)
- [2x DC Motors](https://os.mbed.com/cookbook/Motor)
- 2N9304 BJT
- [Speaker](https://os.mbed.com/users/4180_1/notebook/using-a-speaker-for-audio-output/)
- [H-Bridge](https://os.mbed.com/cookbook/Motor)
- [Microphone](https://os.mbed.com/components/Adafruit-MEMS-Microphone-Breakout-SPW243/)
- [Bluetooth Chip](https://os.mbed.com/users/4180_1/notebook/adafruit-bluefruit-le-uart-friend---bluetooth-low-/)
- Wheels and car frame

N.B: All of the parts used are the ones present in the links. 

##### Schematic
![Schematic for Janus](https://github.com/ginod22/janus/blob/main/Schematic.png)


#### Wiring

![mBed Wiring](https://github.com/ginod22/janus/blob/main/Wiring/mBed.png)
![uLCD Wiring](https://github.com/ginod22/janus/blob/main/Wiring/uLCD.png)
![Microphone Wiring](https://github.com/ginod22/janus/blob/main/Wiring/Microphone.png)
![Speaker Wiring](https://github.com/ginod22/janus/blob/main/Wiring/Speaker2.png)
![Bluetooth Chip Wiring](https://github.com/ginod22/janus/blob/main/Wiring/Bluetooth.png)
![Motors + H-Bridge Wiring](https://github.com/ginod22/janus/blob/main/Wiring/MHB.png)


### Software 
```
function test() {
  console.log("notice the blank line before this function?");
}
```
