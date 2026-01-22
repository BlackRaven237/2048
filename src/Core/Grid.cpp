#include "Core/Grid.h"
#include <cstdlib>
#include <ctime>
#include <utility>

Grid::Grid(Point position, float width) : 
    mWidth(width), mMaxTiles(16), mColor(Color::Gainsboro()), 
    m_position(position), cellSize((mWidth * 0.95) / 4) {}

void Grid::Initialize(int NumberofCells, int NumberofTiles) {
    mCells.clear();
    mTiles.clear();

    float margin = (mWidth * 0.05) / 5;

    for(int i=0; i<NumberofCells; ++i) {
        std::vector<Cell> row; // create a new row
        for (int j=0; j<NumberofCells; ++j) {
            row.push_back(Cell(i, j, cellSize)); // Add cells to row
        }
        mCells.push_back(row); // Add the row to mCells
    }
    InitializeCellsPosition();

    for(int i=0; i<NumberofTiles; ++i) {
        int row = GenerateRandomIndex(), column = GenerateRandomIndex();
        mCells[row][column].ChangeState();
        mTiles.push_back(
            Tile(
                Point(mCells[row][column].position), 
                row,
                column, 
                cellSize
            )
        );
    }
}

void Grid::InitializeCellsPosition() {
    float margin = (mWidth * 0.05) / 5;
    float x = 0.0f, y = m_position.y + margin;
    for (int row=0; row<4; ++row) {
        x = m_position.x + margin;
        for (int column=0; column<4; ++column) {
            // move to the x-coordinate of next cell (horizontally)
            mCells[row][column].position = Point(x, y);
            x += cellSize + margin;
        }
        // move to the y-coordinate of next cell (vertically)
        y += cellSize + margin;
    }
}

void Grid::MoveTiles(Key direction) {
    switch (direction) {
        case Key::UP: slideUp(); break;
        case Key::DOWN: slideDown(); break;
        case Key::LEFT: slideLeft(); break;
        case Key::RIGHT: slideRight(); break;
        default: break;
    }

    SpawnNewTiles(mCells[0][0].size);
}

void Grid::Update() {
    int n = (int)mCells.size();
    for (int row=0; row<n; ++row) {
        for (int cols=0; cols<n; ++cols) {
            //Coord new_coord = mCells[row][cols].GetCoord();
            int idx = CalculateCellIndex(row, cols);
            mTiles[idx].position = mCells[row][cols].position;
            //mTiles[idx].SetCoord(new_coord);
        }
    }
}

void Grid::SpawnNewTiles(float size) {
    if (mTiles.size() > mMaxTiles - 1) return;
    int r, c;
    bool check = true;

    do {
        r = GenerateRandomIndex(), c = GenerateRandomIndex();
        if (!mCells[r][c].GetState()) check = false;
    } while(check);
    mCells[r][c].ChangeState();

    mTiles.push_back(Tile(Point(mCells[r][c].position), r, c, size));

    uint8_t red=135, g=130, b=120;
    for (size_t i=2; i<mTiles.size(); i++) {
        mTiles[i].color = Color(red, g, b);
        red = red + 35;
        g = g + 30;
        b = b + 20;
    }
}

void Grid::Render(SDL_Renderer* renderer) {
    SDL_FRect Grid = {
        m_position.x,
        m_position.y,
        mWidth,
        mWidth
    };
    SDL_SetRenderDrawColor(renderer, mColor.red, mColor.green, mColor.blue, 255);
    SDL_RenderFillRect(renderer, &Grid);

    for(auto& cell : mCells) {
        for (int i=0; i<4; i++) {
            cell[i].Render(renderer);
        }
    }

    for(auto& tile : mTiles) {
        tile.Render(renderer);
    }
}

int Grid::CalculateCellIndex(int row, int column) {
    return row * 4 + column;
}

int Grid::GenerateRandomIndex() {
    // std::uniform_int_distribution<int> dist(0, 3);
    // return dist(mRandomGenerator);
    return rand() % 4;
}


std::vector<Cell> Grid::slideRow(const std::vector<Cell>& row) {
    std::vector<Cell> newRow;
    std::vector<Cell> emptyCells;

    for (auto cell : row) {
        // Collecting only cells which are occupied
        if(cell.GetState()) {
            newRow.push_back(cell);
        } else {
            emptyCells.push_back(cell);
        }
    }

    for (auto& cell : emptyCells) {
        newRow.push_back(cell);
    }

    return newRow;
}

void Grid::slideLeft() {
    for(auto& row : mCells) {
        row = slideRow(row);
    }
}

void Grid::slideRight() {
    for(auto& row : mCells) {
        //std::cout << "cell position before reverse: (" << coord.row << ", " << coord.column << ")" << std::endl;
        reverse(row.begin(), row.end());
        //std::cout << "cell position after reverse: (" << coord.row << ", " << coord.column << ")" << std::endl;
        row = slideRow(row);
        reverse(row.begin(), row.end());
    }
}

void Grid::slideUp() {
    showCells();
    Transpose();
    showCells();

    slideRight();
    Transpose();
    showCells();
}

void Grid::slideDown() {
    showCells();
    Transpose();
    showCells();

    slideLeft();
    Transpose();
    showCells();
}

void Grid::Transpose() {
    size_t n = mCells.size();
    for(size_t i=0; i<n; ++i) {
        for(size_t j=i+1; j<n; ++j) {
            // swapping the i-th row with the j-th column
            std::swap(mCells[i][j], mCells[j][i]);
        }
    }
}

void Grid::Reverse(std::vector<Cell>& row) {

}

void Grid::showCells() {
    std::cout << "current cell position" << std::endl;

    for (auto& row : mCells) {
        for (auto& cell : row) {
            std::cout << "[" << cell.cellRow << ", " << cell.cellColumn << "]";
        }
        std::cout << std::endl;
    }
    std::cout << "\n";
}