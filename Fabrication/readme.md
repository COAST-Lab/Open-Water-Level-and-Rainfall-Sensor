**Here is a guide for building the Open Water Level and Precipitation Sensor. Some directions are derived from the IORodeo site which this sensor was adapted from. A BOM can be found [here](https://github.com/COAST-Lab/Open-Water-Level-and-Rainfall-Sensor/tree/d36a67804bb3516f8769341ffb8f02172248dd15/Fabrication/Bill%20of%20Materials).**

**1. Prepare the Enclosure**

The Polycase shipped with this kit is a 5.1 x 3.7 x 2.2 inches weatherproof enclosure with 10 optional M16/20 knockouts. For convenience, 3 of the M20 knockouts have already been removed as shown in the image below. You will also remove the knockout next to this one for the rainfall cable. In this step you will further prepare the enclosure by attaching the mounting feet, the PCB mounting hardware and adding the vent plug to the vent hole.

<img width="1000" height="667" alt="image" src="https://github.com/user-attachments/assets/6ab4b2c1-3001-49e0-b455-3c41c1603a9c" />



i) Attach the 4 mounting feet to the base of the enclosure using a hammer to gently tap the feet into place

<img width="1600" height="1450" alt="image" src="https://github.com/user-attachments/assets/3f38e087-c12c-4082-bdbf-c0c9c4b315b4" />


   
ii) Insert the 4 PCB mounting parts into the corners of the enclosure. Press them firmly into place, one in each corner.

<img width="1000" height="667" alt="image" src="https://github.com/user-attachments/assets/45ce7fd1-b576-47d4-b67b-53cb2007c3a8" />


   
iii) Unscrew to separate the two parts of the vent plug. Place the vent part into the bottom right knockout with the plastic ring inside the enclosure. Screw the parts back together again so that the vent plug is facing out of the enclosure as shown in the images below

<img width="1000" height="667" alt="image" src="https://github.com/user-attachments/assets/4072d424-6a1b-4faa-8072-ae4a52e65f0e" />


  
**2. Mounting the MaxSonar ultrasonic distance sensor**

Note: The XL-MaxSonar-WRMA1 in the kit comes with an adapter PCB pre-mounted for easy, solder-less connection to the electronics. To use the MaxSonar distance sensor with the waterproof enclosure, it is first modified to fit the M20 knockout using a 0.75" to 0.5" reducer pipe fitting. An extending pipe (1.85" long) fits over the adapter before connecting to the reducer. These steps cover attaching the cable, pipe fittings and mounting the sensor into the enclosure.

i) Attach the 20 cm cable to the sonar sensor

   <img width="1000" height="667" alt="image" src="https://github.com/user-attachments/assets/f9603466-3aef-4560-a2e8-f22543effeb1" />

ii) Take the assembled pipe connector out of its bag and unscrew to separate into the 3 individual parts shown below
<img width="1000" height="667" alt="image" src="https://github.com/user-attachments/assets/fd11e4b4-b552-4d1f-891b-aaefefa5ee56" />

  
iii) Fit the extender pipe over the cable and adapter and screw directly onto the max sonar sensor. Fold the cable into the extender pipe leaving approx. 1-2 inches of cable sticking out
<img width="1000" height="667" alt="image" src="https://github.com/user-attachments/assets/dfea946d-58bc-45df-9a77-a818cf1eb837" />
 
iv) Next fit the reducer over the cable and screw into the pipe connector.
<img width="1000" height="667" alt="image" src="https://github.com/user-attachments/assets/48c95b81-b935-4cbb-92e5-cbcf5060be26" />
 
v) Fit the assembled sensor into the enclosure placing the black locknut inside the enclosure to secure the sensor in place.
<img width="1000" height="667" alt="image" src="https://github.com/user-attachments/assets/39cdec32-913d-4973-945b-96c4b2ad36a4" />
   
**3. Attaching the electronics to the PCB**
   
i) Solder the Gravity Sensor to the corresponding vias under the PCB. This will require stripping the wires from the Gravity sensor. The circuit diagram [here](https://github.com/COAST-Lab/Open-Water-Level-and-Rainfall-Sensor/blob/7bba7204df4ac1aff715286652a65af4b2cf0a13/Fabrication/OWLR%20Circuit%20Diagram.jpg) shows correct connections.


ii)  Mount the Feather Tripler PCB into the enclosure using the 4 mounting screws. Tighten down with the screwdriver to secure in place
  
iii) Connect the cable from the MaxSonar to the middle JST PH 4-pin connector (J3). Use the image below to verify the cable is inserted in the correct orientation. Next, insert the micro SD card into the SD card socket on the Adalogger and insert both the Adalogger FeatherWing and Boron onto the PCB.
 
iv) Remove the backing from the antenna and stick it to the underside of the lid.

<img width="1000" height="667" alt="image" src="https://github.com/user-attachments/assets/accc778f-53ff-4d52-8984-846e1f8c2622" />
  
**4. Flashing Firmware and Integrating Particle**
   
i) Flash the code here to the Boron. 
  
ii) To use cellular, follow the instructions here to integrate your Boron with Google Sheets through the Particle Console. 

 
**5. Prepare the Rainfall Sensor**
    
i) Use the middle knockout to attach the Plastic Submersible Cord Grip .39-.55". This may require shaving a wider circumference on the knockout to fit this cord grip. 
  
ii) Run the rainfall cable gland through the cord grip and plug it into the gravity sensor port. 
 
iii) Due to know specific placement for the gravity sensor, electrical tape was used to hold it in place between the boron and adalogger. 



**6. Prepare the Solar Power system**
   
i) Take the waterproof cable entry out of its bag and unscrew to separate into the 3 individual parts shown below. Push the rubber ring out of the main part.
<img width="1000" height="667" alt="image" src="https://github.com/user-attachments/assets/aadb9e1c-fb78-4f73-b6ae-31c2985cda07" />
  
ii) Take the end of the solar system power cable and pass it through the "cap" end in the orientation shown below
<img width="1000" height="667" alt="image" src="https://github.com/user-attachments/assets/1ff4fee5-f2d4-4c87-ba24-cf9cc4d9feb8" />
 
iii) Next, work the rubber gasket onto the power cable. This can be a tight fit over the plug, so gently push/slide the rubber gasket until it goes onto the cable
<img width="1000" height="667" alt="image" src="https://github.com/user-attachments/assets/40b7d375-e520-41d7-90eb-bd47f6a0dcbf" />
<img width="1000" height="667" alt="image" src="https://github.com/user-attachments/assets/05824e5f-e441-4abc-8372-bb262512994f" />

iv) Next, pass the main part onto the cable and re-insert the rubber gasket back in place
 
v) Screw these two parts back together again. The lock nut will be used in the next step.
<img width="1000" height="667" alt="image" src="https://github.com/user-attachments/assets/a3037e58-74b5-415e-9ea0-d2e3ebafc9a4" />

vi) Place the lock-nut into the enclosure and pass the end of the power supply cable through the enclosure knockout and lock-nut into the DC jack plug on the Feather Tripler. Once you have the power cable situated, tighten down the lock-nut inside the enclosure and the waterproof cable entry on the other side. The cable should be tightly gripped in place.  
