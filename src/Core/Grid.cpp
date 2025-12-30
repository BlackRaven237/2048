#include "Core/Grid.h"

Grid::Grid(Coord2D pos, float width) : mPosition(pos), mWidth(width), mColor(Color::Gainsboro()) {}

void Grid::Initialize(int NumberofCells, int NumberofTiles) {
    mCells.clear();
    mTiles.clear();

    float size = (mWidth * 0.95) / 4;
    float margin = (mWidth * 0.05) / 5;

    for(int i=0; i<NumberofCells; ++i) {
        mCells.push_back(Cell(i, size));
    }
    SetCellsPosition(size, margin);

    for(int i=0; i<NumberofTiles; ++i) {
        Coord2D position(mCells[i].position);
        mCells[i].ChangeState();
        mTiles.push_back(Tile(position, i, i, size));
    }
}

void Grid::SetCellsPosition(float size, float margin) {
    float x = 0.0f, y = mPosition.y + margin;
    int cellIndex = 0;
    for (int row=0; row<4; ++row) {
        x = mPosition.x + margin;
        for (int column=0; column<4; ++column) {
            cellIndex = CalculateCellIndex(row, column);
            mCells[cellIndex].position = Coord2D(x, y);
            // move to the x-coordinate of next cell (horizontally)
            x += size + margin;
        }
        // move to the y-coordinate of next cell (vertically)
        y += size + margin;
    }
}

void Grid::Update() {
    for (auto& tile : mTiles) {
        tile.Update(mCells);
    }
}

void Grid::MoveTiles(Key key) {
    for (auto& tile : mTiles) {
        tile.Move(key);
    }
}

void Grid::Render(SDL_Renderer* renderer) {
    SDL_FRect Grid = {
        mPosition.x,
        mPosition.y,
        mWidth,
        mWidth
    };
    SDL_SetRenderDrawColor(renderer, mColor.red, mColor.green, mColor.blue, 255);
    SDL_RenderFillRect(renderer, &Grid);

    for(auto& cell : mCells) {
        cell.Render(renderer);
    }

    for(auto& tile : mTiles) {
        tile.Render(renderer);
    }
}

int Grid::CalculateCellIndex(int row, int column) {
    return row * 4 + column;
}

int Grid::GenerateRandomIndex() {
    std::uniform_int_distribution<int> dist(0, 15);
    return dist(mRandomGenerator);
}