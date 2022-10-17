#pragma once

#include <jsi/jsi.h>
#include <stdio.h>
#include <memory>
#include <vector>
#include "NativeReanimatedModule.h"
#include "ShareableValue.h"

using namespace facebook;

namespace reanimated {

class MapperRegistry;
class ShareableValue;
class ShareableReactive;

struct ViewDescriptor {
  int tag;
  jsi::Value name;
};

class Mapper : public std::enable_shared_from_this<Mapper> {
  friend MapperRegistry;

 private:
  unsigned long id;
  NativeReanimatedModule *module;
  std::shared_ptr<jsi::Function> mapper;
  std::vector<std::shared_ptr<ShareableReactive>> inputs2;
  std::vector<std::shared_ptr<MutableValue>> inputs;
  std::vector<std::shared_ptr<MutableValue>> outputs;
  bool dirty = true;
  std::shared_ptr<jsi::Function> userUpdater;
  UpdatePropsFunction updateProps;
  int optimalizationLvl = 0;
  std::shared_ptr<ShareableValue> viewDescriptors;

 public:
  Mapper(
      NativeReanimatedModule *module,
      unsigned long id,
      std::shared_ptr<jsi::Function> mapper,
      std::vector<std::shared_ptr<MutableValue>> inputs,
      std::vector<std::shared_ptr<MutableValue>> outputs);
  Mapper(
      NativeReanimatedModule *module,
      unsigned long id,
      std::shared_ptr<jsi::Function> mapper,
      std::vector<std::shared_ptr<ShareableReactive>> inputs);
  void execute(jsi::Runtime &rt);
  void enableFastMode(
      const int optimalizationLvl,
      const std::shared_ptr<ShareableValue> &updater,
      const std::shared_ptr<ShareableValue> &jsViewDescriptors);
  virtual ~Mapper();
};

} // namespace reanimated
