#include "bimap.h"

#include <assert.h>
#include <deque>
#include <string>
#include <unordered_map>

struct BiMap::Impl {
    Impl() = default;
    std::deque<std::string> dict_strings;
    std::unordered_map<std::string_view, std::string_view> key_ref;
    std::unordered_map<std::string_view, std::string_view> value_ref;
};

BiMap::BiMap() : impl_(std::make_unique<Impl>()){};

BiMap::~BiMap() = default;

BiMap::BiMap(BiMap &&) noexcept = default;
BiMap &BiMap::operator=(BiMap &&) noexcept = default;

BiMap::BiMap(const BiMap &other)
    // Если other не пуст, копируем его поле impl_
    : impl_(other.impl_ ? std::make_unique<Impl>(*other.impl_) : nullptr) {
}

BiMap& BiMap::operator=(const BiMap& other) {
    if (this != std::addressof(other)) {
        BiMap::impl_ = other.impl_ ? std::make_unique<Impl>(*other.impl_) : nullptr;
    }
    return *this;
}

bool BiMap::Add(std::string_view key, std::string_view value) {
    if (auto key_it = BiMap::impl_->key_ref.find(key); key_it != BiMap::impl_->key_ref.end()) {
        return false;
    }
    if (auto val_it = BiMap::impl_->value_ref.find(value); val_it != BiMap::impl_->value_ref.end()) {
        return false;
    }
    BiMap::impl_->dict_strings.push_back({key.begin(), key.end()});
    std::string_view key_view = BiMap::impl_->dict_strings.back();
    BiMap::impl_->dict_strings.push_back({value.begin(), value.end()});
    std::string_view val_view = BiMap::impl_->dict_strings.back();
    BiMap::impl_->key_ref[key_view] = val_view;
    BiMap::impl_->value_ref[val_view] = key_view;
    return true;
}

std::optional<std::string_view> BiMap::FindKey(std::string_view key) const noexcept {
    auto key_pos = BiMap::impl_->value_ref.find(key);
    if (key_pos != BiMap::impl_->value_ref.end())
        return key_pos->second;
    return std::nullopt;
}

std::optional<std::string_view> BiMap::FindValue(std::string_view value) const noexcept {
    auto val_pos = BiMap::impl_->key_ref.find(value);
    if (val_pos != BiMap::impl_->key_ref.end())
        return val_pos->second;
    return std::nullopt;
}
