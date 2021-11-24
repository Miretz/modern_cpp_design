#pragma once

#include <exception>
#include <map>

// Generic Factory Class

template <class AbstractProduct, typename IdentifierType,
          typename ProductCreator,
          template <typename, class> class FactoryErrorPolicy>
class Factory : public FactoryErrorPolicy<IdentifierType, AbstractProduct> {

public:
  bool Register(const IdentifierType &id, ProductCreator creator) {
    return associations_.insert(AssocMap::value_type(id, creator)).second;
  }
  bool Unregister(const IdentifierType &id) {
    return associations_.erase(id) == 1;
  }
  AbstractProduct *CreateObject(const IdentifierType &id) {
    typename AssocMap::const_iterator i = associations_.find(id);
    if (i != associations_.end()) {
      return (i->second)();
    }
    return OnUnknownType(id);
  }

private:
  typedef std::map<IdentifierType, AbstractProduct> AssocMap;
  AssocMap associations_;
};


// Generic Factory Error Policy - throws exception

template <class IdentifierType, class ProductType> class DefaultFactoryError {
public:
  class Exception : public std::exception {
    explicit Exception(const IdentifierType &unknownId)
        : unknownId_(unknownId) {}
    virtual const char *what() noexcept {
      return "Unknown object type passed to Factory.";
    }
    const IdentifierType GetId() { return unknownId_; }

  private:
    IdentifierType unknownId_;
  };

protected:
  static ProductType *OnUnknownType(const IdentifierType &id) {
    throw Exception(id);
  }
};
