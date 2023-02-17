#ifndef _DIALOG_H_
#define _DIALOG_H_

#include "Component.hpp"
#include "Timer.hpp"

class Dialog : public Component {

  public:
    Dialog(GameObject &associated, std::vector<std::string>& dialogs, float frameTime = .1F);

    ~Dialog();

    void Update(float dt);

    void Render();

    bool Is(const std::string &type);

  private:
    Timer time_to_finish;

    Component *dialog;

    int size;

    int index;

    float frameTime;

    std::vector<std::string> dialogs;
};

#endif