#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>

class MergeSort
{
public:
    void sort(std::vector<int>& arr)
    {
        if (arr.size() <= 1)
            return;

        int mid = arr.size() / 2;
        std::vector<int> left(arr.begin(), arr.begin() + mid);
        std::vector<int> right(arr.begin() + mid, arr.end());

        std::thread left_thread([this, &left] {
            this->sort(left);
            });
        sort(right);

        left_thread.join();

        std::merge(left.begin(), left.end(), right.begin(), right.end(), arr.begin());
    }
};

int main()
{
    std::setlocale(LC_ALL, "rus");
    std::vector<int> arr(5);
    std::cout << "Введите 5 чисел: ";

    for (int i = 0; i < 10; i++)
    {
        std::cin >> arr[i];
    }

    MergeSort merge_sort;
    std::thread merge_sort_thread([&]()
        {
            merge_sort.sort(arr);
        });

    merge_sort_thread.join();

    std::cout << "Отсортированный лист: ";
    for (int i = 0; i < 10; i++) std::cout << arr[i] << " ";
    {
        std::cout << std::endl;
    }

    return 0;
}