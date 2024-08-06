#include <iostream>
#include <cmath>
using namespace std;

// To obtain final Transformation Matrix
void multiplyMatrices(const double h1[4][4], const double h2[4][4], double H[4][4]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            H[i][j] = 0;
            for (int k = 0; k < 4; ++k) {
                H[i][j] += h1[i][k] * h2[k][j];
            }
        }
    }
}

// To simplify printing the final matrix
void printMatrix(const double mat[4][4]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    double x1 = 1, x2 = 2, x3 = 0.5, z1 = 2, z2 = 1.5, l4;
    double a1, a2, a3, a4 = 0, a5, a6;
    const double pi = 3.14159265358979323846;

    cout << "Enter The angles:" << endl;
    cout << "Angle 1 (in degrees): ";
    cin >> a1;
    cout << "Angle 2 (in degrees): ";
    cin >> a2;
    cout << "Angle 3 (in degrees): ";
    cin >> a3;
    // cout << "Angle 4 (in degrees): ";
    // cin >> a4;
    cout << "Angle 5 (in degrees): ";
    cin >> a5;
    cout << "Angle 6 (in degrees): ";
    cin >> a6;
    cout << "Enter value of length of prismatic joint: ";
    cin >> l4;

    // Conversion of degrees to radians
    a1 = (a1 / 180) * pi;
    a2 = (a2 / 180) * pi;
    a3 = (a3 / 180) * pi;
    a5 = (a5 / 180) * pi;
    a6 = (a6 / 180) * pi;

    // To whoever reads this:
    // Following is the rotation matrices of respective axes. Since there were multiple angles for the same matrix
    // and since I am dumb and cutting corners, bear with me.

    // Rotation matrices
    double xRot[3][3] = {
        {1, 0, 0},
        {0, cos(a6), -sin(a6)},
        {0, sin(a6), cos(a6)}
    };

    double y1Rot[3][3] = {
        {cos(a2), 0, sin(a2)},
        {0, 1, 0},
        {-sin(a2), 0, cos(a2)}
    };

    double y2Rot[3][3] = {
        {cos(a3), 0, sin(a3)},
        {0, 1, 0},
        {-sin(a3), 0, cos(a3)}
    };

    double y3Rot[3][3] = {
        {cos(a5), 0, sin(a5)},
        {0, 1, 0},
        {-sin(a5), 0, cos(a5)}
    };

    double zRot[3][3] = {
        {cos(a1), -sin(a1), 0},
        {sin(a1), cos(a1), 0},
        {0, 0, 1}
    };

    // New matrix multiplication as Transformation matrix h3 has two matrices in one
    double mul[3][3] = {0};
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 3; ++k) {
                mul[i][j] += xRot[i][k] * y3Rot[k][j];
            }
        }
    }

    // Transformation matrices
    double h1[4][4] = {
        {zRot[0][0], zRot[0][1], zRot[0][2], 0},
        {zRot[1][0], zRot[1][1], zRot[1][2], 0},
        {zRot[2][0], zRot[2][1], zRot[2][2], 0},
        {0, 0, 0, 1}
    };

    double h2[4][4] = {
        {y1Rot[0][0], y1Rot[0][1], y1Rot[0][2], x1},
        {y1Rot[1][0], y1Rot[1][1], y1Rot[1][2], 0},
        {y1Rot[2][0], y1Rot[2][1], y1Rot[2][2], z1},
        {0, 0, 0, 1}
    };

    double h3[4][4] = {
        {y2Rot[0][0], y2Rot[0][1], y2Rot[0][2], -x2},
        {y2Rot[1][0], y2Rot[1][1], y2Rot[1][2], 0},
        {y2Rot[2][0], y2Rot[2][1], y2Rot[2][2], z2},
        {0, 0, 0, 1}
    };

    double h4[4][4] = {
        {mul[0][0], mul[0][1], mul[0][2], l4},
        {mul[1][0], mul[1][1], mul[1][2], 0},
        {mul[2][0], mul[2][1], mul[2][2], 0},
        {0, 0, 0, 1}
    };

    double h5[4][4] = {
        {1, 0, 0, x3},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    };

    // Now to obtain the final Transformation matrix "H", we will multiply all 5 "h"
    double temp1[4][4], temp2[4][4], temp3[4][4], H[4][4];
    multiplyMatrices(h1, h2, temp1);
    multiplyMatrices(temp1, h3, temp2);
    multiplyMatrices(temp2, h4, temp3);
    multiplyMatrices(temp3, h5, H);

    cout << "X coordinate = " << H[0][3] << endl;
    cout << "Y coordinate = " << H[1][3] << endl;

    return 0;
}
