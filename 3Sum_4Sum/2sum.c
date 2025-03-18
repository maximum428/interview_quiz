#include <stdio.h>
#include <stdlib.h>

struct HashMap {
  int* keys;
  int* values;
  int size;
  int capacity;
};

void initHashMap(struct HashMap* map, int capacity) {
  map->keys = (int*)malloc(sizeof(int)* capacity);
  map->values = (int*)malloc(sizeof(int) * capacity);
  map->size = 0;
  map->capacity = capacity;
}

int find(struct HashMap* map, int key) {
  for (int i = 0; i < map->size; i++) {
    if (map->keys[i] == key) {
      return i;
    }
  }
  return -1;
}

void insert(struct HashMap* map, int key, int value) {
  if (map->size == map->capacity) {
    map->capacity *= 2;
    map->keys = (int*)realloc(map->keys, sizeof(int) * map->capacity);
    map->values = (int*)realloc(map->values, sizeof(int) * map->capacity);
  }
  map->keys[map->size] = key;
  map->values[map->size] = value;
  map->size++;
}

int* twoSum(int* nums, int numSize, int target) {
  struct HashMap map;
  initHashMap(&map, 10);

  for (int i = 0; i < numSize; i++) {
    int complement = target - nums[i];
    int index = find(&map, complement);

    if (index != -1) {
      int* res = (int*)malloc(2 * sizeof(int));
      res[0] = map.values[index];
      res[1] = i;
      free(map.keys);
      free(map.values);
      return res;
    }
    insert(&map, nums[i], i);
  }
  free(map.keys);
  free(map.values);
  return NULL;
}

int main() {
  int nums[] = {2, 7, 11, 15};
  int target = 9;

  int* res = twoSum(nums, sizeof(nums)/sizeof(nums[0]), target);

  if (res != NULL) {
    printf("Indices: %d, %d\n", res[0], res[1]);
    free(res);
  } else {
    printf("No solution found.\n");
  }
  return 0;
}
