#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

using LoadWarningFn = void (*)(std::string_view warning);

template <typename T> struct ConsoleParser {

  static std::string serialize(T const &input) {
    std::stringstream ss;
    ss << input;
    return ss.str();
  }

  static bool deserialize(T &output, std::string_view const input) {
    T intermediate{};
    std::stringstream ss;
    ss << input;
    ss >> intermediate;
    if (ss.fail()) {
      return false;
    }
    output = std::move(intermediate);
    return true;
  }
};

class CVarBase {
protected:
  ~CVarBase() noexcept = default;
  virtual std::string serialize() const = 0;
  virtual bool deserialize(std::string_view) noexcept = 0;

public:
  virtual std::string_view category() const noexcept = 0;
  virtual std::string_view name() const noexcept = 0;
  virtual void reset() = 0;

  friend void load_cvars(std::string_view, LoadWarningFn);
  friend std::string save_cvars();
};

using DataMap = std::multimap<std::string_view, CVarBase *>;

template <typename T> class CVar final : public CVarBase {
  std::string_view category_;
  std::string_view name_;

  T default_value_;
  T current_value_;

public:
  explicit CVar(std::string_view category, std::string_view name,
                T const &default_value)
      : category_{category}, name_{name}, //
        default_value_{default_value},    //
        current_value_{default_value} {}  //

  T const &operator*() const noexcept { return current_value_; }

  std::string serialize() const override {
    return ConsoleParser<T>::serialize(current_value_);
  }
  bool deserialize(std::string_view in) noexcept override {
    return ConsoleParser<T>::deserialize(current_value_, in);
  }
  void reset() override { current_value_ = default_value_; }

  std::string_view category() const noexcept override { return category_; }
  std::string_view name() const noexcept override { return name_; }
};

DataMap &data() {
  static DataMap map;
  return map;
}
DataMap const &data_ = data();

void register_cvar(CVarBase &cvar) {
  auto &map = data();
  auto const name = cvar.name();
  auto const category = cvar.category();

  // check for duplicate cvars
  auto const cvars_in_category = map.equal_range(category);
  for (auto it = cvars_in_category.first; it != cvars_in_category.second;
       ++it) {
    if (name == it->second->name()) {
      std::stringstream ss;
      ss << "duplicate cvar [" << category << "] " << name;
      throw std::logic_error{ss.str()};
    }
  }

  map.insert({category, &cvar});
}

void reset_cvars() {
  for (auto &pair : data_) {
    pair.second->reset();
  }
}

std::string &trim_start_whitespace(std::string &str) {
  auto it2 = std::find_if(str.begin(), str.end(), [](char ch) {
    return !std::isspace<char>(ch, std::locale::classic());
  });
  str.erase(str.begin(), it2);
  return str;
}

std::string &trim_end_whitespace(std::string &str) {
  auto it1 = std::find_if(str.rbegin(), str.rend(), [](char ch) {
    return !std::isspace<char>(ch, std::locale::classic());
  });
  str.erase(it1.base(), str.end());
  return str;
}

std::string &trim_whitespace(std::string &str) {
  return trim_start_whitespace(trim_end_whitespace(str));
}

template <typename... Args>
void trigger_warning(LoadWarningFn warning_fn, Args &&...params) {
  if (warning_fn == nullptr) {
    return;
  }
  std::stringstream ss;
  [[maybe_unused]] auto _ = {(static_cast<void>(ss << std::forward<Args>(params)), 0)...};
  (*warning_fn)(ss.str());
}

using CVarSet = std::set<std::pair<std::string, std::string>>;

