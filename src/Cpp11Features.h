// (c) 2025 Patricio Palma C. (patriciop AT gmail)
//
// Created by Patricio Palma on 03-02-25.
//
// Visit https://en.cppreference.com/w/cpp/11 for the full list of features in this release.

#ifndef CPP11FEATURES_H
#define CPP11FEATURES_H
#include <future>
#include <mutex>
#include <thread>
#include <vector>
#include "CppFeatures.h"
#include "Utilities.h"

// TODO: Pending C++11 features
//  - variadic templates
//  - move semantics std::move
//  - rvalue references
//  - decltype & decltype(auto)
//  - noexcept
//  - = delete
//  - new type deduction rules (for C++11)
//  - std::promise

// C++11 keyword "final".
// No class marked as final can be derived.
class Cpp11Features final : public CppFeatures
{
    Cpp11Features() : CppFeatures("C++11")
    {
        // x and y members where already initialized on declaration
        x = y = 7;
    }

    // C++11 in-class members initializer.
    // Initial values for class properties can be stated directly in class declaration
    int x = 1;
    int y = 1;

public:
    // C++11 delegating constructors.
    // This constructor reuses the logic in the custom default constructor while adds more logic.
    explicit Cpp11Features(int j) : Cpp11Features()
    {
        // C++11 keyword "constexpr"
        constexpr  auto p = 10;

        // C++11 static_assert
        static_assert(p>0, "p is not > 0"); // C++11 static assert

        x *= j*p;
    }

    // C++11 keyword "= default"
    ~Cpp11Features() override = default;

    // C++11 keyword "override"
    // It helps the programmer know when overriding a base class function as not using the keyword generates a warning.
    void show_features() override
    {
        ranged_for_loop();
        lambda_function();
        smart_pointers();
        threads();
        locks();
        futures();
    }

private:
    void ranged_for_loop() const
    {
        print_title(__func__);
        // C++11 uniform initialization
        // It is a safer and natural way to initialize objects and object containers.
        // If there type narrowing it will complain, which is a good thing.
        const std::vector v = {1, 2, 3, 4, 5};

        int ni1(3.9); // 3.9 is chopped off to 3. Implicit convertion warning. This is how bad stuff begins.
        //int ni2{3.9}; // 3.9 (double) cannot be narrowed to int. Compiler error.

        // C++11 ranged for-loops and auto keyword
        // A modern way to do the old for-loop stuff.
        for (auto const& i : v)
        {
            std::cout << "in ranged loop " << i << std::endl;
        }
    }

    void lambda_function() const
    {
        print_title(__func__);
        // C++11 local lambda function
        auto local_func = [](const int p)
        {
            std::cout << "Hello, from lamda! " << p << "\n";
        };
        local_func(10);
    }

    static void thread_payload()
    {
        std::cout << "Member function payload started.\n";
    }

    struct thread_functor
    {
        void operator()() const
        {
            std::cout << "Functor payload started.\n";
        }
    };

    void threads() const
    {
        print_title(__func__);

        // C++11 instantiate a thread with static member function as payload
        std::thread memberFunctionThread(Cpp11Features::thread_payload);

        // C++11 wait for the thread to join (to finish) to continue.
        memberFunctionThread.join();

        std::thread functorThread{thread_functor()};
        functorThread.join();

        std::thread lambdaThread{[]{ std::cout << "Lambda payload started.\n";}};
        lambdaThread.join();
    }

    void locks() const
    {
        print_title(__func__);

        // C++11 std::mutex
        // This will control access to counter variable.
        std::mutex mutex;
        int counter = 0;

        // Threads will increase an external counter on the value of the delta provided
        auto payload = [&mutex](int& counter, const int delta)
        {
          for (int i = 0; i<5; ++i)
          {
              std::lock_guard<std::mutex> g(mutex);
              counter += delta;
              std::cout << "delta=" << delta << " counter=" << counter << '\n';
          }
        };

        // C++11 std::array
        // This is an array of 10 null threads.
        std::array<std::thread, 10> threads;

        // launch the requested threads
        for (int i = 0; i < threads.size(); ++i)
        {
            // std::ref is required when passing references to a thread payload, as payload
            // arguments are copied into the thread storage area.
            threads[i] = std::thread(payload, std::ref(counter), i+1);
        }

        // wait for all threads to finish.
        for (auto& thread : threads) { thread.join(); }

        // present results
        std::cout << "outer counter=" << counter << '\n';
    }

    void smart_pointers()
    {
        print_title(__func__);
        // C++11 Smart pointers
        // The old raw pointer but this time they know their business (create and destroy the object) and
        // do it on behalf of the programmer.

        // std::unique_ptr<> is a single owner ptr.
        std::unique_ptr<Dummy> outerDummy;
        {
            // std::shared_ptr<> this uses a reference counter to a specific object,  multiple shared_ptr<> object
            // can exist and point to the same object. The object is destroyed only when no more shared_ptr object are
            // pointing to the object.
            auto sp = std::make_shared<Dummy>("shared/weak ptr example");

            // std::weak_ptr<> this allows to access a shared object, but it does not own an object.
            weakPtr = sp;
            smart_pointers_test("Scope 1");

            auto up = std::make_unique<Dummy>("unique ptr example");

            // std::unique_ptr<> are non-copiable objects but moveable. If a unique_ptr<> could be copied, the single
            // owner rule would fail, this is two std::unique_ptr<> would reference the same object. By moving the
            // std::unique_ptr<> this error avoided, in every time there is always only one ptr.
            outerDummy = std::move(up); // C++11 std::move
        }
        smart_pointers_test("Scope 2");
    }

    void smart_pointers_test(const std::string& text) const
    {
        if (const auto sp = weakPtr.lock())
        {
            std::cout << text << " weakPtr is locked id = " << sp->id << std::endl;
        }
        else
        {
            std::cout << text <<" weakPtr could not be locked" << std::endl;
        }
    }

    // While it is a pointer, it works as a regular object. You do not need
    // to check for null before dereferencing
    std::weak_ptr<Dummy> weakPtr; // C++11 std::weak_ptr

    [[nodiscard]] float futures_payload(const int i) const
    {
        std::cout << "Futures payload started. i=" << i << '\n';
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        return static_cast<float>(i)  * 0.79f;
    }

    void futures() const
    {
        print_title(__func__);

        // C++11 std::async/std::future provides a mechanism to execute asynchronous task potentially
        // as a new thread, that is up to the std::launch policy defined.
        // std::async handles thread instantiation, termination, and exception handling at the cost of less control
        // on the task thread and execution order.

        // std::launch::async : task is executed in a different thread (potentially creating and launching a new thread)
        // std::launch::deferred : task is executed on the calling thread the first time the result is requested.

        std::future<float> asyncTask1 = std::async(std::launch::async, &Cpp11Features::futures_payload, this, 1);

        std::future<float> asyncTask2 = std::async(std::launch::deferred, &Cpp11Features::futures_payload, this, 2);

        std::future<int> asyncTask3   = std::async([](){
            std::cout << "Lambda payload started.\n";
            return 7;
        });

        std::cout << "asyncTask1=" << asyncTask1.get() << '\n';
        std::cout << "asyncTask2=" << asyncTask2.get() << '\n';
        std::cout << "asyncTask3=" << asyncTask3.get() << '\n';
    }
};

#endif //CPP11FEATURES_H
