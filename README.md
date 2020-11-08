# LiquidHacks_Controller

## File Structure
wasdcj/wasdcj.ino is the code for the bottom pedals that control movement
2mpu/2mpu/2mpu.ino is the code that lives on the inside of the blaster and controls cursor movement and monitors button presses

## Usage
Load both Arduinos with their respective code one at a time, and make sure your wiring is set up correctly.

## Inspiration
To put it simply, the R.A.N.G.E (Riot Associated Nerf Gun Experience) came from a desire from our team to find a new way to play Valorant, one of our favorite video gaming experiences of the past year. So we decided what better way to enhance that experience than to truly put ourselves in the game and better see what our character sees with the help of VR while holding a physical blaster (Nerf for obvious reasons, emblazoned with our favorite horse, of course!). It also works with any other game or even any computer program that uses a cursor since it's essentially an accelerometer based mouse with easily programmable inputs.

## What it does
The R.A.N.G.E (Riot Associated Nerf Gun Experience) is a combination of three things:

-A modded Nerf blaster that we gutted to stuff an Arduino Pro Micro, a pair of accelerometers, and a whole bunch of buttons inside to handle cursor movement and abilities

-A Dance Dance Revolution style board that has buttons under wooden plates to handle directional movements running off of another Arduino Pro Micro

-An Oculus Quest using VR Virtual Desktop to run Valorant (this is of course optional, but it really enhances the experience)

## How we built it
Our Arduinos run the show and serve two distinct purposes: 

-The one inside the Nerf blaster reads data from two MPU 6050 accelerometers, on measuring vertical acceleration (measured in g-force) and the other measuring yaw (movement along a horizontal axis). It then process the data generated every clock cycle and converts them into simulated mouse movements relative to the cursor's current location. They also listen for input for various buttons mounted on the blaster (trigger, aim down sights, character abilities, reload, and weapon swapping, etc.). Since the yaw measure is very finicky, we also use the button directly below the trigger to allow for any horizontal cursor movement to be stopped, which allows the user to re-center the gun easily (you'll see this in the video when Derreck is frantically swiping the gun back to the middle every few seconds - it's to reset his cursor to the middle of the screen.

-The Arduino on the footpad listens to input from 6 buttons (4 directions, jump, crouch) and simulates key presses to allow you to move around the map with the pedals.

## Challenges we ran into
-We had to constantly recalibrate the sensitivity and thresholds for movement our code had for the accelerometers, it took us until 8pm on Saturday to finally solve it by tracking an average of the past 3 yaw measurements and multiplying that result by +/-30 to figure out how far to move the cursor horizontally.

-The hardware decided to stop working as expected sometimes (i.e. buttons acting pressed constantly which filled our IDE with lines of 'ddddddddddddddddddddddddddddddddddddddddddddddddddddddddd'

-We had to remove a slice of the blaster for the breadboard we soldered onto to actually fit.

-Getting two Arduinos two work at the same time was harder than it should have been.

## Accomplishments that we're proud of

-Making the cursor movement as smooth as we got it to be - genuinely surprised it worked as well as it did.

-Derreck being REALLY good at working the blaster

-Getting all the blaster buttons to fit on one Arduino in the gun - I was expecting to need a separate one just for accelerometers due to processing power overloading and misunderstanding how event based programming in Arduino language works.

## What we learned

-How to be more comfortable with the Arduino IDE (and its shortcuts)

-The true meaning of 'yaw' 

-A much stronger knowledge of the MPU 6050 accelerometer and how to control it and understand its outputs

## What's next for R.A.N.G.E.

-Implementing a smoother method for horizontal cursor movement based off more complex math
-Adding more buttons to the blaster for more features
