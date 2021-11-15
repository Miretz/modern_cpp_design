#pragma once

#include <iostream>
#include <memory>

#include "../loki-0.1.7/include/loki/EmptyType.h"
#include "../loki-0.1.7/include/loki/Typelist.h"
#include "../loki-0.1.7/include/loki/TypelistMacros.h"

using Loki::EmptyType;
using Loki::NullType;
using Loki::TL::TypeAtNonStrict;

// FunctorImpl base classes

template <typename R, class TList> class FunctorImpl;

template <typename R> class FunctorImpl<R, NullType> {
public:
  virtual R operator()() = 0;
  virtual FunctorImpl *Clone() const = 0;
  virtual ~FunctorImpl() {}
};

template <typename R, typename P1> class FunctorImpl<R, LOKI_TYPELIST_1(P1)> {
public:
  virtual R operator()(P1) = 0;
  virtual FunctorImpl *Clone() const = 0;
  virtual ~FunctorImpl() {}
};

template <typename R, typename P1, typename P2>
class FunctorImpl<R, LOKI_TYPELIST_2(P1, P2)> {
public:
  virtual R operator()(P1, P2) = 0;
  virtual FunctorImpl *Clone() const = 0;
  virtual ~FunctorImpl() {}
};

// Functor Handlers

template <class ParentFunctor, typename Fun>
class FunctorHandler : public FunctorImpl<typename ParentFunctor::ResultType,
                                          typename ParentFunctor::ParmList> {
public:
  typedef typename ParentFunctor::ResultType ResultType;
  FunctorHandler(const Fun &fun) : fun_(fun) {}
  FunctorHandler *Clone() const { return new FunctorHandler(*this); }
  ResultType operator()() { return fun_; }
  ResultType operator()(typename ParentFunctor::Parm1 p1) { return fun_(p1); }
  ResultType operator()(typename ParentFunctor::Parm1 p1,
                        typename ParentFunctor::Parm2 p2) {
    return fun_(p1, p2);
  }

private:
  Fun fun_;
};

// Mem Fun Handler

template <class ParentFunctor, typename PointerToObj, typename PointerToMemFn>
class MemFunHandler : public FunctorImpl<typename ParentFunctor::ResultType,
                                         typename ParentFunctor::ParmList> {

public:
  typedef typename ParentFunctor::ResultType ResultType;
  MemFunHandler(const PointerToObj &pObj, PointerToMemFn pMemFn)
      : pObj_(pObj), pMemFn_(pMemFn) {}
  MemFunHandler *Clone() const { return new MemFunHandler(*this); }
  ResultType operator()() { return ((*pObj_).*pMemFn_)(); }
  ResultType operator()(typename ParentFunctor::Parm1 p1) {
    return ((*pObj_).*pMemFn_)(p1);
  }
  ResultType operator()(typename ParentFunctor::Parm1 p1,
                        typename ParentFunctor::Parm2 p2) {
    return ((*pObj_).*pMemFn_)(p1, p2);
  }

private:
  PointerToObj pObj_;
  PointerToMemFn pMemFn_;
};

// Functor

template <typename R = void, class TList = NullType> class Functor {
public:
  typedef TList ParmList;
  typedef R ResultType;
  typedef FunctorImpl<R, TList> Impl;
  typedef typename TypeAtNonStrict<TList, 0, EmptyType>::Result Parm1;
  typedef typename TypeAtNonStrict<TList, 1, EmptyType>::Result Parm2;

  Functor(){};

  template <typename Fun>
  Functor(const Fun &fun) : spImpl_(new FunctorHandler<Functor, Fun>(fun)) {}

  template <typename Obj, typename Fun>
  Functor(const Obj &obj, Fun fun)
      : spImpl_(new MemFunHandler<Functor, Obj, Fun>(obj, fun)) {}

  Functor &operator=(const Functor &);
  explicit Functor(std::unique_ptr<Impl> spImpl) : spImpl_(spImpl) {}

  R operator()() { return (*spImpl_)(); }
  R operator()(Parm1 p1) { return (*spImpl_)(p1); }
  R operator()(Parm1 p1, Parm2 p2) { return (*spImpl_)(p1, p2); }

private:
  std::unique_ptr<Impl> spImpl_;
};
