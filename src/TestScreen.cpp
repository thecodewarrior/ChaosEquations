#include "TestScreen.h"

#include <facade/layer/RectLayer.h>
#include <liblib/Colors.h>

TestScreen::TestScreen() {
    auto rect = std::make_shared<facade::RectLayer>();
    rect->color = ll::colors::red;
    rect->size = {100, 100};
    rect->pos = {100, 100};
    rect->rotation = glm::radians(15.);
    rect->scale.y = 1.5;

    auto child = std::make_shared<facade::RectLayer>();
    child->color = ll::colors::blue;
    child->size = {50, 50};
    child->pos = {75, 25};

    rect->add(child);

    rect->on_update.connect([rect]() {
        rect->color = rect->mouse_over ? ll::colors::red : ll::colors::pink;
    });

    child->on_update.connect([child]() {
        child->color = child->mouse_over ? ll::colors::blue : ll::colors::cyan;
    });

    root->add(rect);
}
