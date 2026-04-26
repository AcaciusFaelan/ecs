int myMax(int x, int y) {
    if (x > y) {
        return x;
    } else {
        return y;
    }
}

float myMax(float x, float y) {
    if (x > y) {
        return x;
    } else {
        return y;
    }
}

template <typename T>
T myMax(T x, T y) {
    if (x > y) {
        return x;
    } else {
        return y;
    }
}
