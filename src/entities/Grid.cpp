#include "Grid.h"
#include <algorithm>

Grid::Grid(float size, Vector2D position) : 
    Square(size, position), mRandomGenerator(std::random_device{}()) {}

void Grid::Initialize() {
    mCells.clear();
    mTiles.clear();

    InitializeCells();

    for(int i=0; i<2; ++i) {
        AddNewTile(cellSize);
    }
}

void Grid::InitializeCells() {
    cellSize = (size * 0.95) / 4;

    float margin = (size * 0.05) / 5;
    float x = 0.0f;
    float y = position.y + margin;

    for (int row=0; row<4; ++row) {
        std::vector<Cell> _row; // create new row
        x = position.x + margin;

        for (int column=0; column<4; ++column) {
            Vector2D position = Vector2D(x, y);
            _row.push_back(Cell(row, column, cellSize, position)); // Add cells to row
            x += cellSize + margin;
        }

        mCells.push_back(_row);  // Add the row to mCells
        y += cellSize + margin;
    }
}

void Grid::MoveTiles(Key direction) {
    bool moved = false;
    switch (direction) {
        case Key::UP:    moved = slideUp();     break;
        case Key::DOWN:  moved = slideDown();   break;
        case Key::LEFT:  moved = slideLeft();   break;
        case Key::RIGHT: moved = slideRight();  break;
        default: break;
    }

    if (moved) {
        RemoveDeadTiles(); // Clean-up all dead cells
        UpdateOccupiedCells(); // Update cells status
        AddNewTile(cellSize); // Add a new tile

        if (IsGameOver()) SDL_Log("Game Over! Final Score: %d", m_AccumulatedScore);
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
    for (const auto& tile : mTiles) {
        mCells[tile->row][tile->column].SetOccupied(true);
    }
}

void Grid::Update(float deltaTime) {
    for (const auto& tile : mTiles) {
        tile->Move(mCells[tile->row][tile->column].position, deltaTime);
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
    mTiles.push_back(std::make_unique<Tile>(value, mCells[row][column].position, row, column, size));
}

void Grid::RemoveDeadTiles() {
    mTiles.erase(
        std::remove_if(mTiles.begin(), mTiles.end(),
            [](const std::unique_ptr<Tile>& t) { 
                return t->GetValue() == 0; 
            }),
        mTiles.end()
    );
}

void Grid::render(SDL_Renderer* renderer) {
    color = Color::Gainsboro();

    SDL_FRect Grid = {
        position.x,
        position.y,
        size,
        size
    };

    SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, 255);
    SDL_RenderFillRect(renderer, &Grid);

    for(auto& row : mCells) {
        for (auto& cell : row) {
            cell.render(renderer);
        }
    }

    for(const auto& tile : mTiles) {
        tile->render(renderer);
    }

    //renderer->RenderText("Score: " + std::to_string(m_AccumulatedScore), m_position.x, m_position.y - 100.0f, Color(118, 110, 101));
}

void Grid::Reset() {
    mTiles.clear();
    m_AccumulatedScore = 0;

    for (auto& row : mCells) {
        for (auto& cell : row) {
            cell.SetOccupied(false);
        }
    }
}

bool Grid::IsGameOver() {
    // If we have fewer than 16 tiles, the game definitely isn't over.
    if (mTiles.size() < mMaxTiles) {
        return false;
    }

    // Checks for any possible horizontal or vertical merges.
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            Tile* current = GetTileAt(r, c);
            if (!current) continue;

            // Check neighbor to the RIGHT
            if (c < 3) {
                Tile* rightNeighbor = GetTileAt(r, c + 1);
                if (rightNeighbor && current->GetValue() == rightNeighbor->GetValue()) {
                    return false; // A horizontal merge is possible
                }
            }

            // Check neighbor BELOW
            if (r < 3) {
                Tile* downNeighbor = GetTileAt(r + 1, c);
                if (downNeighbor && current->GetValue() == downNeighbor->GetValue()) {
                    return false; // A vertical merge is possible
                }
            }
        }
    }

    return true; 
}

bool Grid::CheckWin() {
    for (const auto& tile : mTiles) {
        if (tile->GetValue() == 2048) return true;
    }
    return false;
}

Tile* Grid::GetTileAt(int row, int column) {
    for(auto& tile : mTiles) {
        if (tile->row == row && tile->column == column) {
            return tile.get();
        }
    }
    return nullptr;
}
    
bool Grid::Merge(std::vector<Tile*>& row) {
    bool merged = false;
    if (row.size() < 2) return false;

    for(size_t i=0; i+1 < row.size(); ++i) {
        if(row[i]->GetValue() == row[i+1]->GetValue()) {
            int newValue = row[i]->GetValue() * 2;
            row[i]->SetValue(newValue);
            m_AccumulatedScore += newValue; // Calculates score after each merge

            row[i+1]->SetValue(0);

            row.erase(row.begin() + i + 1);
            merged = true;
        }
    }
    return merged;
}

std::vector<Tile*> Grid::Compressed(const std::vector<Cell>& row) {
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
        std::vector<Tile*> rowTiles = Compressed(row);
        if(rowTiles.empty()) continue;

        if(Merge(rowTiles)) moved = true;

        for (int i = 0; i < (int)rowTiles.size(); ++i) {
            if (rowTiles[i]->column != i) {
                rowTiles[i]->column = i;
                moved = true;
            }
        }
    }
    return moved;
}

bool Grid::slideRight() {
    bool moved = false;
    for(auto& row : mCells) {
        std::vector<Tile*> rowTiles = Compressed(row);
        if(rowTiles.empty()) continue;

        std::reverse(rowTiles.begin(), rowTiles.end());
        if(Merge(rowTiles)) moved = true;

        int targetColumn = 3;
        for (int i=0; i < (int)rowTiles.size(); ++i) {
            if((int)rowTiles[i]->column != targetColumn) {
                rowTiles[i]->column = targetColumn;
                moved = true;
            }
            targetColumn--;
        }
    }
    return moved;
}

bool Grid::slideUp() {
    std::vector<std::vector<Cell>> TransposedCells = Transpose();
    bool moved = false;
    for (auto& col : TransposedCells) {
        std::vector<Tile*> colTiles = Compressed(col);
        if(colTiles.empty()) continue;

        if(Merge(colTiles)) moved = true;

        for (int i = 0; i < (int)colTiles.size(); ++i) {
            if(colTiles[i]->row != i) {
                colTiles[i]->row = i;
                moved = true;
            }
        }
    }
    return moved;
}

bool Grid::slideDown() {
    std::vector<std::vector<Cell>> TransposedCells = Transpose();
    bool moved = false;
    for (auto& col : TransposedCells) {
        std::vector<Tile*> colTiles = Compressed(col);

        if(colTiles.empty()) continue;

        std::reverse(colTiles.begin(), colTiles.end());
        if(Merge(colTiles)) moved = true;

        int targetColumn = 3;
        for (size_t i=0; i < colTiles.size(); ++i) {
            if((int)colTiles[i]->row != targetColumn) {
                colTiles[i]->row = targetColumn;
                moved = true;
            }
            targetColumn--;
        }
    }

    return moved;
}