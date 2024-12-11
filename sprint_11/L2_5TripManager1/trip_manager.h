#pragma once
#include "flight_provider.h"
#include "hotel_provider.h"

#include <string>
#include <vector>

class Trip {
public:
    //???

    Trip(HotelProvider &hp, FlightProvider &fp) :book_hotels_(hp), book_flights_(fp) {
        
    }

    Trip(const Trip &) = delete;
    Trip &operator=(const Trip &) = delete;

    Trip(Trip &&) = default;

    Trip &operator=(Trip &&) = default;

    void UpdHotelIds(const int value) {
        hotel_ids_ = value;
    }
        void UpdFlightIds(const int value) {
        flight_ids_ = value;
    }

    void Cancel() {
        // отменяем бронирования у провайдеров
        for (int i = 0; i < hotel_ids_; i++) {
        book_hotels_.Cancel(i);
        }
        for (int j = 0; j < flight_ids_; j++) {
        book_flights_.Cancel(j);
        }
    }

    ~Trip() {
        Cancel();
    };

private:
   int hotel_ids_ = 0;
   int flight_ids_ = 0;
    HotelProvider &book_hotels_;
    FlightProvider &book_flights_;
};

class TripManager {
public:
    using BookingId = std::string;
    struct BookingData {
        std::string city_from;
        std::string city_to;
        std::string date_from;
        std::string date_to;
    };

    Trip Book(const BookingData &data) {
        Trip trip(hotel_provider_, flight_provider_);
        for (int i = 0; i < FlightProvider::capacity && i < HotelProvider::capacity; ++i) {
            trip.UpdHotelIds(hotel_provider_.Book({data.city_from, data.city_to, data.date_from}));
            trip.UpdFlightIds(flight_provider_.Book({data.city_to, data.date_from, data.date_to}));
        }
        return trip;
    }

    void Cancel(Trip &trip) {
        trip.Cancel();
    }

private:
    HotelProvider hotel_provider_;
    FlightProvider flight_provider_;
};