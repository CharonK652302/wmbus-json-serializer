# Embedded JSON Serializer for w-M-Bus Meter Data

## Project Overview
This project implements an embedded-friendly C library that serializes structured smart meter data into a predefined JSON format.  
The output format strictly follows the specification provided in the assignment and does not rely on any external JSON libraries.

The library is designed to be transport-agnostic and suitable for constrained embedded environments.

---

## Platform & Language Choice
- **Language:** C
- **Platform:** Generic GCC / PC Console Application

### Justification
The core serialization logic is fully platform-independent and uses only standard C functions (`snprintf`).  
This allows the same code to be reused on embedded platforms such as STM32, ESP32, or bare-metal systems with minimal changes.

---

## Project Structure
