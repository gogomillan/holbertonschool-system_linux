#ifndef GOGOMILLAN
#define GOGOMILLAN

#include <stdlib.h>
#include <stdio.h>

/**
 * struct Cars - Cars struct
 * @id: Id of the car
 * @laps: Laps of the car
 * @next: Next car struct
 * @prev: Previous car struct
 */
typedef struct Cars
{
	int id;
	int laps;
	struct Cars *next;
	struct Cars *prev;
} Cars_t;

void race_state(int *id, size_t size);
void insert_car(Cars_t **cars_list, int id);
void append_car(Cars_t **cars_list, int id);
void push_car(Cars_t *cars_iterator, int id);

#endif
