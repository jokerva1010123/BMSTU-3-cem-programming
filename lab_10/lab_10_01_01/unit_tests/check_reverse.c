#include "check_reverse.h"

START_TEST(one_node)
{
    node_t *head = NULL;
    int arr[3] = {1, 2, 3};
    node_t *tmp = malloc(sizeof(node_t));
    tmp->data = (void *)(arr + 0);
    tmp->next = NULL;
    head = tmp;
    head = reverse(head);
    int rc = 0;
    if (*(int *)(head->data) != 1 || head->next != NULL)
        rc = 1;
    ck_assert_int_eq(rc, 0);
    delete(head);
}
END_TEST

START_TEST(three_node)
{
    node_t *head = NULL;
    int arr[3] = {1, 2, 3};
    for (int i = 0; i < 3; i++)
    {
        node_t *tmp = malloc(sizeof(node_t));
        tmp->data = (void *)(arr + 0);
        tmp->next = NULL;
        if (head == NULL)
        {
            head = tmp;
            continue;
        }
        node_t *cur = head;
        while (cur->next)
            cur = cur->next;
        cur->next = tmp;
    }
    head = reverse(head);
    int rc = 0;
    if (*(int *)(head->data) != 3)
        rc = 1;
    if (head->next == NULL || *(int *)head->next->data != 2)
        rc = 1;
    if (head->next->next == NULL || *(int *)head->next->next->data != 1)
        rc = 1;
    ck_assert_int_eq(rc, 0);
    delete(head);
}
END_TEST

Suite *reverse_test(Suite *s)
{
    TCase *tcase_pos = tcase_create("positives");
    tcase_add_test(tcase_pos, one_node);
    tcase_add_test(tcase_pos, three_node);

    suite_add_tcase(s, tcase_pos);
    return s;
}
