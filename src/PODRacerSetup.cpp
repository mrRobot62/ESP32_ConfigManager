#include "PODRacerSetup.h"


PODRacerSetup::PODRacerSetup(ConfigManager* configManager) {
    this->configManager = configManager;


}

//------------------------------------------------------------------------------
// Default setup for TDataRC, receiver configuration
//  channels do not have default values
//------------------------------------------------------------------------------
void PODRacerSetup::setDefaultValues(const char* namespace_name, TDataRC* data) {
    const char *key = EXTRACT_FIELD_NAME(rcDataNS.gimbal_min);

    // Value value;
    // value.i_val = data->gimbal_min;
    // configManager->write(namespace_name, EXTRACT_FIELD_NAME(data->gimbal_min), value, TYPE_INT);
    
    // value.i_val = data->gimbal_max;
    // configManager->write(namespace_name, EXTRACT_FIELD_NAME(data->gimbal_max),value, TYPE_INT);
    
    // value.i_val = data->gimbal_mid; 
    // configManager->write(namespace_name, EXTRACT_FIELD_NAME(data->gimbal_mid), value, TYPE_INT);
}

//------------------------------------------------------------------------------
// Default setup for TDataRC, surface configuration
//
//------------------------------------------------------------------------------
void PODRacerSetup::setDefaultValues(const char* namespace_name, TDataOFlow* data) {
    Value value;

    // // ein Array wird als BLOB gespeichert
    // // size kann für alle pid und bias verwendet werden
    // size = sizeof(data->pidPGain) / sizeof(data->pidPGain[0]);
    // ARRAY_TO_BLOB(data->pidRGain, blob, size, uint8_t);
    // value.s_val = blob;
    // configManager->write(namespace_name, EXTRACT_FIELD_NAME(data->pidRGain), value, TYPE_BLOB);
    // ARRAY_TO_BLOB(data->pidPGain, blob, size, uint8_t);
    // value.s_val = blob;
    // configManager->write(namespace_name, EXTRACT_FIELD_NAME(data->pidPGain), value, TYPE_BLOB);
    // ARRAY_TO_BLOB(data->pidYGain, blob, size, uint8_t);
    // value.s_val = blob;
    // configManager->write(namespace_name, EXTRACT_FIELD_NAME(data->pidYGain), value, TYPE_BLOB);

    // // ein Array wird als BLOB gespeichert
    // ARRAY_TO_BLOB(data->biasRPY, blob, size, uint8_t);
    // value.s_val = blob;
    // configManager->write(namespace_name, EXTRACT_FIELD_NAME(data->biasRPY), value, TYPE_BLOB);

    // // ein Array wird als BLOB gespeichert
    // ARRAY_TO_BLOB(data->setPointSlipRP, blob, size, uint8_t);
    // value.s_val = blob;
    // configManager->write(namespace_name, EXTRACT_FIELD_NAME(data->setPointSlipRP), value, TYPE_BLOB);
}


//------------------------------------------------------------------------------
// Default setup for TDataSDist - SurfaceTask, surface configuration
//
//------------------------------------------------------------------------------
void PODRacerSetup::setDefaultValues(const char* namespace_name, TDataSurface* data) {
    // Value value;
    // value.i_val = data->pinTOF;
    // configManager->write(namespace_name, EXTRACT_FIELD_NAME(data->pinTOF), value, TYPE_INT);
    // value.i_val = data->pinRXLidar;
    // configManager->write(namespace_name, EXTRACT_FIELD_NAME(data->pinRXLidar), value, TYPE_INT);
    // value.i_val = data->pinTXLidar;
    // configManager->write(namespace_name, EXTRACT_FIELD_NAME(data->pinTXLidar), value, TYPE_INT);

    // // ein Array wird als BLOB gespeichert
    // size = sizeof(data->pidTOF) / sizeof(data->pidTOF[0]);
    // ARRAY_TO_BLOB(data->pidTOF, blob, size, uint8_t);
    // value.s_val = blob;
    // configManager->write(namespace_name, EXTRACT_FIELD_NAME(data->pidTOF), value, TYPE_BLOB);

    // size = sizeof(data->pidLIDAR) / sizeof(data->pidLIDAR[0]);
    // ARRAY_TO_BLOB(data->pidLIDAR, blob, size, uint8_t);
    // value.s_val = blob;
    // configManager->write(namespace_name, EXTRACT_FIELD_NAME(data->pidLIDAR), value, TYPE_BLOB);

    // value.i_val = data->minHoverHeight;
    // configManager->write(namespace_name, EXTRACT_FIELD_NAME(data->minHoverHeight), value, TYPE_INT);
    // value.i_val = data->maxHoverHeight;
    // configManager->write(namespace_name, EXTRACT_FIELD_NAME(data->maxHoverHeight), value, TYPE_INT);
    // value.i_val = data->minHeight;
    // configManager->write(namespace_name, EXTRACT_FIELD_NAME(data->minHeight), value, TYPE_INT);
    // value.i_val = data->maxHeight;
    // configManager->write(namespace_name, EXTRACT_FIELD_NAME(data->maxHeight), value, TYPE_INT);

    // value.i_val = data->sensorConditionMin;
    // configManager->write(namespace_name, EXTRACT_FIELD_NAME(data->sensorConditionMin), value, TYPE_INT);
    // value.i_val = data->sensorConditionMax;
    // configManager->write(namespace_name, EXTRACT_FIELD_NAME(data->sensorConditionMax), value, TYPE_INT);

    // value.i_val = data->pidOutputError;
    // configManager->write(namespace_name, EXTRACT_FIELD_NAME(data->pidOutputError), value, TYPE_INT);

    // value.i_val = data->thresholdRangeMM;
    // configManager->write(namespace_name, EXTRACT_FIELD_NAME(data->thresholdRangeMM), value, TYPE_INT);
    // value.i_val = data->continousScanRate;
    // configManager->write(namespace_name, EXTRACT_FIELD_NAME(data->pinTOF), value, TYPE_INT);

    // value.i_val = data->bias;
    // configManager->write(namespace_name, EXTRACT_FIELD_NAME(data->bias), value, TYPE_INT);

}


