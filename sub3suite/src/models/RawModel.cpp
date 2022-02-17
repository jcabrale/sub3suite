#include "RawModel.h"


s3s_struct::RAW raw_to_struct(s3s_item::RAW *item){
    s3s_struct::RAW raw;
    raw.module = item->module;
    raw.target = item->target;
    raw.results = item->json;
    return raw;
}

QJsonObject raw_to_json(s3s_item::RAW *item){
    QJsonObject raw;
    raw.insert("raw", item->text());
    raw.insert("target", item->target);
    raw.insert("module", item->module);
    raw.insert("json", QString::fromUtf8(item->json));
    return raw;
}

void json_to_raw(const QJsonObject &raw, s3s_item::RAW *item){
    item->setText(raw.value("raw").toString());
    item->target = raw.value("target").toString();
    item->module = raw.value("module").toString();
    item->json = raw.value("json").toString().toUtf8();
    item->setValues(item->json);
}

QByteArray item_to_json(QStandardItem *item){
    QJsonObject json;

    if(item->whatsThis() == JSON_OBJECT)
        json.insert(item->text(), setObj(item));

    if(item->whatsThis() == JSON_ARRAY)
        json.insert(item->text(), setArr(item));

    QJsonDocument document;
    document.setObject(json);
    return document.toJson();
}

QJsonObject setObj(QStandardItem *item){
    QJsonObject obj;
    for(int i = 0; i < item->rowCount(); i++)
    {
        QStandardItem *child_item = item->child(i, 0);

        if(child_item->whatsThis() == JSON_OBJECT){
            obj.insert(child_item->text(), setObj(child_item));
            continue;
        }
        if(child_item->whatsThis() == JSON_ARRAY){
            obj.insert(child_item->text(), setArr(child_item));
            continue;
        }
        obj.insert(child_item->text(), item->child(i, 1)->text());
    }
    return obj;
}

QJsonArray setArr(QStandardItem *item){
    QJsonArray arr;
    for(int i = 0; i < item->rowCount(); i++)
    {
        QStandardItem *child_item = item->child(i, 0);

        if(child_item->whatsThis() == JSON_OBJECT){
            arr.append(setObj(child_item));
            continue;
        }
        if(child_item->whatsThis() == JSON_ARRAY){
            arr.append(setArr(child_item));
            continue;
        }
        arr.append(item->child(i, 1)->text());
    }
    return arr;
}
