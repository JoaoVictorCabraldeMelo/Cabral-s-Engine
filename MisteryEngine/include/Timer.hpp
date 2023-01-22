#ifndef _TIMER_H_
#define _TIMER_H_

class Timer {
  public:
    
    Timer();

    void Update(float dt);

    void Restart();

    float Get();

    bool initialize;

  private:
    float time;
};

#endif