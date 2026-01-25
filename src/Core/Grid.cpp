#include "Core/Grid.h"

Grid::Grid(Vector2D position, float width) : 
    mWidth(width), mMaxTiles(16), m_color(Color::Gainsboro()), 
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
        int row = rand() % mCells.size();
        int column = rand() % mCells.size();
        
        mCells[row][column].SetOccupied(true);

        Tile newTile = Tile(mCells[row][column].position, row, column, cellSize);
        mTiles.push_back(newTile);
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
        case Key::UP: slideUp(); break;;
        case Key::DOWN: slideDown(); break;
        case Key::LEFT: slideLeft(); break;
        case Key::RIGHT: slideRight(); break;
        default: break;
    }

    UpdateOccupiedCells(); // Update cells status
    AddNewTile(cellSize); // Add a new tile
}

void Grid::UpdateOccupiedCells() {
    // Consider all cells are not occupied
    for (auto& row : mCells) {
        for (auto& cell : row) {
            cell.SetOccupied(false);
        }
    }
    // Set the occupation state only to occupied cells 
    for (auto& tile : mTiles) {
        mCells[tile.row][tile.column].SetOccupied(true);
    }
}

void Grid::Update(float deltaTime) {
    for (auto& tile : mTiles) {
        tile.Move(mCells[tile.row][tile.column].position, deltaTime);
    }
}

void Grid::AddNewTile(float size) {
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

void Grid::Render(Window* window) {
    SDL_FRect Grid = {
        m_position.x,
        m_position.y,
        mWidth,
        mWidth
    };
    SDL_SetRenderDrawColor(window->GetRenderer(), m_color.red, m_color.green, m_color.blue, 255);
    SDL_RenderFillRect(window->GetRenderer(), &Grid);

    for(auto& row : mCells) {
        for (auto& cell : row) {
            cell.Render(window->GetRenderer());
        }
    }

    for(auto& tile : mTiles) {
        tile.Render(window);
    }
}

void Grid::EmptyGrid() {
    // for (auto& tile : mTiles) {
    //     mTiles.pop_back();
    // }

    // for (auto& row : mCells) {
    //     for(auto& cell : row) {
    //         row.pop_back();
    //     }
    //     mCells.pop_back();
    // }
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