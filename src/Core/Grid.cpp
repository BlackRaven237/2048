#include "Core/Grid.h"
#include <cstdlib>
#include <ctime>

Grid::Grid(Coord2D pos, float width) : 
    mWidth(width), mMaxTiles(16), mColor(Color::Gainsboro()), 
    mPosition(pos) {}

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
        int r = GenerateRandomIndex(), c = GenerateRandomIndex();
        int index = CalculateCellIndex(r, c);
        mCells[index].ChangeState();

        mTiles.push_back(Tile(Coord2D(mCells[index].position), r, c, size));
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

void Grid::MoveTiles(Key key) {
        // switch (key)
        // {
        // case Key::UP:

        //     break;
        // case Key::DOWN:
        //     for (int i=3; i>0; i--) {
        //         for (int j=3; j>0; j--) {
        //             int idx = CalculateCellIndex(i, j);
        //             mTiles[idx].Move(mCells, key);
        //         }
        //     }
        //     break;
        // case Key::LEFT:
        //     for (int j=0; j<3; j++) {
        //         for (int i=3; i>=0; i--) {
        //             int idx = CalculateCellIndex(i, j);
        //             mTiles[idx].Move(mCells, key);
        //         }
        //     }
        //     break;
        // case Key::RIGHT:
        //     for (int j=3; j>=0; j--) {
        //         for (int i=0; i<3; i++) {
        //             int idx = CalculateCellIndex(i, j);
        //             mTiles[idx].Move(mCells, key);
        //         }
        //     }
        //     break;
        // }
    if (key == Key::UP || key == Key::LEFT) {
        for (auto& tile : mTiles) {
            tile.Move(mCells, key);
        }
    }
    if (key == Key::DOWN) {
        for (int i=3; i>=0; i--) {
            for (int j=3; j>=0; j--) {
                int idx = CalculateCellIndex(i, j);
                mTiles[idx].Move(mCells, key);
            }
        }
    }
        if (key == Key::RIGHT) {
        for (int i=0; i<3; i++) {
            for (int j=3; j>0; j--) {
                int idx = CalculateCellIndex(i, j);
                mTiles[idx].Move(mCells, key);
            }
        }
    }
    SpawnNewTiles(mCells[0].size);
}

void Grid::Update() {
    for (auto& tile : mTiles) {
        tile.Update(mCells);
    }
}

void Grid::SpawnNewTiles(float size) {
    if (mTiles.size() > mMaxTiles - 1) return;
    int idx, r, c;
    bool check = true;

    do {
        r = GenerateRandomIndex(), c = GenerateRandomIndex();
        idx = CalculateCellIndex(r, c);
        if (!mCells[idx].GetState()) check = false;
    } while(check);
    mCells[idx].ChangeState();

    mTiles.push_back(Tile(Coord2D(mCells[idx].position), r, c, size));
    uint8_t red=135, g=130, b=120;
    for (int i=2; i<mTiles.size(); i++) {
        mTiles[i].color = Color(red, g, b);
        red = red + 35;
        g = g + 30;
        b = b + 20;
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
    // std::uniform_int_distribution<int> dist(0, 3);
    // return dist(mRandomGenerator);
    return rand() % 4;
}