#include <array>
#include <deque>
#include <iostream>
#include <chrono>
#include <algorithm>
#include <queue>
#include <list>

// This benchmark was used to decide what collection to use for
// the tetris grid. It  compares std::deque with std::array.
// I thought it could be faster to copy arrays every frame
// due to the memory being contiguous thus easier to iterate through,
// but it isn't. We will use std::deque.


inline void iter(std::array<std::array<bool, 10>, 20>& arr) {
    std::copy(arr.rbegin() + 1, arr.rend(), arr.rbegin());
    arr[0] = std::array<bool, 10>();
}

inline void iter(std::deque<std::array<bool, 10>>& dq) {
    dq.pop_back();
    dq.emplace_front();
}

inline void iter(std::queue<std::array<bool, 10>, std::list<std::array<bool, 10>>>& q) {
    q.pop();
    q.emplace();
}


template<class T>
void benchmark(T& coll) {
    auto start{std::chrono::high_resolution_clock::now()};

    for (auto i{0}; i < 100000; ++i) {
        iter(coll);

        // Simulate some operations
        for (auto& e: coll) {
            for (auto e2: e) {
                auto i = 3;
                i += 5;
                if (i == 3) {
                    i = 1;
                }
            }
        }
    }

    auto end{std::chrono::high_resolution_clock::now()};

    auto elapsed{std::chrono::duration<double, std::milli>(end - start)};
    std::cerr << elapsed.count() << " ms elapsed.\n";
}

int main() {
    std::array<std::array<bool, 10>, 20> arr;
    std::deque<std::array<bool, 10>> dq(20);

    std::cerr << "Benchmarking Array... ";
    benchmark(arr);

    std::cerr << "Benchmarking deque... ";
    benchmark(dq);

    return 0;
};