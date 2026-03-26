Here is a guide for building the Open Water Level and Precipitation Sensor. Some directions are derived from the IORodeo site which this sensor was adapted from. 

1. The Polycase shipped with this kit is a 5.1 x 3.7 x 2.2 inches weatherproof enclosure with 10 optional M16/20 knockouts. For convenience, 3 of the M20 knockouts have already been removed as shown in the image below. You will also remove the knockout next to this one for the rainfall cable. In this step you will further prepare the enclosure by attaching the mounting feet, the PCB mounting hardware and adding the vent plug to the vent hole.
   
i) Attach the 4 mounting feet to the base of the enclosure using a hammer to gently tap the feet into place
   
ii) Insert the 4 PCB mounting parts into the corners of the enclosure. Press them firmly into place, one in each corner.
   
iii) Unscrew to separate the two parts of the vent plug. Place the vent part into the bottom right knockout with the plastic ring inside the enclosure. Screw the parts back together again so that the vent plug is facing out of the enclosure as shown in the images below


  
2. Mounting the MaxSonar ultrasonic distance sensor

Note: The XL-MaxSonar-WRMA1 in the kit comes with an adapter PCB pre-mounted for easy, solder-less connection to the electronics. To use the MaxSonar distance sensor with the waterproof enclosure, it is first modified to fit the M20 knockout using a 0.75" to 0.5" reducer pipe fitting. An extending pipe (1.85" long) fits over the adapter before connecting to the reducer. These steps cover attaching the cable, pipe fittings and mounting the sensor into the enclosure.

i) Attach the 20 cm cable to the sonar sensor
   
ii) Take the assembled pipe connector out of its bag and unscrew to separate into the 3 individual parts shown below
  
iii) Fit the extender pipe over the cable and adapter and screw directly onto the max sonar sensor. Fold the cable into the extender pipe leaving approx. 1-2 inches of cable sticking out
 
iv) Next fit the reducer over the cable and screw into the pipe connector.
  
v) Fit the assembled sensor into the enclosure placing the black locknut inside the enclosure to secure the sensor in place.


   
3. Attaching the electronics to the PCB
   
i) Solder the Gravity Sensor to the corresponding vias under the PCB. This will require stripping the wires from the Gravity sensor. The circuit diagram here shows correct connections.
   
ii)  Mount the Feather Tripler PCB into the enclosure using the 4 mounting screws. Tighten down with the screwdriver to secure in place
  
iii) Connect the cable from the MaxSonar to the middle JST PH 4-pin connector (J3). Use the image below to verify the cable is inserted in the correct orientation. Next, insert the micro SD card into the SD card socket on the Adalogger and insert both the Adalogger FeatherWing and Boron onto the PCB.
 
iv) Connect the cable from the MaxSonar to the middle JST PH 4-pin connector (J3). Use the image below to verify the cable is inserted in the correct orientation. Next, insert the micro SD card into the SD card socket on the Adalogger and insert both the Adalogger FeatherWing and Boron onto the PCB.


  
4. Flashing Firmware and Integrating Particle
   
i) Flash the code here to the Boron. 
  
ii) To use cellular, follow the instructions here to integrate your Boron with Google Sheets through the Particle Console. 


 
5. Prepare the Rainfall Sensor
    
i) Use the middle knockout to attach the Plastic Submersible Cord Grip .39-.55". This may require shaving a wider circumference on the knockout to fit this cord grip. 
  
ii) Run the rainfall cable gland through the cord grip and plug it into the gravity sensor port. 
 
iii) Due to know specific placement for the gravity sensor, electrical tape was used to hold it in place between the boron and adalogger. 



6. Prepare the Solar Power system
   
i) Take the waterproof cable entry out of its bag and unscrew to separate into the 3 individual parts shown below. Push the rubber ring out of the main part.
  
ii) Take the end of the solar system power cable and pass it through the "cap" end in the orientation shown below
 
iii) Next, work the rubber gasket onto the power cable. This can be a tight fit over the plug, so gently push/slide the rubber gasket until it goes onto the cable

iv) Next, pass the main part onto the cable and re-insert the rubber gasket back in place
 
v) Screw these two parts back together again. The lock nut will be used in the next step.

vi) Place the lock-nut into the enclosure and pass the end of the power supply cable through the enclosure knockout and lock-nut into the DC jack plug on the Feather Tripler. Once you have the power cable situated, tighten down the lock-nut inside the enclosure and the waterproof cable entry on the other side. The cable should be tightly gripped in place.  
