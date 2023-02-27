#include <re.h>

static void bad(void)
{
	struct list *list;
	struct list *list2;
	struct le le1;
	struct le le2;
	struct le *le;

	list = mem_zalloc(sizeof(struct list), NULL);
	list_append(list, &le1, NULL);
	list_append(list, &le2, NULL);

	LIST_FOREACH(list, le)
	{
		list_unlink(le);
		/* -> le->next = NULL */
	}

	for ((le) = list_head((list)); (le); (le) = (le)->next) {
		list_unlink(le);
	}

	le = list_head(list);
	while (le) {
		list_unlink(le);
		/* -> le->next = NULL */
	}

	list2 = mem_zalloc(sizeof(struct list), NULL);

	LIST_FOREACH(list, le)
	{
		list_move(le, list2);
		/* -> le->next = NULL */
	}

	for ((le) = list_head((list)); (le); (le) = (le)->next) {
		list_move(le, list2);
		/* -> le->next = NULL */
	}

	le = list_head(list);
	while (le) {
		list_move(le, list2);
		/* -> le->next = NULL */
		le = le->next;
	}

	mem_deref(list);
	mem_deref(list2);
}


static void good(void)
{
	struct list *list;
	struct list *list2;
	struct le le1;
	struct le le2;
	struct le *le;

	list = mem_zalloc(sizeof(struct list), NULL);
	list_append(list, &le1, NULL);
	list_append(list, &le2, NULL);

	le = list_head(list);
	while (le) {
		le = le->next;
		list_unlink(le);
	}

	list2 = mem_zalloc(sizeof(struct list), NULL);

	le = list_head(list);
	while (le) {
		le = le->next;
		list_move(le, list2);
	}

	mem_deref(list);
	mem_deref(list2);
}


int main(void)
{
	bad();
	good();
	return 0;
}
