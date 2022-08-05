#include <iostream>
#include <queue>
#include <thread>
#include <chrono>
#include <mutex>
#include <future>
#include <unordered_set>
#include <atomic>

#include <vector>

#include <unistd.h>
#include <limits.h>


extern "C"{

void sum(std::vector<int> arr) {

for (int i = 0; i < 2; ++i)
	for (int j = 0; j < 2000000000; ++j)
    		;

int ans = 0;

    for (int i = 0; i < arr.size(); ++i) {
    
    //for (int j = 0; j < 2000000000; ++j)
    	//;
        ans += arr[i];
    }
    std::cout << "\nsum ( ";
    for (int i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] <<' ';
    }
    std::cout << " )  = " << ans << '\n';
}

void multiply(std::vector<int> arr) {

int ans = 1;
    for (int i = 0; i < arr.size(); ++i) {
        ans *= arr[i];
    }
    std::cout << "\nmultiply ( ";
    for (int i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] <<' ';
    }
    std::cout << " )  = " << ans << '\n';
}

void prime1_100(){
    std::cout << "\nprime numbers in range 1..100:\n";
    int i;
    for (i = 2; i <= 100; i++)
    {
        int j = 2;
        for (; j<i; j++)
        {
            if (i%j == 0)
                break;
        }
        if (j>=i)
        {
            std::cout << i << ' ';
        }
    }
    std::cout << '\n';
}

}

class thread_pool {
public:
    thread_pool(uint32_t num_threads) {
        threads.reserve(num_threads);
        for (uint32_t i = 0; i < num_threads; ++i) {
            threads.emplace_back(&thread_pool::run, this);
        }
    }

    template <typename Func, typename ...Args>
    int64_t add_task(const Func& task_func, Args&&... args) {
        int64_t task_idx = last_idx++;

        std::lock_guard<std::mutex> q_lock(q_mtx);
        q.emplace(std::async(std::launch::deferred, task_func, args...), task_idx);
        q_cv.notify_one();
        return task_idx;
    }

    void wait(int64_t task_id) {
        std::unique_lock<std::mutex> lock(completed_task_ids_mtx);
        completed_task_ids_cv.wait(lock, [this, task_id]()->bool {
            return completed_task_ids.find(task_id) != completed_task_ids.end();
            });
    }

    void wait_all() {
        std::unique_lock<std::mutex> lock(q_mtx);
        completed_task_ids_cv.wait(lock, [this]()->bool {
            std::lock_guard<std::mutex> task_lock(completed_task_ids_mtx);
            return q.empty() && last_idx == completed_task_ids.size();
            });
    }

    bool calculated(int64_t task_id) {
        std::lock_guard<std::mutex> lock(completed_task_ids_mtx);
        if (completed_task_ids.find(task_id) != completed_task_ids.end()) {
            return true;
        }
        return false;
    }

    ~thread_pool() {
        quite = true;
        for (uint32_t i = 0; i < threads.size(); ++i) {
            q_cv.notify_all();
            threads[i].join();
        }
    }

private:

    void run() {
        while (!quite) {
            std::unique_lock<std::mutex> lock(q_mtx);
            q_cv.wait(lock, [this]()->bool { return !q.empty() || quite; });

            if (!q.empty()) {
                auto elem = std::move(q.front());
                q.pop();
                lock.unlock();

                elem.first.get();

                std::lock_guard<std::mutex> lock(completed_task_ids_mtx);
                completed_task_ids.insert(elem.second);

                completed_task_ids_cv.notify_all();
            }
        }
    }

    std::queue<std::pair<std::future<void>, int64_t>> q;
    std::mutex q_mtx;
    std::condition_variable q_cv;

    std::unordered_set<int64_t> completed_task_ids;
    std::condition_variable completed_task_ids_cv;
    std::mutex completed_task_ids_mtx;

    std::vector<std::thread> threads;


    std::atomic<bool> quite{ false };
    long last_idx = 0;
};

int num_out;

extern "C"
void f(int &num)
{num = 10;}

thread_pool tp0(2);
std::vector<int> task_identifiers;

template <typename Func, typename ...Args>
void shell(std::vector<int>& task_identifiers, thread_pool &tp, const Func& task_func, Args&&... args)
{
	task_identifiers.push_back(tp.add_task(task_func, args...));
}

extern "C"
{

//------------------------
void foo(int* a, int *b, int n)
{	
	
	n = task_identifiers.size();
	for(int i = 0; i < n; ++i)
	{
		a[i] = task_identifiers[i];
		b[i] = tp0.calculated(a[i]);
	}
}
//------------------------

void array_sum(int* a, int n) {	

	
    		
	std::vector<int> a1(a, a+n);
	shell(task_identifiers, tp0, &sum, a1);
}

void array_product(int* a, int n) {	
for (int j = 0; j < 50000000; ++j)
    		;
 	std::vector<int> a1(a, a+n);
     	shell(task_identifiers, tp0, &multiply, a1);
     	
}

void foo_(long size)
{	
	short *ar = new short[size];

	for(long i = 0; i < size; ++i)
		ar[i] = 1;
	long S = 0;
	for(long i = 0; i < size; ++i)
		S += ar[i];
	std::cout << S << '\n';
 
     	std::cout << sizeof(char) << '\n';
     	std::cout << sizeof(short) << '\n';
     	std::cout << sizeof(int) << '\n';
     	std::cout << sizeof(long) << '\n';
     	std::cout << sizeof(long long) << '\n';
}

void foo1(int *array_1, long size)
{
	long S = 0;
	for(long i = 0; i < size; ++i)
		S += array_1[i];
	
	std :: cout << S << '\n';
}

void foo2(double *array_1, long size)
{
	double S = 0;
	for(long i = 0; i < size; ++i)
		S += array_1[i];
	
	std :: cout << S << '\n';
}


void add_prime() {
	shell(task_identifiers, tp0, &prime1_100);
}

void unif_ver(int range)
{
	int i, j;

	int *arr = new int[range];
	for (i=0; i < range; i++)
		arr[i] = 0;

	srand (time(NULL));
	
	int iter = 5000000;
	
	int number;

		for (i=0; i < iter; i++)
		{
			number = rand() % range;
			arr[number]++;
		}

	for (i=0; i < range; i++)
		std ::cout<<'\n' << i <<' '<< (double)arr[i] << ' ' << (double)arr[i] / iter * 100 << '%'  ;
	std::cout << '\n';
		
	//std::cout << "\nRAND_MAX = " << RAND_MAX << '\n';
}

void add_unif_ver(int range) {

	shell(task_identifiers, tp0, &unif_ver, range);
}
/*
void timer(int interval) {

	int tasks_calculated;
	
	do
	{
		sleep(interval);
		tasks_calculated = 0;
		std::cout << '\n' << "task_id" << '\t' << "\tcalculated";
		for(int j = 0; j < task_identifiers.size() - 1; ++j)
		{
		
			std::cout << '\n' << j << "\t\t";
			tp0.calculated(j)? std::cout << "выполнено" : std::cout << "выполняется/в очереди";
			tasks_calculated += tp0.calculated(j);
		}
		std::cout << '\n';
	}
	while(tasks_calculated != task_identifiers.size() - 1);
}

void add_timer(int interval) {
	shell(task_identifiers, tp0, &timer, interval);
}
*/
void all_tasks_ids()
{
	for(int i : task_identifiers)
    		std::cout << i <<' ';
    	std::cout << std::endl;
}

}
