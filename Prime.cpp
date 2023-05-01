//
// Created by shaohong.jiang on 4/24/2023.
//

#include <math.h>

#include "Prime.h"

bool Prime::is_Prime(int x) {
    if (x < 4) {
        return x > 1;
    }
    int total = floor(sqrt(x));
    int i = 2;
    for (i; i <= total; i++) {
        if (x % i == 0) return false;
    }
    return true;
}
int Prime::next_Prime(int x) {
    while (!is_Prime(x)) {
        x++;
    }
    return x;
}
