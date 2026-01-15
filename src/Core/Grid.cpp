#include "Core/Grid.h"
#include <cstdlib>
#include <ctime>

Grid::Grid(Point pos, float width) : 
    mWidth(width), mMaxTiles(16), mColor(Color::Gainsboro()), 
    m_position(pos) {}

void Grid::Initialize(int NumberofCells, int NumberofTiles) {
    mCells.clear();
    mTiles.clear();

    float size = (mWidth * 0.95) / 4;
    float margin = (mWidth * 0.05) / 5;

    for(int i=0; i<NumberofCells; ++i) {
        std::vector<Cell> row; // create a new row
        for (int j=0; j<NumberofCells; ++j) {
            row.push_back(Cell(Coord(i, j), size)); // Add cells to row
        }
        mCells.push_back(row); // Add the row to mCells
    }
    SetCellsPosition(size, margin);

    for(int i=0; i<NumberofTiles; ++i) {
        int row = GenerateRandomIndex(), column = GenerateRandomIndex();
        row = i+1, column = i;
        mCells[row][column].ChangeState();
        mTiles.push_back(
            Tile(
                Point(mCells[row][column].position), 
                Coord(mCells[row][column].GetCoord()), 
                size
            )
        );
    }
}

void Grid::SetCellsPosition(float size, float margin) {
    float x = 0.0f, y = m_position.y + margin;
    for (int row=0; row<4; ++row) {
        x = m_position.x + margin;
        for (int column=0; column<4; ++column) {
            // move to the x-coordinate of next cell (horizontally)
            mCells[row][column].position = Point(x, y);
            x += size + margin;
        }
        // move to the y-coordinate of next cell (vertically)
        y += size + margin;
    }
}

void Grid::MoveTiles(Key key) {
    for (auto tile : mTiles) {
        tile.Move(mCells[0], key);
    }
    SpawnNewTiles(mCells[0][0].size);
}

void Grid::Update() {
    for (auto& tile : mTiles) {
        tile.Update(mCells[0]);
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

    mTiles.push_back(Tile(Point(mCells[r][c].position), Coord(r, c), size));
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