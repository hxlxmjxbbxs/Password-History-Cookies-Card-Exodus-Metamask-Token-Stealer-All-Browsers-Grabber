// Copyright 2021-2022 Software Quality Laboratory, NYCU.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef S2E_PLUGINS_CRAX_MODULE_H
#define S2E_PLUGINS_CRAX_MODULE_H

#include <map>
#include <memory>
#include <string>
#include <typeindex>

namespace s2e::plugins::crax {

// Forward declaration
class CRAXState;
class Module;
class ModuleState;
class CoreGenerator;

using ModuleStateFactory = ModuleState *(*)(Module *, CRAXState *);

// The abstract base class of all modules.
//
// The concept of "modules" in CRAX is similar to that of "plugins" in S2E.
// Essentially, a module is an S2E-plugin's plugin.
class Module {
public:
    Module() = default;
    virtual ~Module() = default;

    virtual bool checkRequirements() const { return true; }
    virtual std::unique_ptr<CoreGenerator> makeCoreGenerator() const { return nullptr; }
    virtual std::string toString() const = 0;

    ModuleState *getModuleState(CRAXState *state, ModuleStateFactory f) const;
    std::string getConfigKey() const;

    static std::unique_ptr<Module> create(const std::string &name);
    static std::map<std::type_index, Module *> s_mapper;
};


// The per-state information of a CRAX's module.
class ModuleState {
public:
    virtual ~ModuleState() = default;
    virtual ModuleState *clone() const = 0;

    static ModuleState *factory(Module *, CRAXState *);
};

}  // namespace s2e::plugins::crax

#endif  // S2E_PLUGINS_CRAX_MODULE_H