// readValuesForTask für dataRC Task
void PODRacerSetup::readValuesForTask(const char* namespace_name, TDataRC* data) {
    // KeyValuePair kv;
    // configManager->read_key_value(namespace_name, TO_STRING(data->gimbal_min), &kv);
    // data->gimbal_min = kv.value.i_val;

    // configManager->read_key_value(namespace_name, TO_STRING(data->gimbal_max), &kv);
    // data->gimbal_max = kv.value.i_val;

    // configManager->read_key_value(namespace_name, TO_STRING(data->gimbal_center),&kv);
    // data->gimbal_center = kv.value.i_val;

    // // channels ist uint16_t[16]-array und kann so gelesen
    // configManager->read_key_value(namespace_name, TO_STRING(data->channels), &kv);
    // memcpy(data->channels, kv.value.s_val.c_str(), sizeof(data->channels));  // Kopiere die Daten zurück in das uint16_t-Array

}


// readValuesForTask für dataOpticalFlow Task
void PODRacerSetup::readValuesForTask(const char* namespace_name, TDataOFlow* data) {
    // configManager->read_key_value(namespace_name, TO_STRING(opticalFlowData->pidRGain), { .s_val = (char*)opticalFlowData->pidRGain });
    // configManager->read_key_value(namespace_name, TO_STRING(opticalFlowData->pidPGain), { .s_val = (char*)opticalFlowData->pidPGain });
    // configManager->read_key_value(namespace_name, TO_STRING(opticalFlowData->pidYGain), { .s_val = (char*)opticalFlowData->pidYGain });
    // configManager->read_key_value(namespace_name, TO_STRING(opticalFlowData->biasRPY), { .s_val = (char*)opticalFlowData->biasRPY });
    // configManager->read_key_value(namespace_name, TO_STRING(opticalFlowData->setPointSlipRP), { .s_val = (char*)opticalFlowData->setPointSlipRP });
    KeyValuePair kv;
    // dataOpticalFlow besteht ausschließlich aus uint8_t arrays

    // configManager->read_key_value(namespace_name, TO_STRING(data->pidRGain), &kv);
    // memcpy(data->pidRGain, kv.value.s_val.c_str(), sizeof(data->pidRGain));  // uint8_t[3]

    // configManager->read_key_value(namespace_name, TO_STRING(data->pidPGain), &kv);
    // memcpy(data->pidPGain, kv.value.s_val.c_str(), sizeof(data->pidPGain));  // uint8_t[3]

    // configManager->read_key_value(namespace_name, TO_STRING(data->pidYGain), &kv);
    // memcpy(data->pidYGain, kv.value.s_val.c_str(), sizeof(data->pidYGain));  // uint8_t[3]

    // configManager->read_key_value(namespace_name, TO_STRING(data->biasRPY), &kv);
    // memcpy(data->biasRPY, kv.value.s_val.c_str(), sizeof(data->biasRPY));  // uint8_t[3]

    // configManager->read_key_value(namespace_name, TO_STRING(data->setPointSlipRP), &kv);
    // memcpy(data->setPointSlipRP, kv.value.s_val.c_str(), sizeof(data->setPointSlipRP));  // uint16_t[2]

}
