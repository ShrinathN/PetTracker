# PetTracker
A simple LoRa based device to act as a beacon/pet proximity sensor. Made for my dog Thunder.

## How does it work?
The RF96 LoRa radio transmits a packet every ~8 seconds which can be picked up by any nearby receiver. The packet contains the pet's name.
It is only a proxyimity sensor, it will not give the exact position of the transmitter.

## Circuit Diagram
![Circuit Diagram](https://raw.githubusercontent.com/ShrinathN/PetTracker/master/images/circuit.png)

This is the circuit diagram. The 3V power supply can go up to 3V3 and it can be replaced with a battery or whatever you want.

## Runtime
![Runtime](https://raw.githubusercontent.com/ShrinathN/PetTracker/master/images/runtime.png)

I have not tested this out but this is a rough estimate of how long the beacon should be able to function on different types of cells.
