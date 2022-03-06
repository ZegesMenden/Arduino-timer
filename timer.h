#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

typedef void(*timer_callback_t)(uint32_t time, uint32_t delta_time);

class timer
{
    public:
        /**
         * @brief Construct a new timer object
         * 
         * ALL TIMES ARE IN MICROSECONDS
         * @param callback the function to call every time the timer expires
         * 
         */
        timer(timer_callback_t callback) { 
            this->callback = callback; 
        };

        /**
         * @brief Construct a new timer object
         * 
         * ALL TIMES ARE IN MICROSECONDS
         * @param callback the function to call every time the timer expires
         * @param interval the interval in microseconds that the timer will expire
         */
        timer(timer_callback_t callback, uint32_t interval) { 
            this->callback = callback; 
            this->interval = interval; 
        };

        /**
         * @brief Construct a new timer object.
         * 
         * ALL TIMES ARE IN MICROSECONDS
         * @param callback the function to call every time the timer expires
         * @param interval the interval in microseconds that the timer will expire
         * @param first_run the time in microseconds that the timer will first expire
         */
        timer(timer_callback_t callback, uint32_t interval, uint32_t first_run) { 
            this->callback = callback; 
            this->interval = interval; 
            this->first_run = first_run; 
            this->next_run = first_run;
        };

        /**
         * @brief Set the timer's callback
         * 
         * @param callback the function to call every time the timer expires
        */
        void set_callback(timer_callback_t callback) {
            this->callback = callback;
        };

        /**
         * @brief Set the timer's interval
         * 
         * @param interval the interval in microseconds that the timer will expire
         */
        void set_interval(uint32_t interval) {
            this->interval = interval;
        };

        /**
         * @brief Set the timer's first run
         * 
         * @param first_run the time in microseconds that the timer will first expire
         */
        void set_first_run(uint32_t first_run) {
            this->first_run = first_run; 
            this->next_run = first_run; 
        };

        inline void check_timer(uint32_t time) __attribute__((always_inline)); 
        inline void check_timer(uint32_t time)
        {
            if (time >= next_run) {
                callback(time, time - last_run);
                last_run = micros();
                next_run = micros() + interval;
            }
        };

    private:

        timer_callback_t callback;
        volatile uint32_t interval, first_run, last_run, next_run;

};

#endif
