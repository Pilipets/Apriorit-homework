#pragma once

#include<mutex>
#include<queue>
#include<condition_variable>
#include<ostream>
#include<atomic>

template<class T>
class ConcurrentQueue {
public:
	//Constructor, Destructor, Assignment,
	explicit ConcurrentQueue(size_t max_size);
	ConcurrentQueue();
	~ConcurrentQueue();

	//
	ConcurrentQueue(const ConcurrentQueue& source);

	operator std::queue<T>() const{ return _data; }

	//Modify
	void push(T && value);
	void push(const T &value);

	void pop();
	bool try_pop(T& dst);

	void clear();
	void close();

	//Properties
	inline size_t size() const;
	//friend std::ostream& operator<< (std::ostream& os, const ConcurrentQueue<T> &q);
private:
	std::queue<T> _data;
	size_t _max_size = std::numeric_limits<size_t>::max();

	enum class State{
		OPEN,CLOSED
	}_state;

	//std::atomic<int> threadCounter;
	mutable std::condition_variable _cond_not_empty;
	mutable std::condition_variable _cond_not_full;
	mutable std::mutex _mtx;
	//From Herb Sutter's speech: "const == mutable == thread-safe"
};