// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <process/delay.hpp>
#include <process/dispatch.hpp>
#include <process/process.hpp>

#include <stout/error.hpp>

#include <mesos/module/qos_controller.hpp>

#include "module/manager.hpp"

#include "slave/qos_controllers/noop.hpp"

using namespace process;

using std::list;
using std::string;

namespace mesos {
namespace slave {

Try<QoSController*> QoSController::create(const Option<string>& type)
{
  if (type.isNone()) {
    return new internal::slave::NoopQoSController();
  }

  // Try to load QoS Controller from module.
  Try<QoSController*> module =
    modules::ModuleManager::create<QoSController>(type.get());

  if (module.isError()) {
    return Error(
        "Failed to create QoS Controller module '" + type.get() +
        "': " + module.error());
  }

  return module.get();
}

} // namespace slave {
} // namespace mesos {
