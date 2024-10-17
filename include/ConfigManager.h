#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <nvs.h>
#include <nvs_flash.h>
#include <Arduino.h>

// Definiere ValueType enum
typedef enum {
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_STRING
} ValueType;

// Definiere eine Union, die verschiedene Datentypen aufnehmen kann
typedef union {
    int i_val;
    double d_val;
    char s_val[50];
} Value;

// Definiere eine Struktur für Key/Value-Paare mit Namespace und flexiblem Wert
typedef struct {
    char key[50];
    char nspace[10];  // Der Namespace mit einer Länge von maximal 10 Bytes
    Value value;      // Union für den Wert
    ValueType type;   // Typ des Wertes
} KeyValuePair;

class ConfigManager {
public:
    ConfigManager();  // Konstruktor

    void nvs_init();  // Initialisiert NVS

    bool read_namespace(const char* namespace_name, KeyValuePair* kv_array, size_t* count);
    bool write(const char* namespace_name, const char* key, Value value, ValueType type, bool overwrite = true);
    bool delete_namespace(const char* namespace_name);
    bool delete_all_namespaces();
    bool read_key_value(const char* namespace_name, const char* key, KeyValuePair* kv);

private:
    void read_value(nvs_handle_t handle, KeyValuePair& kv);
};

#endif // CONFIG_MANAGER_H
