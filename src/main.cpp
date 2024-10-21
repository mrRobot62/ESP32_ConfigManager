#include <Arduino.h>
#include "ConfigManager2.h"

ConfigManager configManager;

// Template-Funktion zur Ausgabe eines Arrays
template <typename T>
void printArray(const T* array, size_t size, String fmt = "%d, ") {
    Serial.println(">>> PrintArray()");
    for (size_t i = 0; i < size; i++) {
        Serial.printf(fmt.c_str(), array[i]); // Standardformatierung für int
    }
    Serial.println(); // Neue Zeile nach der Ausgabe
}

void printKVP(KeyValuePair &kvp) {
    switch (kvp.value.type) {
        case TYPE_INT:
            Serial.printf("NS: '%s', Key: '%s', ValueType: %d, Value: ",  kvp.nspace, kvp.key, kvp.value.type);
            Serial.print(kvp.value.i_val);
            break;
        case TYPE_DOUBLE:
            Serial.printf("NS: '%s', Key: '%s', ValueType: %d, Value: ",  kvp.nspace, kvp.key, kvp.value.type);
            Serial.print(kvp.value.d_val);
            break;
        case TYPE_STRING:
            Serial.printf("NS: '%s', Key: '%s', ValueType: %d, Value: ",  kvp.nspace, kvp.key, kvp.value.type);
            Serial.print(kvp.value.s_val);
            break;
        case TYPE_BLOB:
            configManager.printBlob(kvp.value);
            break;
    }
}

void setup() {
    Serial.begin(115200);
    delay(100);
    // Direkte Initialisierung für TYPE_INT

    configManager.initFlash();

    Serial.println("TEST : integer value write/read");
    KeyValuePair kvp = {
        "integerKey",                       // key
        "namespace1",                       // nspace
        {  .type = TYPE_INT, .i_val = 42 },  // value (int), Type (TYPE_INT)
    };
    configManager.setKeyValue(kvp);
    kvp.value.i_val = 0;
    Serial.println("   reset kvp.value");
    configManager.getKeyValue(kvp);

    Serial.println("TEST : double/float value write/read");
    kvp = {
        "floatKey",                       // key
        "namespace1",                       // nspace
        { .type = TYPE_DOUBLE, .d_val = 3.1451 },  // value (int), Type (TYPE_DOUBLE)
    };
    configManager.setKeyValue(kvp);
    kvp.value.d_val = 0.0;
    Serial.println("   reset kvp.value");
    configManager.getKeyValue(kvp);

    Serial.println("\nTEST : String value write/read");
    Value v;
    v.s_val = "Hello esp32 world";
    v.type = TYPE_STRING;
    // direkt Zuweiseung für Value ala {.s_val = "xxxxx"} funktioniert nicht
    kvp = {
        "stringKey",                      // key
        "namespace1",                     // nspace
        v                                 // value (int), Type (TYPE_STRING)
    };
    configManager.setKeyValue(kvp);
    kvp.value.d_val = 0.0;
    Serial.println("   reset kvp.value");
    configManager.getKeyValue(kvp);

    // ------- ARRAY persistieren und lesen ---------------
    Serial.println("\nTEST : BLOB value write/read (uint8_t array)");
    uint8_t pidR[] = {50,5,0};
    uint8_t result[3];
    uint8_t* buf;
    size_t bufLength;
    //memset(&v, 0, sizeof(Value));
    v.blob_val.elements = ARRAY_ELEMENTS(pidR);
    kvp = {
        "uint8Array", "namespace1", v
    };
    kvp.value = v;
    configManager.arrayToByteArray(
        pidR,                           // das Array was serialisiert werden soll
        sizeof(pidR),                   // Anzahl Bytes von pidR
        ARRAY_ELEMENTS(pidR),           // Anzahl der Elemente im pidR
        &kvp.value.blob_val.data,       // date werden hier als blob abgelegt
        &kvp.value.blob_val.length      // Anzahl Bytes des blobs
    );

    Serial.println(">>>> save");
    configManager.setKeyValue(kvp);
    kvp.value.d_val = 0.0;
    Serial.println("   reset kvp.value");
    configManager.getKeyValue(kvp);
    uint8_t result8[ARRAY_ELEMENTS(pidR)];
    configManager.byteArrayToArray(
        kvp.value.blob_val.data, 
        kvp.value.blob_val.length,
        &result8
    );
    printArray(result8, ARRAY_ELEMENTS(result8) );

    Serial.println("\nTEST : BLOB value write/read (uint16_t array)");
    uint16_t channels[] = {1000,1000,1000,1000,1500,1500,1500,1500};
    uint16_t result16[ARRAY_ELEMENTS(channels)];
    v.blob_val.elements = ARRAY_ELEMENTS(channels);

    kvp = {
        "uint16Array", "namespace1", v
    };
    kvp.value = v;
    configManager.arrayToByteArray(
        channels,                           // das Array was serialisiert werden soll
        sizeof(channels),                   // Anzahl Bytes von pidR
        ARRAY_ELEMENTS(channels),           // Anzahl der Elemente im pidR
        &kvp.value.blob_val.data,       // date werden hier als blob abgelegt
        &kvp.value.blob_val.length      // Anzahl Bytes des blobs
    );

    Serial.println(">>>> save");
    configManager.setKeyValue(kvp);
    kvp.value.d_val = 0.0;
    Serial.println("   reset kvp.value");
    configManager.getKeyValue(kvp);
    configManager.byteArrayToArray(
        kvp.value.blob_val.data, 
        kvp.value.blob_val.length,
        &result16
    );
    printArray(result16, ARRAY_ELEMENTS(result16) );


    Serial.println("\nTEST : BLOB value write/read (double array)");
    double doubles[] = {1.0, 1.1, 123.456, 3.1451235};
    double resultDbl[ARRAY_ELEMENTS(doubles)];
    v.blob_val.elements = ARRAY_ELEMENTS(doubles);

    kvp = {
        "doubleArray", "namespace2", v
    };
    kvp.value = v;
    configManager.arrayToByteArray(
        doubles,                           // das Array was serialisiert werden soll
        sizeof(doubles),                   // Anzahl Bytes von pidR
        ARRAY_ELEMENTS(doubles),           // Anzahl der Elemente im pidR
        &kvp.value.blob_val.data,       // date werden hier als blob abgelegt
        &kvp.value.blob_val.length      // Anzahl Bytes des blobs
    );

    Serial.println(">>>> save");
    configManager.setKeyValue(kvp);
    kvp.value.d_val = 0.0;
    Serial.println("   reset kvp.value");
    configManager.getKeyValue(kvp);
    configManager.byteArrayToArray(
        kvp.value.blob_val.data, 
        kvp.value.blob_val.length,
        &resultDbl
    );
    printArray(resultDbl, ARRAY_ELEMENTS(resultDbl), "%07.4f, ");

    Serial.println("\nTEST : getAllNamespaces()");
    size_t max_namespaces = 10;
    char* namespaces[max_namespaces];
    uint8_t count = configManager.getAllNamespaces(namespaces, max_namespaces);
    Serial.printf("MaxNamespaces found: %d \n", count);
    printArray(namespaces, count, "%s, ");

    int err = configManager.deleteAllNamespaces();
}

void loop() {

}