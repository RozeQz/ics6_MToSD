/*
MIT License

Copyright (c) 2019 МГТУ им. Н.Э. Баумана, кафедра ИУ-6, Михаил Фетисов,

Программа-заготовка для домашнего задания
*/

#ifndef HW_L3_DOMAIN_LAYER_H
#define HW_L3_DOMAIN_LAYER_H

#include "hw/l4_InfrastructureLayer.h"

const size_t MAX_NAME_LENGTH = 256;
const size_t MAX_LANGUAGE_LENGTH = 64;
const size_t MAX_DIFFICULTY = 10;
const size_t MIN_DURATION = 1;
const size_t MAX_DURATION = 1024;

class Subscriber
{
    std::string _email;

public:
    Subscriber() = delete;
    // Subscriber(const Subscriber &s) = delete;

    Subscriber &operator=(const Subscriber &s) = delete;

    Subscriber(const std::string email);

    const std::string getEmail() const;
};

class Subscribtion : public ICollectable
{
    uint32_t _id;
    std::string _name;
    std::string _language;
    uint8_t _difficulty;
    uint16_t _duration;
    uint32_t _cost;
    Subscriber _sub;
    bool _paid;

public:
    Subscribtion() = delete;
    // Subscribtion(const Subscribtion &p) = delete;

    Subscribtion &operator=(const Subscribtion &p) = delete;

    Subscribtion(uint32_t _id, const std::string &_name, const std::string &_language, uint8_t _difficulty, uint16_t _duration, uint32_t _cost, Subscriber _sub, bool paid);

    uint32_t getId() const;
    const std::string &getName() const;
    const std::string &getLanguage() const;
    uint8_t getDifficulty() const;
    uint16_t getDuration() const;
    uint32_t getCost() const;
    Subscriber getSub() const;
    bool isPaid() const;

    virtual bool write(std::ostream &os) override;
};

class ItemCollector : public ACollector
{
public:
    virtual std::shared_ptr<ICollectable> read(std::istream &is) override;
};

class Manager : public ItemCollector
{
private:
    std::vector<std::shared_ptr<Subscribtion>> _list_of_subs;

public:
    Manager(std::vector<std::shared_ptr<Subscribtion>> _list_of_subs);

    std::vector<std::shared_ptr<Subscribtion>> getUnpaidSubscribtions();
};

#endif // HW_L3_DOMAIN_LAYER_H
