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
        mCells[row][column].SetOccupied(true);
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

    SpawnNewTiles(cellSize);
}

void Grid::Update(float deltaTime) {
    for (auto& tile : mTiles) {
        tile.Move(mCells[tile.tileRow][tile.tileColumn].position, deltaTime);
    }

    for (auto& row : mCells) {
        for (auto& cell : row) {
            cell.SetOccupied(false);
        }
    }

    for (auto& tile : mTiles) {
        mCells[tile.tileRow][tile.tileColumn].SetOccupied(true);
    }
}

void Grid::SpawnNewTiles(float size) {
    if (mTiles.size() >= mMaxTiles - 1) return;
    int row, column;
    bool check = true;

    do {
        row = GenerateRandomIndex(), column = GenerateRandomIndex();
        if (!mCells[row][column].GetState()) check = false;
    } while(check);
    mCells[row][column].SetOccupied(true);

    mTiles.push_back(Tile(Point(mCells[row][column].position), row, column, size));

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

    for(auto& row : mCells) {
        for (auto& cell : row) {
            cell.Render(renderer);
        }
    }

    for(auto& tile : mTiles) {
        tile.Render(renderer);
    }
}

void Grid::Clear() {
    mTiles.clear();
    mCells.clear();
}

int Grid::GenerateRandomIndex() {
    return rand() % 4;
}

Tile* Grid::getTileAt(int row, int column) {
    for(auto& tile : mTiles) {
        if (tile.tileRow == row && tile.tileColumn == column) {
            return &tile;
        }
    }
    return nullptr;
}

std::vector<Tile*> Grid::CollectTilesinRow(const std::vector<Cell>& row) {
    // Collecting tiles from occupied cells
    std::vector<Tile*> RowTiles;
    for (const auto& cell : row) {
        Tile* tile = getTileAt(cell.cellRow, cell.cellColumn);
        if (tile) {
            RowTiles.push_back(tile);
        }
    }

    return RowTiles;
}

void Grid::slideLeft() {
    for(auto& row : mCells) {
        std::vector<Tile*> rowTiles = CollectTilesinRow(row);
        for (size_t i = 0; i < rowTiles.size(); ++i) {
            rowTiles[i]->tileColumn = i; 
        }
    }
}

void Grid::slideRight() {
    for(auto& row : mCells) {
        std::vector<Tile*> rowTiles = CollectTilesinRow(row);
        int targetColumn = 3;
        for (int i = (int)rowTiles.size() - 1; i>=0; --i) {
            rowTiles[i]->tileColumn = targetColumn;
            targetColumn--;
        }
    }
}

void Grid::slideUp() {
    std::vector<std::vector<Cell>> TransposedCells = Transpose();

    for (auto& col : TransposedCells) {
        std::vector<Tile*> colTiles = CollectTilesinRow(col);
        for (size_t i = 0; i < colTiles.size(); ++i) {
            colTiles[i]->tileRow = i;
        }
    }
}

std::vector<std::vector<Cell>> Grid::Transpose() {
    std::vector<std::vector<Cell>> Transposed;
    for(int j=0; j < (int)mCells.size(); ++j) {
        std::vector<Cell> column;
        for(int i=0; i < (int)mCells.size(); ++i) {
            column.push_back(mCells[i][j]);
        }
        Transposed.push_back(column);
    }
    return Transposed;
}

void Grid::slideDown() {
    std::vector<std::vector<Cell>> TransposedCells = Transpose();

    for (auto& col : TransposedCells) {
        std::vector<Tile*> colTiles = CollectTilesinRow(col);
        int targetColumn = 3;
        for (int i = (int)colTiles.size() - 1; i >= 0; --i) {
            colTiles[i]->tileRow = targetColumn;
            targetColumn--;
        }
    }
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