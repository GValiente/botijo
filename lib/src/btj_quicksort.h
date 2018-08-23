/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_QUICKSORT_H
#define BTJ_QUICKSORT_H

namespace btj
{

// https://codereview.stackexchange.com/questions/77782/quick-sort-implementation

namespace detail
{
    template<class Cmp, class Swap>
    int partition(int left, int right, const Cmp& cmp, Swap& swap, bool& swapped) noexcept
    {
        int mid = left + (right - left) / 2;

        // Move the mid point value to the front:
        swap(mid, left);

        int i = left + 1;
        int j = right;

        while(i <= j)
        {
            while(i <= j && cmp(i, mid))
            {
                ++i;
            }

            while(i <= j && cmp(mid, j))
            {
                --j;
            }

            if(i < j)
            {
                swap(i, j);
                swapped = true;
            }
        }

        swap(i - 1, left);
        return i - 1;
    }

    template<class Cmp, class Swap>
    void quicksort(int left, int right, const Cmp& cmp, Swap& swap, bool& swapped)
    {
        if(left >= right)
        {
            return;
        }

        int result = partition(left, right, cmp, swap, swapped);
        quicksort(left, result - 1, cmp, swap, swapped);
        quicksort(result + 1, right, cmp, swap, swapped);
    }
}

template<class Cmp, class Swap>
bool quicksort(int left, int right, const Cmp& cmp, Swap& swap)
{
    if(left >= right)
    {
        return false;
    }

    bool swapped = false;
    int result = detail::partition(left, right, cmp, swap, swapped);
    detail::quicksort(left, result - 1, cmp, swap, swapped);
    detail::quicksort(result + 1, right, cmp, swap, swapped);
    return swapped;
}

}

#endif
