#include <stdio.h>
#include "serializer.h"

int main(void)
{
    GatewayData g = {
        .gatewayId = "gateway_1234",
        .date = "1970-01-01",
        .deviceType = "stromleser",
        .interval_minutes = 15,
        .total_readings = 1,
        .device_count = 1
    };

    DeviceReading *d = &g.readings[0];
    snprintf(d->media, sizeof(d->media), "water");
    snprintf(d->meter, sizeof(d->meter), "waterstarm");
    snprintf(d->deviceId, sizeof(d->deviceId), "stromleser_50898527");
    snprintf(d->unit, sizeof(d->unit), "m3");
    d->data_count = 1;

    DataPoint *p = &d->data[0];
    snprintf(p->timestamp, sizeof(p->timestamp), "1970-01-01 00:00");
    snprintf(p->meter_datetime, sizeof(p->meter_datetime), "1970-01-01 00:00");
    p->total_m3 = 107.752;
    snprintf(p->status, sizeof(p->status), "OK");

    char json[1024];

    int res = serialize_to_json(&g, json, sizeof(json));
    if (res < 0) {
        printf("Serialization failed (buffer too small)\n");
        return -1;
    }

    printf("%s\n", json);
    return 0;
}
