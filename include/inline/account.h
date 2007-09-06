#ifndef INLINE_ACCOUNT_H
#define INLINE_ACCOUNT_H

/*
 * myuser_find(const char *name)
 *
 * Retrieves an account from the accounts DTree.
 *
 * Inputs:
 *      - account name to retrieve
 *
 * Outputs:
 *      - account wanted or NULL if it's not in the DTree.
 *
 * Side Effects:
 *      - none
 */
static inline myuser_t *myuser_find(const char *name)
{
	return mowgli_dictionary_retrieve(mulist, name);
}

/*
 * mynick_find(const char *name)
 *
 * Retrieves a nick from the nicks DTree.
 *
 * Inputs:
 *      - nickname to retrieve
 *
 * Outputs:
 *      - nick wanted or NULL if it's not in the DTree.
 *
 * Side Effects:
 *      - none
 */
static inline mynick_t *mynick_find(const char *name)
{
	return mowgli_dictionary_retrieve(nicklist, name);
}

static inline mychan_t *mychan_find(const char *name)
{
	return mowgli_dictionary_retrieve(mclist, name);
}

static inline boolean_t chanacs_source_has_flag(mychan_t *mychan, sourceinfo_t *si, unsigned int level)
{
	return si->su != NULL ? chanacs_user_has_flag(mychan, si->su, level) :
		chanacs_find(mychan, si->smu, level) != NULL;
}

/* Destroy a chanacs if it has no flags */
static inline void chanacs_close(chanacs_t *ca)
{
	if (ca->level == 0)
		object_unref(ca);
}

/* Call this with a chanacs_t with level==0 */
static inline boolean_t chanacs_is_table_full(chanacs_t *ca)
{
	return chansvs.maxchanacs > 0 &&
		LIST_LENGTH(&ca->mychan->chanacs) > chansvs.maxchanacs;
}

#endif