# NAIT-Final-Project
code from my final project for NAIT's electronics engineering technologist final semester project
THIS README WILL BE SHORT AS I WROTE A LARGE TECHNICAL DOCUMENT ON THIS PROJECT WHICH CAN BE VIEWED @ https://mindset-design.github.io/Portfolio-Site/Site/dist/index.html 
THERE IS ALSO A YOUTUBE VIDEO AVAILABLE @ https://www.youtube.com/watch?v=rxiFlBYINkI
THIS PROJECT ISNT HOW I'D ACTUALLY MAKE  A DRINK MACHINE I WAS SIMPLY MAKING A PROJECT THAT WAS TO MEET THE MARKING RUBRIC 

//final codesys\\
this file contains the codesys files which controlled the raspberry pi. This had an hmi that was hosted locally over wifi at its ip adress and sent info to another via parallel connection to a  micro that was wirelessly communicating to the drink machine micro 

//touch pad\\
this file contains the adruino code that was for the wireless touch pad controller for the drink machine. It has the code to turn on leds when the motion sensor was tripped and send requests to the drink machine when a touch pad was pressed

//codesys\\
this file contains the arduino file for the parallel connection to the raspberry pi and wireless to the drink machine

//motor controller\\
this file is for the actuall drink machine. It controls the motors, receives signals from the other micros and takes the water temperature which is sent back the the raspberry pi to be displayed in the HMI.
