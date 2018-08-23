/*
 * botijo (c) 2018 Gustavo Valiente gustavo.valiente.m@gmail.com
 *
 * MIT License, see LICENSE file.
 */

#ifndef BTJ_SORT_INFO_COMPARATOR_H
#define BTJ_SORT_INFO_COMPARATOR_H

#include "btj_vector.h"

namespace btj
{

/**
 * @brief Stable less or equal Vector<SortInfo> comparator.
 */
template<typename SortInfo>
class SortInfoComparator
{

public:
    const Vector<SortInfo>& sortInfos;

    bool operator()(std::size_t a, std::size_t b) const noexcept
    {
        if(sortInfos[a] == sortInfos[b])
        {
            return a <= b;
        }

        return sortInfos[a] < sortInfos[b];
    }
};

}

#endif
