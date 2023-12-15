# E-Comet-Software-for-Shell-Eco-Marathon
DC Motor Controller software for the [Shell Eco-Marathon](https://www.shellecomarathon.com/) by the team E-Comet Pierrard from the [School of Engineering of Pierrard-Virton](https://www.henallux.be/ecole-dingenieurs-departement-ingenieur-industriel-de-pierrard-virton).

![SolidWorks-Ecomet](https://github.com/HugoBrunner/E-Comet-Software-for-Shell-Eco-Marathon/assets/146762597/fdcfead4-378e-41e6-80af-602ade4bbf07)

The E-Comet team is composed of nine electromechanical engineering students. The team is composed of five subgroups :
- Electronics and software
- Aerodynamic and shell design
- Propulsion
- Chassis
- Steering  
  
We are designing a electric prototype to eventually participate to the Shell Eco-Marathon Europe and Africa 2024 at Nogaro in France.

## Software

### The goal of the code of the DC motor driver
The code is there to control the DC motor thanks to a potentiometer. It will also collect all the data from the sensors and write them on micro SD card. Finally, it will used the data to stop the driver if there are problems like to much current or to much heat at the MOSFET surface.

### The goal of the Arduino
The code is there to show the speed informations to the driver. In fact, it will record the actual speed of the prototype and will calculate the mean speed. Theses two speeds are displayed on the screen.

### Python Script
The Python script is used to process the data from the board to calculate the energy consumption, mean velocity or the battery voltage change. The script will give a LaTeX report with data and plots.

### Useful links
- [Legacy PIC24 MCU & dsPIC DSC Peripheral Library](https://www.microchip.com/SWLibraryWeb/product.aspx?product=PIC24%20MCU%20dsPIC%20Peripheral%20Lib#)
- [MPLAB® Code Configurator](https://www.microchip.com/en-us/tools-resources/configure/mplab-code-configurator)
- [dspic33ck-power-pwm-complementary](https://github.com/microchip-pic-avr-examples/dspic33ck-power-pwm-complementary)
- [MCC Card tutorial](https://microchip.my.site.com/s/article/dsPIC33Cx--How-to-create-an-SD-card-Example-using-MCC-Classic)

## Controller PCB design
Git repository for the [PCB design](https://cadlab.io/project/27305/master/files)
### Datasheet
- [dsPIC33CK32MP105](https://github.com/HugoBrunner/E-Comet-Software-for-Shell-Eco-Marathon/blob/master/Software_Shell/dsPIC33CK64MP105_Family_Data_Sheet_DS70005363E-1919058.pdf)

### Renders of the controller
Some renders of the PCB :
![PCB_cote](https://github.com/HugoBrunner/E-Comet-Software-for-Shell-Eco-Marathon/assets/146762597/f9fb2a41-4999-4e1d-90c8-e5f32ad385d9)
![PCB_dessous](https://github.com/HugoBrunner/E-Comet-Software-for-Shell-Eco-Marathon/assets/146762597/2173212e-2715-44cf-a522-24eec73d3cae)
![PCB_dessus](https://github.com/HugoBrunner/E-Comet-Software-for-Shell-Eco-Marathon/assets/146762597/059b0242-5ef5-439a-95d5-404cf600eb5a)

## Renders of the prototype
Coming soon...

## Links to follow our adventure
If you want to see how our project is going :
- [Instagram](https://www.instagram.com/pierrardecomet/?igshid=MzRlODBiNWFlZA%3D%3D)  
- [Linkedin](https://www.linkedin.com/company/e-comet-pierrard/)  
- [Facebook](https://www.facebook.com/profile.php?id=100092158477900)
