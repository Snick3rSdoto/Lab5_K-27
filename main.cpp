#include <iostream>
#include <string>
#include <thread>
#include <future>
#include <chrono>
#include <syncstream>

void slow(const std::string& name) {
    std::this_thread::sleep_for(std::chrono::seconds(7));
    std::osyncstream(std::cout) << name << " completed (Slow)\n";
}

void quick(const std::string& name) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::osyncstream(std::cout) << name << " completed (Quick)\n";
}

void run_chain_C2_D2() {
    slow("C2");   
    quick("D2");  
}

void work() {
    using clock = std::chrono::steady_clock;

    auto start_time = clock::now();

    std::osyncstream(std::cout) << "Starting work (Variant #14)...\n";

    auto future_A1 = std::async(std::launch::async, slow, "A1");

    auto future_C2_D2 = std::async(std::launch::async, run_chain_C2_D2);

    quick("C1");
    quick("A2");

    future_A1.get();  

    quick("B");

    quick("D1");

    future_C2_D2.get();

    auto end_time = clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;

    std::osyncstream(std::cout) << "Work is done!\n";
    std::osyncstream(std::cout) << "Total time: "
        << elapsed.count() << " seconds.\n";
}

int main() {
    work();
    return 0;
}

