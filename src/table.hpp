#ifndef _TABLE_HPP_
#define _TABLE_HPP_

class Table
{
private:
    int _row;
    int _column;
    vector<vector<int> > _table;
public:
    Table(int row, int column) : _row(row), _column(column) {
        _table.resize(row);
        for (int i=0; i<row; ++i) {
            _table[i].resize(column);
        }
    }
    /* 
     * 
     */
    inline vector<vector<int> > GetTable() {
        return _table;
    }
    inline int GetVal(int DesPos, int OutChan) {
        return _table[DesPos][OutChan];
    }
    inline int GetRow() {
        return _row;
    }
    inline int GetColumn() {
        return _column;
    }
};

#endif