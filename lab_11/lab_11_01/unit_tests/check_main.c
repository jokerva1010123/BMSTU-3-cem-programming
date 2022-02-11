#include <check.h>
#include "../inc/main.h"
#include "check_snprintf.h"

int main(void)
{    
    Suite *s_my_snprintf = suite_create("test_my_snprintf");

    s_my_snprintf = my_snprintf_suite(s_my_snprintf);

    SRunner *runner_my_snprintf = srunner_create(s_my_snprintf);

    srunner_run_all(runner_my_snprintf, CK_VERBOSE);

    int failed = srunner_ntests_failed(runner_my_snprintf);

    srunner_free(runner_my_snprintf);

    return failed;
}
