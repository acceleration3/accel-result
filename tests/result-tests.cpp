#include <iostream>
#include <cstdint>

#include <accel/result>

enum class generic_error_codes : std::uint32_t
{
    failed1,
    failed2
};

accel::result<int, generic_error_codes> test_function(int param)
{
    if (param == 0)
        return generic_error_codes::failed1;
    else if (param == 1)
        return generic_error_codes::failed2;
    else
        return 1337;
}

int main(int argc, char* argv[])
{
    {
        auto result = test_function(0);
        ACC_ASSERT(!result.has_value());

        auto error = result.get_error();
        ACC_ASSERT(error == generic_error_codes::failed1);
    
        ACC_ASSERT(result.value_or(42) == 42);
    }

    {
        auto result = test_function(1);
        ACC_ASSERT(!result.has_value());

        auto error = result.get_error();
        ACC_ASSERT(error == generic_error_codes::failed2);
    
        ACC_ASSERT(result.value_or(42) == 42);
    }

    {
        auto result = test_function(2);
        ACC_ASSERT(result.has_value());
    }

    std::cout << "All tests ran successfully.\n";

    return 0;
}