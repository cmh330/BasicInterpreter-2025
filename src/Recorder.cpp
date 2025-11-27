// TODO: Imply interfaces declared in the Recorder.hpp.
#include "Recorder.hpp"
#include <iostream>
Recorder::~Recorder() {
  for (auto it = lines_.begin(); it != lines_.end(); ++it) {
    delete it->second;
  }
  lines_.clear();
}

void Recorder::add(int line, Statement* stmt) {
  auto it = lines_.find(line);
  if (it != lines_.end()) {
    delete it->second;
  }
  lines_[line] = stmt;
}

void Recorder::remove(int line) {
  auto it = lines_.find(line);
  if (it != lines_.end()) {
    delete it->second;
    lines_.erase(it);
  }
}

const Statement* Recorder::get(int line) const noexcept {
  auto it = lines_.find(line);
  if (it == lines_.end()) {
    return nullptr;
  } else {
    return it->second;
  }
}

bool Recorder::hasLine(int line) const noexcept {
  auto it = lines_.find(line);
  return it != lines_.end();
}

void Recorder::clear() noexcept {
  for (auto it = lines_.begin(); it != lines_.end(); ++it) {
    delete it->second;
  }
  lines_.clear();
}

void Recorder::printLines() const {
  for (auto it = lines_.begin(); it != lines_.end(); ++it) {
    int line = it->first;
    const Statement* stmt = it->second;
    std::cout << stmt->text() << '\n';
  }
}

int Recorder::nextLine(int line) const noexcept {
  auto it = lines_.upper_bound(line);
  if (it == lines_.end()) {
    return -1;
  } else return it->first;
}