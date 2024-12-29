   template <typename... Args>
    iterator Emplace(const_iterator pos, Args &&...args) {
        assert(pos >= begin() && pos <= end());
    iterator result = nullptr;
    size_t shift = pos - begin();
    if (size_ == Capacity()) {
        RawMemory<T> new_data(size_ == 0 ? 1 : size_ * 2);
        result = new (new_data + shift) T(std::forward<Args>(args)...);
        if constexpr (std::is_nothrow_move_constructible_v<T> || !std::is_copy_constructible_v<T>) {
            std::uninitialized_move_n(begin(), shift, new_data.GetAddress());
            std::uninitialized_move_n(begin() + shift, size_ - shift, new_data.GetAddress() + shift + 1);
        }
        else {
            try {
                std::uninitialized_copy_n(begin(), shift, new_data.GetAddress());
                std::uninitialized_copy_n(begin() + shift, size_ - shift, new_data.GetAddress() + shift + 1);
            }
            catch (...) {
                std::destroy_n(new_data.GetAddress() + shift, 1);
                throw;
            }
        }
        std::destroy_n(begin(), size_);
        data_.Swap(new_data);
    }
    else {
        if (size_ != 0) {
            new (data_ + size_) T(std::move(*(end() - 1)));
            try {
                std::move_backward(begin() + shift, end(), end() + 1);
            }
            catch (...) {
                std::destroy_n(end(), 1);
                throw;
            }
            std::destroy_at(begin() + shift);
        }
        result = new (data_ + shift) T(std::forward<Args>(args)...);
    }
    ++size_;
    return result;
    }