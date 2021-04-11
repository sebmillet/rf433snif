// rf433snif.ino

// Sébastien Millet, May 2019, March 2020, March 2021

// Raw recording and display of RF433 status switch timings.

//
// Schematic:
//   RF433 RECEIVER plugged on D2
//

#define PIN_RFINPUT 2

#include <Arduino.h>

#define CONTINUOUS_RECORD 0

// Below: IDS_ stands for "IDentify Signal"
//        _d stands for "duration" (between a transition from low to high or
//        high to low).
// Durations are in microseconds.

    // Minimum initial sequence duration to start identifying a signal
#define IDS_MIN_INITSEQ 4000
    // Maximum value of max_d / min_d, expressed as a power of 2.
    // max_d is the maximum duration seen so far, min_d the minimum. 'Duration'
    // means the duration between two transitions (signal going low to high or
    // high to low).
    // That means, during the first IDS_BE_STRICT_DURING_FIRST_N transitions,
    // this inequality must be verified:
    //   (max_d / min_d) < (2 ^ IS_MAX_SCALE)
#define IDS_MAX_SCALE 5
    // Minimum transition duration
#define IDS_D_MIN 64
    // Check signal consistency during the first IDS_BE_STRICT_DURING_FIRST_N
    // transitions. After that number, keep recording no matter the signal.
    // In a tri-coded signal ('low-low-high' versus 'low-high-high'), 20
    // transitions make 10 bits (if Manchester-coded it is variable...)
#define IDS_BE_STRICT_DURING_FIRST_N 20

uint16_t timings[500];
unsigned long start_t;
unsigned long end_t = 0;
unsigned long initseq_d;

    // Leave it to 2 unless you know what you are doing.
    // micros() counter produces multiple of 4, therefore we can divide times by
    // 4 without loosing accuracy, and this allows us to store bigger values.
#define SCALE_FACTOR         2
#define MAX_DURATION (50000 << SCALE_FACTOR)

// Manage printf-like output to Serial

#include <stdarg.h>

char serial_printf_buffer[80];
void serial_printf(const char* msg, ...)
     __attribute__((format(printf, 1, 2)));

    // NOTE
    //   Assume Serial has been initialized (Serial.begin(...))
void serial_printf(const char* msg, ...) {
    va_list args;

    va_start(args, msg);

    vsnprintf(serial_printf_buffer, sizeof(serial_printf_buffer), msg, args);
    va_end(args);
    Serial.print(serial_printf_buffer);
}

void setup() {
    pinMode(PIN_RFINPUT, INPUT);
    Serial.begin(115200);
}

void loop() {
    serial_printf("Waiting for signal...\n");

    bool recording = 0;
    unsigned int timing_pos;
    unsigned long d_min;
    unsigned long d_max;
    int val;
    unsigned long previous_loop_d = 0;
    while (1) {
        if (!recording) {
            initseq_d = previous_loop_d;
            if (!initseq_d) {
                unsigned long t0 = micros();
                while((initseq_d = (micros() - t0)) < MAX_DURATION
                      && digitalRead(PIN_RFINPUT) == LOW)
                    ;
            }
            if (initseq_d >= IDS_MIN_INITSEQ || CONTINUOUS_RECORD) {
                timing_pos = 0;
                val = HIGH;
                start_t = micros();
                d_min = 0;
                d_max = 0;
                recording = 1;
            }
            previous_loop_d = 0;
            continue;
        }

        unsigned long d;
        unsigned long last_t = micros();
        while ((d = (micros() - last_t)) < MAX_DURATION
               && digitalRead(PIN_RFINPUT) == val)
            ;

        if (!d_min)
            d_min = d;
        else if (d < d_min)
            d_min = d;

        if (d > d_max)
            d_max = d;

        if (timing_pos < IDS_BE_STRICT_DURING_FIRST_N && !CONTINUOUS_RECORD) {
            if ((d_min << IDS_MAX_SCALE) < d_max || d < IDS_D_MIN) {

                    // If ever we come upon a LOW value that has proper
                    // duration, maybe it was the initseq of a signal just
                    // starting.
                    // Should that be the case, we don't want to discard it
                    //   => it'll be analyzed during next loop.
                previous_loop_d = (val == LOW ? d : 0);

                recording = 0;
                continue;
            }
        }

        timings[timing_pos++] = (d >> SCALE_FACTOR);

        if (timing_pos >= sizeof(timings) / sizeof(*timings))
            break;

        val = (val == LOW ? HIGH : LOW);
    }

    unsigned long last_end_t = end_t;
    end_t = micros();
    unsigned long signal_d = end_t - start_t;

    if (last_end_t)
        serial_printf("^\n|---> < %lu us > elapsed without recording\nv\n",
                      start_t - last_end_t);

    serial_printf("Signal duration: %lu us\n", signal_d);
    serial_printf("  N  %6s,%6s\n", "LOW", "HIGH");
    serial_printf("-----BEGIN RF433 LOW HIGH SEQUENCE-----\n");
    serial_printf("     %6s,%6lu\n", "", initseq_d);

    for(unsigned int i = 0; i + 1 < timing_pos; i += 2) {
        serial_printf("%03i  %6lu,%6lu\n", i >> 1,
                      (unsigned long)timings[i] << SCALE_FACTOR,
                      (unsigned long)timings[i + 1] << SCALE_FACTOR);
    }
    serial_printf("-----END RF433 LOW HIGH SEQUENCE-----\n");

}

// vim: ts=4:sw=4:tw=80:et
