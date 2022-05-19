#include <optional>
#include <algorithm>
#include <random>
#include <array>

using namespace std;

class RubiksCubeTTT {
    private:
        /*
        Cube Faces(initial positions):
           [4]
        [3][2][1][0]
           [5]
        Face Space Positions:
        [0][1][2]
        [3][4][5]
        [6][7][8]
        x = true
        o = false
        */
        std::array<std::array<bool, 9>, 6> cubeFaces;

        void generateFaces();
        void generateFace(int face);

        optional<bool> checkFaceWin(int face);

        void rotateSectionUp(int col);
        void rotateSectionDown(int col);
        void rotateSectionLeft(int row);
        void rotateSectionRight(int row);
        void rotateFaceC(int face);
        void rotateFaceCC(int face);
    public:
        RubiksCubeTTT();

        std::array<bool, 9> getFace(int face);
        std::array<std::array<bool,9>, 6> getFaces();
        void rotate(int dir);
        void rotateSections(int space, int dir);
        optional<bool> winner();
};