#include "Core/Grid.h"

Grid::Grid(Vector2D position, float width) : 
    mWidth(width), mMaxTiles(16), m_color(Color::Gainsboro()), 
    m_position(position), cellSize((mWidth * 0.95) / 4),
    m_AccumulatedScore(0), mRandomGenerator(std::random_device{}()) {}

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
        std::uniform_int_distribution<int> index(0, (int)mCells.size() - 1);
        int row = index(mRandomGenerator);
        int column = index(mRandomGenerator);
        
        mCells[row][column].SetOccupied(true);

        Tile newTile = Tile(2, mCells[row][column].position, row, column, cellSize);
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
    bool moved = false;
    switch (direction) {
        case Key::UP: moved = slideUp(); break;
        case Key::DOWN: moved = slideDown(); break;
        case Key::LEFT: moved = slideLeft(); break;
        case Key::RIGHT: moved = slideRight(); break;
        default: break;
    }

    if (moved) {
        UpdateOccupiedCells(); // Update cells status
        AddNewTile(cellSize); // Add a new tile
    }
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
    int value;

    // Collecting the row and column of empty cells
    std::vector<std::pair<int, int>> emptyCells;
    for (auto& row : mCells) {
        for (auto& cell : row) {
            if (!cell.isOccupied()) emptyCells.push_back({cell.row, cell.column});
        }
    }

    if (emptyCells.empty()) return;
    
    // Choosing a random pair in those empty cells
    std::uniform_int_distribution<int> dist(0, (int)emptyCells.size() - 1);
    int randomIndex = dist(mRandomGenerator);
    int row = emptyCells[randomIndex].first;
    int column = emptyCells[randomIndex].second;

    // Marks cell as occupied
    mCells[row][column].SetOccupied(true);

    std::bernoulli_distribution dist2(0.15f); // 15% for '4' 
    if (dist2(mRandomGenerator)) {
        value = 4;
    } else {
        value = 2;
    }

    // Creating a new tile 
    Tile newTile(value, mCells[row][column].position, row, column, size);

    newTile.color = Color(238, 228, 218);
    mTiles.push_back(newTile);
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
    mTiles.clear();
    for (auto& row : mCells) {
        for (auto& cell : row) {
            cell.SetOccupied(false);
        }
    }
}

Tile* Grid::GetTileAt(int row, int column) {
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
        Tile* tile = GetTileAt(cell.row, cell.column);
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

bool Grid::slideLeft() {
    bool moved = false;
    for(auto& row : mCells) {
        std::vector<Tile*> rowTiles = CollectTiles(row);
        if(rowTiles.empty()) continue;

        for (size_t i = 0; i < rowTiles.size(); ++i) {
            rowTiles[i]->column = i; 
        }
        moved = true;
    }
    return moved;
}

bool Grid::slideRight() {
    bool moved = false;
    for(auto& row : mCells) {
        std::vector<Tile*> rowTiles = CollectTiles(row);
        if(rowTiles.empty()) continue;

        int targetColumn = 3;
        for (int i = (int)rowTiles.size() - 1; i>=0; --i) {
            rowTiles[i]->column = targetColumn;
            targetColumn--;
        }
        moved = true;
    }
    return moved;
}

bool Grid::slideUp() {
    std::vector<std::vector<Cell>> TransposedCells = Transpose();
    bool moved = false;
    for (auto& col : TransposedCells) {
        std::vector<Tile*> colTiles = CollectTiles(col);
        if(colTiles.empty()) continue;

        for (size_t i = 0; i < colTiles.size(); ++i) {
            colTiles[i]->row = i;
        }
        moved = true;
    }
    return moved;
}

bool Grid::slideDown() {
    std::vector<std::vector<Cell>> TransposedCells = Transpose();
    bool moved = false;
    for (auto& col : TransposedCells) {
        std::vector<Tile*> colTiles = CollectTiles(col);
        if(colTiles.empty()) continue;

        int targetColumn = 3;
        for (int i = (int)colTiles.size() - 1; i >= 0; --i) {
            colTiles[i]->row = targetColumn;
            targetColumn--;
        }
        moved = true;
    }
    return moved;
}