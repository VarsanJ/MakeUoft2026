## Relief Jacket

## Inspiration
Large earthquakes occur around the world, from Turkey (2023) to Japan (2011). Earthquakes are not preventable or controllable. Instead, they are a natural consequence of the movement of tectonic plates underneath the planet. What we have seen is that after earthquakes, the rescue process is prolonged as emergency services try to find people. These locations can be hard to access or sometimes completely trapped. Often, this is compounded with limited connectivity from the earthquake zone to the outside world. We as a team wanted to design a product that would make it easier to detect and find people. 

## What it does
"Relief Jacket" is a product that would be distributed to areas prone to natural disasters, such as people living near the Ring of Fire. It is connected to a map, where in emergency situations the jacket provides live location information and appends it to a website. This information is designed to be accessed by emergency response personnel. Individuals requiring more immediate attention can send distress signals using the joystick, which is then logged to the map. To aid with survival, the jacket collects information such as body temperature reading and distance from obstructions in the front. For people who are still able to move, this enables them to make decisions such as whether to take medication for a fever or if they should move somewhere else with less obstructions. 

## How we built it
The design uses two microcontrollers connected simultaneously. The Arduino Uno Q is used to control the sensors and displays. The breadboard is connected to a Breadboard Power Supply, which brings down 9V to 5V, which is necessary for the components. The GPIO digital pins on the Arduino are used to control the components and transmit information/receive data. The ESP-32 Dev Board is used to connect to the network and the map. The joystick clicks are used to append panics to the map, and the web page with information can be accessed by individuals using the ESP-32's own network, ensuring connectivity regardless of available connections. 

## Challenges and Learning Opportunities
Challenges we encountered include difficulty with seeing the information on the LED Board due to contrast, issues with providing a strong, adequate power supply on the breadboard, and accuracy issues with readings from the sensors. Debugging these issues required individual wire testing, running test programs to isolate the issues, and incorporating new hardware components. These challenges were learning opportunity, since we were able to collaboratively problem solve and find solutions. Furthermore, throughout the project, we gained experience in not just the hardware but also deploying a web solution to complement the design. We are proud of our accomplishments in getting sensory readings, displaying the sensory readings, and being able to incorporate it with the actual prototype jacket (a T-shirt). 

## What's next for Relief Jacket
Future design objectives include:
- Incorporating a camera with the Arduino Uno Q's AI processing power to get smart live-time image detection, helping individuals find rescuers and vice-versa.
- Using PCB Design and soldering components to the actual design to ensure a more stable connection in contrast to using wiring (wiring is for the prototype).
- Incorporating a radio based communication system on the jacket such that individuals can try to communicate with nearby rescuers.
