#pragma once
namespace raii {
template <typename Provider>
class Booking {
private:
    using BookingId = typename Provider::BookingId;

    Provider *provider_;
    BookingId book_id_;

public:
    Booking(Provider *p, BookingId book) :provider_(p), book_id_(book) {
        p = nullptr;
    }
    Booking(const Booking &) = delete;
    Booking(Booking &&other) = default;
    Booking &operator=(const Booking &) = delete;
    Booking &operator=(Booking &&other) = default;

    ~Booking() {
        provider_->CancelOrComplete(*this);
    }

    // Эта функция не требуется в тестах, но в реальной программе она может быть нужна
    BookingId GetId() const {
        return book_id_;
    }
};
} // namespace
