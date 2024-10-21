#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <nvs.h>
#include <nvs_flash.h>
#include <Arduino.h>
#include <String.h>

#define SERIALIZE_TO_STRING(dataString, array, size, type)  \
    do {                                                    \
        for (size_t i = 0; i < size; i++) {                 \
            dataString += (char)((type *)array)[i];         \
        }                                                   \
    } while (0)


// Originales Makro
#define TO_STRING(x) #x

// zerlegt zum Beispiel data.gimbal_min und gibt nur gimbal_min zurück
// oder wenn ein Pointer genutzt wird dann gibt data->gimbal_min ebenfalls nur gimbal_min zurück
#define EXTRACT_FIELD_NAME(field) (strrchr(#field, '.') ? strrchr(#field, '.') + 1 : (strrchr(#field, '-') ? strrchr(#field, '>') + 1 : #field))

//
// Kann anhang eines "Field_names" in der übergebenen Struktur das passende Attribut setzen
// Beispiel: SET_DATA_TO_STRUCT(&data, TData, gimbal_min, 1000)

// #define SET_DATA_TO_STRUCT(struct_ptr, struct_type, field_name, value) \
//     do { \
//         size_t offset = offsetof(struct_type, field_name); \
//         *(typeof(((struct_type *)0)->field_name) *)((char *)(struct_ptr) + offset) = value; \
//     } while(0)

// // Makro zur Deserialisierung eines Strings in ein Array
// #define DESERIALIZE_FROM_STRING(dataString, array, size, type)      \
//     do {                                                            \
//         String tempString = dataString;                             \
//         char *token = strtok((char *)tempString.c_str(), ",");      \
//         size_t index = 0;                                           \
//         while (token != nullptr && index < size) {                  \
//             ((type *)array)[index] = (type)atoi(token);             \
//             token = strtok(nullptr, ",");                           \
//             index++;                                                \
//         }                                                           \
//     } while (0)

typedef char* TYPE_CBLOB;

#define ARRAY_TO_BLOB(array, blob, size, type) \
    do { \
        size_t actual_size = (size) * sizeof(type); \
        blob = (TYPE_CBLOB)malloc((actual_size * 2) + 1); \
        for (size_t i = 0; i < actual_size; i++) { \
            sprintf(&blob[i * 2], "%02X", ((uint8_t*)array)[i]); \
        } \
        blob[actual_size * 2] = '\0'; \
    } while(0)

#define BLOB_TO_ARRAY(blob, array, size, type) \
    do { \
        size_t actual_size = (size) * sizeof(type); \
        for (size_t i = 0; i < actual_size; i++) { \
            sscanf(&blob[i * 2], "%2hhX", &((uint8_t*)array)[i]); \
        } \
    } while(0)

// Definiere ValueType enum
typedef enum {
    TYPE_INT,
    TYPE_DOUBLE,
    TYPE_STRING,
    TYPE_BLOB
} ValueType;

// Definiere eine Union, die verschiedene Datentypen aufnehmen kann
typedef struct {
    int i_val;
    double d_val;
    String s_val;
} Value;

// Definiere eine Struktur für Key/Value-Paare mit Namespace und flexiblem Wert
typedef struct {
    String key;
    String nspace;
    Value value;      // Struktur die einen bliebigen Wert beinhaltet
    ValueType type;   // Datentyp des wertes (TYPE_INT, TYPE_DOUBLE, TYPE_STRING, TYPE_BLOB)
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
    int getAllNamespaces(char namespaces[][16], size_t max_namespaces);

private:
    void read_value(nvs_handle_t handle, KeyValuePair& kv);
};

#endif // CONFIG_MANAGER_H
