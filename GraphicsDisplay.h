#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include "subject.h"
#include "observer.h"
#include "state.h"
#include "info.h"
#include "window.h"

class GraphicsDisplay : public Observer<Info, State> {
    int n, width;
    Xwindow w;
  public:
    GraphicsDisplay(int n);
    void Winner(Colour c);
    void notify(Subject<Info, State> &whoFrom) override;
};

#endif
