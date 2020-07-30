#include <fpr/stl/bmap.h>
#include <iostream>
#include <ranges>
#include <vector>

int
main(void)
{
    fpr::bmap<int, float> a;
    a.insert({ 0, 0.1f });
    return 0;
}