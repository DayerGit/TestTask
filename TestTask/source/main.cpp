#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void FindMinMax(unsigned int* nums, unsigned int count,  unsigned int* Min, unsigned int* Max) {
	if (nums == NULL || Min == NULL || Max == NULL || count == 0) return;

	for (unsigned int i = 0; i < count; i++) {
		if (nums[*Min] > nums[i]) *Min = i;
		if (nums[*Max] < nums[i]) *Max = i;
	}
}

unsigned int Sum(unsigned int* nums, unsigned int count) {
    unsigned int summ = 0;
    for (unsigned int i = 0; i < count; i++) {
        summ += nums[i];
    }
    return summ;
}

int Solution(unsigned int* nums, unsigned int count) {
	if (nums == NULL || count == 0) return -1;
    if (Sum(nums, count) % count != 0) return -1;

	unsigned int MinIndex = 0, MaxIndex = 0, Steps = 0;
	
	FindMinMax(nums, count, &MinIndex, &MaxIndex);

	while (nums[MinIndex] != nums[MaxIndex]) {
        nums[MaxIndex]--;

        if (MinIndex < MaxIndex) {
            if (MaxIndex - MinIndex > count / 2) {
                if (MaxIndex < count - 1) MaxIndex++;
                else MaxIndex = 0;
            }
            else {
                if (MaxIndex > 0) MaxIndex--;
                else MaxIndex = count - 1;
            }
        }
        else {
            if (MinIndex - MaxIndex < count / 2) {
                if (MaxIndex < count - 1) MaxIndex++;
                else MaxIndex = 0;
            }
            else {
                if (MaxIndex > 0) MaxIndex--;
                else MaxIndex = count - 1;
            }
        }

        nums[MaxIndex]++;
		Steps++;
		MinIndex = MaxIndex = 0;
		FindMinMax(nums, count, &MinIndex, &MaxIndex);
	}

	return Steps;
}

int main(void) {
    unsigned int count = 0;

    setlocale(LC_ALL, "RU");
    printf("Введите количество игроков: "); scanf_s("%i", &count);
    unsigned int* nums = (unsigned int*)calloc(count, sizeof(unsigned int));

    for (unsigned int i = 0; i < count; i++) {
        printf("Введите количество карт у игрока номер %i: ", i+1); scanf_s("%i", &nums[i]);
    }

    printf("Выполнено %i ходов\n", Solution(nums, count));

	return 0;
}