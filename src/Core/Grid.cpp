#include "Core/Grid.h"

Grid::Grid(Vector2D position, float width) : 
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
                mCells[row][column].position, 
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
            mCells[row][column].position = Vector2D(x, y);
            x += cellSize + margin;
        }
        // move to the y-coordinate of next cell (vertically)
        y += cellSize + margin;
    }
}

void Grid::MoveTiles(Key direction) {
    switch (direction) {
        case Key::UP: slideUp(); return;
        case Key::DOWN: slideDown(); return;
        case Key::LEFT: slideLeft(); return;
        case Key::RIGHT: slideRight(); return;
        default: break;
    }
}

void Grid::Update(float deltaTime) {
    for (auto& tile : mTiles) {
        tile.Move(mCells[tile.row][tile.column].position, deltaTime);
    }

    for (auto& row : mCells) {
        for (auto& cell : row) {
            cell.SetOccupied(false);
        }
    }

    for (auto& tile : mTiles) {
        mCells[tile.row][tile.column].SetOccupied(true);
    }

    SpawnNewTiles(cellSize);
}

void Grid::SpawnNewTiles(float size) {
    if (mTiles.size() >= mMaxTiles) return;

    // Collecting the row and column of empty cells
    std::vector<std::pair<int, int>> emptyCells;
    for (auto& row : mCells) {
        for (auto& cell : row) {
            if (!cell.isOccupied()) emptyCells.push_back({cell.row, cell.column});
        }
    }

    if (!emptyCells.empty()) {
        // Choosing a random pair in those empty cells
        int randomIndex = rand() % emptyCells.size();
        int row = emptyCells[randomIndex].first;
        int column = emptyCells[randomIndex].second;

        // Marks cell as occupied
        mCells[row][column].SetOccupied(true);

        // Creating a new tile 
        Tile newTile(Vector2D(mCells[row][column].position), row, column, size);

        newTile.color = Color(238, 228, 218);
        mTiles.push_back(newTile);
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
        if (tile.row == row && tile.column == column) {
            return &tile;
        }
    }
    return nullptr;
}

std::vector<Tile*> Grid::CollectTiles(const std::vector<Cell>& row) {
    // Collecting tiles from occupied cells
    std::vector<Tile*> RowTiles;
    for (const auto& cell : row) {
        Tile* tile = getTileAt(cell.row, cell.column);
        if (tile) {
            RowTiles.push_back(tile);
        }
    }

    return RowTiles;
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

void Grid::slideLeft() {
    for(auto& row : mCells) {
        std::vector<Tile*> rowTiles = CollectTiles(row);
        for (size_t i = 0; i < rowTiles.size(); ++i) {
            rowTiles[i]->column = i; 
        }
    }
}

void Grid::slideRight() {
    for(auto& row : mCells) {
        std::vector<Tile*> rowTiles = CollectTiles(row);
        int targetColumn = 3;
        for (int i = (int)rowTiles.size() - 1; i>=0; --i) {
            rowTiles[i]->column = targetColumn;
            targetColumn--;
        }
    }
}

void Grid::slideUp() {
    std::vector<std::vector<Cell>> TransposedCells = Transpose();

    for (auto& col : TransposedCells) {
        std::vector<Tile*> colTiles = CollectTiles(col);
        for (size_t i = 0; i < colTiles.size(); ++i) {
            colTiles[i]->row = i;
        }
    }
}

void Grid::slideDown() {
    std::vector<std::vector<Cell>> TransposedCells = Transpose();

    for (auto& col : TransposedCells) {
        std::vector<Tile*> colTiles = CollectTiles(col);
        int targetColumn = 3;
        for (int i = (int)colTiles.size() - 1; i >= 0; --i) {
            colTiles[i]->row = targetColumn;
            targetColumn--;
        }
    }
}