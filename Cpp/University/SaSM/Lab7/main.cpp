#include <iostream>
#include "../Lab3/cdg.h"
#include <climits>

struct Time {
    double start;
    double enter;
    double finish;
    Time() = default;
    Time(double start_, double enter_,
         double finish_): start(start_),
                          enter(enter_), finish(finish_) {}
    Time(const Time &time) = default;
};

struct Detail {
    int channel_number;
    Time time;
    Detail() = default;
    Detail(int channel_number_, Time time_):
            channel_number(channel_number_), time(time_) {}
    Detail(const Detail &det) = default;
};

std::ostream& operator<<(std::ostream& os, Detail &det) {
    os << "Start time: " << det.time.start
       << "s, entering time: " << det.time.enter << "s, channel number: "
       << det.channel_number << ", finish time: " << det.time.finish << "s.";
    return os;
}

int main() {
    const double mu = 25, a = 3;
    const double delta = 1, lambda = 0.1;
    size_t n, n_channels = 3;
    std::cout << "Enter number of details:";
    std::cin >> n;
    std::vector<double> start = cdg::gamma(n, 0.5 / lambda, 2);
    std::vector<double> enter = cdg::uniform(n, a - delta, a + delta);
    std::vector<double> processing = cdg::exponential(n, 1. / mu);
    std::vector<double> channels(n_channels);
    std::vector<Detail> details(n);
    details[0] = Detail(0, Time(start[0], start[0] + enter[0],
                                start[0] + enter[0] + processing[0]));
    channels[0] = details[0].time.finish;
    for (int i = 1; i < n; ++i) {
        details[i].time.start  = details[i-1].time.start + start[i];
        double ready_to_go = std::max(details[i].time.start, details[i-1].time.enter);
        bool no_wait = false;
        double free_time = std::numeric_limits<double>::max();
        int ch_number = -1;
        for (int j = 0; j < n_channels; ++j) {
            if (ready_to_go > channels[j]) {
                details[i].time.enter = ready_to_go + enter[i];
                details[i].channel_number = j;
                no_wait = true;
                break;
            }
            if (free_time > channels[j]) {
                free_time = channels[j];
                ch_number = j;
            }
        }
        if (!no_wait) {
            details[i].time.enter = free_time + enter[i];
            details[i].channel_number = ch_number;
        }
        details[i].time.finish = details[i].time.enter + processing[i];
        channels[details[i].channel_number] = details[i].time.finish;
    }
    std::cout << "Average entering interval time: " << details[n-1].time.start / n << "s.";
    auto sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += processing[i];
    }
    std::cout << " Average processing time: " << sum / n << "s.\n";
    for (int i = 0; i < n; ++i) {
        std::cout << "Detail " + std::to_string(i+1) + ": " << details[i] << '\n';
    }
    std::cout << "Finish time: " << details[n-1].time.finish << "s.\n";
    return 0;
}