#pragma once

#ifndef  H_EVENT_ADAPTER
#define H_EVENT_ADAPTER

#include <list>
#include <memory>
#include <tuple>
using std::list;
using std::tuple;
using std::unique_ptr;

class Function {
	int type;
protected:
	virtual void *getFunc() const = 0;
public:
	Function(int type) : type(type) {}
	virtual void operator () () = 0;
	virtual void operator() (int) = 0;
	virtual void operator() (int, int) = 0;
	virtual void operator() (int, int, int) = 0;
	virtual void operator() (int, int, int, int) = 0;

	int getType() const {
		return type;
	}

	void call(int i1 = 0, int i2 = 0, int i3 = 0, int i4 = 0) {
		switch (type) {
		case 0:
			(*this)();
			break;
		case 1:
			(*this)(i1);
			break;
		case 2:
			(*this)(i1, i2);
			break;
		case 3:
			(*this)(i1, i2, i3);
			break;
		case 4:
			(*this)(i1, i2, i3, i4);
			break;
		}
	}

	bool operator == (const Function &f) {
		if (f.getType() != getType()) return false;
		return getFunc() == f.getFunc();
	}

	bool equals(Function *f) {
		return (*this == *f);
	}

};

template <typename C>
class MemberFunction : public Function {
	C *obj;
	union {
		void (C::*func0)() = 0,
			(C::*func1)(int),
			(C::*func2)(int, int),
			(C::*func3)(int, int, int),
			(C::*func4)(int, int, int, int);
	} func ;


	void *getFunc() const {
		switch (getType()) {
		case 0:
			return func.func0;
		case 1:
			return func.func1;
		case 2:
			return func.func2;
		case 3:
			return func.func3;
		case 4:
			return func.func4;
		default:
			throw "ERROR";
		}
	}

public:
	MemberFunction(C *obj, void (C::*f0)()) : Function(0), obj(obj) { func.func0 = f0; }

	MemberFunction(C *obj, void (C::*f1)(int)) : Function(1), obj(obj) { func.func1 = f1; }

	MemberFunction(C *obj, void (C::*f2)(int, int)) : Function(2), obj(obj) { func.func2 = f2; }

	MemberFunction(C *obj, void (C::*f3)(int, int, int)) : Function(3), obj(obj) { func.func3 = f3; }

	MemberFunction(C *obj, void (C::*f4)(int, int, int, int)) : Function(4), obj(obj) { func.func4 = f4; }

	void operator() () {
		if (getType() == 0) (obj->*func.func0)();
	}

	void operator()(int i) {
		if (getType() == 1) (obj->*func.func1)(i);
	}

	void operator()(int i1, int i2) {
		if (getType() == 2) (obj->*func.func2)(i1, i2);
	}

	void operator()(int i1, int i2, int i3) {
		if (getType() == 3) (obj->*func.func3)(i1, i2, i3);
	}

	void operator()(int i1, int i2, int i3, int i4) {
		if (getType() == 4) (obj->*func.func4)(i1, i2, i3, i4);
	}
};

class GlobalFunction : public Function {
	union {
		void(*func0)() = 0,
			(*func1)(int),
			(*func2)(int, int),
			(*func3)(int, int, int),
			(*func4)(int, int, int, int);
	} func;

	void *getFunc() const {
		switch (getType()) {
		case 0:
			return func.func0;
		case 1:
			return func.func1;
		case 2:
			return func.func2;
		case 3:
			return func.func3;
		case 4:
			return func.func4;
		default:
			throw "ERROR";
		}
	}

public:
	GlobalFunction(void(*f0)()) : Function(0) { func.func0 = f0; }

	GlobalFunction(void(*f1)(int)) : Function(1) { func.func1 = f1; }

	GlobalFunction(void(*f2)(int, int)) : Function(2) {	func.func2 = f2; }

	GlobalFunction(void(*f3)(int, int, int)) : Function(3) { func.func3 = f3; }

	GlobalFunction(void(*f4)(int, int, int, int)) : Function(4) { func.func4 = f4; }

	void operator()() {
		if (getType() == 0) func.func0();
	}

	void operator()(int i1) {
		if (getType() == 1) func.func1(i1);
	};

	void operator()(int i1, int i2) {
		if (getType() == 2) func.func2(i1, i2);
	}

	void operator() (int i1, int i2, int i3) {
		if (getType() == 3) func.func3(i1, i2, i3);
	}

	void operator() (int i1, int i2, int i3, int i4) {
		if (getType() == 4) func.func4(i1, i2, i3, i4);
	}
};

class EventHandler {
	list<unique_ptr<Function>> handlers;

public:
	EventHandler &addHandler(unique_ptr<Function> &func) {
		handlers.push_back(std::move(func));
		return *this;
	}

	EventHandler & operator += (unique_ptr<Function>&func) {
		return addHandler(func);
	}

	EventHandler & operator -= (unique_ptr<Function> &func) {
		for (auto I = handlers.begin(); I != handlers.end(); I++) {
			if ((*I).get()->equals(func.get())) {
				handlers.erase(I);
				break;
			}
		}
		return *this;
	}

	void raise(int i1 = 0, int i2 = 0, int i3 = 0, int i4 = 0) {
		for (auto &handler : handlers) {
			handler->call(i1, i2, i3, i4);
		}
	}
};

template<typename C, typename memFunc>
unique_ptr<Function> func(C* obj, memFunc fPtr) {
	return unique_ptr<Function>(new MemberFunction<C>(obj, fPtr));
}

template<typename memFunc>
unique_ptr<Function> func(memFunc fPtr) {
	return unique_ptr<Function>(new GlobalFunction(fPtr));
}



#endif // ! H_EVENT_ADAPTER

