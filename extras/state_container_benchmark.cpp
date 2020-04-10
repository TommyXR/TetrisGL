#include <chrono>
#include <cstdint>
#include <array>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <random>
#include <iostream>
#include <map>

enum class id : std::uint8_t { a = 0, b = 1, c = 2, d = 3, e = 4, f = 5, g = 6, h = 7 };

struct A {
    int i{42};
    float j{2.61};
};

inline void iter(std::array<std::unique_ptr<A>, 8>& arr, id id) {
    auto idx{static_cast<int>(id)};

    // Simulate some operations
    if (arr[idx]->i == arr[idx]->j) {
        arr[idx]->i = 34;
        arr[idx]->j *= 6;
    }
}

inline void iter(std::unordered_map<id, std::unique_ptr<A>>& map, id id) {

    // simulate some operations
    if (map[id]->i == map[id]->j) {
        map[id]->i = 34;
        map[id]->j *= 6;
    }
}

inline void iter(std::map<id, std::unique_ptr<A>>& map, id id) {
    // simulate some operations
    if (map[id]->i == map[id]->j) {
        map[id]->i = 34;
        map[id]->j *= 6;
    }
}

inline void iter(std::map<int, std::unique_ptr<A>>& map, id id) {
    auto idx{static_cast<int>(id)};
    // simulate some operations
    if (map[idx]->i == map[idx]->j) {
        map[idx]->i = 34;
        map[idx]->j *= 6;
    }
}

inline void iter(std::unordered_map<int, std::unique_ptr<A>>& map, id id) {
    auto idx{static_cast<int>(id)};
    // simulate some operations
    if (map[idx]->i == map[idx]->j) {
        map[idx]->i = 34;
        map[idx]->j *= 6;
    }
}


template<class T>
void benchmark(T& coll, std::array<id, 2000000> ids) {
    auto start{std::chrono::high_resolution_clock::now()};

    for (auto i: ids) {
        iter(coll, i);
    }

    auto end{std::chrono::high_resolution_clock::now()};

    auto elapsed{std::chrono::duration<double, std::milli>(end - start)};
    std::cerr << elapsed.count() << " ms elapsed.\n";
}



int main() {
    std::array<id, 2000000> indices;
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> dis(0, 7);

    // Random indices to access.
    std::generate(indices.begin(), indices.end(),
          [&generator, &dis]() { return static_cast<id>(dis(generator)); });

    std::array<std::unique_ptr<A>, 8> arr;
    std::unordered_map<id, std::unique_ptr<A>> umap;
    std::map<id, std::unique_ptr<A>> map;
    std::map<int, std::unique_ptr<A>> imap;
    std::unordered_map<int, std::unique_ptr<A>> iumap;

    for (int i = 0; i < 8; ++i) {
        arr[i] = std::make_unique<A>();
        imap[i] = std::make_unique<A>();
        iumap[i] = std::make_unique<A>();
        map[static_cast<id>(i)] = std::make_unique<A>();
        umap[static_cast<id>(i)] = std::make_unique<A>();
    }

    std::cerr << "Benchmarking Array... ";
    benchmark(arr, indices);

    std::cerr << "Benchmarking Map of ints... ";
    benchmark(imap, indices);


    std::cerr << "Benchmarking Map of ids... ";
    benchmark(map, indices);

    std::cerr << "Benchmarking Unordered Map of ids... ";
    benchmark(umap, indices);

    std::cerr << "Benchmarking Unordered Map of ints... ";
    benchmark(iumap, indices);



    return 0;
}
