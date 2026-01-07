#include "serializer.h"
#include <stdio.h>

int serialize_to_json(const GatewayData *g, char *out, size_t size)
{
    int written = 0;

    written += snprintf(out + written, size - written,
        "[{"
        "\"gatewayId\":\"%s\","
        "\"date\":\"%s\","
        "\"deviceType\":\"%s\","
        "\"interval_minutes\":%d,"
        "\"total_readings\":%d,"
        "\"values\":{"
        "\"device_count\":%d,"
        "\"readings\":[",
        g->gatewayId,
        g->date,
        g->deviceType,
        g->interval_minutes,
        g->total_readings,
        g->device_count
    );

    if (written >= size) return -1;

    for (int i = 0; i < g->device_count; i++) {
        DeviceReading *d = &g->readings[i];

        written += snprintf(out + written, size - written,
            "{"
            "\"media\":\"%s\","
            "\"meter\":\"%s\","
            "\"deviceId\":\"%s\","
            "\"unit\":\"%s\","
            "\"data\":[",
            d->media,
            d->meter,
            d->deviceId,
            d->unit
        );

        for (int j = 0; j < d->data_count; j++) {
            DataPoint *p = &d->data[j];

            written += snprintf(out + written, size - written,
                "{"
                "\"timestamp\":\"%s\","
                "\"meter_datetime\":\"%s\","
                "\"total_m3\":%.3f,"
                "\"status\":\"%s\""
                "}%s",
                p->timestamp,
                p->meter_datetime,
                p->total_m3,
                p->status,
                (j < d->data_count - 1) ? "," : ""
            );
        }

        written += snprintf(out + written, size - written,
            "]}"
            "%s",
            (i < g->device_count - 1) ? "," : ""
        );
    }

    written += snprintf(out + written, size - written,
        "]}}]"
    );

    return (written < size) ? written : -1;
}
