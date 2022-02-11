#include "check_add.h"
#include "check_delete.h"
#include "check_multi.h"


int main(void)
{
    int no_failed = 0;

    Suite *s_add = suite_create("add_test");
    Suite *s_delete = suite_create("delete_test");
    Suite *s_multi = suite_create("multi_test");

    s_add = add_suite(s_add);
    s_delete = delete_suite(s_delete);
    s_multi = delete_suite(s_multi);

    SRunner *runner_add = srunner_create(s_add);
    SRunner *runner_delete = srunner_create(s_delete);
    SRunner *runner_multi = srunner_create(s_multi);

    srunner_run_all(runner_add, CK_VERBOSE);
    srunner_run_all(runner_delete, CK_VERBOSE);
    srunner_run_all(runner_multi, CK_VERBOSE);

    no_failed += srunner_ntests_failed(runner_add);
    no_failed += srunner_ntests_failed(runner_delete);
    no_failed += srunner_ntests_failed(runner_multi);

    srunner_free(runner_add);
    srunner_free(runner_delete);
    srunner_free(runner_multi);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;

}