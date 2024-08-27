<h1 align="center" >IOT Smart Crossroad</h1>

<p align="center">
  <img src="https://raw.githubusercontent.com/catppuccin/catppuccin/main/assets/palette/macchiato.png" width="400" />
</p>

"IOT smart crossroad" is a simulator project that uses ESP32 together with other sensors and output devices to create a simple smart crossroad. The project contains two ESP32 boards, this is the second board. You can check out the first board [here](https://github.com/vicyan1611/IOT_smart_crossroads).

Use PlatformIO with ESP32 and Arduino Framework, Wokwi for VSCode, C++

<h2>Installation</h2>

- Install the PlatformIO and Wokwi for VSCode via [this tutorial](https://vinhphamthanh.dev/posts/config-wokwi-for-vscode/).
- Build the project using PlatformIO.
- Run the simulator.

<h2>Functions</h2>

- The ultrasonic sensor counts the number of cars on the road and sends them to the MQTT broker server, the other board will receive and calculate traffic light time. 
- Walkers can press a button to get priority to the light.
- Auto-detect sound (simulated with a PIR motion sensor) from priority cars to put down the barriers.
- Auto turn on/off street lights.