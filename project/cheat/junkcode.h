#include <iostream>
#include <Windows.h>
#include <functional>
#include <thread>
#include "../encrypt/xor.hpp"


#define JUNK_CODE_CONDITION(N, DIVISOR) ((N) % (DIVISOR) == 0)

#define JUNK_CODE_FUNCTION_1() { \
    int var1 = 42; \
    if (var1 % 2 == 0) { \
        var1 *= 2; \
    } else { \
        var1 += 3; \
    } \
}

#define JUNK_CODE_FUNCTION_2() { \
    int var2 = 77; \
    while (var2 > 0) { \
        var2 -= 5; \
        if (var2 == 10) { \
            var2 /= 2; \
        } \
    } \
}
#define JUNK_CODE_FUNCTION_3() { \
    int var3 = 13; \
    for (int i = 0; i < 4; ++i) { \
        var3 += i; \
        if (var3 % 3 == 0) { \
            var3 *= 3; \
        } \
    } \
}

#define JUNK_CODE_FUNCTION_4() { \
    int var4 = 55; \
    do { \
        var4 += 4; \
        if (var4 > 50) { \
            var4 -= 10; \
        } \
    } while (var4 < 60); \
}

#define JUNK_CODE_FUNCTION_5() { \
    int var5 = 21; \
    if (var5 % 2 == 0) { \
        var5 *= 2; \
    } else { \
        var5 += 3; \
    } \
}

#define JUNK_CODE_FUNCTION_6() { \
    int var6 = 64; \
    while (var6 > 0) { \
        var6 -= 7; \
        if (var6 == 14) { \
            var6 /= 2; \
        } \
    } \
}

#define JUNK_CODE_FUNCTION_7() { \
    int var7 = 17; \
    for (int i = 0; i < 5; ++i) { \
        var7 += i; \
        if (var7 % 3 == 0) { \
            var7 *= 3; \
        } \
    } \
}

#define JUNK_CODE_FUNCTION_8() { \
    int var8 = 49; \
    do { \
        var8 += 6; \
        if (var8 > 40) { \
            var8 -= 8; \
        } \
    } while (var8 < 70); \
}

#define JUNK_CODE_FUNCTION_9() { \
    int var9 = 33; \
    if (var9 % 2 == 0) { \
        var9 *= 2; \
    } else { \
        var9 += 3; \
    } \
}

#define JUNK_CODE_FUNCTION_10() { \
    int var10 = 88; \
    while (var10 > 0) { \
        var10 -= 9; \
        if (var10 == 18) { \
            var10 /= 2; \
        } \
    } \
}

