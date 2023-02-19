# MakeUofT-2023-Air-Drums
## Inspiration
As a team of retired high school musicians, we were looking to develop something based on an instrument that is intuitive to play while easy to jam with other musicians without having to worry about moving the instruments around and finding enough place to place them. Looking upon what we have, we decided that it is a good idea to build this drum-less and kit-less drumkit to make use of the joystick, and the two accelerometers. 

## What it does
The Drum-less Kit-less Drumkit (DKD) is a set of hardware extensions that can be installed on drumsticks or anything rigid that one wishes to attach it to. It uses the MPU6050 accelerometer to detect downward accelerating motions for triggering sound outputs while the player can choose the sound desired using the joystick on the right hand. Furthermore, all components are wirelessly connected to the ESP32 microcontroller which can be paired to a computer via Bluetooth. Together, the computer acts as the primary device that receives the input signal from the secondary device, the ESP32, then decodes the incoming signal to output a sound file.

## How we built it
The DKD utilizes an ESP32 with two accelerometers and a joystick to detect drum “hits” and sends them to a computer to be played. We separated the desired end product into its modules subtasks, which were all prototyped and tested individually on breadboards with Arduino UNOs before being combined slowly into the final result.

## Challenges we ran into
Many of us had to learn new languages and protocols to achieve our desired results with the hardware, which was a challenge in itself. Additionally, some faulty hardware was the source of many headaches, as it is very hard to single step through the script while having external sensors attached to the Arduino, and always assumed there were software errors instead. 

## Accomplishments that we're proud of
We are proud that we were able to connect multiple sensors to one primary device via the I2C protocol. Furthermore, we were able to establish a wireless connection from the ESP32 chip to the computer.

## What we learned
Some learned how to code in C with Arduino, and learned how to utilize external libraries, while others learned how to code in python to read wireless serial inputs and output sound files as needed.

## What's next for Drum-less Kit-less Drumkit
More sounds, and more attachments! Additional controls on the sticks or horizontal position detection to change sounds would significantly add to the experience. Sensors to detect feet movement could also simulate pedals for even more sounds.