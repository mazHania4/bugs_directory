#include "Pair.h"

template<typename K, typename V>
Pair<K, V>::Pair(K newKey, V newValue) {
    key = newKey;
    value = newValue;
}

template<typename K, typename V>
K Pair<K, V>::getKey() {
    return key;
}

template<typename K, typename V>
V Pair<K, V>:: getValue() {
    return value;
}

template<typename K, typename V>
void Pair<K, V>:: setValue(V newValue) {
    value = newValue;
}

template<typename K, typename V>
void Pair<K, V>::setKey(K newKey) {
    key = newKey;
}