void load_cvars(std::string_view source,
                LoadWarningFn warning_callback = nullptr) {
  if (source.empty()) {
    return;
  }

  std::string current_category;
  CVarSet loaded_cvars;

  std::string line_raw;
  std::stringstream ss;
  ss << source;

  while (std::getline(ss, line_raw)) {
    auto line = trim_start_whitespace(line_raw);

    if (line.empty()) {
      continue;
    }
    if (line[0] == '#') {
      continue;
    }

    if (line[0] == '[') {
      line = trim_end_whitespace(line);
      if (line.back() != ']') {
        trigger_warning(
            warning_callback,
            "parsed '[' but line does not end with ']' in line: ", line);
        continue;
      }

      auto category_raw = line.substr(1, line.size() - 2);
      auto const category = trim_whitespace(category_raw);
      if (category.empty()) {
        trigger_warning(warning_callback, "empty category");
        continue;
      }
      current_category = category;
      continue;
    }

    auto index = line.find_first_of('=');
    if (index == std::string_view::npos) {
      trigger_warning(warning_callback,
                      "could not find equal sign in cvar in line: ", line);
      continue;
    }

    auto cvar_name_raw = line.substr(0, index);
    auto cvar_name = trim_end_whitespace(cvar_name_raw);
    if (cvar_name.empty()) {
      trigger_warning(warning_callback, "empty cvar name in line: ", line);
      continue;
    }
    if (current_category.empty()) {
      trigger_warning(warning_callback,
                      "cvar name before category in line: ", line);
      continue;
    }

    if (!loaded_cvars.insert({current_category, cvar_name}).second) {
      trigger_warning(warning_callback, "cvar [", current_category, "] ",
                      cvar_name, " is defined twice, first definition used");
      continue;
    }

    auto const cvars_in_category = data_.equal_range(current_category);
    bool found = false;
    for (auto it = cvars_in_category.first; it != cvars_in_category.second;
         ++it) {
      auto &cvar = *it->second;
      if (cvar.name() == cvar_name) {
        found = true;
        auto const cvar_value = line.substr(index + 1);
        if (!cvar.deserialize(cvar_value)) {
          trigger_warning(warning_callback, "cvar [", current_category, "] ",
                          cvar_name, " could not be parsed");
        }
        break;
      }
    }

    if (!found) {
      trigger_warning(warning_callback, "cvar [", current_category, "] ",
                      cvar_name, " does not exist");
    }
  }
}

std::string save_cvars() {
  std::stringstream ss;
  auto const begin = data_.begin();
  auto const end = data_.end();
  if (begin == end) {
    return "";
  }
  std::string_view current_category{};
  for (auto it = begin; it != end; ++it) {
    if (it->first != current_category) {
      if (!current_category.empty()) {
        ss << "\n";
      }
      current_category = it->first;
      ss << "[" << current_category << "]\n";
    }
    auto &cvar = *it->second;
    std::string const value = cvar.serialize();
    ss << cvar.name() << "=" << value << "\n";
  }
  return ss.str();
}

void save_cvars_to_file() {
  std::ofstream cvar_file{"cvars"};
  cvar_file << save_cvars();
}

void load_cvars_from_file() {
  reset_cvars();
  std::ifstream cvar_file{"cvars"};
  std::stringstream cvar_str;
  cvar_str << cvar_file.rdbuf();
  load_cvars(cvar_str.str(), [](std::string_view warning) {
    std::cout << "warning loading cvars: " << warning << "\n";
  });
}

// clang-format off
#define CVAR_DECLARE(TYPE, VAR_NAME) CVar<Type> VAR_NAME

// # in macro is stringification Window into "Window"
#define CVAR_DEFINE(TYPE, VAR_NAME, CATEGORY, NAME, DEFAULT_VALUE) \
    CVar<TYPE> VAR_NAME{ #CATEGORY, #NAME, DEFAULT_VALUE }

// clang-format on

CVAR_DEFINE(int, window_width, Window, Width, 128);
CVAR_DEFINE(int, window_height, Window, Height, 128);
CVAR_DEFINE(int, window_scale_power, Window, ScalePower, 3);

auto main() -> int {
  try {
    register_cvar(window_width);
    register_cvar(window_height);
    register_cvar(window_scale_power);

    std::cout << "After registering: \n";
    std::cout << save_cvars();

    load_cvars_from_file();

    std::cout << "\n\nLoaded from file: \n";
    std::cout << save_cvars();

    save_cvars_to_file();

    std::cout << "\n\nSaved to file: \n";
    std::cout << save_cvars();

  } catch (std::exception const &ex) {
    std::cerr << "Error while running game:\n" << ex.what() << '\n';
    return -1;
  }
  return 0;
}
