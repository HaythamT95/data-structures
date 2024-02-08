#include <stdio.h> /*printf*/
#include <stdlib.h> /*srand, rand*/
#include <time.h> /*clock, time, CLOCKS_PER_SEC*/
#include <assert.h> /*assert*/
#include <string.h> /*memset*/

#define ARRAY_SIZE 5000
#define NUM_BITS 10
#define BITS_PASS 2
#define HIST_SIZE (1<<(NUM_BITS - BITS_PASS))

typedef struct 
{
    unsigned int num;
    void *data;
}data_ty;

static void GenerateRandomArray(data_ty datas_[], size_t size_);

static void RadixSort(data_ty datas_[],data_ty dest_[], size_t size_,
		size_t num_important_bits, size_t bit_per_pass, size_t histogram_[]);

static void CountSort(data_ty datas_[],data_ty dest_[],
						size_t size_, int min_, int max_, size_t histogram_[]);

static unsigned int ToDigit(int msb_, int lsb_, unsigned int num);

static void PrintValues(data_ty dest_[], size_t size_);

int main()
{
	data_ty datas[ARRAY_SIZE];
	data_ty dest[ARRAY_SIZE];
	size_t histogram[HIST_SIZE];
	clock_t start;
    clock_t end;
    double time_;

	srand((unsigned int)time(NULL));

	GenerateRandomArray(datas, ARRAY_SIZE);

	start = clock();
	RadixSort(datas, dest, ARRAY_SIZE, NUM_BITS, BITS_PASS, histogram);
    end = clock();

    PrintValues(dest,ARRAY_SIZE);

	time_ = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("RadixSort took %f seconds\n", time_);

	return 0;
}

void RadixSort(data_ty datas_[],data_ty dest_[], size_t size_,
		size_t num_important_bits, size_t bit_per_pass, size_t histogram_[])
{
	size_t i = 0;
 	data_ty *temp;

	assert(NULL != datas_);
	assert(NULL != dest_);
	assert(NULL != histogram_);
	assert(1 < num_important_bits);
	assert(1 < bit_per_pass);

    for (i = 0; i < num_important_bits; i += bit_per_pass)
    {
        if (0 == (i % (2 * bit_per_pass)))
        {
            CountSort(datas_, dest_, size_, i + bit_per_pass - 1, i, histogram_);
        }
        else
        {
            CountSort(dest_, datas_, size_, i + bit_per_pass - 1, i, histogram_);
        }
    }

    if (0 != (num_important_bits % (2 * bit_per_pass)))
    {
        temp = (0 == (num_important_bits % bit_per_pass)) ? dest_ : datas_;
        memcpy(datas_, temp, size_ * sizeof(data_ty));
    }
}

void CountSort(data_ty datas_[], data_ty dest_[], size_t size_, int msb_, int lsb_, size_t histogram_[])
{
	size_t i = 0;
	unsigned int key = 0;
	size_t hist_size = 0;

	/*assert*/
	assert(NULL != datas_);
	assert(NULL != dest_);
	assert(NULL != histogram_);
	assert(0 != size_);

	/*Calc histogram size*/
	hist_size = (1 << (msb_ - lsb_ + 1));

	/* for i = 0 to max_ */
		/*histogram_[i] = 0*/
	memset(histogram_, 0,sizeof(size_t) * hist_size);

	/* for j = 0 to size_ */
	for(i = 0; i < size_; ++i)
	{
		/*Get key using ToDigit*/
		key = ToDigit(msb_, lsb_, datas_[i].num);

		/*histogram_[key] = histogram_[key] + 1*/
        ++histogram_[key];
	}

	/*for i = 1 to max_*/
	for(i = 1; i < hist_size; ++i)
	{
		/*histogram_[i] = histogram_[i] + histogram_[i-1]*/
		histogram_[i] = histogram_[i] + histogram_[i-1];
	}

	/*for j = size_ to 1*/
	for(i = size_; i > 0; --i)
	{
		/*Get key using ToDigit*/
		key = ToDigit(msb_, lsb_, datas_[i-1].num);

		/*dest_[histogram_[datas_[j]]] = datas_[j]*/
		dest_[histogram_[key] - 1] = datas_[i-1];

		/*histogram_[datas_[j]] = histogram_[datas_[j]] - 1*/
		--histogram_[key];
	}
}

unsigned int ToDigit(int msb_, int lsb_, unsigned int num)
{
	int shift = msb_ - lsb_ + 1;
	num >>= lsb_;
	num <<= (32 - shift);
	num >>= (32 - shift);
	return num;
}

void GenerateRandomArray(data_ty datas_[], size_t size_) 
{
	size_t i = 0;

	assert(NULL != datas_);
	assert(0 != size_);

    for (i = 0; i < size_; ++i) 
    {
        datas_[i].num = (rand() % 101);  
        datas_[i].data = NULL;
    }
}

void PrintValues(data_ty dest_[], size_t size_)
{
	size_t i = 0;

	assert(NULL != dest_);
	assert(0 != size_);

	for(i = 0; i < size_; ++i)
	{
		printf("%d ",dest_[i].num);
	}
	printf("\n");
}