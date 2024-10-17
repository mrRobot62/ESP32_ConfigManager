#include <Arduino.h>
#include "ConfigManager.h"

// Beispiel zur Nutzung der Klasse
ConfigManager configManager;

void setup() {
    Serial.begin(115200);

    // Beispiel zum Schreiben eines neuen Wertes in einen Namespace
    Value val1;
    Value val1b;
    val1.i_val = 42;
    val1b.i_val = 4711;
    configManager.write("example_ns", "int_key", val1, TYPE_INT);
    Serial.printf("Write Key: '%s' mit Value : %d\n", "int_key", val1.i_val );

    configManager.write("example_ns_two", "int_key", val1b, TYPE_INT);

    // Überschreiben der 42 mit 43
    val1.i_val = 43;
    Serial.printf("Überschreiben Key: '%s' mit Value : %d\n", "int_key", val1.i_val );
    configManager.write("example_ns", "int_key", val1, TYPE_INT);
    KeyValuePair kv;
    strncpy( kv.value.s_val, "", sizeof( kv.value.s_val));
    if (configManager.read_key_value("example_ns", "int_key", &kv)) {
        Serial.print(">>> Key: '");
        Serial.print(kv.key);
        Serial.print("', Value: ");
        if (kv.type == TYPE_INT) {
            Serial.println(kv.value.i_val);
        } else if (kv.type == TYPE_DOUBLE) {
            Serial.println(kv.value.d_val);
        } else if (kv.type == TYPE_STRING) {
            Serial.println(kv.value.s_val);
        }
    }
    // Protected Key
    val1.i_val = 99;
    Serial.printf("Protected versuche zu überschreiben Key: '%s' mit Value : %d\n", "int_key", val1.i_val );
    configManager.write("example_ns", "int_key", val1, TYPE_INT, false);
    kv.value.i_val = 0;
    kv.value.d_val = 0.0;
    strncpy( kv.value.s_val, "", sizeof( kv.value.s_val));
    if (configManager.read_key_value("example_ns", "int_key", &kv)) {
        Serial.print(">>> Key: '");
        Serial.print(kv.key);
        Serial.print("', Value: ");
        if (kv.type == TYPE_INT) {
            Serial.println(kv.value.i_val);
        } else if (kv.type == TYPE_DOUBLE) {
            Serial.println(kv.value.d_val);
        } else if (kv.type == TYPE_STRING) {
            Serial.println(kv.value.s_val);
        }
    }
    Value val2;
    Value val2b;
    val2.d_val = 3.1415;
    val2b.d_val = 11.2345;
    configManager.write("example_ns", "double_key", val2, TYPE_DOUBLE);
    configManager.write("example_ns_two", "double_key", val2b, TYPE_DOUBLE);

    Value val3;
    strncpy(val3.s_val, "Hello, ESP32!", sizeof(val3.s_val));
    configManager.write("example_ns", "string_key", val3, TYPE_STRING);

    // Beispiel zum Lesen eines einzelnen Wertes
    kv.value.i_val = 0;
    kv.value.d_val = 0.0;
    strncpy( kv.value.s_val, "", sizeof( kv.value.s_val));
    if (configManager.read_key_value("example_ns", "int_key", &kv)) {
        Serial.print("Key: ");
        Serial.print(kv.key);
        Serial.print(", Value: ");
        if (kv.type == TYPE_INT) {
            Serial.println(kv.value.i_val);
        } else if (kv.type == TYPE_DOUBLE) {
            Serial.println(kv.value.d_val);
        } else if (kv.type == TYPE_STRING) {
            Serial.println(kv.value.s_val);
        }
    }

    // Beispiel zum Lesen aller Key/Value-Paare eines Namespace
    KeyValuePair kv_array[10];
    size_t count = 10;

    if (configManager.read_namespace("example_ns", kv_array, &count)) {
      Serial.println("------ example_ns -------------");
        for (size_t i = 0; i < count; i++) {
            Serial.print("Key: ");
            Serial.print(kv_array[i].key);
            Serial.print(", Value: ");
            if (kv_array[i].type == TYPE_INT) {
                Serial.println(kv_array[i].value.i_val);
            } else if (kv_array[i].type == TYPE_DOUBLE) {
                Serial.println(kv_array[i].value.d_val);
            } else if (kv_array[i].type == TYPE_STRING) {
                Serial.println(kv_array[i].value.s_val);
            }
        }
    }

    if (configManager.read_namespace("example_ns_two", kv_array, &count)) {
      Serial.println("------ example_ns_two -------------");
        for (size_t i = 0; i < count; i++) {
            Serial.print("Key: ");
            Serial.print(kv_array[i].key);
            Serial.print(", Value: ");
            if (kv_array[i].type == TYPE_INT) {
                Serial.println(kv_array[i].value.i_val);
            } else if (kv_array[i].type == TYPE_DOUBLE) {
                Serial.println(kv_array[i].value.d_val);
            } else if (kv_array[i].type == TYPE_STRING) {
                Serial.println(kv_array[i].value.s_val);
            }
        }
    }

    // Beispiel zum Löschen eines Namespaces
    configManager.delete_namespace("example_ns");
    configManager.delete_namespace("example_ns_two");
    
}

void loop() {
    // nichts zu tun im Loop
}