#define JUNK_CODE(N) \
    if (JUNK_CODE_CONDITION(N, 1)) { \
        if (N % 2 == 0) { \
            for (int q = 0; q < N; ++q) { \
            int randomVar4 = 77; \
            for (int p = 0; p < 8; ++p) { \
                int t = p + 6; \
                do { \
                    t += 5; \
                    if (t == 18) { \
                        JUNK_CODE_FUNCTION_1(); \
                        int innerVar1 = t * randomVar4 / 3; \
                        for (int q = 0; q < N; ++q) { \
                            int randomVar4 = 77; \
                            for (int p = 0; p < 6; ++p) { \
                                int t = p + 3; \
                                do { \
                                    t += 2; \
                                    if (t == 11) { \
                                        JUNK_CODE_FUNCTION_1(); \
                                        int innerVar1 = t * randomVar4 / 3; \
                                    } \
                                } while (t < 18); \
                            } \
                            if (randomVar4 > 35) { \
                                int r = randomVar4 / 5; \
                                do { \
                                    JUNK_CODE_FUNCTION_1(); \
                                    r -= 4; \
                                } while (r > 0); \
                            } \
                        } \
                    } \
                } while (t < 30); \
            } \
            \
            if (randomVar4 > 35) { \
                int r = randomVar4 / 5; \
                do { \
                                for (int p = 0; p < 8; ++p) { \
                int t = p + 6; \
                do { \
                    t += 5; \
                    if (t == 18) { \
                        JUNK_CODE_FUNCTION_1(); \
                        int innerVar1 = t * randomVar4 / 3; \
                        for (int q = 0; q < N; ++q) { \
                            int randomVar4 = 77; \
                            for (int p = 0; p < 6; ++p) { \
                                int t = p + 3; \
                                do { \
                                    t += 2; \
                                    if (t == 11) { \
                                        JUNK_CODE_FUNCTION_1(); \
                                        int innerVar1 = t * randomVar4 / 3; \
                                    } \
                                } while (t < 18); \
                            } \
                            if (randomVar4 > 35) { \
                                int r = randomVar4 / 5; \
                                do { \
                                    JUNK_CODE_FUNCTION_1(); \
                                    r -= 4; \
                                } while (r > 0); \
                            } \
                        } \
                    } \
                } while (t < 30); \
            } \
                    r -= 4; \
                } while (r > 0); \
            } \
            \
                for (int p = 0; p < 8; ++p) { \
                int t = p + 6; \
                do { \
                    t += 5; \
                    if (t == 18) { \
                        JUNK_CODE_FUNCTION_1(); \
                        int innerVar1 = t * randomVar4 / 3; \
                        for (int q = 0; q < N; ++q) { \
                            int randomVar4 = 77; \
                            for (int p = 0; p < 6; ++p) { \
                                int t = p + 3; \
                                do { \
                                    t += 2; \
                                    if (t == 11) { \
                                        JUNK_CODE_FUNCTION_1(); \
                                        int innerVar1 = t * randomVar4 / 3; \
                                    } \
                                } while (t < 18); \
                            } \
                            if (randomVar4 > 35) { \
                                int r = randomVar4 / 5; \
                                do { \
                                    JUNK_CODE_FUNCTION_1(); \
                                    r -= 4; \
                                } while (r > 0); \
                            } \
                        } \
                    } \
                } while (t < 30); \
            } \
        } \
        } else { \
            for (int q = 0; q < N; ++q) { \
            int randomVar4 = 89; \
            for (int p = 0; p < 7; ++p) { \
                int t = p + 4; \
                do { \
                    t += 3; \
                    if (t == 14) { \
                        JUNK_CODE_FUNCTION_1(); \
                        int innerVar1 = t * randomVar4 / 2; \
                        JUNK_CODE_FUNCTION_1(); \
                    } \
                } while (t < 25); \
            } \
            \
            if (randomVar4 > 40) { \
                int r = randomVar4 / 6; \
                do { \
                    JUNK_CODE_FUNCTION_1(); \
                    r -= 3; \
                } while (r > 0); \
            } \
            \
                    JUNK_CODE_FUNCTION_1(); \
        } \
        } \
    } \
    if (JUNK_CODE_CONDITION(N, 2)) { \
        if (N % 2 == 0) { \
            for (int q = 0; q < N; ++q) { \
            int randomVar4 = 63; \
            for (int p = 0; p < 6; ++p) { \
                int t = p + 5; \
                do { \
                    t += 4; \
                    if (t == 17) { \
                        for (int q = 0; q < N; ++q) { \
                            int randomVar4 = 42; \
                            for (int p = 0; p < 4; ++p) { \
                                int t = p + 2; \
                                do { \
                                    t += 1; \
                                    if (t == 7) { \
                                        JUNK_CODE_FUNCTION_2(); \
                                        int innerVar1 = t * randomVar4 / 3; \
                                    } \
                                } while (t < 11); \
                            } \
                            if (randomVar4 > 20) { \
                                int r = randomVar4 / 4; \
                                do { \
                                    JUNK_CODE_FUNCTION_2(); \
                                    r -= 2; \
                                } while (r > 0); \
                            } \
                        } \
                        int innerVar1 = t * randomVar4 / 4; \
                        for (int q = 0; q < N; ++q) { \
                            int randomVar4 = 42; \
                            for (int p = 0; p < 4; ++p) { \
                                int t = p + 2; \
                                do { \
                                    t += 1; \
                                    if (t == 7) { \
                                        JUNK_CODE_FUNCTION_2(); \
                                        int innerVar1 = t * randomVar4 / 3; \
                                    } \
                                } while (t < 11); \
                            } \
                            if (randomVar4 > 20) { \
                                int r = randomVar4 / 4; \
                                do { \
                                    JUNK_CODE_FUNCTION_2(); \
                                    r -= 2; \
                                } while (r > 0); \
                            } \
                        } \
                    } \
                } while (t < 28); \
            } \
            \
            if (randomVar4 > 30) { \
                int r = randomVar4 / 7; \
                do { \
                        for (int q = 0; q < N; ++q) { \
                            int randomVar4 = 42; \
                            for (int p = 0; p < 4; ++p) { \
                                int t = p + 2; \
                                do { \
                                    t += 1; \
                                    if (t == 7) { \
                                        JUNK_CODE_FUNCTION_2(); \
                                        int innerVar1 = t * randomVar4 / 3; \
                                    } \
                                } while (t < 11); \
                            } \
                            if (randomVar4 > 20) { \
                                int r = randomVar4 / 4; \
                                do { \
                                    JUNK_CODE_FUNCTION_2(); \
                                    r -= 2; \
                                } while (r > 0); \
                            } \
                        } \
                    r -= 2; \
                } while (r > 0); \
            } \
            \
                        for (int q = 0; q < N; ++q) { \
                            int randomVar4 = 42; \
                            for (int p = 0; p < 4; ++p) { \
                                int t = p + 2; \
                                do { \
                                    t += 1; \
                                    if (t == 7) { \
                                        JUNK_CODE_FUNCTION_2(); \
                                        int innerVar1 = t * randomVar4 / 3; \
                                    } \
                                } while (t < 11); \
                            } \
                            if (randomVar4 > 20) { \
                                int r = randomVar4 / 4; \
                                do { \
                                    JUNK_CODE_FUNCTION_2(); \
                                    r -= 2; \
                                } while (r > 0); \
                            } \
                        } \
        } \
        } else { \
            for (int q = 0; q < N; ++q) { \
            int randomVar4 = 52; \
            for (int p = 0; p < 7; ++p) { \
                int t = p + 4; \
                do { \
                    t += 3; \
                    if (t == 16) { \
                        for (int q = 0; q < N; ++q) { \
                            int randomVar4 = 42; \
                            for (int p = 0; p < 4; ++p) { \
                                int t = p + 2; \
                                do { \
                                    t += 1; \
                                    if (t == 7) { \
                                        JUNK_CODE_FUNCTION_2(); \
                                        int innerVar1 = t * randomVar4 / 3; \
                                    } \
                                } while (t < 11); \
                            } \
                            if (randomVar4 > 20) { \
                                int r = randomVar4 / 4; \
                                do { \
                                    JUNK_CODE_FUNCTION_2(); \
                                    r -= 2; \
                                } while (r > 0); \
                            } \
                        } \
                        int innerVar1 = t * randomVar4 / 5; \
                        for (int q = 0; q < N; ++q) { \
                            int randomVar4 = 42; \
                            for (int p = 0; p < 4; ++p) { \
                                int t = p + 2; \
                                do { \
                                    t += 1; \
                                    if (t == 7) { \
                                        JUNK_CODE_FUNCTION_2(); \
                                        int innerVar1 = t * randomVar4 / 3; \
                                    } \
                                } while (t < 11); \
                            } \
                            if (randomVar4 > 20) { \
                                int r = randomVar4 / 4; \
                                do { \
                                    JUNK_CODE_FUNCTION_2(); \
                                    r -= 2; \
                                } while (r > 0); \
                            } \
                        } \
                    } \
                } while (t < 27); \
            } \
            \
            if (randomVar4 > 25) { \
                int r = randomVar4 / 6; \
                do { \
                        for (int q = 0; q < N; ++q) { \
                            int randomVar4 = 42; \
                            for (int p = 0; p < 4; ++p) { \
                                int t = p + 2; \
                                do { \
                                    t += 1; \
                                    if (t == 7) { \
                                        JUNK_CODE_FUNCTION_2(); \
                                        int innerVar1 = t * randomVar4 / 3; \
                                    } \
                                } while (t < 11); \
                            } \
                            if (randomVar4 > 20) { \
                                int r = randomVar4 / 4; \
                                do { \
                                    JUNK_CODE_FUNCTION_2(); \
                                    r -= 2; \
                                } while (r > 0); \
                            } \
                        } \
                    r -= 1; \
                } while (r > 0); \
            } \
            \
                        for (int q = 0; q < N; ++q) { \
                            int randomVar4 = 42; \
                            for (int p = 0; p < 4; ++p) { \
                                int t = p + 2; \
                                do { \
                                    t += 1; \
                                    if (t == 7) { \
                                        JUNK_CODE_FUNCTION_2(); \
                                        int innerVar1 = t * randomVar4 / 3; \
                                    } \
                                } while (t < 11); \
                            } \
                            if (randomVar4 > 20) { \
                                int r = randomVar4 / 4; \
                                do { \
                                    JUNK_CODE_FUNCTION_2(); \
                                    r -= 2; \
                                } while (r > 0); \
                            } \
                        } \
        } \
        } \
    } \
    if (JUNK_CODE_CONDITION(N, 3)) { \
        if (N % 2 == 0) { \
            for (int q = 0; q < N; ++q) { \
            int randomVar4 = 63; \
            for (int p = 0; p < 9; ++p) { \
                int t = p + 7; \
                do { \
                    t += 4; \
                    if (t == 21) { \
                    for (int q = 0; q < N; ++q) { \
                        int randomVar4 = 17; \
                        for (int p = 0; p < 3; ++p) { \
                            int t = p + 1; \
                            do { \
                                t += 1; \
                                if (t == 4) { \
                                    JUNK_CODE_FUNCTION_3(); \
                                    int innerVar1 = t * randomVar4 / 2; \
                                } \
                            } while (t < 6); \
                        } \
                        if (randomVar4 > 10) { \
                            int r = randomVar4 / 3; \
                            do { \
                                JUNK_CODE_FUNCTION_3(); \
                                r -= 1; \
                            } while (r > 0); \
                        } \
                    } \
                        int innerVar1 = t * randomVar4 / 2; \
                    for (int q = 0; q < N; ++q) { \
                        int randomVar4 = 17; \
                        for (int p = 0; p < 3; ++p) { \
                            int t = p + 1; \
                            do { \
                                t += 1; \
                                if (t == 4) { \
                                    JUNK_CODE_FUNCTION_3(); \
                                    int innerVar1 = t * randomVar4 / 2; \
                                } \
                            } while (t < 6); \
                        } \
                        if (randomVar4 > 10) { \
                            int r = randomVar4 / 3; \
                            do { \
                                JUNK_CODE_FUNCTION_3(); \
                                r -= 1; \
                            } while (r > 0); \
                        } \
                    } \
                    } \
                } while (t < 35); \
            } \
            \
            if (randomVar4 > 40) { \
                int r = randomVar4 / 3; \
                do { \
                    for (int q = 0; q < N; ++q) { \
                        int randomVar4 = 17; \
                        for (int p = 0; p < 3; ++p) { \
                            int t = p + 1; \
                            do { \
                                t += 1; \
                                if (t == 4) { \
                                    JUNK_CODE_FUNCTION_3(); \
                                    int innerVar1 = t * randomVar4 / 2; \
                                } \
                            } while (t < 6); \
                        } \
                        if (randomVar4 > 10) { \
                            int r = randomVar4 / 3; \
                            do { \
                                JUNK_CODE_FUNCTION_3(); \
                                r -= 1; \
                            } while (r > 0); \
                        } \
                    } \
                    r -= 2; \
                } while (r > 0); \
            } \
            \
                    for (int q = 0; q < N; ++q) { \
                        int randomVar4 = 17; \
                        for (int p = 0; p < 3; ++p) { \
                            int t = p + 1; \
                            do { \
                                t += 1; \
                                if (t == 4) { \
                                    JUNK_CODE_FUNCTION_3(); \
                                    int innerVar1 = t * randomVar4 / 2; \
                                } \
                            } while (t < 6); \
                        } \
                        if (randomVar4 > 10) { \
                            int r = randomVar4 / 3; \
                            do { \
                                JUNK_CODE_FUNCTION_3(); \
                                r -= 1; \
                            } while (r > 0); \
                        } \
                    } \
        } \
        } else { \
            for (int q = 0; q < N; ++q) { \
            int randomVar4 = 92; \
            for (int p = 0; p < 6; ++p) { \
                int t = p + 9; \
                do { \
                    t += 3; \
                    if (t == 24) { \
                    for (int q = 0; q < N; ++q) { \
                        int randomVar4 = 17; \
                        for (int p = 0; p < 3; ++p) { \
                            int t = p + 1; \
                            do { \
                                t += 1; \
                                if (t == 4) { \
                                    JUNK_CODE_FUNCTION_3(); \
                                    int innerVar1 = t * randomVar4 / 2; \
                                } \
                            } while (t < 6); \
                        } \
                        if (randomVar4 > 10) { \
                            int r = randomVar4 / 3; \
                            do { \
                                JUNK_CODE_FUNCTION_3(); \
                                r -= 1; \
                            } while (r > 0); \
                        } \
                    } \
                        int innerVar1 = t * randomVar4 / 4; \
                    for (int q = 0; q < N; ++q) { \
                        int randomVar4 = 17; \
                        for (int p = 0; p < 3; ++p) { \
                            int t = p + 1; \
                            do { \
                                t += 1; \
                                if (t == 4) { \
                                    JUNK_CODE_FUNCTION_3(); \
                                    int innerVar1 = t * randomVar4 / 2; \
                                } \
                            } while (t < 6); \
                        } \
                        if (randomVar4 > 10) { \
                            int r = randomVar4 / 3; \
                            do { \
                                JUNK_CODE_FUNCTION_3(); \
                                r -= 1; \
                            } while (r > 0); \
                        } \
                    } \
                    } \
                } while (t < 33); \
            } \
            \
            if (randomVar4 > 50) { \
                int r = randomVar4 / 4; \
                do { \
                    for (int q = 0; q < N; ++q) { \
                        int randomVar4 = 17; \
                        for (int p = 0; p < 3; ++p) { \
                            int t = p + 1; \
                            do { \
                                t += 1; \
                                if (t == 4) { \
                                    JUNK_CODE_FUNCTION_3(); \
                                    int innerVar1 = t * randomVar4 / 2; \
                                } \
                            } while (t < 6); \
                        } \
                        if (randomVar4 > 10) { \
                            int r = randomVar4 / 3; \
                            do { \
                                JUNK_CODE_FUNCTION_3(); \
                                r -= 1; \
                            } while (r > 0); \
                        } \
                    } \
                    r -= 5; \
                } while (r > 0); \
            } \
            \
                    for (int q = 0; q < N; ++q) { \
                        int randomVar4 = 17; \
                        for (int p = 0; p < 3; ++p) { \
                            int t = p + 1; \
                            do { \
                                t += 1; \
                                if (t == 4) { \
                                    JUNK_CODE_FUNCTION_3(); \
                                    int innerVar1 = t * randomVar4 / 2; \
                                } \
                            } while (t < 6); \
                        } \
                        if (randomVar4 > 10) { \
                            int r = randomVar4 / 3; \
                            do { \
                                JUNK_CODE_FUNCTION_3(); \
                                r -= 1; \
                            } while (r > 0); \
                        } \
                    } \
        } \
        } \
    } \
    if (JUNK_CODE_CONDITION(N, 5)) { \
        if (N % 2 == 0) { \
            for (int u = 0; u < N; ++u) { \
            int randomVar6 = 51; \
            for (int v = 0; v < 6; ++v) { \
                int w = v + 2; \
                do { \
                    w += 3; \
                    if (w == 11) { \
                    for (int q = 0; q < N; ++q) { \
                        int randomVar4 = 7; \
                        for (int p = 0; p < 2; ++p) { \
                            int t = p + 1; \
                            do { \
                                t += 1; \
                                if (t == 2) { \
                                    JUNK_CODE_FUNCTION_5(); \
                                    int innerVar1 = t * randomVar4 / 2; \
                                } \
                            } while (t < 3); \
                        } \
                        if (randomVar4 > 5) { \
                            int r = randomVar4 / 2; \
                            do { \
                                JUNK_CODE_FUNCTION_5(); \
                                r -= 1; \
                            } while (r > 0); \
                        } \
                    } \
                        int innerVar4 = w * randomVar6 / 2; \
                    for (int q = 0; q < N; ++q) { \
                        int randomVar4 = 7; \
                        for (int p = 0; p < 2; ++p) { \
                            int t = p + 1; \
                            do { \
                                t += 1; \
                                if (t == 2) { \
                                    JUNK_CODE_FUNCTION_5(); \
                                    int innerVar1 = t * randomVar4 / 2; \
                                } \
                            } while (t < 3); \
                        } \
                        if (randomVar4 > 5) { \
                            int r = randomVar4 / 2; \
                            do { \
                                JUNK_CODE_FUNCTION_5(); \
                                r -= 1; \
                            } while (r > 0); \
                        } \
                    } \
                    } \
                } while (w < 15); \
            } \
            \
            if (randomVar6 > 25) { \
                int x = randomVar6 / 4; \
                do { \
                    for (int q = 0; q < N; ++q) { \
                        int randomVar4 = 7; \
                        for (int p = 0; p < 2; ++p) { \
                            int t = p + 1; \
                            do { \
                                t += 1; \
                                if (t == 2) { \
                                    JUNK_CODE_FUNCTION_5(); \
                                    int innerVar1 = t * randomVar4 / 2; \
                                } \
                            } while (t < 3); \
                        } \
                        if (randomVar4 > 5) { \
                            int r = randomVar4 / 2; \
                            do { \
                                JUNK_CODE_FUNCTION_5(); \
                                r -= 1; \
                            } while (r > 0); \
                        } \
                    } \
                    x -= 2; \
                } while (x > 0); \
            } \
            \
                    for (int q = 0; q < N; ++q) { \
                        int randomVar4 = 7; \
                        for (int p = 0; p < 2; ++p) { \
                            int t = p + 1; \
                            do { \
                                t += 1; \
                                if (t == 2) { \
                                    JUNK_CODE_FUNCTION_5(); \
                                    int innerVar1 = t * randomVar4 / 2; \
                                } \
                            } while (t < 3); \
                        } \
                        if (randomVar4 > 5) { \
                            int r = randomVar4 / 2; \
                            do { \
                                JUNK_CODE_FUNCTION_5(); \
                                r -= 1; \
                            } while (r > 0); \
                        } \
                    } \
        } \
        } else { \
            for (int y = 0; y < N; ++y) { \
            int randomVar2 = 68; \
            for (int z = 0; z < 7; ++z) { \
                int a = z + 4; \
                do { \
                    a += 4; \
                    if (a == 16) { \
                    for (int q = 0; q < N; ++q) { \
                        int randomVar4 = 7; \
                        for (int p = 0; p < 2; ++p) { \
                            int t = p + 1; \
                            do { \
                                t += 1; \
                                if (t == 2) { \
                                    JUNK_CODE_FUNCTION_5(); \
                                    int innerVar1 = t * randomVar4 / 2; \
                                } \
                            } while (t < 3); \
                        } \
                        if (randomVar4 > 5) { \
                            int r = randomVar4 / 2; \
                            do { \
                                JUNK_CODE_FUNCTION_5(); \
                                r -= 1; \
                            } while (r > 0); \
                        } \
                    } \
                        int innerVar2 = a * randomVar2 / 3; \
                    for (int q = 0; q < N; ++q) { \
                        int randomVar4 = 7; \
                        for (int p = 0; p < 2; ++p) { \
                            int t = p + 1; \
                            do { \
                                t += 1; \
                                if (t == 2) { \
                                    JUNK_CODE_FUNCTION_5(); \
                                    int innerVar1 = t * randomVar4 / 2; \
                                } \
                            } while (t < 3); \
                        } \
                        if (randomVar4 > 5) { \
                            int r = randomVar4 / 2; \
                            do { \
                                JUNK_CODE_FUNCTION_5(); \
                                r -= 1; \
                            } while (r > 0); \
                        } \
                    } \
                    } \
                } while (a < 20); \
            } \
            \
            if (randomVar2 > 40) { \
                int b = randomVar2 / 5; \
                do { \
                    for (int q = 0; q < N; ++q) { \
                        int randomVar4 = 7; \
                        for (int p = 0; p < 2; ++p) { \
                            int t = p + 1; \
                            do { \
                                t += 1; \
                                if (t == 2) { \
                                    JUNK_CODE_FUNCTION_5(); \
                                    int innerVar1 = t * randomVar4 / 2; \
                                } \
                            } while (t < 3); \
                        } \
                        if (randomVar4 > 5) { \
                            int r = randomVar4 / 2; \
                            do { \
                                JUNK_CODE_FUNCTION_5(); \
                                r -= 1; \
                            } while (r > 0); \
                        } \
                    } \
                    b -= 3; \
                } while (b > 0); \
            } \
            \
                    for (int q = 0; q < N; ++q) { \
                        int randomVar4 = 7; \
                        for (int p = 0; p < 2; ++p) { \
                            int t = p + 1; \
                            do { \
                                t += 1; \
                                if (t == 2) { \
                                    JUNK_CODE_FUNCTION_5(); \
                                    int innerVar1 = t * randomVar4 / 2; \
                                } \
                            } while (t < 3); \
                        } \
                        if (randomVar4 > 5) { \
                            int r = randomVar4 / 2; \
                            do { \
                                JUNK_CODE_FUNCTION_5(); \
                                r -= 1; \
                            } while (r > 0); \
                        } \
                    } \
        } \
        } \
    } \


__forceinline void Junk()
{
    std::string(crypt(" "));
    JUNK_CODE(500);
}
