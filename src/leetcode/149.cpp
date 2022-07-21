//
// 149.cpp
// Created by AUGUS on 2022/7/18.
// Max Points on a Line
//

#include <vector>

namespace leetcode {
    int maxPoints(std::vector<std::vector<int>> &points) {
        if (points.size() <= 2) {
            return points.size();
        }

        int res = 2;
        long abx, aby, bcx, bcy;
        for (int i = 0; i < points.size(); i++) {
            int duplicate = 0;
            int sameSlope = 1;
            for (int j = i + 1; j < points.size(); j++) {
                abx = points[i][0] - points[j][0];
                aby = points[i][1] - points[j][1];

                if (abx == 0 && aby == 0) {
                    // duplicate points
                    duplicate++;
                } else {
                    // same slope
                    sameSlope++;
                    for (int k = j + 1; k < points.size(); k++) {
                        bcx = points[j][0] - points[k][0];
                        bcy = points[j][1] - points[k][1];
                        if (abx * bcy == aby * bcx) {
                            // 3 points in line
                            sameSlope++;
                        }
                    }
                }
                res = std::max(res, duplicate + sameSlope);
                sameSlope = 1;
            }
        }
        return res;
    }
}

int main() { return 1; }