#include <iostream>

#include <accel/result>

enum class generic_error_codes
{
    failed1,
    failed2
};

static const char* translate_generic_error(generic_error_codes code)
{
    switch (code)
    {
        case generic_error_codes::failed1: return "Operation failed because of reason 1.";
        case generic_error_codes::failed2: return "Operation failed because of reason 2.";
        default: return "Unknown error.";
    }
}

using generic_error = accel::error<generic_error_codes, translate_generic_error>;

accel::result<int, generic_error> test_function(int param)
{
    if (param == 0)
        return generic_error(generic_error_codes::failed1);
    else if (param == 1)
        return generic_error(generic_error_codes::failed2);
    else
        return 1337;
}

int main(int argc, char* argv[])
{
    {
        auto result = test_function(0);
        ACC_ASSERT(!result.has_value());

        auto error = result.get_error();
        ACC_ASSERT(error.get_error_type() == generic_error_codes::failed1);
        std::cout << error.get_message() << "\n";

        ACC_ASSERT(result.value_or(42) == 42);
    }

    {
        auto result = test_function(1);
        ACC_ASSERT(!result.has_value());

        auto error = result.get_error();
        ACC_ASSERT(error.get_error_type() == generic_error_codes::failed2);
        std::cout << error.get_message() << "\n";

        ACC_ASSERT(result.value_or(314159) == 314159);
    }

    {
        auto result = test_function(2);
        ACC_ASSERT(result.has_value());
        ACC_ASSERT(result.get_value() == 1337);
        ACC_ASSERT(result.value_or(42) == 1337);
    }

    std::cout << "All tests ran successfully.\n";

    return 0;
}