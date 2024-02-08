#include <unistd.h> /*getpid*/
#include <stddef.h> /*size_t*/
#include <time.h> /*time_t*/
#include <pthread.h>

#include "uid.h"

#define BAD_TIMESTAMP ((time_t)-1)

const uid_ty bad_uid = {0, ((time_t)-1), 0};
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

uid_ty UIDGenerate(void)
{
	uid_ty new_uid;
	static size_t counter = 0;
	new_uid.time_stamp = time(NULL);
	
	if(BAD_TIMESTAMP == new_uid.time_stamp)
	{
		return UIDGetBadUID();
	}

	new_uid.pid = (size_t) getpid();
	
	pthread_mutex_lock(&mutex);

	new_uid.id_counter = counter;
	++counter;

	pthread_mutex_unlock(&mutex);

	return new_uid;
}

int UIDSame(uid_ty first, uid_ty second)
{
	return 	first.pid == second.pid && 
			first.time_stamp == second.time_stamp &&
			first.id_counter == second.id_counter;
}

uid_ty UIDGetBadUID(void)
{
	return bad_uid;
}