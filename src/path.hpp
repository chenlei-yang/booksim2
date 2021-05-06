#ifndef PATH_HPP
#define PATH_HPP

#include <vector>
#include "flit.hpp"
#include "routers/router.hpp"
#include "hara.hpp"

class Step {
private:
  int _rid;
  int _vc;
  int _outport;
  int _time;
  int _pos;
  int _minQy;
public:
  Step(const Router* r, int out_port, int vc, int time, const Flit* f) {
    _rid = r->GetID();
    _vc = vc;
    _outport = out_port;
    _time = time;
  }
  Step(const Router* r, int pos, int minQy, int out_port, int vc, int time, const Flit* f) {
    _rid = r->GetID();
    _pos = pos;
    _minQy = minQy;
    _vc = vc;
    _outport = out_port;
    _time = time;
  }
  int RID() {
    return _rid;
  }
  int VC() {
    return _vc;
  }
  int OutPort() {
    return _outport;
  }
  int Time() {
    return _time;
  }
  int Pos() {
    return _pos;
  }
  int MinQy() {
    return _minQy;
  }
};

class Path {
private:
    int size;
    int id;
    int src;
    int dest;
    std::vector<Step> _path;

public:
    Path() {
      _path.clear();
      size = 0;
    }

    Path(const Router* r, int out_port, int vc, int time, const Flit *f) {
      size = 0;
      _path.clear();
      Add(r, out_port, vc, time, f);
    }

    Path(const Router* r, int pos, int out_port, int minQy, int vc, int time, const Flit *f) {
      size = 0;
      _path.clear();
      Add(r, pos, minQy, out_port, vc, time, f);
    }

    void Add(Step s) {
      _path.push_back(s);
      size++;
    }

    void Add(const Router* r, int out_port, int vc, int time, const Flit *f) {
      Step s(r, out_port, vc, time, f);
      id = f->id;
      src = f->src;
      dest = f->dest;
      Add(s);
    }

    void Add(const Router* r, int pos, int minQy, int out_port, int vc, int time, const Flit *f) {
      Step s(r, pos, minQy, out_port, vc, time, f);
      id = f->id;
      src = f->src;
      dest = f->dest;
      Add(s);
    }

    int InChannel() {
      int sz = _path.size();
      if (sz >= 1) {
        int port = _path[sz-1].OutPort();
        int vc = _path[sz-1].VC();
        if (port == Port::W) return HaraCh::E;
        if (port == Port::E) return HaraCh::W;
        if (port == Port::N) {
          if (vc == 0) return HaraCh::S1;
          return HaraCh::S2;
        }
        if (port == Port::S) {
          if (vc == 0) return HaraCh::N1;
          return HaraCh::N2;
        }
      }
      return HaraCh::L;
    }

    void Show() {
      int sz = _path.size();
      if (sz == 0) {
        return;
      }
      int x = _path[0].RID() / 8;
      int y = _path[0].RID() % 8;
      printf("path(id = %d from (%d,%d) to (%d,%d)): (%d,%d)(%s)", id, src / 8,
             src % 8, dest / 8, dest % 8, x, y,
             Port::get_hara_ch(_path[0].OutPort(), _path[0].VC()).c_str());
      for (int i = 1; i < sz; ++i) {
        x = _path[i].RID() / 8;
        y = _path[i].RID() % 8;
        printf("->(%d,%d)(%s)", x, y,
               Port::get_hara_ch(_path[i].OutPort(), _path[i].VC()).c_str());
      }
      printf("->(%d,%d)\n",dest / 8, dest % 8);
    }

    void Update(vector<Router *> router) {
      int sz = _path.size();
      for (int i = 0; i < sz - 1; ++i) {
        router[_path[i].RID()]->UpdateTable(_path[i+1].RID(), _path[i].OutPort(), _path[i+1].Time() - _path[i].Time());
      }
    }

    void UpdateHara(vector<Router *> router) {
      int sz = _path.size();
      for (int i = 0; i < sz - 1; ++i) {
        for (int j = i + 1; j < sz - 1; ++j) {
          router[_path[i].RID()]->UpdateTableHara(
              _path[j].RID(), Port::port2ch(_path[i].OutPort(), _path[i].VC()),
              _path[j].Time() - _path[i].Time());
        }
      }
    }

    void UpdateHaraStep(Router* r, int pos) {
      int sz = _path.size();
    }
};

#endif