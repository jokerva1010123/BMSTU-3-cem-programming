#include "check_sort.h"
#include "check_key.h"


int main()
{
    int no_failed = 0;
    Suite *s_filter;

    Suite *s1_sort;
    Suite *s2_sort;

    SRunner *runner_key;
    SRunner *runner_mysort;
    SRunner *runner_mycmp;

    s1_sort = mycmp_suite();
    s2_sort = mysort_suite();

    s_filter = key_suite();

    runner_key = srunner_create(s_filter);

    runner_mycmp = srunner_create(s1_sort);
    runner_mysort = srunner_create(s2_sort);

    srunner_run_all(runner_key, CK_VERBOSE);
    srunner_run_all(runner_mycmp, CK_VERBOSE);
    srunner_run_all(runner_mysort, CK_VERBOSE);

    no_failed += srunner_ntests_failed(runner_key);
    no_failed += srunner_ntests_failed(runner_mycmp);
    no_failed += srunner_ntests_failed(runner_mysort);

    srunner_free(runner_mycmp);
    srunner_free(runner_mysort);
    srunner_free(runner_key);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}