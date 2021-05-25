#include "entity/observer_subject.h"

namespace csci3081{
void ObserverSubject::AddObserver(const IEntityObserver& add) { observers_.insert((IEntityObserver*) &add);};
void ObserverSubject::RemoveObserver(const IEntityObserver& remove) {observers_.erase((IEntityObserver*) &remove);};
void ObserverSubject::notify(picojson::object& details, IEntity* entity){
    picojson::value value = JsonHelper::ConvertPicojsonObjectToValue(details); 
    for(auto observer : observers_){
        observer->OnEvent(value, *entity);
    }
}

picojson::object ObserverSubject::buildNotification(std::string notificationType) {
    picojson::object obj;
    JsonHelper::AddStringToJsonObject(obj, "type", "notify");
    JsonHelper::AddStringToJsonObject(obj, "value", notificationType);
    return obj;
}

picojson::object ObserverSubject::buildNotification(std::string notificationType, std::vector<std::vector<float>>& path) {
    picojson::object obj;

    JsonHelper::AddStringToJsonObject(obj, "type", "notify");
    JsonHelper::AddStringToJsonObject(obj, "value", notificationType);
    JsonHelper::AddStdVectorVectorFloatToJsonObject(obj, "path", path);
    return obj;
}

}