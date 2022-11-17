#ifndef UNITEMP_OneWire
#define UNITEMP_OneWire

#include "../unitemp.h"

//Коды семейства устройств
typedef enum DallasFamilyCode {
    FC_DS18S20 = 0x10,
    FC_DS1822 = 0x22,
    FC_DS18B20 = 0x28,
} DallasFamilyCode;

//Режим питания датчка
typedef enum PowerMode {
    PWR_PASSIVE, //Питание от линии данных
    PWR_ACTIVE //Питание от источника питания
} PowerMode;

typedef struct {
    //Порт подключения датчика
    const GPIO* gpio;
    //Количество устройств на шине
    //Обновляется при ручном добавлении датчика на эту шину
    int8_t device_count;
    //Режим питания датчиков на шине
    PowerMode powerMode;
} OneWireBus;

typedef struct OneWireSensor {
    //Указатель на шину OneWire
    OneWireBus* bus;
    //Текущий адрес устройства на шине OneWire
    uint8_t deviceID[8];
    //Код семейства устройств
    DallasFamilyCode familyCode;

} OneWireSensor;

/**
 * @brief Выделение памяти для датчика на шине OneWire
 *
 * @param sensor Указатель на датчик
 * @param st Тип датчика
 * @return Истина если всё ок
 */
bool unitemp_OneWire_sensor_alloc(Sensor* sensor, uint8_t* anotherValues);

/**
 * @brief Высвобождение памяти инстанса датчика
 * 
 * @param sensor Указатель на датчик
 */
bool unitemp_OneWire_sensor_free(Sensor* sensor);

/**
 * @brief Инициализации датчика на шине One Wire
 *
 * @param sensor Указатель на датчик (тип Sensor)
 * @return Истина если инициализация упспешная
 */
bool unitemp_OneWire_sensor_init(Sensor* sensor);

/**
 * @brief Деинициализация датчика
 *
 * @param sensor Указатель на датчик (тип Sensor)
 */
bool unitemp_OneWire_sensor_deinit(Sensor* sensor);

/**
 * @brief Обновить значение с датчка
 * 
 * @param sensor Указатель на датчик (тип Sensor)
 * @return Статус обновления
 */
UnitempStatus unitemp_OneWire_sensor_update(Sensor* sensor);

/**
 * @brief Запуск общения с датчиками на шине one wire
 * 
 * @param bus Указатель на шину 
 * @return Истина если хотя бы одно устройство отозвалось
 */
bool unitemp_onewire_bus_start(OneWireBus* bus);

/**
 * @brief Выделение памяти для шины one wire и её инициализация
 * 
 * @param gpio Порт на котором необходимо создать шину
 * @return При успехе возвращает указатель на шину one wire
 */
OneWireBus* uintemp_onewire_bus_alloc(const GPIO* gpio);

/**
 * @brief Деинициализация шины one wire
 * 
 * @param bus Указатель на шину
 * @return Истина если шина была деинициализирована, ложь если на шине остались устройства
 */
bool unitemp_onewire_bus_deinit(OneWireBus* bus);

/**
 * @brief Инициализация шины one wire
 * 
 * @param bus Указатель на шину
 * @return Истина если инициализация успешна
 */
bool unitemp_onewire_bus_init(OneWireBus* bus);

/**
 * @brief Инициализация процесса поиска адресов на шине one wire
 */
void unitemp_onewire_enum_init(void);

/**
 * @brief Перечисляет устройства на шине one wire и получает очередной адрес
 * 
 * @param instance 
 * @return Возвращает указатель на буфер, содержащий восьмибайтовое значение адреса, либо NULL, если поиск завешён
 */
uint8_t* unitemp_onewire_enum_next(OneWireBus* bus);

extern const SensorType DS18x2x;
#endif