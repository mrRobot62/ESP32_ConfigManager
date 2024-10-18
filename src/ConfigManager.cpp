#include "ConfigManager.h"

// Konstruktor: Initialisiert NVS
ConfigManager::ConfigManager() {
    nvs_init();
}

// Initialisiert NVS (Non-Volatile Storage)
void ConfigManager::nvs_init() {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
}

// Liest alle Key/Value Paare in einem Namespace
bool ConfigManager::read_namespace(const char* namespace_name, KeyValuePair* kv_array, size_t* count) {
    nvs_handle_t nvs_handle;
    esp_err_t err = nvs_open(namespace_name, NVS_READONLY, &nvs_handle);
    if (err != ESP_OK) {
        Serial.println("Error opening NVS handle!");
        return false;
    }

    nvs_iterator_t it = nvs_entry_find(NVS_DEFAULT_PART_NAME, namespace_name, NVS_TYPE_ANY);
    size_t i = 0;
    while (it != nullptr && i < *count) {
        nvs_entry_info_t info;
        nvs_entry_info(it, &info);

        strncpy(kv_array[i].key, info.key, sizeof(kv_array[i].key));
        strncpy(kv_array[i].nspace, namespace_name, sizeof(kv_array[i].nspace));
        
        read_value(nvs_handle, kv_array[i]);  // Hilfsfunktion, um den Wert auszulesen

        it = nvs_entry_next(it);
        i++;
    }
    *count = i;
    nvs_close(nvs_handle);
    return true;
}

// Schreibt ein Key/Value Paar in einen Namespace, mit optionaler Überschreibungsverhinderung
bool ConfigManager::write(const char* namespace_name, const char* key, Value value, ValueType type, bool overwrite) {
    nvs_handle_t nvs_handle;
    esp_err_t err = nvs_open(namespace_name, NVS_READWRITE, &nvs_handle);
    if (err != ESP_OK) {
        Serial.println("Error opening NVS handle!");
        return false;
    }

    // Überprüfen, ob der Schlüssel bereits existiert, wenn overwrite = false
    if (!overwrite) {
        KeyValuePair kv;
        if (read_key_value(namespace_name, key, &kv)) {
            Serial.println("Key already exists, skipping write.");
            nvs_close(nvs_handle);
            return false;  // Schlüssel existiert, nicht überschreiben
        }
        Serial.println("not protected")  ;  
    }
    if (type == TYPE_INT) {
        err = nvs_set_i32(nvs_handle, key, value.i_val);
    } else if (type == TYPE_DOUBLE) {
        err = nvs_set_blob(nvs_handle, key, &value.d_val, sizeof(double));
    } else if (type == TYPE_STRING) {
        err = nvs_set_str(nvs_handle, key, value.s_val);
    }

    if (err != ESP_OK) {
        Serial.println("Failed to write key/value pair!");
        nvs_close(nvs_handle);
        return false;
    }

    err = nvs_commit(nvs_handle);
    if (err != ESP_OK) {
        Serial.println("Commit failed!");
    } else {
        Serial.println("Value successfully written and committed.");
    }
    nvs_close(nvs_handle);
    return err == ESP_OK;
}

// Löscht einen gesamten Namespace
bool ConfigManager::delete_namespace(const char* namespace_name) {
    esp_err_t err = nvs_flash_erase_partition(namespace_name);
    return err == ESP_OK;
}

// Löscht alle Namespaces im Flash
bool ConfigManager::delete_all_namespaces() {
    esp_err_t err = nvs_flash_erase();
    return err == ESP_OK;
}

// Liest ein einzelnes Key/Value Paar
bool ConfigManager::read_key_value(const char* namespace_name, const char* key, KeyValuePair* kv) {
    nvs_handle_t nvs_handle;
    esp_err_t err = nvs_open(namespace_name, NVS_READONLY, &nvs_handle);
    if (err != ESP_OK) {
        Serial.println("Error opening NVS handle!");
        return false;
    }

    strncpy(kv->key, key, sizeof(kv->key));
    strncpy(kv->nspace, namespace_name, sizeof(kv->nspace));

    read_value(nvs_handle, *kv);

    nvs_close(nvs_handle);
    return true;
}

void ConfigManager::read_value(nvs_handle_t handle, KeyValuePair& kv) {
    size_t required_size = 0;
    size_t sizeDouble = sizeof(double);
    esp_err_t err = nvs_get_str(handle, kv.key, nullptr, &required_size);
    if (err == ESP_OK) {
        kv.type = TYPE_STRING;
        nvs_get_str(handle, kv.key, kv.value.s_val, &required_size);
        Serial.println("String value successfully read.");
    } else if (nvs_get_i32(handle, kv.key, &kv.value.i_val) == ESP_OK) {
        kv.type = TYPE_INT;
        Serial.println("Integer value successfully read.");
    } else if (nvs_get_blob(handle, kv.key, &kv.value.d_val, &sizeDouble) == ESP_OK) {
        kv.type = TYPE_DOUBLE;
        Serial.println("Double value successfully read.");
    } else {
        Serial.print("Failed to read key: ");
        Serial.println(kv.key);
        Serial.print("Error code: ");
        Serial.println(err);  // Protokolliert den Fehlercode
    }
}

int ConfigManager::getAllNamespaces(char namespaces[][16], size_t max_namespaces) {
    size_t namespace_count = 0;  // Anzahl der gefundenen Namespaces

    nvs_iterator_t it = nvs_entry_find(NVS_DEFAULT_PART_NAME, nullptr, NVS_TYPE_ANY);
    while (it != nullptr && namespace_count < max_namespaces) {
        nvs_entry_info_t info;
        nvs_entry_info(it, &info);

        // Überprüfen, ob der Namespace bereits in der Liste ist
        bool found = false;
        for (size_t i = 0; i < namespace_count; ++i) {
            if (strncmp(namespaces[i], info.namespace_name, 16) == 0) {
                found = true;
                break;
            }
        }

        // Wenn der Namespace noch nicht in der Liste ist, hinzufügen
        if (!found) {
            strncpy(namespaces[namespace_count], info.namespace_name, 16);
            namespace_count++;
        }

        it = nvs_entry_next(it);
    }

    return namespace_count;  // Rückgabe der Anzahl der gefundenen Namespaces
}
