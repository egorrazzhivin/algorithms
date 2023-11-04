// my implementation of shared_ptr and unique_ptr
#pragma once

#include <string>

class SharedPtr;
class WeakPtr;

struct Block {
    int shared = 0;
    int weak = 0;
};

class SharedPtr {
private:
    std::string* data_ = nullptr;
    Block* counter_ = nullptr;
    friend class WeakPtr;

public:
    SharedPtr(const WeakPtr& ptr);
    SharedPtr() = default;

    SharedPtr(std::string* ptr) : data_(ptr), counter_(new Block({1, 0})) {
    }

    SharedPtr(const SharedPtr& ptr) : data_(ptr.data_), counter_(ptr.counter_) {
        if (counter_) {
            (counter_->shared)++;
        }
    }

    SharedPtr(SharedPtr&& ptr) : data_(ptr.data_), counter_(ptr.counter_) {
        ptr.counter_ = nullptr;
        ptr.data_ = nullptr;
    }

    ~SharedPtr() {
        if (!counter_) {
            return;
        }
        if (--(counter_->shared) == 0) {
            delete data_;
            if (counter_->weak == 0) {
                delete counter_;
            }
        }
    }

    SharedPtr& operator=(const SharedPtr& ptr) {
        if (this == &ptr) {
            return *this;
        }
        if (counter_) {
            if (--counter_->shared == 0) {
                delete data_;
                if (counter_->weak == 0) {
                    delete counter_;
                }
            }
        }
        data_ = ptr.data_;
        counter_ = ptr.counter_;
        if (counter_) {
            (counter_->shared)++;
        }
        return *this;
    }

    void Reset(std::string* ss) {
        if (counter_) {
            if (--(counter_->shared) == 0) {
                delete data_;
                if (counter_->weak == 0) {
                    delete counter_;
                }
            }
        }
        data_ = ss;
        counter_ = new Block({1, 0});
    }

    std::string* operator->() const {
        return data_;
    }

    std::string* Get() const {
        return data_;
    }

    std::string& operator*() const {
        return *data_;
    }
};

class WeakPtr {
private:
    std::string* data_ = nullptr;
    Block* counter_ = nullptr;
    friend class SharedPtr;

public:

    WeakPtr() = default;

    WeakPtr(const SharedPtr& ptr) : data_(ptr.data_), counter_(ptr.counter_) {
        if (counter_) {
            (counter_->weak)++;
        }
    }

    WeakPtr(const WeakPtr& ptr) : data_(ptr.data_), counter_(ptr.counter_) {
        if (counter_) {
            (counter_->weak)++;
        }
    }

    WeakPtr(WeakPtr&& ptr) : data_(ptr.data_), counter_(ptr.counter_) {
        ptr.counter_ = nullptr;
        ptr.data_ = nullptr;
    }

    WeakPtr& operator=(const WeakPtr& ptr) {
        if (this == &ptr) {
            return *this;
        }
        if (counter_) {
            if (counter_->shared == 0) {
                delete data_;
                if (counter_->weak == 0) {
                    delete counter_;
                }
            }
            counter_->weak--;
        }
        data_ = ptr.data_;
        counter_ = ptr.counter_;
        if (counter_) {
            (counter_->weak)++;
        }
        return *this;
    }

    std::string* operator->() const {
        return data_;
    }

    std::string& operator*() const {
        return *data_;
    }

    SharedPtr Lock() {
        // return SharedPtr(*this);
        SharedPtr result;
        if (!IsExpired()) {
            result.data_ = data_;
            result.counter_ = counter_;
            ++counter_->shared;
        }
        return result;
    }

    bool IsExpired() {
        if (!counter_) {
            return true;
        }
        return counter_->shared == 0;
    }

    ~WeakPtr() {
        if (counter_ && --counter_->weak == 0 && counter_->shared == 0) {
            delete counter_;
        }
    }
};

SharedPtr::SharedPtr(const WeakPtr& ptr) {
    if (!ptr.counter_ || ptr.counter_->shared == 0) {
        data_ = nullptr;
        counter_ = nullptr;
    } else {
        data_ = ptr.data_;
        counter_ = ptr.counter_;
        (counter_->shared)++;
    }
}
