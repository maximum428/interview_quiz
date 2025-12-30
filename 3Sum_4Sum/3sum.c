#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    //return (*(int*)a - *(int*)b);
    return (*(int*)a > *(int*)b) - (*(int*)a < *(int*)b);
}

void backtrack(int* nums, int nums_size, int* res_size, int*** res, int* vec, int vec_size, int value, int start) {
    if (vec_size == 3 && value == 0) {
        (*res) = realloc(*res, (*res_size + 1) * sizeof(int*));  // Resize result array
        (*res)[*res_size] = malloc(3 * sizeof(int));  // Allocate space for a new triplet
        for (int i = 0; i < 3; i++) {
            (*res)[*res_size][i] = vec[i];
        }
        (*res_size)++;
        return;
    }

    for (int i = start; i < nums_size; i++) {
        if (i > start && nums[i] == nums[i - 1]) {
            continue;
        }
        vec[vec_size] = nums[i];
        backtrack(nums, nums_size, res_size, res, vec, vec_size + 1, value + nums[i], i + 1);
    }
}

int** three_sum1(int* nums, int nums_size, int* return_size) {
    int** res = NULL;
    *return_size = 0;
    int* vec = malloc(3 * sizeof(int));  // Temporary vector to store triplet
    qsort(nums, nums_size, sizeof(int), compare);  // Sort the array

    backtrack(nums, nums_size, return_size, &res, vec, 0, 0, 0);
    
    free(vec);
    return res;
}

int** three_sum2(int* nums, int nums_size, int* return_size) {
    int** res = NULL;
    *return_size = 0;
    qsort(nums, nums_size, sizeof(int), compare);  // Sort the array

    for (int i = 0; i < nums_size; i++) {
        int first = -nums[i], second = i + 1, third = nums_size - 1;
        while (second < third) {
            int sum = nums[second] + nums[third];
            if (first < sum) {
                third--;
            } else if (first > sum) {
                second++;
            } else {
                res = realloc(res, (*return_size + 1) * sizeof(int*));
                res[*return_size] = malloc(3 * sizeof(int));
                res[*return_size][0] = nums[i];
                res[*return_size][1] = nums[second];
                res[*return_size][2] = nums[third];
                (*return_size)++;

                // Skip duplicates
                while (second < third && nums[second] == nums[second + 1]) {
                    second++;
                }
                while (second < third && nums[third] == nums[third - 1]) {
                    third--;
                }
            }
        }
        while (i + 1 < nums_size && nums[i] == nums[i + 1]) {
            i++;
        }
    }

    return res;
}

void print_result(int** res, int res_size) {
    for (int i = 0; i < res_size; i++) {
        printf("[ ");
        for (int j = 0; j < 3; j++) {
            printf("%d ", res[i][j]);
        }
        printf("]\n");
    }
}

void free_result(int** res, int res_size) {
    for (int i = 0; i < res_size; i++) {
        free(res[i]);
    }
    free(res);
}

int main() {
    int nums[] = {-1, 0, 1, 2, -1, -4};
    int nums_size = sizeof(nums) / sizeof(nums[0]);

    int return_size = 0;

    // Test three_sum1
    int** res1 = three_sum1(nums, nums_size, &return_size);
    printf("Result from three_sum1:\n");
    print_result(res1, return_size);
    free_result(res1, return_size);

    return_size = 0;
    
    // Test three_sum2
    int** res2 = three_sum2(nums, nums_size, &return_size);
    printf("\nResult from three_sum2:\n");
    print_result(res2, return_size);
    free_result(res2, return_size);

    return 0;
}
