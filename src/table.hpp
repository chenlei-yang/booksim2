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
    inline std::vector<std::vector<int> > GetTable() {
        return m_table;
    }
    inline int GetVal(int DesPos, int OutChan) {
        return m_table[DesPos][OutChan];
    }
    inline int GetRowSize() {
        return m_row;
    }
    inline int GetColumnSize() {
        return m_column;
    }
};

#endif