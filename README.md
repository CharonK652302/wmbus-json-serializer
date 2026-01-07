w-M-Bus JSON Serialization Library (Embedded C)
## Overview

This project is a small embedded-oriented C library that converts structured smart meter data into a fixed JSON format.

The goal of the assignment was not to work with real meters or wireless M-Bus communication, but to focus on how meter data would be represented internally and serialized safely before being sent to a gateway or backend system.

The implementation follows the exact JSON structure defined in the assignment and avoids the use of any external JSON libraries.

## Understanding of the Problem

In a typical smart-meter or gateway firmware, raw measurements are first stored in internal data structures and later serialized into a transport-friendly format such as JSON.

This assignment simulates that step of the pipeline:

Meter data → internal structures → JSON output

The main challenges were:

Keeping the implementation suitable for embedded systems

Avoiding dynamic memory allocation

Generating JSON manually without helper libraries

Preventing buffer overflows

Producing output that strictly matches the required structure

The focus was on clarity, correctness, and deterministic behavior, rather than on hardware or communication interfaces.

## Design Approach
## Data Modeling

The data is modeled using simple C structs:

Gateway-level metadata (ID, date, interval, etc.)

A list of device readings

Each device containing one or more measurement data points

Fixed-size arrays are used instead of dynamic memory allocation to keep memory usage predictable, which is important for embedded firmware.

JSON Serialization

JSON is generated manually using snprintf():

This allows precise control over formatting

Prevents buffer overflows by tracking the written length

Keeps the implementation portable and lightweight

The serializer writes into a caller-provided buffer, making it independent of any transport layer (UART, radio, file system, etc.).

## Public API
int serialize_to_json(
    const GatewayData *input,
    char *output,
    size_t output_size
);

## API Behavior

Serializes the provided data structure into JSON

Writes output into the given buffer

Returns the number of bytes written

Returns -1 if the buffer is too small or input is invalid

## Project Structure
.
├── include/
│   └── serializer.h     
├── src/
│   └── serializer.c    
├── examples/
│   └── main.c          
├── README.md

## Build and Run

The project can be built using GCC:

gcc src/serializer.c examples/main.c -Iinclude -o demo
./demo

The example application creates sample meter data, calls the serialization function, and prints the resulting JSON to the console.

## Example Output

[{"gatewayId":"gateway_1234","date":"1970-01-01","deviceType":"stromleser","interval_minutes":15,"total_readings":1,"values":{"device_count":1,"readings":[{"media":"water","meter":"waterstarm","deviceId":"stromleser_50898527","unit":"m3","data":[{"timestamp":"1970-01-01 00:00","meter_datetime":"1970-01-01 00:00","total_m3":107.752,"status":"OK"}]}]}}]

## Assumptions and Limitations

Buffer sizes are fixed and chosen conservatively for this example

No dynamic memory allocation is used

Input validation is minimal and assumes well-formed data

The implementation focuses only on serialization, not transport or storage

## Possible Extensions

If extended further, this library could:

Support multiple gateways in one output

Add compile-time configuration for buffer sizes

Integrate with UART, MQTT, or file systems

Include unit tests for different input scenarios

## Final Notes

This implementation focuses on embedded software fundamentals:

Clear data modeling

Safe memory usage

Simple and readable logic

Strict adherence to interface and format requirements

The code is intentionally kept small and understandable, similar to what would be expected in real embedded firmware projects.