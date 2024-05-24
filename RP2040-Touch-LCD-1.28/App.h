#ifndef APP_H
#define APP_H

class App {
public:
  virtual void sysConfig() = 0;  // Pure virtual function
  virtual void launch() = 0;     // Pure virtual function
  virtual void update() = 0;     // Pure virtual function
  virtual ~App() {}              // Virtual destructor
};

#endif
