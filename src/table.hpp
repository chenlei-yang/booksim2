#ifndef _TABLE_HPP_
#define _TABLE_HPP_

#include "OutputChannel.h"
#include <vector>

class Table {
private:
    int m_row;
    int m_column;
    std::vector<std::vector<int> > m_table;
public:
    Table(int row, int column) : m_row(row), m_column(column) {
        m_table.resize(row);
        for (int i=0; i<row; ++i) {
            m_table[i].resize(column);
        }
    }
    int LoadFromFile(std::string filename) {
        freopen(filename.c_str(), "r", stdin);
        for (int i=0; i<m_row; ++i) {
            for (int j=0; j<m_column; ++j) {
                scanf("%d", &m_table[i][j]);
            }
        }
        fclose(stdin);
        return 0;
    }
    int SaveToFile(std::string filename) {
        freopen(filename.c_str(), "w", stdout);
        for (int i = 0; i < m_row; ++i) {
            for (int j = 0; j < m_column; ++j) {
                printf("%d ", m_table[i][j]);
            }
            printf("\n");
        }
        fclose(stdout);
        return 0;
    }
    inline int SetValue(int r, int c, int val) {
      if (!(0 <= r && r < m_row))
        return -1;
      if (!(0 <= c && c < m_column))
        return -1;
      m_table[r][c] = val;
      return 0;
    }
    inline void AverageValue(int r, int c, int val) {
        if (!(0<=r && r<m_row)) return;
        if (!(0<=c && c<m_column)) return;
        if (m_table[r][c] == 0) m_table[r][c] = val;
        else m_table[r][c] = m_table[r][c] * 0.5 + val * 0.5;
        // else m_table[r][c] = (m_table[r][c] + val) / 2;
    }

    inline void AverageValueHara(int r, int c, int val) {
        if (!(0<=r && r<m_row)) return;
        if (!(0<=c && c<m_column)) return;
        auto alpha = 0.5;
        m_table[r][c] = (1 - alpha) * m_table[r][c] + alpha * val;
    }

    inline void AverageValueHaraStep(int r, int c, int By, int minQy) {
        if (!(0<=r && r<m_row)) return;
        if (!(0<=c && c<m_column)) return;
        auto alpha = 0.5;
        // Qx(d,y)=(1−α)Qx(d,y)+α(By+minQy(d,z))
        m_table[r][c] = (1 - alpha) * m_table[r][c] + alpha * (By + minQy);
    }
    inline std::vector<std::vector<int> > GetTable() {
        return m_table;
    }
    inline int GetVal(int r, int c) {
        if (!(0<=r && r<m_row)) return -1;
        if (!(0<=c && c<m_column)) return -1;
        return m_table[r][c];
    }
    inline int GetRowSize() {
        return m_row;
    }
    inline int GetColumnSize() {
        return m_column;
    }
    inline void show() {
        for (int i=0; i<m_row; ++i) {
            for (int j=0; j<m_column; ++j) {
                printf("%d\t", m_table[i][j]);
            }
            printf("\n");
        }
    }
};

#endif