#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <stddef.h>

#define MAX_DEVICES 5
#define MAX_DATAPOINTS 5

typedef struct {
    char timestamp[20];
    char meter_datetime[20];
    float total_m3;
    char status[10];
} DataPoint;

typedef struct {
    char media[10];
    char meter[20];
    char deviceId[30];
    char unit[10];
    int data_count;
    DataPoint data[MAX_DATAPOINTS];
} DeviceReading;

typedef struct {
    char gatewayId[20];
    char date[11];
    char deviceType[20];
    int interval_minutes;
    int total_readings;
    int device_count;
    DeviceReading readings[MAX_DEVICES];
} GatewayData;

int serialize_to_json(
    const GatewayData *input,
    char *output,
    size_t output_size
);

#endif